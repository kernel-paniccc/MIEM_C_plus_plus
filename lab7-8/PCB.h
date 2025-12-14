#ifndef PCB_H
#define PCB_H

#include <pthread.h>
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
    public:
        PCB(int ProcessID, string ProcessName, string ProcessStatus, vector<int> cpuRegisters);
        // гетеры
        int getId() const;
        string getName() const;
        string getStatus() const;
        int getCounter() const;

};

#endif // PCB_H