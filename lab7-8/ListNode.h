#ifndef LN_H
#define LN_H

#include <string>
#include <vector>
#include "PCB.h"

using namespace std;

class ListNode {
    private:
        PCB data;
        ListNode* next;
    public:
       ListNode(const PCB& data, ListNode* next);
};

#endif // LN_H
