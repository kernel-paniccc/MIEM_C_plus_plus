#include <iostream>
using namespace std;


void inputData(float** p, int d, int h) {
	for (int i = 0; i < d; ++i) {
		cout << "День " << (i + 1) << ": ";
		for (int j = 0; j < h; ++j)
			cin >> *(*(p + i) + j);
	}
}

float dayAverage(float* row, int h) {
	float sum = 0;
	for (int i = 0; i < h; ++i)
		sum += *(row + i);
	return sum / h;
}

float overallAverage(float** p, int d, int h) {
	float sum = 0;
	for (int i = 0; i < d; ++i)
		for (int j = 0; j < h; ++j)
			sum += *(*(p + i) + j);
	return sum / (d * h);
}

void showHotDays(float** p, int d, int h) {
	float avg = overallAverage(p, d, h);
	cout << "\nОбщая средняя температура: " << avg << endl;
	cout << "Теплые дни:" << endl;

	for (int i = 0; i < d; ++i) {
		float dayAvg = dayAverage(*(p + i), h);
		if (dayAvg > avg)
			cout << "День " << (i + 1) << " (среднее = " << dayAvg << ")" << endl;
	}
}

int main() {
	int d, h;

	cout << "Введите количество дней: ";
	cin >> d;
	cout << "Введите количество измерений в дне: ";
	cin >> h;


	float** data = new float*[d];
	for (int i = 0; i < d; ++i)
		*(data + i) = new float[h];

	inputData(data, d, h);
	showHotDays(data, d, h);


	for (int i = 0; i < d; ++i)
		delete[] *(data + i);
	delete[] data;
	return 0;
}
