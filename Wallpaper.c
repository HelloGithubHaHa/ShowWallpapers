#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "KeyboardHook.h"

char path[256] = "";

int file_num = 0;
char *filenames[100000];
int file_index;

void callback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == 'Z' && GetAsyncKeyState(VK_CONTROL)<0 && GetAsyncKeyState(VK_MENU)<0) {
        char command[1024] = "";
        strcat(command, "move ");
        strcat(command, path);
        strcat(command, " C:\\DonotLike\\");
        system(command);
        filenames[file_index] = "";
    }
}

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
    stopHook();
    printf("º¸≈Ãπ≥◊”“—œ˙ªŸ\n");
    return FALSE;
}

// …Ë÷√◊¿√Ê±⁄÷Ω
int main()
{
    char *dir = "C:\\AllPictures\\";
    char *name = "*";

    strcat(path, dir);
    strcat(path, name);

    WIN32_FIND_DATA ffd;
    HANDLE hFind = FindFirstFile(path, &ffd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
                int length = strlen(ffd.cFileName);
                char *filename = malloc(length + 1);
                strcpy(filename, ffd.cFileName);
                filenames[file_num] = filename;
                ++file_num;
            }
        } while (FindNextFile(hFind, &ffd) != FALSE);
        FindClose(hFind);
    } else {
        printf("Error");
        return -1;
    }

    if (file_num > 0) {
        BOOL bResult = startHook(callback);
        if (!bResult) {
            printf("º¸≈Ãπ≥◊”…Ë÷√ ß∞‹£°");
            return -1;
        }
        bResult = SetConsoleCtrlHandler(HandlerRoutine, TRUE);
        if (!bResult) {
            stopHook();
            printf("øÿ÷∆Ã®π≥◊”…Ë÷√ ß∞‹£°");
            return -1;
        }

        SetTimer(NULL, 0, 10000, NULL);
        MSG msg;

        srand(time(NULL));
        int length;
        while (GetMessage(&msg, NULL, 0, 0)) {
            switch (msg.message) {
                case WM_TIMER:
                    do {
                        file_index = rand() % file_num;
                        length = strlen(filenames[file_index]);
                    } while (length == 0);
                    path[0] = 0;
                    strcat(path, dir);
                    strcat(path, filenames[file_index]);
                    printf("%s\n", path);
                    SystemParametersInfo(SPI_SETDESKWALLPAPER, TRUE, path, TRUE);
                    break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        
    }

    return 0;
}