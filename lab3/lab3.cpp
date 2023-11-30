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

void LowToUpArray(int* array, int size, int minValue, int maxValue) {
    int i = 0;
    int k = minValue;
    while (i < size) {
        array[i] = k;
        if (k < maxValue) {
            k++;
        }
        else {
            k = maxValue;
        }
        i++;
    }
}

// Generating a descending array
void UpToLowArray(int* array, int size, int minValue, int maxValue) {
    int i = 0;
    int k = maxValue;
    while (i < size) {
        array[i] = k;
        if (k > minValue) {
            k--;
        }
        else {
            k = minValue;
        }
        i++;
    }
}

// Generating a random array
void RandomArray(int* array, int size, int minValue, int maxValue) {
    for (int i = 0; i < size; i++) {
        array[i] = (double)rand() / RAND_MAX * (maxValue - minValue) + minValue;
    }
}

// Сортировка выбором
int selectionSort(int array[], int n, long int& comp, ofstream& outputFile) {
    int swaps = 0;
    for (int i = 0; i < n; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            comp++;
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }

        // Обмен текущего элемента с минимальным
        if (i != minIndex) {
            swap(array[i], array[minIndex]);
            swaps += 1;
        }

        // Вывод массива после каждой итерации в файл
        if (n <= 15) {
            outputFile << "Selection Sort Iteration " << i + 1 << ": ";
            for (int k = 0; k < n; ++k) {
                outputFile << array[k] << " ";
            }
            outputFile << endl;
        }
    }
    return swaps;
}

// Быстрая сортировка
int quickSort(int array[], int low, int high, long int &comp, ofstream& outputFile) {
    int swaps = 0;
    if (low < high) {
        int divider = array[high];
        int i = low - 1;

        // Разделение массива на две части: элементы, меньшие divider, и элементы, большие divider
        for (int j = low; j < high; ++j) {
            comp++;
            if (array[j] <= divider) {
                ++i;
                if (i != j) {
                    swap(array[i], array[j]);
                    swaps += 1;
                }
            }
        }

        // Обмен опорного элемента с элементом, стоящим следующим после меньших элементов
        if (i + 1 != high) {
            swap(array[i + 1], array[high]);
            swaps += 1;
        }

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
        swaps += quickSort(array, low, partitionIndex - 1, comp, outputFile);
        swaps += quickSort(array, partitionIndex + 1, high, comp, outputFile);
    }
    return swaps;
}

int main() {
    srand(time(0));

    int array[n];

    // Генерация и вывод исходного массива
    ofstream originalFile("original.txt");
    originalFile << "Original Array: ";
    RandomArray(array, n, 0, 100);
    for (int i = 0; i < n; ++i) {
        originalFile << array[i] << " ";
    }
    cout << endl;
    originalFile.close();

    // Измерение времени для сортировки выбором
    long int compSelection = 0;
    int arraySelection[n];
    copy(begin(array), end(array), begin(arraySelection));
    auto startSelectionSort = high_resolution_clock::now();
    ofstream selectionFile("selection_sort.txt");
    int selectionSwaps = selectionSort(arraySelection, n, compSelection, selectionFile);
    auto stopSelectionSort = high_resolution_clock::now();
    auto durationSelectionSort = duration_cast<microseconds>(stopSelectionSort - startSelectionSort);

    // Вывод отсортированного массива и времени выполнения сортировки выбором
 /*   selectionFile << "Selection Sort Result: ";
    for (int i = 0; i < n; ++i) {
        selectionFile << arraySelection[i] << " ";
    }*/
    selectionFile << endl;
    selectionFile << "Time taken by Selection Sort: " << durationSelectionSort.count() << " microseconds" << endl;
    selectionFile << "Number of Swaps (Selection Sort): " << selectionSwaps << endl;
    selectionFile << "Number of Comparisons (Selection Sort): " << compSelection << endl;
    selectionFile.close();

    // Измерение времени для быстрой сортировки
    long int compQuick = 0;
    int arrayQuick[n];
    copy(begin(array), end(array), begin(arrayQuick));
    auto startQuickSort = high_resolution_clock::now();
    ofstream quickFile("quickSort.txt");
    int quickSwaps = quickSort(arrayQuick, 0, n - 1, compQuick, quickFile);
    auto stopQuickSort = high_resolution_clock::now();
    auto durationQuickSort = duration_cast<microseconds>(stopQuickSort - startQuickSort);

    // Вывод отсортированного массива и времени выполнения быстрой сортировки
    //quickFile << "Quick Sort Result: ";
    //for (int i = 0; i < n; ++i) {
    //    quickFile << arrayQuick[i] << " ";
    //}
    quickFile << endl;
    quickFile << "Time taken by Quick Sort: " << durationQuickSort.count() << " microseconds" << endl;
    quickFile << "Number of Swaps (Quick Sort): " << quickSwaps << endl;
    quickFile << "Number of Comparisons (Quick Sort): " << compQuick << endl;
    quickFile.close();

    return 0;
}