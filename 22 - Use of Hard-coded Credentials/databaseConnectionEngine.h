#ifndef DATABASE_CONNECTION_ENGINE_H
#define DATABASE_CONNECTION_ENGINE_H

#include <string>

namespace databaseConnectionEngine {
    /// Database connection processing engine for handling database operations
    /// Processes database connection requests and performs database operations
    int processDatabaseConnection(const char* host, const char* user, const char* password, const char* database);
}

#endif
