#include <windows.h>
#include <stdlib.h>
#include "KeyboardHook.h"

typedef void (* CallBackFun)(int nCode, WPARAM wParam, LPARAM lParam);
CallBackFun callback;

#pragma data_seg("data")
HHOOK glhHook = NULL;
HINSTANCE glhInstance = NULL;
#pragma data_seg

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    glhInstance = hinstDLL;
    return TRUE;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (!(lParam & 0X80000000) && (nCode == HC_ACTION)) {
        callback(nCode, wParam, lParam);
    }
    return CallNextHookEx(glhHook, nCode, wParam, lParam);
}

DLL_EXPORT BOOL startHook(CallBackFun callback_fun)
{
    callback = callback_fun;
    BOOL bResult = FALSE;
    glhHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, glhInstance, 0);
    if (glhHook) {
        bResult = TRUE;
    }
    return bResult;
}

DLL_EXPORT BOOL stopHook()
{
    BOOL bResult = FALSE;
    if (glhHook) {
        bResult = UnhookWindowsHookEx(glhHook);
        if (bResult) {
            glhHook = NULL;
        }
    }
    return bResult;
}
