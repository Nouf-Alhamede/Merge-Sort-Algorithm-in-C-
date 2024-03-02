#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib> // random
#include <ctime> //time clac
#include <chrono>// time
#include <random>
#include <functional>
using namespace std;
using namespace std::chrono;

void merge(std::vector<int>& array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);

        merge(array, left, mid, right);
    }
}
 std::vector<int> generate_random_array(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 500);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

std::vector<int> generate_sorted_array(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

std::vector<int> generate_reverse_sorted_array(int size) {
    std::vector<int> arr(size);
    for (int i = size; i > 0; i--) {
        arr[size - i] = i;
    }
    return arr;
}


/*void measureTime(const std::string & operation, std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    float milliseconds = duration.count() / 1000.0f; // Convert to milliseconds as a float
    std::cout << operation << " execution time: " << milliseconds << " milliseconds" << std::endl;
}
*/


int main() {


    std::vector<double> timeBest;
    std::vector<double> timeAverage;
    std::vector<double> timeWorst;
    std::vector<int> arraySize = {800, 1000, 1300, 1400, 1500,3000 ,6000,8000,9000};
    //100, 200, 400, 800,1500,3000,6000,8000,9000,10000,11000,13000

    for (int i : arraySize) {
        std::vector<int> array = generate_random_array(i);
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(array, 0, array.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        float milliseconds = duration.count() / 1000.0f;
        timeBest.push_back(milliseconds);
        cout<< milliseconds<<"  milliseconbs"<< endl;

        array = generate_sorted_array(i);
        auto start1 = std::chrono::high_resolution_clock::now();
        mergeSort(array, 0, array.size() - 1);
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds durat = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
        float millisecond = durat.count() / 1000.0f;
        timeAverage.push_back(millisecond);
        cout<< millisecond<<"  milliseconbs"<< endl;

        array = generate_sorted_array(i);
        auto start2 = std::chrono::high_resolution_clock::now();
        mergeSort(array, 0, array.size() - 1);
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds dura = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
        float millisecon = dura.count() / 1000.0f;
        timeWorst.push_back(millisecon);
        cout<< millisecon<<"  milliseconbs"<< endl;

    }


    std::cout << "Array Size ------------- Merge Sort Execution time -------------" << std::endl;
    std::cout << "     Best Case     Average Case     Worst Case" << std::endl;
    std::cout << "---------- ----------- -------------- ------------" << std::endl;
    for (int i = 0; i < arraySize.size(); i++) {
        std::cout << arraySize[i] << "      " << timeBest[i] << "          " << timeAverage[i] << "          " << timeWorst[i] << std::endl;
    }

    return 0;

}

