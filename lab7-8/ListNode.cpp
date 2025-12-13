#include "ListNode.h"
#include "PCB.h"


using namespace std;


ListNode::ListNode(const PCB& data, ListNode* next):
    data(data),
    next(next) {}
