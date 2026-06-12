#pragma once
#include <string>
#include "imgui/imgui.h"

class AWindow {
public:
    AWindow(const std::string& name) : windowName(name), isVisible(false) {}
    virtual ~AWindow() = default;

    // every UI window needs to implement this to draw its actual content
    virtual void draw() = 0;

    void show() { isVisible = true; }
    void hide() { isVisible = false; }
    bool isShown() const { return isVisible; }

protected:
    // wraps imgui
    bool beginWindow() {
        if (!isVisible) return false;
        ImGui::Begin(windowName.c_str(), &isVisible);
        return true;
    }

    // to finalize rendering a window frame
    void endWindow() {
        ImGui::End();
    }

    std::string windowName;
    bool isVisible;
};
