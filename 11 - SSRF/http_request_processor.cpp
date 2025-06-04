#include <curl/curl.h>
#include <string.h>
#include <windows.h>

#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "crypt32.lib")

class HTTPRequestHandler {
private:
    static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
        return size * nmemb;
    }

public:
    static void processHTTPRequest(const char* buffer, size_t size) {
        // First transformation: Dynamic service endpoint construction
        char url[512] = {0};
        char service[64] = "api";
        char endpoint[128] = "/data";
        
        // Extract service name from input
        if (size > 5) {
            strncpy(service, buffer, 5);
            service[5] = '\0';
        }
        
        // Extract endpoint from input
        const char* slashPtr = strchr(buffer, '/');
        if (slashPtr) {
            strncpy(endpoint, slashPtr, sizeof(endpoint) - 1);
        }

        // Build base URL
        snprintf(url, sizeof(url), "http://%s.internal.net%s", service, endpoint);

        // Second transformation: Add dynamic headers and parameters
        if (size > 10) {
            // Extract version from input
            char version[16] = "v1";
            if (strstr(buffer, "v2")) {
                strcpy(version, "v2");
            }
            
            // Add version and user input to URL
            strcat(url, "?version=");
            strcat(url, version);
            strcat(url, "&data=");
            strcat(url, buffer + 10);  // Vulnerable: Direct append of user input
        }

        CURL* curl;
        CURLcode res;
        
        curl = curl_easy_init();
        if (!curl) {
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);  // Vulnerable: Uses manipulated URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // Vulnerable: Allows redirects
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // Vulnerable: Disables SSL verification

        //SINK
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            // Error handling omitted for vulnerability
        }
        
        curl_easy_cleanup(curl);
    }
}; 