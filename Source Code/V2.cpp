#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// ======================================================
// Constants
// ======================================================

const double PARTITION_FACTOR = 0.75;

// ======================================================
// Binary Search
// ======================================================

int binarySearch(const vector<int>& arr, int low, int high, int target)
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

// ======================================================
// Calculate Current Position
// ======================================================

int calculateCurrent(int low, int high)
{
    int remaining = high - low + 1;

    int jump = max(1, (int)(remaining * PARTITION_FACTOR));

    int current = low + jump;

    if (current > high)
        current = high;

    return current;
}

// ======================================================
// Decide Whether To Switch To Binary Search
// ======================================================

bool shouldUseBinary(int low, int high)
{
    int blockSize = high - low + 1;

    if (blockSize <= 1)
        return true;

    // Estimated comparisons if we stop now
    double binaryCost = log2(blockSize);

    // Estimated block after one more partition
    int nextBlock = max(1, (int)(blockSize * (1.0 - PARTITION_FACTOR)));

    // One comparison for partition + binary afterwards
    double continueCost = 1.0 + log2(nextBlock);

    return binaryCost <= continueCost;
}

// ======================================================
// Algorithm OF 1032
// ======================================================

int AlgorithmOF1032(const vector<int>& arr, int target)
{
    if (arr.empty())
        return -1;

    if (target < arr.front() || target > arr.back())
        return -1;

    int low = 0;
    int high = arr.size() - 1;

    while (low <= high)
    {
        if (shouldUseBinary(low, high))
        {
            return binarySearch(arr, low, high, target);
        }

        int current = calculateCurrent(low, high);

        if (arr[current] == target)
            return current;

        if (arr[current] < target)
        {
            low = current + 1;
        }
        else
        {
            high = current;
        }
    }

    return -1;
}

// ======================================================
// Main
// ======================================================

int main()
{
    vector<int> arr;

    for (int i = 1; i <= 100; i++)
        arr.push_back(i);

    int target;

    cout << "Enter Target : ";
    cin >> target;

    int ans = AlgorithmOF1032(arr, target);

    if (ans == -1)
        cout << "\nTarget Not Found\n";
    else
        cout << "\nTarget Found at Index : " << ans << endl;

    return 0;
}