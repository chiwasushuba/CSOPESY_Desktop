#pragma once
#include "AWindow.h"
#include <chrono>

class Desktop : public AWindow {
public:
    Desktop();
    ~Desktop() override = default;

    void draw() override;

private:
    void drawClock();
    
    void drawBackgroundPattern(ImVec2 displaySize);
};