#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// =====================================================
// Selection Policy 2
// Square-Root Future Cost Policy
// We are taking the remaining elements to calculate the future cost of the search. Then we use this future cost to determine how far to jump in the search space. The jump distance is calculated as the square root of the remaining elements, which allows for a more efficient search as we get closer to the target.
// =====================================================

int selectionPolicy2(int low, int high)
{
    int remaining = high - low + 1;

    // Adaptive Jump
    int jump = max(1, (int)sqrt(remaining));

    int current = low + jump;

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

    int low = 0;
    int high = arr.size() - 1;

    while(low <= high)
    {
        int current = selectionPolicy2(low, high);

        if(arr[current] == target)
            return current;

        if(arr[current] < target)
            low = current + 1;
        else
            high = current - 1;
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