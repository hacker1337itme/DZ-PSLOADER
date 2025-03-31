#include <windows.h>
#include <wininet.h>
#include <stdio.h>

#pragma comment(lib, "wininet.lib")

void DownloadFile(const char* url, const char* filename) {
    HINTERNET hInternet, hConnect;
    DWORD bytesRead;
    char buffer[4096];
    FILE* file;

    // Initialize WinINet
    hInternet = InternetOpen("Downloader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        printf("InternetOpen failed. Error: %lu\n", GetLastError());
        return;
    }

    // Open URL
    hConnect = InternetOpenUrl(hInternet, url, NULL, 0, 0, 0);
    if (hConnect == NULL) {
        printf("InternetOpenUrl failed. Error: %lu\n", GetLastError());
        InternetCloseHandle(hInternet);
        return;
    }

    // Open file for writing
    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return;
    }

    // Read data from URL and write to file
    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        fwrite(buffer, 1, bytesRead, file);
    }

    printf("Downloaded %s successfully.\n", filename);

    // Clean up
    fclose(file);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
}

void PrintBanner() {
    printf("****************************************\n");
    printf("*           PS1 File Downloader         *\n");
    printf("*           by EL-HA9                   *\n");
    printf("*             DZ-LAB                    *\n");
    printf("****************************************\n");
}

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        printf("Usage: %s <url> <filename>\n", argv[0]);
        return 1;
    }

    const char* url = argv[1];
    const char* filename = argv[2];

    // Print ASCII banner
    PrintBanner();

    // Download file
    DownloadFile(url, filename);

    return 0;
}
