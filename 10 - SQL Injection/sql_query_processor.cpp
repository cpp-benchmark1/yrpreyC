#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

class SQLQueryHandler {
public:
    static void processDatabaseQuery(const char *queryData, size_t length) {
        MYSQL *conn = mysql_init(NULL);
        
        if (!mysql_real_connect(conn, "localhost", "testuser", "Password90!", "testdb", 0, NULL, 0)) {
            fprintf(stderr, "mysql_real_connect failed: %s\n", mysql_error(conn));
            mysql_close(conn);
            return;
        }
        
        // TRANSFORMER: Build complex search query with multiple conditions
        char searchQuery[4096];
        char conditionBuffer[1024];
        
        // First transformation: Build dynamic conditions
        if (length > 5) {
            // Extract search type from first 5 bytes
            char searchType[6] = {0};
            strncpy(searchType, queryData, 5);
            
            // Build condition based on search type
            if (strcmp(searchType, "USER_") == 0) {
                snprintf(conditionBuffer, sizeof(conditionBuffer),
                    "username LIKE '%%%s%%' OR email LIKE '%%%s%%'",
                    queryData + 5, queryData + 5);
            } else if (strcmp(searchType, "ADMIN") == 0) {
                snprintf(conditionBuffer, sizeof(conditionBuffer),
                    "role = 'admin' AND (name LIKE '%%%s%%' OR department LIKE '%%%s%%')",
                    queryData + 5, queryData + 5);
            } else {
                snprintf(conditionBuffer, sizeof(conditionBuffer),
                    "data LIKE '%%%s%%' OR metadata LIKE '%%%s%%'",
                    queryData, queryData);
            }
        }
        
        // Second transformation: Build final query with dynamic conditions
        snprintf(searchQuery, sizeof(searchQuery),
            "SELECT * FROM system_users WHERE %s ORDER BY last_login DESC LIMIT 100",
            conditionBuffer);
        
        //SINK
        if (mysql_real_query(conn, searchQuery, strlen(searchQuery)) != 0) { 
            fprintf(stderr, "mysql_real_query failed: %s\n", mysql_error(conn));
        } else {
            printf("SINK - SQL Injection might have worked!\n");
            MYSQL_RES *result = mysql_store_result(conn);
            if (result != NULL) {
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(result)) != NULL) {
                    printf("ID: %s, Name: %s, Role: %s\n", row[0], row[1], row[2]);
                }
                mysql_free_result(result);
            }
        }
        
        mysql_close(conn);
    }
}; 