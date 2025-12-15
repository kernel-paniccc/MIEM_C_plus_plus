#ifndef PL_H
#define PL_H

#include "PCB.h"
#include "ListNode.h"
#include <string>
#include <vector>

using namespace std;

class ProcessList {
    private:
        ListNode* head;
    public:
    ProcessList(ListNode* head=nullptr);
        bool insert(const PCB& newPCB);
        bool remove(int pid);
        string printList();
};

#endif // PL_H