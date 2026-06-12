cmake_minimum_required(VERSION 3.16)
project(CSOPESY_Desktop CXX C)

# Force modern C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Turn off documentation/examples for GLFW so it compiles fast
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# 2. Tell CMake to look into your glfw-3.4 folder and add it to the build tree
# (This provides the internal 'glfw' target to link against!)
add_subdirectory(glfw-3.4)

# 3. Collect All Source Files
set(PROJECT_SOURCES
    main.cpp
    Desktop.cpp
    TaskManager.cpp
    
    # Points exactly to the gl.c file inside your local glfw-3.4 folder
    # glfw-3.4/deps/glad/gl.c
    
    # Core Dear ImGui implementation files
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp
    
    # Dear ImGui platform and renderer backends
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
)

# 4. Create the Executable Target
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# 5. Define Include Directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}                  # Root folder (for Desktop.h)
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui             # Your imgui/ folder
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.4/include  # Path to glfw3.h inside the source
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.4/deps     # Path to glad/gl.h inside the source
)

# 6. Link Libraries 
# (We pass the 'glfw' target created by step 2, along with native Windows graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    opengl32
    gdi32
)