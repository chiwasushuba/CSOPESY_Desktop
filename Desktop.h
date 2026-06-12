#pragma once
#include "AWindow.h"
#include "TaskManager.h"
#include "SystemInfoWindow.h"
#include "NotesWindow.h"
#include <chrono>

class Desktop : public AWindow {
public:
    Desktop();
    ~Desktop() override;

    void draw() override;

private:
    TaskManager* tmInstance;
    SystemInfoWindow* sysInfoInstance;
    NotesWindow* notesInstance;
    void drawClock();
    void drawTaskbar(ImVec2 displaySize);
    
    void drawBackgroundPattern(ImVec2 displaySize);
};