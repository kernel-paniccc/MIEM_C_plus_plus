#include <iostream>
#include <string>
#include <vector>
#include "ProcessList.h"
#include "ListNode.h"

using namespace std;

ProcessList::ProcessList(ListNode* head)
    : head(head) {};


bool ProcessList::insert(const PCB& newPCB) {
    int newPid = newPCB.getId();

    if (head == nullptr) {
        ListNode* newNode = new ListNode(newPCB, nullptr);
        head = newNode;
        cout << "Создан новый список, т.к. вы задали первый процесс";
        return true;
    }

    if (newPid == head->getData().getId()) {
        cout << "Ошибка PID";
        return false;
    }



    if (newPid < head->getData().getId()) {
        ListNode* newNode = new ListNode(newPCB, head);
        head = newNode;
        return true;
    }

    ListNode* prev = head;
    ListNode* curr = head->getNext();

    while (curr && curr->getData().getId()  < newPid) {
        prev = curr;
        curr = curr->getNext();
    }

    if (curr && curr->getData().getId() == newPid) {
        cout << "Ошибка PID";
    }

    ListNode* newNode = new ListNode(newPCB, curr);
    prev->setNext(newNode);
    return true;

}



bool ProcessList::remove(int pid) {
    
}
