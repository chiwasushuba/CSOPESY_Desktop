#include "TaskManager.h"
#include "imgui/imgui.h"

TaskManager::TaskManager() : AWindow("Task Manager"), selectedRow(-1) {
    populateDummyData();
}

void TaskManager::populateDummyData() {
    processes = {
        { 1024, "System Idle Process", 74.5f, 0.1f },
        { 4,    "System",              1.2f,  4.2f },
        { 1420, "csopesy_kernel.exe",  12.4f, 142.5f },
        { 2844, "desktop_shell.exe",   2.1f,  64.8f },
        { 3912, "file_explorer.exe",   0.0f,  28.4f },
        { 5120, "chrome_simulation",   9.8f,  412.0f }
    };
}

void TaskManager::draw() {
    if (!beginWindow()) return;

    ImGui::Text("CPU Usage: 25.5%% | Physical Memory: 651.0 MB");
    ImGui::Separator();
    ImGui::Spacing();

    static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY;
    
    if (ImGui::BeginTable("ProcessTable", 4, flags, ImVec2(0, -35))) {
        ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("PID", ImGuiTableColumnFlags_WidthFixed, 60.0f);
        ImGui::TableSetupColumn("CPU (%)", ImGuiTableColumnFlags_WidthFixed, 70.0f);
        ImGui::TableSetupColumn("Memory (MB)", ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableHeadersRow();

        for (int i = 0; i < (int)processes.size(); i++) {
            ImGui::TableNextRow();
            
            // Process Name
            ImGui::TableSetColumnIndex(0);
            bool isSelected = (selectedRow == i);
            if (ImGui::Selectable(processes[i].name.c_str(), isSelected, ImGuiSelectableFlags_SpanAllColumns)) {
                selectedRow = i;
            }

            // PID
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%d", processes[i].pid);

            // CPU
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%.1f%%", processes[i].cpu);

            // Memory
            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%.1f MB", processes[i].memory);
        }
        ImGui::EndTable();
    }

    ImGui::Separator();

    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 110.0f);


    if (ImGui::Button("End Task", ImVec2(90, 24))) {
        if (selectedRow >= 0 && selectedRow < (int)processes.size()) {
            processes.erase(processes.begin() + selectedRow);
            selectedRow = -1;
        }
    }

    endWindow();
}
