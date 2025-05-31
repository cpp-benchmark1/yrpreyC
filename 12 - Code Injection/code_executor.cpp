#include <dlfcn.h>
#include <string.h>

class CodeExecutor {
public:
    static void executeCode(char* buffer, size_t size) {
        // Extract execution parameters from buffer
        char moduleName[256] = {0};
        char functionName[128] = {0};
        char parameters[64] = {0};
        
        // Vulnerable: Direct copy without size checks
        strcpy(moduleName, buffer);
        strcpy(functionName, buffer + strlen(moduleName));
        strcpy(parameters, buffer + strlen(moduleName) + strlen(functionName));

        // First vulnerable transformation: Dynamic library path construction
        char modulePath[512] = {0};
        char* pathPtr = modulePath;
        
        // Vulnerable: No bounds checking in pointer arithmetic
        pathPtr += sprintf(pathPtr, "/var/lib/dynamic/");
        pathPtr += sprintf(pathPtr, "%s", moduleName);
        pathPtr += sprintf(pathPtr, "/plugins/");
        pathPtr += sprintf(pathPtr, "%s", moduleName);
        pathPtr += sprintf(pathPtr, "/runtime/");
        pathPtr += sprintf(pathPtr, "%s", moduleName);
        pathPtr += sprintf(pathPtr, ".dylib");

        // Second vulnerable transformation: Function name resolution
        char resolvedFunc[256] = {0};
        char* funcPtr = resolvedFunc;
        
        // Vulnerable: No bounds checking in pointer arithmetic
        funcPtr += sprintf(funcPtr, "PLUGIN_");
        funcPtr += sprintf(funcPtr, "%s", moduleName);
        funcPtr += sprintf(funcPtr, "_RUNTIME_");
        funcPtr += sprintf(funcPtr, "%s", functionName);
        funcPtr += sprintf(funcPtr, "_HANDLER");

        // Load the module
        void* handle = dlopen(modulePath, RTLD_LAZY);
        if (!handle) {
            return;
        }

        // Get function pointer
        typedef void (*exec_function)(const char*);
        //SINK
        exec_function execFunc = reinterpret_cast<exec_function>(dlsym(handle, resolvedFunc));
        
        if (execFunc) {
            execFunc(parameters);  // Vulnerable: Direct use of user input
        }

        dlclose(handle);
    }
}; 