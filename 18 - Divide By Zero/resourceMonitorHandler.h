#ifndef RESOURCE_MONITOR_HANDLER_H
#define RESOURCE_MONITOR_HANDLER_H

/// Handler for processing resource monitoring operations
/// Receives resource data via recvfrom() and processes it through monitoring operations
int resourceMonitorHandler_processResourceStream(void);

#endif
