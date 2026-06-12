# CSOPESY_Desktop

## Requirements

This project already includes GLFW and Dear ImGui in the repository, so you do not need to install those separately.

Install these build tools on Windows:

1. CMake 3.16 or newer.
2. A C++17 compiler toolchain, such as Visual Studio 2022 Build Tools with the Desktop development with C++ workload, or MinGW-w64.

## Build and Run

If you already have a configured `build/` folder, you can run the app with:

```bat
run.bat
```

If this is a fresh checkout and the build folder has not been configured yet, run these commands from the repository root:

```bat
cmake -S . -B build
cmake --build build
build\CSOPESY_Desktop.exe
```

If you are using Visual Studio, open the folder in VS Code or Visual Studio after installing the C++ workload, then configure and build the `CSOPESY_Desktop` target from there.
