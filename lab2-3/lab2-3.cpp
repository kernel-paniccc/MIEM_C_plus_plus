#include <iostream>
using namespace std;

void inputData(float* p, int n) {
    for (int i = 0; i < n; ++i)
        cin >> *(p + i);
}

float average(const float* p, int n) {
    float sum = 0;
    for (int i = 0; i < n; ++i)
        sum += *(p + i);
    return sum / n;
}

float minValue(const float* p, int n) {
    float min = *p;
    for (int i = 1; i < n; ++i)
        if (*(p + i) < min)
            min = *(p + i);
    return min;
}

float maxValue(const float* p, int n) {
    float max = *p;
    for (int i = 1; i < n; ++i)
        if (*(p + i) > max)
            max = *(p + i);
    return max;
}


float* filterAboveAverage(float* p, int n, int& count) {
    float avg = average(p, n);
    count = 0;
    for (int i = 0; i < n; ++i)
        if (*(p + i) > avg)
            count++;
    float* q = new float[count];
    int j = 0;
    for (int i = 0; i < n; ++i)
        if (*(p + i) > avg)
            *(q + j++) = *(p + i);
    return q;
}

int main() {
    int n;
    cout << "Введите количество измерений:";
    cin >> n;
    float* data = new float[n];
    cout << "Введите значения:";
    inputData(data, n);

    float avg = average(data, n);
    cout << "Среднее значение: " << avg << endl;
    cout << "Минимум: " << minValue(data, n) << endl;
    cout << "Максимум: " << maxValue(data, n) << endl;

    int aboveCount;
    float* above = filterAboveAverage(data, n, aboveCount);
    cout << "Значения выше среднего:" << endl;
    for (int i = 0; i < aboveCount; ++i)
        cout << *(above + i) << " ";
    cout << endl;

    delete[] data;
    delete[] above;
    return 0;
}