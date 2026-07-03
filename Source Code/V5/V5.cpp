#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

//--------------------------------------------------
// Thresholds
//--------------------------------------------------

const double START_THRESHOLD = 0.35;
const double END_THRESHOLD = 0.65;

//--------------------------------------------------
// Result Structure
//--------------------------------------------------

struct Result
{
    int index;
    int iterations;
    int comparisons;
};

//--------------------------------------------------
// Policy 0 - Binary Search
//--------------------------------------------------

Result binarySearch(const vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target)
            return {mid, 0, 0};

        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return {-1, 0, 0};
}

//--------------------------------------------------
// Selection Policy 1
//--------------------------------------------------

int selectionPolicy1(int low, int high, int originalSize)
{
    int remaining = high - low + 1;

    double progress = 1.0 - (double)remaining / originalSize;
    double jumpPercentage = 1.0 - progress;

    int jump = max(1, (int)(remaining * jumpPercentage));

    int current = low + jump - 1;

    if (current > high)
        current = high;

    return current;
}

//--------------------------------------------------
// Selection Policy 2
//--------------------------------------------------

int selectionPolicy2(int low, int high)
{
    int remaining = high - low + 1;

    int jump = max(1, (int)sqrt(remaining));

    int current = low + jump - 1;

    if (current > high)
        current = high;

    return current;
}

//--------------------------------------------------
// Policy 1 Search
//--------------------------------------------------

Result policy1Search(const vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size() - 1;
    int originalSize = arr.size();

    while (low <= high)
    {
        int current = selectionPolicy1(low, high, originalSize);

        if (arr[current] == target)
            return {current, 0, 0};

        if (arr[current] < target)
            low = current + 1;
        else
            high = current - 1;
    }

    return {-1, 0, 0};
}

//--------------------------------------------------
// Policy 2 Search
//--------------------------------------------------

Result policy2Search(const vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high)
    {
        int current = selectionPolicy2(low, high);

        if (arr[current] == target)
            return {current, 0, 0};

        if (arr[current] < target)
            low = current + 1;
        else
            high = current - 1;
    }

    return {-1, 0, 0};
}

//--------------------------------------------------
// Estimate Relative Position
//--------------------------------------------------

double estimatePosition(const vector<int>& arr, int target)
{
    if (arr.front() == arr.back())
        return 0.5;

    double estimate = (double)(target - arr.front()) /
                      (arr.back() - arr.front());

    estimate = max(0.0, min(1.0, estimate));

    return estimate;
}

//--------------------------------------------------
// Selection Policy 3
//--------------------------------------------------

Result policy3Search(const vector<int>& arr, int target)
{
    double estimate = estimatePosition(arr, target);

    if (estimate <= START_THRESHOLD)
        return policy2Search(arr, target);

    if (estimate >= END_THRESHOLD)
        return policy1Search(arr, target);

    return binarySearch(arr, target);
}

//--------------------------------------------------
// Main
//--------------------------------------------------

int main()
{
    int n;

    cout << "Enter Array Size: ";
    cin >> n;

    vector<int> arr;

    for (int i = 1; i <= n; i++)
        arr.push_back(i);

    int target;

    cout << "Enter Target: ";
    cin >> target;

    Result result = policy3Search(arr, target);

    if (result.index == -1)
        cout << "Target Not Found\n";
    else
        cout << "Target Found At Index: " << result.index << endl;

    return 0;
}