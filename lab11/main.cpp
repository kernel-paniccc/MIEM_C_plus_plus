#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<int> prices;
    string line;
    int price;

    cout << "Введите список цен товаров: ";
    getline(cin, line);

    stringstream input(line);
    while (input >> price) {
        prices.push_back(price);
    }

    if (prices.empty()) {
        cout << "Список цен пуст.\n";
        return 0;
    }

    sort(prices.begin(), prices.end(), greater<int>());

    double sum = 0.0;
    for (vector<int>::iterator it = prices.begin(); it != prices.end(); ++it) {
        sum += *it;
    }

    double average = sum / prices.size();


    for (vector<int>::iterator it = prices.begin(); it != prices.end();) {
        if (*it < average) {
            it = prices.erase(it);
        } else {
            ++it;
        }
    }

    cout << "Цены выше среднего: ";
    for (vector<int>::iterator it = prices.begin(); it != prices.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    return 0;
}
