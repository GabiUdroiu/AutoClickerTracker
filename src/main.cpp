#include "ClickProcessor.h"
#include "Analyzer.h"
#include "MouseHook.h"
#include "Utils.h"
#include <Windows.h>
#include <iostream>

int main() {
    ClickProcessor processor;
    Analyzer analyzer;
    MouseHook mouseHook(processor, analyzer);
    Color(FOREGROUND_GREEN);
    std::cout << "Ticks: \n";
    Color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    if(!mouseHook.install()) {
        std::cerr << "Failed to set hook!" << std::endl;
        return 1;
    }
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    mouseHook.uninstall();
    return 0;
}
