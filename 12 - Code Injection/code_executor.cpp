#include <windows.h>
#include <string.h>
#include <cstdio>

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
        pathPtr += sprintf(pathPtr, "C:\\Program Files\\Dynamic\\");
        pathPtr += sprintf(pathPtr, "%s", moduleName);
        pathPtr += sprintf(pathPtr, "\\plugins\\");
        pathPtr += sprintf(pathPtr, "%s", moduleName);
        pathPtr += sprintf(pathPtr, "\\runtime\\");
        pathPtr += sprintf(pathPtr, "%s", moduleName);
        pathPtr += sprintf(pathPtr, ".dll");

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
        HMODULE handle = LoadLibraryA(modulePath);
        
        if (!handle) {
            return;
        }

        // Get function pointer
        typedef void (WINAPI *exec_function)(const char*);
        //SINK
        exec_function execFunc = reinterpret_cast<exec_function>(GetProcAddress(handle, resolvedFunc));
        
        if (execFunc) {
            execFunc(parameters);  // Vulnerable: Direct use of user input
        }

        FreeLibrary(handle);
    }
};

// Add WinMain entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Example usage
    char buffer[] = "test_module\0test_function\0test_params";
    CodeExecutor::executeCode(buffer, sizeof(buffer));
    return 0;
} 