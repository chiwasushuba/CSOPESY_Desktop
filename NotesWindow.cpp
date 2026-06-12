#include "NotesWindow.h"
#include "imgui/imgui.h"
#include <cstring>

NotesWindow::NotesWindow() : AWindow("Quick Notes") {
    const char* initialNote = "- Add scheduler metrics\n- Check process state transitions\n- Demo taskbar flow";
    std::strncpy(quickNote, initialNote, sizeof(quickNote) - 1);
    quickNote[sizeof(quickNote) - 1] = '\0';
}

void NotesWindow::draw() {
    if (!beginWindow()) return;

    ImGui::Text("Quick Notes");
    ImGui::Separator();
    ImGui::TextWrapped("This is a placeholder productivity panel for the taskbar app launcher.");
    ImGui::Spacing();

    ImGui::InputTextMultiline("##NotesInput", quickNote, sizeof(quickNote), ImVec2(-1.0f, 180.0f));

    ImGui::Spacing();
    ImGui::Text("Status: Draft is local to this session.");

    endWindow();
}
