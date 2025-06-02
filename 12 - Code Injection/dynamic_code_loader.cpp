#include <dlfcn.h>
#include <string.h>

class DynamicCodeLoader {
public:
    static void loadDynamicCode(char* buffer, size_t size) {
        // Extract component information from buffer
        char componentName[256] = {0};
        char libraryPath[128] = {0};
        char initFunc[64] = {0};
        
        // Vulnerable: Direct copy without size checks
        strcpy(componentName, buffer);
        strcpy(libraryPath, buffer + strlen(componentName));
        strcpy(initFunc, buffer + strlen(componentName) + strlen(libraryPath));

        // First vulnerable transformation: Dynamic library path construction
        char fullPath[512] = {0};
        strcpy(fullPath, "/usr/local/lib/");  // Vulnerable: No bounds checking
        strcat(fullPath, componentName);      // Vulnerable: No bounds checking
        strcat(fullPath, "/components/");     // Vulnerable: No bounds checking
        strcat(fullPath, libraryPath);        // Vulnerable: No bounds checking
        strcat(fullPath, ".so");              // Vulnerable: No bounds checking

        // Second vulnerable transformation: Function name resolution
        char resolvedFunc[256] = {0};
        strcpy(resolvedFunc, "COMPONENT_");   // Vulnerable: No bounds checking
        strcat(resolvedFunc, componentName);  // Vulnerable: No bounds checking
        strcat(resolvedFunc, "_");            // Vulnerable: No bounds checking
        strcat(resolvedFunc, initFunc);       // Vulnerable: No bounds checking
        strcat(resolvedFunc, "_INIT");        // Vulnerable: No bounds checking

        // Load the dynamic library
        void* handle = dlopen(fullPath, RTLD_LAZY);
        if (!handle) {
            return;
        }

        // Get initialization function pointer
        typedef void (*init_component)();
        //SINK
        init_component initFuncPtr = reinterpret_cast<init_component>(dlsym(handle, resolvedFunc));
        
        if (initFuncPtr) {
            initFuncPtr();
        }

        dlclose(handle);
    }
}; 