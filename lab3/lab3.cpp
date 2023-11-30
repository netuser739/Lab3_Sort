#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <fstream>
#include <chrono>

using namespace std;
using namespace chrono;

const int n = 1000;

// ������� ��� ������ ���� ��������� �������
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Generating an increasing array
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

// ���������� �������
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
        // ����� �������� �������� � �����������
        if (i != minIndex) {
            swap(array[i], array[minIndex]);
            swaps += 1;
        }

        // ����� ������� ����� ������ �������� � ����
 /*       if (n <= 14) {
            outputFile << "Selection Sort Iteration " << i + 1 << ": ";
            for (int k = 0; k < n; ++k) {
                outputFile << array[k] << " ";
            }
            outputFile << endl;
        }*/
    }
    params.push_back(swaps);
    params.push_back(comp);

    return params;
}

// ������� ����������
vector<long int> quickSort(int array[], int low, int high, ofstream& outputFile) {
    vector<long int> paramsLeft;
    vector<long int> paramsRight;
    vector<long int> params;
    int swaps = 0;
    long int comp = 0;

    if (low < high) {
        int divider = array[high];
        int i = low - 1;

        // ���������� ������� �� ��� �����: ��������, ������� divider, � ��������, ������� divider
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
        // ����� �������� �������� � ���������, ������� ��������� ����� ������� ���������
        if (i + 1 != high) {
            swap(array[i + 1], array[high]);
            swaps += 1;
        }

        // ����� ������� ����� ������ �������� � ����
      /*  if (sizeof(array) / 4 <= 14) {
            outputFile << "Quick Sort Iteration: ";
            for (int k = low; k <= high; ++k) {
                outputFile << array[k] << " ";
            }
            outputFile << endl;
        }*/

        int partitionIndex = i + 1;

        // ���������� ��������� ��� ����� �������
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
    
    // ��������� � ����� ��������� �������
    ofstream originalFile("original.txt");
    originalFile << "Original Array: ";
    LowToUpArray(array, n, 0, 100);
    for (int i = 0; i < n; ++i) {
        originalFile << array[i] << " ";
    }
    originalFile.close();
    ofstream file("data.txt");

    // ��������� ������� ��� ���������� �������
    int arraySelection[n];
    copy(begin(array), end(array), begin(arraySelection));
    auto startSelectionSort = high_resolution_clock::now();
    vector<long int> selectionParams = selectionSort(arraySelection, n, file);
    auto stopSelectionSort = high_resolution_clock::now();
    auto durationSelectionSort = duration_cast<microseconds>(stopSelectionSort - startSelectionSort);

    // ����� ���������������� ������� � ������� ���������� ���������� �������
    //selectionFile << "Selection Sort Result: ";
    //for (int i = 0; i < n; ++i) {
    //    selectionFile << arraySelection[i] << " ";
    //}
    //selectionFile << endl;
    file << "Time taken by Selection Sort: " << durationSelectionSort.count() << " microseconds" << endl;
    file << "Number of Swaps (Selection Sort): " << selectionParams[0] << endl;
    file << "Number of Comparisons (Selection Sort): " << selectionParams[1] << endl;

    // ��������� ������� ��� ������� ����������
    int arrayQuick[n];
    copy(begin(array), end(array), begin(arrayQuick));
    auto startQuickSort = high_resolution_clock::now();
    vector<long int> quickParams = quickSort(arrayQuick, 0, n - 1, file);
    auto stopQuickSort = high_resolution_clock::now();
    auto durationQuickSort = duration_cast<microseconds>(stopQuickSort - startQuickSort);

    // ����� ���������������� ������� � ������� ���������� ������� ����������
    //quickFile << "Quick Sort Result: ";
    //for (int i = 0; i < n; ++i) {
    //    quickFile << arrayQuick[i] << " ";
    //}
    //quickFile << endl;
    file << "Time taken by Quick Sort: " << durationQuickSort.count() << " microseconds" << endl;
    file << "Number of Swaps (Quick Sort): " << quickParams[0] << endl;
    file << "Number of Comparisons (Quick Sort): " << quickParams[1] << endl;
    file.close();

    return 0;
}

//int main() {
//    srand(time(0));
//
//    void(*genArr[])(int*, int, int, int) = { LowToUpArray, UpToLowArray, RandomArray };
//    ofstream file("data.txt");  
//
//    steady_clock::time_point startTimeSelection;
//    steady_clock::time_point stopTimeSelection;
//    microseconds durationTimeSelection;
//
//    steady_clock::time_point startTimeQuick;
//    steady_clock::time_point stopTimeQuick;
//    microseconds durationTimeQuick;
//
//    file << "Array Type\t\tTime\t\t\tSwaps\t\tComparations" << endl;
//    file << "\t\t\tSelect\tQuick\tSelect\tQuick\tSelect\tQuick\t" << endl;
//
//    for (int i = 0; i < 3; i++) {
//        int array[n];
//
//        // Array generating
//        genArr[i](array, n, 0, 100);
//
//        // ��������� ������� ��� ���������� �������
//        int arraySelection[n];
//        int arrayQuick[n];
//        copy(begin(array), end(array), begin(arraySelection));
//        startTimeSelection = high_resolution_clock::now();
//        vector<long int> selectionParams = selectionSort(arraySelection, n, file);
//        stopTimeSelection = high_resolution_clock::now();
//        durationTimeSelection = duration_cast<microseconds>(stopTimeSelection - startTimeSelection);
//
//
//        // ��������� ������� ��� ���������� �������
//        copy(begin(array), end(array), begin(arrayQuick));
//        startTimeQuick = high_resolution_clock::now();
//        vector<long int> quickParams = quickSort(arrayQuick, 0, n - 1, file);
//        stopTimeQuick = high_resolution_clock::now();
//        durationTimeQuick = duration_cast<microseconds>(stopTimeQuick - startTimeQuick);
//
//        switch (i)
//        {
//        case 0:
//            file << "Icrease\t\t";
//            break;
//        case 1:
//            file << "Decrease\t";
//            break;
//        case 2:
//            file << "Random\t\t";
//            break;
//        }
//
//        file << durationTimeSelection.count();
//        file << "\t\t" << durationTimeQuick.count();
//        file << "\t\t" << selectionParams[0];
//        file << "\t\t" << quickParams[0];
//        file << "\t\t" << selectionParams[1];
//        file << "\t\t" << quickParams[1] << endl;
//
//        selectionParams.clear();
//        quickParams.clear();
//    }
//    file.close();
//
//    return 0;
//}