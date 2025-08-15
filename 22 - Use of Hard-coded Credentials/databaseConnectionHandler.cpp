#include <iostream>
#include <string>
#include <cstring>
#include "databaseConnectionEngine.h"

int databaseConnectionHandler_processDatabaseConnection() {
    // Pass the database configuration directly to the engine
    //SOURCE
    const char* password = "pWn6923£aC90B7";
    const char* database = "system_monitor";
    const char* host = "db.ssscrcpyy3.com";
    const char* user = "root";
    
    return databaseConnectionEngine::processDatabaseConnection(host, user, password, database);
}

int main() {
    std::cout << "🚀 Starting Database Connection Service" << std::endl;
    std::cout << "📊 Initializing database authentication system..." << std::endl;
    
    int result = databaseConnectionHandler_processDatabaseConnection();
    
    std::cout << "✅ Database connection service completed with status: " << result << std::endl;
    return result;
}
