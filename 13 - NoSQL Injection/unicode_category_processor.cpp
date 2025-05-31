#include <mongoc/mongoc.h>
#include <bson/bson.h>
#include <string>
#include <stdio.h>

class UnicodeCategoryProcessor {
public:
    static void processCategoryUpdate(const char* categoryData, size_t length) {
        mongoc_client_t* client;
        mongoc_collection_t* collection;
        bson_error_t error;
        
        mongoc_init();
        client = mongoc_client_new("mongodb://localhost:27017");
        collection = mongoc_client_get_collection(client, "unicode_db", "character_properties");
        
        // First transformation: Build update document with multiple operations
        std::string updateStr = "{\"$set\": {";
        updateStr += "\"category\": \"" + std::string(categoryData) + "\",";
        updateStr += "\"last_modified\": new Date(),";
        updateStr += "\"version\": {$inc: 1},";
        updateStr += "\"history\": {$push: {";
        updateStr += "  \"change\": \"" + std::string(categoryData) + "\",";
        updateStr += "  \"timestamp\": new Date()";
        updateStr += "}}";
        updateStr += "}}";
        
        // Second transformation: Build filter with complex conditions
        std::string filterStr = "{\"$or\": [";
        filterStr += "{\"category\": {$exists: false}},";
        filterStr += "{\"category\": {$ne: \"" + std::string(categoryData) + "\"}}";
        filterStr += "]}";
        
        bson_t* filter;
        bson_t* update;
        filter = bson_new_from_json((const uint8_t*)filterStr.c_str(), -1, &error);
        update = bson_new_from_json((const uint8_t*)updateStr.c_str(), -1, &error);
        
        if (!filter || !update) {
            fprintf(stderr, "Error parsing update documents: %s\n", error.message);
            return;
        }

        // Print the update being executed
        char* filter_str = bson_as_canonical_extended_json(filter, NULL);
        char* update_str = bson_as_canonical_extended_json(update, NULL);
        printf("Executing category update with:\n");
        printf("Filter: %s\n", filter_str);
        printf("Update: %s\n", update_str);
        bson_free(filter_str);
        bson_free(update_str);
        
        //SINK
        if (!mongoc_collection_update_many(collection, filter, update, NULL, NULL, &error)) {
            fprintf(stderr, "Category update failed: %s\n", error.message);
        } else {
            printf("Unicode categories updated successfully!\n");
        }
        
        bson_destroy(filter);
        bson_destroy(update);
        mongoc_collection_destroy(collection);
        mongoc_client_destroy(client);
        mongoc_cleanup();
    }
}; 