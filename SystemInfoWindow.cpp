#include "SystemInfoWindow.h"
#include "imgui/imgui.h"

SystemInfoWindow::SystemInfoWindow() : AWindow("System Information") {}

void SystemInfoWindow::draw() {
    if (!beginWindow()) return;

    ImGui::Text("System Information");
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text("Hostname: CSOPESY-WORKSTATION");
    ImGui::Text("Kernel Build: v1.0.3-alpha");
    ImGui::Text("CPU: 4 Cores @ 3.20 GHz");
    ImGui::Text("RAM: 8 GB (5.1 GB available)");
    ImGui::Text("Storage: 128 GB / 256 GB used");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextWrapped("Placeholder diagnostics panel. You can later wire this to real runtime metrics.");

    endWindow();
}
