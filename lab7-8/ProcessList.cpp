#include <iostream>
#include <string>
#include <sstream>
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
        cout << "Создан новый список, т.к. спска нет";
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
        return false;
    }

    ListNode* newNode = new ListNode(newPCB, curr);
    prev->setNext(newNode);
    return true;

}



bool ProcessList::remove(int pid) {

    if (head == nullptr) {
        cout << "Списка нет :_(";
        return false;
    }

    if (head->getData().getId() == pid) {
        ListNode* head1 = head;
        head = head->getNext();
        delete head1;
        return true;
    }

    ListNode* prev = head;
    ListNode* curr = head->getNext();
    while (curr && curr->getData().getId() < pid) {
        prev = curr;
        curr = curr->getNext();
    }
    
    if (curr && curr->getData().getId() == pid) {
    prev->setNext(curr->getNext());
    delete curr;
    return true;
    }

    return false;
}


string ProcessList::printList() {
    
    if (head == nullptr) { return "Список пуст\n"; }

    stringstream out;
    for (ListNode* curr = head; curr; curr = curr->getNext()) {
        out << "\nPID:"; out << curr->getData().getId(); out << " ";
        out << "Name:"; out << curr->getData().getName(); out << " ";
        out << "Status:"; out << curr->getData().getStatus(); out << " "; 
        out << "Counter:"; out << curr->getData().getCounter(); out << " \n";
    };
    
    return out.str();

}