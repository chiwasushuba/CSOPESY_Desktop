#include "Desktop.h"
#include "TaskManager.h"
#include <ctime>
#include <string>
#include <GLFW/glfw3.h>

Desktop::Desktop()
    : AWindow("Desktop"),
      tmInstance(nullptr),
      sysInfoInstance(nullptr),
      notesInstance(nullptr) {
    this->show(); // desktop shows by default
}

Desktop::~Desktop() {
    delete tmInstance;
    delete sysInfoInstance;
    delete notesInstance;
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

    drawTaskbar(displaySize);

    // Every single frame, if the instance exists and is visible, draw it
    if (tmInstance && tmInstance->isShown()) { 
        tmInstance->draw(); 
    }

    if (sysInfoInstance && sysInfoInstance->isShown()) {
        sysInfoInstance->draw();
    }

    if (notesInstance && notesInstance->isShown()) {
        notesInstance->draw();
    }

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
    // Use std::localtime which is safe here since this is a single-threaded UI draw call
    std::tm* timeinfo = std::localtime(&time);
    if (!timeinfo) return;
    char buffer[64];
    std::strftime(buffer, sizeof(buffer), "%A, %b %d, %Y | %I:%M:%S %p", timeinfo);

    ImVec2 textSize = ImGui::CalcTextSize(buffer);
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    ImVec2 clockPosition = ImVec2(displaySize.x - textSize.x - 20.0f, 20.0f);

    ImGui::SetCursorPos(clockPosition);
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 0.9f), "%s", buffer);
}

void Desktop::drawTaskbar(ImVec2 displaySize) {
    const float barHeight = 56.0f;
    const float edgePadding = 10.0f;
    const ImVec2 buttonSize(56.0f, 36.0f);
    const float buttonSpacing = 8.0f;

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    const ImVec2 barMin(0.0f, displaySize.y - barHeight);
    const ImVec2 barMax(displaySize.x, displaySize.y);

    drawList->AddRectFilled(barMin, barMax, IM_COL32(8, 12, 24, 220));
    drawList->AddLine(ImVec2(0.0f, barMin.y), ImVec2(displaySize.x, barMin.y), IM_COL32(56, 189, 248, 140), 1.5f);

    ImVec2 currentPos(edgePadding, displaySize.y - barHeight + (barHeight - buttonSize.y) * 0.5f);

    ImGui::SetCursorPos(currentPos);
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(21, 94, 117, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(14, 116, 144, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(8, 145, 178, 255));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    if (ImGui::Button("SYS", buttonSize)) {
        if (sysInfoInstance == nullptr) {
            sysInfoInstance = new SystemInfoWindow();
            sysInfoInstance->show();
        } else if (sysInfoInstance->isShown()) {
            sysInfoInstance->hide();
        } else {
            sysInfoInstance->show();
        }
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);

    currentPos.x += buttonSize.x + buttonSpacing;
    ImGui::SetCursorPos(currentPos);
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(76, 29, 149, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(109, 40, 217, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(124, 58, 237, 255));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    if (ImGui::Button("NOTE", buttonSize)) {
        if (notesInstance == nullptr) {
            notesInstance = new NotesWindow();
            notesInstance->show();
        } else if (notesInstance->isShown()) {
            notesInstance->hide();
        } else {
            notesInstance->show();
        }
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);

    currentPos.x += buttonSize.x + buttonSpacing;
    ImGui::SetCursorPos(currentPos);
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(180, 120, 24, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(217, 140, 24, 255));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(234, 179, 8, 255));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    if (ImGui::Button("TM", buttonSize)) {
        if (tmInstance == nullptr) {
            tmInstance = new TaskManager();
            tmInstance->show();
        } else if (tmInstance->isShown()) {
            tmInstance->hide();
        } else {
            tmInstance->show();
        }
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);

    std::string runningApps = "Running: Desktop";
    if (tmInstance && tmInstance->isShown()) runningApps += " | Task Manager";
    if (sysInfoInstance && sysInfoInstance->isShown()) runningApps += " | System Info";
    if (notesInstance && notesInstance->isShown()) runningApps += " | Notes";

    ImVec2 runningTextSize = ImGui::CalcTextSize(runningApps.c_str());
    ImVec2 runningPos(displaySize.x - runningTextSize.x - 120.0f, displaySize.y - barHeight + 19.0f);
    ImGui::SetCursorPos(runningPos);
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 0.82f), "%s", runningApps.c_str());

    const ImVec2 pwrBtnSize(78.0f, 36.0f);
    ImVec2 pwrPos(displaySize.x - pwrBtnSize.x - edgePadding, displaySize.y - barHeight + (barHeight - pwrBtnSize.y) * 0.5f);
    ImGui::SetCursorPos(pwrPos);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.75f, 0.15f, 0.15f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.90f, 0.20f, 0.20f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.60f, 0.10f, 0.10f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    if (ImGui::Button("PWR", pwrBtnSize)) {
        GLFWwindow* currentWindow = glfwGetCurrentContext();
        if (currentWindow) {
            glfwSetWindowShouldClose(currentWindow, GLFW_TRUE);
        }
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
}