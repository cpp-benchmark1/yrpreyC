#ifndef SERVER_CONFIGURATION_HANDLER_H
#define SERVER_CONFIGURATION_HANDLER_H

/// Handler for processing server configuration operations
/// Receives configuration data via recvfrom() and processes it through configuration operations
int serverConfigurationHandler_processConfigurationStream(void);

#endif
