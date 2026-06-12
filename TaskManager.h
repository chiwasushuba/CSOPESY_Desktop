#pragma once
#include "AWindow.h"
#include <vector>
#include <string>

struct ProcessDummy {
    int pid;
    std::string name;
    float cpu;
    float memory;
};

class TaskManager : public AWindow {
public:
    TaskManager();
    void draw() override;

private:
    std::vector<ProcessDummy> processes;
    int selectedRow;
    void populateDummyData();
};
