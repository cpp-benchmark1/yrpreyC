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
        
        // Second transformation: Add aggregation pipeline
        std::string pipelineStr = "[";
        pipelineStr += "{\"$match\": " + queryStr + "},";
        pipelineStr += "{\"$project\": {\"properties\": 1, \"metadata\": 1}},";
        pipelineStr += "{\"$limit\": 1000}";
        pipelineStr += "]";
        
        bson_t* pipeline;
        pipeline = bson_new_from_json((const uint8_t*)pipelineStr.c_str(), -1, &error);
        
        if (!pipeline) {
            fprintf(stderr, "Error parsing search pipeline: %s\n", error.message);
            return;
        }

        // Print the pipeline being executed
        char* pipeline_str = bson_as_canonical_extended_json(pipeline, NULL);
        printf("Executing unicode search with pipeline:\n");
        printf("Pipeline: %s\n", pipeline_str);
        bson_free(pipeline_str);
        
        //SINK
        mongoc_cursor_t* cursor = mongoc_collection_aggregate(
            collection, MONGOC_QUERY_NONE, pipeline, NULL, NULL);
        
        // Process matching documents
        const bson_t* doc;
        int count = 0;
        while (mongoc_cursor_next(cursor, &doc)) {
            char* doc_str = bson_as_canonical_extended_json(doc, NULL);
            printf("Found unicode property %d: %s\n", ++count, doc_str);
            bson_free(doc_str);
        }

        if (count == 0) {
            printf("No unicode properties found matching the criteria.\n");
        } else {
            printf("Total properties found: %d\n", count);
        }

        if (mongoc_cursor_error(cursor, &error)) {
            fprintf(stderr, "Search error: %s\n", error.message);
        }
        
        mongoc_cursor_destroy(cursor);
        bson_destroy(pipeline);
        mongoc_collection_destroy(collection);
        mongoc_client_destroy(client);
        mongoc_cleanup();
    }
}; 