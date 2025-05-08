#include "MouseHook.h"
#include "ClickProcessor.h"
#include "Analyzer.h"
#include "Utils.h"
#include <iostream>
#include <fstream>

using namespace std;

int outputcount = 0;

HHOOK MouseHook::hook = nullptr;
ClickProcessor* MouseHook::processor = nullptr;
Analyzer* MouseHook::analyzer = nullptr;

MouseHook::MouseHook(ClickProcessor& cp, Analyzer& az) {
    processor = &cp;
    analyzer = &az;
}

bool MouseHook::install() {
    hook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    return hook != nullptr;
}

void MouseHook::uninstall() {
    if(hook) {
        UnhookWindowsHookEx(hook);
        hook = nullptr;
    }
}

LRESULT CALLBACK MouseHook::MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    static ofstream fout("data/data.txt", ios::app);

    if(nCode == HC_ACTION && wParam == WM_LBUTTONDOWN) {
        processor->recordClick();

        const auto& delays = processor->getDelays();
        int tickDelta = delays.empty() ? 0 : delays.back();

        //cout << "Click " << processor->getClickCount() << ": Tick Delta = " << tickDelta << '\n';
        double currentCPS = processor->getCPS();
        
        //cout << "Current CPS: " << currentCPS << '\n';
        fout << tickDelta << " ";
        if(tickDelta != 0)
            cout << tickDelta << ' ';
        else {
            Color(FOREGROUND_RED);  // Set text color to red
            cout << tickDelta << ' ';  // This will print in red
            Color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to normal
        }
        if(processor->getClickCount() % 26 == 25)
            cout << '\n';


        if(processor->getClickCount() >= 100) {
            cout << "\n#" << ++outputcount << '\n';
            cout <<"Max CPS: " << processor->getMaxCPS() << '\n';
            analyzer->analyze(delays);
            fout.flush();
            processor->reset();
            cout << '\n';
            Color(FOREGROUND_GREEN);
            cout << "Ticks: \n";
            Color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
