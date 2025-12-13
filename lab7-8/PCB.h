#ifndef PCB_H
#define PCB_H

#include <string>
#include <vector>

using namespace std;

class PCB {
    private:
        int ProcessID;
        string ProcessName;
        string ProcessStatus;
        int CommandCounter;
        vector <int> cpuRegisters;
};

#endif // PCB_H