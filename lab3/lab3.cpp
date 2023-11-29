#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

const int n = 15;

// Функция для обмена двух элементов массива
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Generating an increasing array
void UpToLowArray(int* array, int size, int minValue, int maxValue) {
    if (size >= (maxValue - minValue + 1)) {
        for (int i = 0; i < size; i++) {
            array[i] = maxValue;
            if (minValue < maxValue)
                maxValue--;
        }
    }
    else {
        int left = maxValue - size + 1;
        int right = maxValue;
        for (int i = 0; i < size; i++) {
            array[i] = (double)rand() / RAND_MAX * (right - left) + left;
            right = array[i] - 1;
            if (left > size)
                left = right - size + 1;
            else
                left--;
        }
    }
}

// Generating a descending array
void LowToUpArray(int* array, int size, int minValue, int maxValue) {
    if (size >= (maxValue - minValue + 1)) {
        for (int i = 0; i < size; i++) {
            array[i] = minValue;
            if (minValue < maxValue)
                minValue++;
        }
    }
    else {
        int left = minValue;
        int right = maxValue - size + 1;
        for (int i = 0; i < size; i++) {
            array[i] = (double)rand() / RAND_MAX * (right - left) + left;
            left = array[i] + 1;
            right++;
        }
    }
}

// Сортировка выбором
vector<long int> selectionSort(int array[], int n, ofstream& outputFile) {
    vector<long int> params;
    int swaps = 0;
    long int comp = 0;
    for (int i = 0; i < n; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            comp++;
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        // Обмен текущего элемента с минимальным
        swap(array[i], array[minIndex]);
        swaps += 1;

        // Вывод массива после каждой итерации в файл
        if (n <= 15) {
            outputFile << "Selection Sort Iteration " << i + 1 << ": ";
            for (int k = 0; k < n; ++k) {
                outputFile << array[k] << " ";
            }
            outputFile << endl;
        }
    }
    params.push_back(swaps);
    params.push_back(comp);

    return params;
}

vector<long int> selectionSort_Down(int array[], int n, ofstream& outputFile) {
    vector<long int> params;
    int swaps = 0;
    long int comp = 0;
    for (int i = 0; i < n; ++i) {
        int maxIndex = i;
        for (int j = i + 1; j < n; ++j) {
            comp++;
            if (array[j] > array[maxIndex]) {
                maxIndex = j;
            }
        }
        // Обмен текущего элемента с минимальным
        swap(array[i], array[maxIndex]);
        swaps += 1;

        // Вывод массива после каждой итерации в файл
        if (n <= 15) {
            outputFile << "Selection Sort Iteration " << i + 1 << ": ";
            for (int k = 0; k < n; ++k) {
                outputFile << array[k] << " ";
            }
            outputFile << endl;
        }
    }
    params.push_back(swaps);
    params.push_back(comp);

    return params;
}


// Быстрая сортировка
vector<long int> quickSort(int array[], int low, int high, ofstream& outputFile) {
    vector<long int> paramsLeft;
    vector<long int> paramsRight;
    vector<long int> params;
    int swaps = 0;
    long int comp = 0;

    if (low < high) {
        int divider = array[high];
        int i = low - 1;

        // Разделение массива на две части: элементы, меньшие divider, и элементы, большие divider
        for (int j = low; j < high; ++j) {
            comp++;
            if (array[j] < divider) {
                ++i;
                swap(array[i], array[j]);
                swaps += 1;
            }
        }
        // Обмен опорного элемента с элементом, стоящим следующим после меньших элементов
        swap(array[i + 1], array[high]);
        swaps += 1;

        // Вывод массива после каждой итерации в файл
        if (n <= 15) {
            outputFile << "Quick Sort Iteration: ";
            for (int k = low; k <= high; ++k) {
                outputFile << array[k] << " ";
            }
            outputFile << endl;
        }

        int partitionIndex = i + 1;

        // Рекурсивно сортируем обе части массива
        paramsLeft = quickSort(array, low, partitionIndex - 1, outputFile);
        paramsRight = quickSort(array, partitionIndex + 1, high, outputFile);
    }

    if (!paramsLeft.empty()) {
        swaps += paramsLeft.front();
        comp += paramsLeft.back();
        paramsLeft.clear();
    }

    if (!paramsRight.empty()) {
        swaps += paramsRight.front();
        comp += paramsRight.back();
        paramsRight.clear();
    }

    params.push_back(swaps);
    params.push_back(comp);

    return params;
}

int main() {
    srand(time(0));

    int array[n];

    // Генерация и вывод исходного массива
    cout << "Original Array: ";
    ofstream originalFile("original.txt");
    originalFile << "Original Array: ";
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 100;  // Заполняем массив случайными числами от 0 до 99
        cout << array[i] << " ";
        originalFile << array[i] << " ";
    }
    cout << endl;
    originalFile.close();

    // Измерение времени для сортировки выбором
    auto startSelectionSort = high_resolution_clock::now();
    int arraySelection[n];
    copy(begin(array), end(array), begin(arraySelection));
    ofstream selectionFile("selection_sort.txt");
    vector<long int> selectionParams = selectionSort_Down(arraySelection, n, selectionFile);
    auto stopSelectionSort = high_resolution_clock::now();
    auto durationSelectionSort = duration_cast<microseconds>(stopSelectionSort - startSelectionSort);

    // Вывод отсортированного массива и времени выполнения сортировки выбором
    selectionFile << "Selection Sort Result: ";
    for (int i = 0; i < n; ++i) {
        selectionFile << arraySelection[i] << " ";
    }
    selectionFile << endl;
    selectionFile << "Time taken by Selection Sort: " << durationSelectionSort.count() << " microseconds" << endl;
    selectionFile << "Number of Swaps (Selection Sort): " << selectionParams[0] << endl;
    selectionFile << "Number of Comparisons (Selection Sort): " << selectionParams[1] << endl;
    selectionFile.close();

    // Измерение времени для быстрой сортировки
    auto startQuickSort = high_resolution_clock::now();
    int arrayQuick[n];
    copy(begin(array), end(array), begin(arrayQuick));
    ofstream quickFile("quickSort.txt");
    vector<long int> quickParams = quickSort(arrayQuick, 0, n - 1, quickFile);
    auto stopQuickSort = high_resolution_clock::now();
    auto durationQuickSort = duration_cast<microseconds>(stopQuickSort - startQuickSort);

    // Вывод отсортированного массива и времени выполнения быстрой сортировки
    quickFile << "Quick Sort Result: ";
    for (int i = 0; i < n; ++i) {
        quickFile << arrayQuick[i] << " ";
    }
    quickFile << endl;
    quickFile << "Time taken by Quick Sort: " << durationQuickSort.count() << " microseconds" << endl;
    quickFile << "Number of Swaps (Quick Sort): " << quickParams[0] << endl;
    quickFile << "Number of Comparisons (Quick Sort): " << quickParams[1] << endl;
    quickFile.close();

    return 0;
}