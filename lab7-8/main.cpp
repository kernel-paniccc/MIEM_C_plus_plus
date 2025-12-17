#include <iostream>
#include <string>
#include <vector>

#include "ProcessList.h"


int main() {
    ProcessList plist;

    PCB p5(5, "Test1", "Work", 1, {1,2,3});
    PCB p10(10, "Test2", "Work", 2, {4,5,6});
    PCB p20(20, "Test3", "Kill", 3, {7,8,9});

    plist.insert(p5);
    plist.insert(p10);
    plist.insert(p10); // задублируем процесс
    plist.insert(p20);

    cout << "\n==проверка работы:==\n";
    cout << plist.printList();

    plist.remove(5);
    cout << "\n==удалим начальный:==\n";
    cout << plist.printList();

    plist.remove(52); 
    cout << "\n==тест на удаление несуществующего:==\n";
    cout << plist.printList();

    return 0;
}
