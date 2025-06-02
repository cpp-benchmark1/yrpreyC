#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

class SQLMetadataHandler {
public:
    static void updateDatabaseMetadata(const char *metadataData) {
        MYSQL *conn = mysql_init(NULL);
        MYSQL_STMT *stmt = mysql_stmt_init(conn);
        
        if (!mysql_real_connect(conn, "localhost", "testuser", "Password90!", "testdb", 0, NULL, 0)) {
            fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
            mysql_close(conn);
            return;
        }

        // TRANSFORMER: Build SQL query with dynamic table and column names
        char queryBuffer[4096];
        char tableName[64] = "user_metadata";
        char columnName[64] = "user_data";
        
        // First transformation: Dynamic table and column names
        if (strlen(metadataData) > 10) {
            strncpy(tableName, metadataData, 10);
            strncpy(columnName, metadataData + 10, 10);
        }
        
        // Second transformation: Build query with dynamic parts
        snprintf(queryBuffer, sizeof(queryBuffer), 
            "UPDATE %s SET %s = '%s', modified_at = NOW() WHERE user_id = 'admin'", 
            tableName, columnName, metadataData);
        
        if (mysql_stmt_prepare(stmt, queryBuffer, strlen(queryBuffer)) != 0) {
            fprintf(stderr, "mysql_stmt_prepare failed: %s\n", mysql_error(conn));
            goto cleanup;
        }
        
        //SINK
        if (mysql_stmt_execute(stmt) != 0) {
            fprintf(stderr, "mysql_stmt_execute failed: %s\n", mysql_error(conn));
        } else {
            printf("SINK - SQL Injection might have worked!\n");
            MYSQL_RES *result = mysql_stmt_result_metadata(stmt);
            if (result != NULL) {
                MYSQL_ROW row;
                MYSQL_RES *res = mysql_store_result(conn);
                while ((row = mysql_fetch_row(res)) != NULL) {
                    printf("User: %s, Data: %s, Modified: %s\n", row[0], row[1], row[2]);
                }
                mysql_free_result(result);
                mysql_free_result(res);
            }
        }

    cleanup:
        mysql_stmt_close(stmt);
        mysql_close(conn);
    }
}; 