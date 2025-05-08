#pragma once
#include <Windows.h>

class ClickProcessor;
class Analyzer;

class MouseHook {
public:
    MouseHook(ClickProcessor& cp, Analyzer& az);
    bool install();
    void uninstall();

private:
    static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
    static HHOOK hook;
    static ClickProcessor* processor;
    static Analyzer* analyzer;
};
