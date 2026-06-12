#include <iostream>
#include <memory>

// Include Graphics / UI dependencies
#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h" // Replace with your chosen OpenGL loader if different
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// Include your Component 1 files
#include "Desktop.h"

int main() {
    // ========================================================================
    // PHASE 1: Bootstrapping (Hardware / Window Subsystem Setup)
    // ========================================================================
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Target OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the emulator viewport window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "CSOPESY Desktop OS Emulator", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable VSync

    // Initialize OpenGL function pointers
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    //     std::cerr << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }
    if (!gladLoadGL(glfwGetProcAddress)) {
        return -1; 
    }

    // Setup Dear ImGui Context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // ========================================================================
    // PHASE 2 & 3: Kernel Initialization & System Services
    // ========================================================================
    // Instantiate Component 1: The Desktop directly. 
    // Since we don't have the full UIManager singleton registry architecture built yet, 
    // we manage it locally right here for testing!
    std::unique_ptr<Desktop> myDesktop = std::make_unique<Desktop>();

    // ========================================================================
    // PHASE 4: Enter Main Loop (Continuously Handle Events & Render Interface)
    // ========================================================================
    while (!glfwWindowShouldClose(window)) {
        // 1. Poll operating system input events (keyboard, mouse, sizing changes)
        glfwPollEvents();

        // 2. Start a fresh, raw Dear ImGui frame interface build
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 3. Render Component 1: The Desktop Background layer
        if (myDesktop && myDesktop->isShown()) {
            myDesktop->draw();
        }

        // 4. Finalize high-level widget processing lists into low-level rendering data
        ImGui::Render();

        // 5. Instruct OpenGL to clear the backbuffer context frame
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Default dark buffer backup
        glClear(GL_COLOR_BUFFER_BIT);

        // 6. Draw the ImGui frame graphics pipeline structures over the screen
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // 7. Swap front and back display buffer maps (Double Buffering refresh)
        glfwSwapBuffers(window);
    }

    // ========================================================================
    // PHASE 5: Shutdown and Cleanup (Gracefully terminate resources)
    // ========================================================================
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}