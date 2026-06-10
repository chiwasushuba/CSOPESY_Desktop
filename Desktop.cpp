#include "Desktop.h"
#include <ctime>
#include <GLFW/glfw3.h>

Desktop::Desktop() : AWindow("Desktop") {
    this->show(); // desktop shows by default
}

void Desktop::draw() {
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(displaySize);

    ImGui::Begin("DesktopWindow", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBackground);

    drawBackgroundPattern(displaySize);

    ImGui::SetCursorPos(ImVec2(20, 20));
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 0.4f), "CSOPESY OS v1.0");

    // clock widget
    drawClock();

    // PWR Shutdown button
    ImVec2 buttonSize = ImVec2(70.0f, 35.0f);
    float edgePadding = 20.0f;
    ImVec2 pwrBtnPos = ImVec2(
        displaySize.x - buttonSize.x - edgePadding,
        displaySize.y - buttonSize.y - edgePadding
    );
    ImGui::SetCursorPos(pwrBtnPos);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.75f, 0.15f, 0.15f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.90f, 0.20f, 0.20f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.60f, 0.10f, 0.10f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);

    if (ImGui::Button("PWR", buttonSize)) {
        GLFWwindow* currentWindow = glfwGetCurrentContext();
        if (currentWindow) {
            glfwSetWindowShouldClose(currentWindow, GLFW_TRUE);
        }
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);

    ImGui::End();
}

//Bacground
void Desktop::drawBackgroundPattern(ImVec2 displaySize) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    drawList->AddRectFilledMultiColor(
        ImVec2(0, 0),
        displaySize,
        IM_COL32(15, 23, 42, 255),  
        IM_COL32(15, 23, 42, 255), 
        IM_COL32(30, 41, 59, 255),  
        IM_COL32(30, 41, 59, 255)  
    );

    // Creates grid
    float gridSize = 40.0f; 
    ImU32 gridColor = IM_COL32(255, 255, 255, 12); 

    // Vertical
    for (float x = 0; x < displaySize.x; x += gridSize) {
        drawList->AddLine(ImVec2(x, 0), ImVec2(x, displaySize.y), gridColor, 1.0f);
    }

    // Horizontal
    for (float y = 0; y < displaySize.y; y += gridSize) {
        drawList->AddLine(ImVec2(0, y), ImVec2(displaySize.x, y), gridColor, 1.0f);
    }

    drawList->AddLine(ImVec2(0, 0), ImVec2(displaySize.x, 0), IM_COL32(56, 189, 248, 100), 2.0f); // Neon blue accent line
}

//Clock
void Desktop::drawClock() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm timeinfo;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&timeinfo, &time);
#else
    localtime_r(&time, &timeinfo);
#endif

    char buffer[64];
    std::strftime(buffer, sizeof(buffer), "%A, %b %d, %Y | %I:%M:%S %p", &timeinfo);

    ImVec2 textSize = ImGui::CalcTextSize(buffer);
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    ImVec2 clockPosition = ImVec2(displaySize.x - textSize.x - 20.0f, 20.0f);

    ImGui::SetCursorPos(clockPosition);
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 0.9f), "%s", buffer);
}