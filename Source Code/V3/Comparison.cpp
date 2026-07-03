#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

//==================================================
// Result Structure
//==================================================

struct Result
{
    int index;
    int iterations;
    int comparisons;
    long long time; // microseconds
};

//==================================================
// Binary Search
//==================================================

Result binarySearch(const vector<int>& arr, int target)
{
    auto start = high_resolution_clock::now();

    int low = 0;
    int high = arr.size() - 1;

    int iterations = 0;
    int comparisons = 0;

    while(low <= high)
    {
        iterations++;

        int mid = low + (high - low) / 2;

        comparisons++;
        if(arr[mid] == target)
        {
            auto stop = high_resolution_clock::now();

            return {
                mid,
                iterations,
                comparisons,
                duration_cast<microseconds>(stop - start).count()
            };
        }

        comparisons++;
        if(arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    auto stop = high_resolution_clock::now();

    return {
        -1,
        iterations,
        comparisons,
        duration_cast<microseconds>(stop - start).count()
    };
}

//==================================================
// Selection Policy 1
//==================================================

int selectionPolicy1(int low, int high, int originalSize)
{
    int remaining = high - low + 1;

    double progress =
        1.0 - ((double)remaining / originalSize);

    double jumpPercentage =
        1.0 - progress;

    int jump =
        max(1, (int)(remaining * jumpPercentage));

    int current = low + jump;

    if(current > high)
        current = high;

    return current;
}

//==================================================
// Policy 1 Search
//==================================================

Result policy1Search(const vector<int>& arr, int target)
{
    auto start = high_resolution_clock::now();

    int low = 0;
    int high = arr.size() - 1;
    int originalSize = arr.size();

    int iterations = 0;
    int comparisons = 0;

    while(low <= high)
    {
        iterations++;

        int current =
            selectionPolicy1(low, high, originalSize);

        comparisons++;
        if(arr[current] == target)
        {
            auto stop = high_resolution_clock::now();

            return {
                current,
                iterations,
                comparisons,
                duration_cast<microseconds>(stop - start).count()
            };
        }

        comparisons++;
        if(arr[current] < target)
            low = current + 1;
        else
            high = current - 1;
    }

    auto stop = high_resolution_clock::now();

    return {
        -1,
        iterations,
        comparisons,
        duration_cast<microseconds>(stop - start).count()
    };
}

//==================================================
// Selection Policy 2
//==================================================

int selectionPolicy2(int low, int high)
{
    int remaining = high - low + 1;

    int jump =
        max(1, (int)sqrt(remaining));

    int current = low + jump;

    if(current > high)
        current = high;

    return current;
}

//==================================================
// Policy 2 Search
//==================================================

Result policy2Search(const vector<int>& arr, int target)
{
    auto start = high_resolution_clock::now();

    int low = 0;
    int high = arr.size() - 1;

    int iterations = 0;
    int comparisons = 0;

    while(low <= high)
    {
        iterations++;

        int current =
            selectionPolicy2(low, high);

        comparisons++;
        if(arr[current] == target)
        {
            auto stop = high_resolution_clock::now();

            return {
                current,
                iterations,
                comparisons,
                duration_cast<microseconds>(stop - start).count()
            };
        }

        comparisons++;
        if(arr[current] < target)
            low = current + 1;
        else
            high = current - 1;
    }

    auto stop = high_resolution_clock::now();

    return {
        -1,
        iterations,
        comparisons,
        duration_cast<microseconds>(stop - start).count()
    };
}

//==================================================
// Print Result
//==================================================

void printResult(string name, Result r)
{
    cout << "\n=====================================\n";
    cout << name << endl;
    cout << "-------------------------------------\n";
    cout << "Index        : " << r.index << endl;
    cout << "Iterations   : " << r.iterations << endl;
    cout << "Comparisons  : " << r.comparisons << endl;
    cout << "Time (us)    : " << r.time << endl;
}

//==================================================
// Main
//==================================================

int main()
{
    int n;

    cout << "Enter Array Size : ";
    cin >> n;

    vector<int> arr;

    for(int i = 1; i <= n; i++)
        arr.push_back(i);

    int target;

    cout << "Enter Target : ";
    cin >> target;

    Result binary = binarySearch(arr, target);
    Result policy1 = policy1Search(arr, target);
    Result policy2 = policy2Search(arr, target);

    printResult("Binary Search", binary);
    printResult("Selection Policy 1", policy1);
    printResult("Selection Policy 2", policy2);

    cout << "\n=====================================\n";
    cout << "Correctness Check\n";
    cout << "=====================================\n";

    if(binary.index == policy1.index &&
       binary.index == policy2.index)
    {
        cout << "All algorithms returned the same result.\n";
    }
    else
    {
        cout << "Mismatch detected!\n";
    }

    return 0;
}