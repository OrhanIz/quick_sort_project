#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib> // rand() için
#include <ctime>   // clock() için

// Partition işlemi
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low]; // Pivot elemanı
    int left = low + 1;
    int right = high;

    while (left <= right) {
        while (left <= right && arr[left] <= pivot) left++;
        while (left <= right && arr[right] >= pivot) right--;
        if (left < right) std::swap(arr[left], arr[right]);
    }
    std::swap(arr[low], arr[right]);
    return right;
}

// Pivot seçme stratejileri
void selectPivot(std::vector<int>& arr, int low, int high, const std::string& strategy) {
    if (strategy == "first") {
        // İlk eleman pivot olarak seçili, işlem yapılmaz.
    }
    else if (strategy == "middle") {
        int mid = low + (high - low) / 2;
        std::swap(arr[low], arr[mid]); // Ortadaki eleman pivot olarak seçildi.
    }
    else if (strategy == "random") {
        int randomIndex = low + rand() % (high - low + 1);
        std::swap(arr[low], arr[randomIndex]); // Rastgele bir eleman pivot olarak seçildi.
    }
    else if (strategy == "median") {
        int mid = low + (high - low) / 2;
        std::vector<std::pair<int, int>> candidates = { {arr[low], low}, {arr[mid], mid}, {arr[high], high} };
        std::sort(candidates.begin(), candidates.end());
        std::swap(arr[low], arr[candidates[1].second]); // Medyan pivot olarak seçildi.
    }
}

// QuickSort fonksiyonu
void quickSort(std::vector<int>& arr, int low, int high, const std::string& strategy) {
    if (low < high) {
        selectPivot(arr, low, high, strategy);
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1, strategy);
        quickSort(arr, pivotIndex + 1, high, strategy);
    }
}

// Zaman ölçümü fonksiyonu
double measureTime(std::vector<int>& arr, const std::string& strategy) {
    clock_t start = clock();
    quickSort(arr, 0, arr.size() - 1, strategy);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

// Test verileri oluşturma fonksiyonları
std::vector<int> generateRandomVector(int size) {
    std::vector<int> vec(size);
    for (int& x : vec) x = rand() % 100000; 
    return vec;
}

std::vector<int> generateSortedVector(int size) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i) vec[i] = i;
}

std::vector<int> generateReverseSortedVector(int size) {
    std::vector<int> vec(size);
    for (int i = 0; i < size; ++i) vec[i] = size - i; 
}

int main() {
    srand(time(0)); 
    // Test için boyutlar, stratejiler ve veri türleri
    std::vector<int> sizes = { 10000, 20000, 30000, 40000, 50000 };
    std::vector<std::string> strategies = { "first", "middle", "random", "median" };
    std::vector<std::string> dataTypes = { "random", "sorted", "reverse" };

    // Stratejiye ve veri türüne göre ölçümleri yap
    for (const std::string& strategy : strategies) {
        std::cout << "Pivot Strategy: " << strategy << "\n";
        for (const int size : sizes) {
            for (const std::string& dataType : dataTypes) {
                std::vector<int> data;
                if (dataType == "random") data = generateRandomVector(size);
                else if (dataType == "sorted") data = generateSortedVector(size);
                else if (dataType == "reverse") data = generateReverseSortedVector(size);

                double timeTaken = measureTime(data, strategy);
                std::cout << "Size: " << size
                    << ", Data Type: " << dataType
                    << ", Time: " << timeTaken << " seconds\n";
            }
        }
        std::cout << "---------------------------------------\n";
    }

    return 0;
}
