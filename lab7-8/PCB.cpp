#include <string>
#include <vector>
#include "PCB.h"

using namespace std;

PCB::PCB(int ProcessID, string ProcessName, string ProcessStatus, int CommandCounter, vector<int> cpuRegisters)
    : ProcessID(ProcessID),
      ProcessName(ProcessName),
      ProcessStatus(ProcessStatus),
      CommandCounter(CommandCounter),
      cpuRegisters(cpuRegisters) {};

int PCB::getId() const { return ProcessID; }

string PCB::getName() const { return ProcessName; }

string PCB::getStatus() const { return ProcessStatus; }

int PCB::getCounter() const { return CommandCounter; }


