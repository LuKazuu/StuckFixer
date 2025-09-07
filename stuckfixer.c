
#include <windows.h>

#define HOTKEY_FIX  1
#define HOTKEY_EXIT 2

void SimulateFocusSwitch() {
    HWND current = GetForegroundWindow();
    HWND dummy = CreateWindowEx(WS_EX_TOOLWINDOW, "STATIC", "", WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT, 100, 100,
                                NULL, NULL, NULL, NULL);
    ShowWindow(dummy, SW_SHOWNOACTIVATE);
    SetForegroundWindow(dummy);
    Sleep(100);
    ShowWindow(dummy, SW_HIDE);
    DestroyWindow(dummy);
    SetForegroundWindow(current);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register hotkeys
    RegisterHotKey(NULL, HOTKEY_FIX, MOD_CONTROL | MOD_SHIFT, 'F');  // Ctrl+Shift+F
    RegisterHotKey(NULL, HOTKEY_EXIT, MOD_CONTROL | MOD_SHIFT, 'Q'); // Ctrl+Shift+Q

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            if (msg.wParam == HOTKEY_FIX) {
                SimulateFocusSwitch();
            } else if (msg.wParam == HOTKEY_EXIT) {
                break;
            }
        }
    }

    // Cleanup
    UnregisterHotKey(NULL, HOTKEY_FIX);
    UnregisterHotKey(NULL, HOTKEY_EXIT);
    return 0;
}
