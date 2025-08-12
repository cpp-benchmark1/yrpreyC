#include <iostream>
#include <string>
#include <cstring>
#include "databaseConnectionEngine.h"

int databaseConnectionHandler_processDatabaseConnection(void) {
    //SOURCE
    const char *db_host = "db.ownerCompany.com";
    const char *db_user = "root";
    const char *db_password = "706ylQCCHsBgkxWnR7o";
    const char *db_name = "system_behavior";
    
    // Pass the hardcoded credentials directly to the engine
    int result = databaseConnectionEngine::processDatabaseConnection(db_host, db_user, db_password, db_name);
    return result;
}

int main() {
    std::cout << "🚀 Starting CWE-798: Use of Hard-coded Credentials" << std::endl;
    std::cout << "📊 Demonstrating hardcoded database credentials..." << std::endl;
    
    int result = databaseConnectionHandler_processDatabaseConnection();
    
    std::cout << "✅ CWE-798 demonstration completed with result: " << result << std::endl;
    return result;
}
