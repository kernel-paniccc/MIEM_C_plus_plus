#ifndef PL_H
#define PL_H

#include "ListNode.h"
#include <string>
#include <vector>

using namespace std;

class PL {
    private:
        ListNode* head;
    public:
        PL(ListNode* head);
        bool insert(const PCB& newPCB);
        bool remove(int pid);
        string printList();
};

#endif // PL_H