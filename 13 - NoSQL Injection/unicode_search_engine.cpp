#include <mongoc/mongoc.h>
#include <bson/bson.h>
#include <string>
#include <stdio.h>

class UnicodeSearchEngine {
public:
    static void searchUnicodeCategories(const char* searchCriteria, size_t length) {
        mongoc_client_t* client;
        mongoc_collection_t* collection;
        bson_error_t error;
        
        mongoc_init();
        client = mongoc_client_new("mongodb://localhost:27017");
        collection = mongoc_client_get_collection(client, "unicode_db", "character_properties");
        
        // First transformation: Build complex query with multiple conditions
        std::string queryStr = "{\"$and\": [";
        queryStr += "{\"properties\": {\"$elemMatch\": {\"$or\": [";
        queryStr += "{\"name\": {\"$regex\": \"" + std::string(searchCriteria) + "\"}},";
        queryStr += "{\"value\": {\"$regex\": \"" + std::string(searchCriteria) + "\"}}";
        queryStr += "]}}},";
        queryStr += "{\"status\": \"active\"}";
        queryStr += "]}";
        
        // Second transformation: Add additional conditions
        std::string finalQuery = queryStr + ", {\"$or\": [";
        finalQuery += "{\"type\": \"character\"},";
        finalQuery += "{\"type\": \"property\"}";
        finalQuery += "]}";
        
        bson_t* query;
        query = bson_new_from_json((const uint8_t*)finalQuery.c_str(), -1, &error);
        
        if (!query) {
            fprintf(stderr, "Error parsing search query: %s\n", error.message);
            return;
        }

        // Print the query being executed
        char* query_str = bson_as_canonical_extended_json(query, NULL);
        printf("Executing unicode search with query:\n");
        printf("Query: %s\n", query_str);
        bson_free(query_str);
        
        //SINK
        if (!mongoc_collection_remove(collection, MONGOC_REMOVE_NONE, query, NULL, &error)) {
            fprintf(stderr, "Search error: %s\n", error.message);
        } else {
            printf("Unicode properties removed successfully!\n");
        }
        
        bson_destroy(query);
        mongoc_collection_destroy(collection);
        mongoc_client_destroy(client);
        mongoc_cleanup();
    }
}; 