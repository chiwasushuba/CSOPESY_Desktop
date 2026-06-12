#pragma once
#include "AWindow.h"

class NotesWindow : public AWindow {
public:
    NotesWindow();
    void draw() override;

private:
    char quickNote[512];
};
