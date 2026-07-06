#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// =====================================================
// Selection Policy 1
// Progress-Based Quadratic Policy
// We are taking remaining and the original size to calculate the progress of the search. Then we use this progress to determine how far to jump in the search space. The jump distance is calculated as a percentage of the remaining elements, which allows for a more efficient search as we get closer to the target.
//How Far to the search we are?
// =====================================================

int selectionPolicy1(int low, int high, int originalSize)
{
    int remaining = high - low + 1;

    // Search Progress (0.0 -> 1.0)
    double progress = 1.0 - ((double)remaining / originalSize);

    // Jump Percentage
    double jumpPercentage = 1.0 - progress;

    // Jump Distance
    int jump = max(1, (int)(remaining * jumpPercentage));

    // Current Index
    int current = low + jump;

    // Prevent Out of Bounds
    if(current > high)
        current = high;

    return current;
}

// =====================================================
// Algorithm OF 1032
// =====================================================

int AlgorithmOF1032(const vector<int>& arr, int target)
{
    if(arr.empty())
        return -1;

    if(target < arr.front() || target > arr.back())
        return -1;

    int originalSize = arr.size();

    int low = 0;
    int high = originalSize - 1;

    while(low <= high)
    {
        int current = selectionPolicy1(low, high, originalSize);

        if(arr[current] == target)
            return current;

        if(arr[current] < target)
        {
            low = current + 1;
        }
        else
        {
            high = current - 1;
        }
    }

    return -1;
}

// =====================================================
// Main
// =====================================================

int main()
{
    vector<int> arr;

    for(int i = 1; i <= 10000000; i++)
        arr.push_back(i);

    int target;

    cout << "Enter Target : ";
    cin >> target;

    int ans = AlgorithmOF1032(arr, target);

    if(ans == -1)
        cout << "\nTarget Not Found\n";
    else
        cout << "\nTarget Found at Index : " << ans << endl;

    return 0;
}