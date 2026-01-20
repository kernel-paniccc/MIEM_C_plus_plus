#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Структура для хранения статистики одной группы
template<class KeyT, class T, class SumT>
struct GroupInfo {
    KeyT   key;      
    int    count;    
    T      minElem;  
    T      maxElem;  
    SumT   sum;     
    double mid;      
};

template<class T, class KeyFunc, class ValueFunc>
auto groupStats(T* arr, int n, KeyFunc keyFunc, ValueFunc valueFunc)
{

    auto firstKey = keyFunc(arr[0]);      
    auto firstVal = valueFunc(arr[0]);     
    
    using KeyT = decltype(firstKey);       
    using SumT = decltype(firstVal);       
    

    vector<GroupInfo<KeyT, T, SumT>> groups;
    

    for (int i = 0; i < n; i++) {
        
        KeyT key = keyFunc(arr[i]);
        SumT val = valueFunc(arr[i]);
        
        bool found = false;
        int groupIndex = -1;
        
        for (int j = 0; j < groups.size(); j++) {
            if (groups[j].key == key) {
                found = true;
                groupIndex = j;
                break;
            }
        }
        
        if (!found) {
            GroupInfo<KeyT, T, SumT> newGroup;
            newGroup.key = key;
            newGroup. count = 1;
            newGroup.minElem = arr[i];
            newGroup.maxElem = arr[i];
            newGroup.sum = val;
            newGroup.mid = (double)val;
            
            groups.push_back(newGroup);
        }

        else {
            groups[groupIndex].count = groups[groupIndex].count + 1;
            

            if (arr[i] < groups[groupIndex].minElem) {
                groups[groupIndex].minElem = arr[i];}

            if (arr[i] > groups[groupIndex].maxElem) {
                groups[groupIndex].maxElem = arr[i];}

            groups[groupIndex].sum = groups[groupIndex].sum + val;
            groups[groupIndex].mid = (double)groups[groupIndex].sum / groups[groupIndex].count;
        }
    }
    
    return groups;
}

int main()
{
    
    int a[] = {12, 25, 37, 42, 15, 52};
    int size_a = 6;
    
    auto r1 = groupStats(a, size_a,
        [](int x) { return x % 10; },
        [](int x) { return x; } 
    );
    
    for (int i = 0; i < r1.size(); i++) {
        cout << r1[i]. key << ", "
             << r1[i]. count << ", "
             << r1[i].minElem << ", "
             << r1[i].maxElem << ", "
             << r1[i]. sum << ", "
             << r1[i].mid << "\n";
    }

    
    string b[] = {"test_string", "njrfbewcklxw", "iopvtnjwcbjcrk"};
    int size_b = 3;
    
    auto r2 = groupStats(b, size_b,
        [](string s) { return s[0]; },
        [](string s) { return (int)s.size(); }
    );
    
    for (int i = 0; i < r2.size(); i++) {
        cout << r2[i].key << ", "
             << r2[i].count << ", "
             << r2[i].minElem << ", "
             << r2[i].maxElem << ", "
             << r2[i].sum << ", "
             << r2[i].mid << "\n";
    }
    
    return 0;
}