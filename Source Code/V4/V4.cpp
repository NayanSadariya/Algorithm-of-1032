#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const double START_THRESHOLD = 0.30;
const double END_THRESHOLD = 0.70;

//--------------------------------------------------
// Selection Policy 1
//--------------------------------------------------

int selectionPolicy1(int low, int high, int originalSize)
{
    int remaining = high - low + 1;

    double progress = 1.0 - (double)remaining / originalSize;
    double jumpPercentage = 1.0 - progress;

    int jump = max(1, (int)(remaining * jumpPercentage));

    int current = low + jump;

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

    int current = low + jump;

    if (current > high)
        current = high;

    return current;
}

//--------------------------------------------------
// Policy 1 Search
//--------------------------------------------------

int policy1Search(const vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size() - 1;
    int originalSize = arr.size();

    while (low <= high)
    {
        int current = selectionPolicy1(low, high, originalSize);

        if (arr[current] == target)
            return current;

        if (arr[current] < target)
            low = current + 1;
        else
            high = current - 1;
    }

    return -1;
}

//--------------------------------------------------
// Policy 2 Search
//--------------------------------------------------

int policy2Search(const vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high)
    {
        int current = selectionPolicy2(low, high);

        if (arr[current] == target)
            return current;

        if (arr[current] < target)
            low = current + 1;
        else
            high = current - 1;
    }

    return -1;
}

//--------------------------------------------------
// Relative Position Estimation
//--------------------------------------------------

double estimatePosition(const vector<int>& arr, int target)
{
    if (arr.front() == arr.back())
        return 0.5;

    return (double)(target - arr.front()) /
           (arr.back() - arr.front());
}

//--------------------------------------------------
// Selection Policy 3
//--------------------------------------------------

int policy3Search(const vector<int>& arr, int target)
{
    double estimate = estimatePosition(arr, target);

    cout << "Estimated Position : "
         << estimate * 100
         << "%\n\n";

    if (estimate <= START_THRESHOLD)
    {
        cout << "Selected Policy : Policy 2\n";
        return policy2Search(arr, target);
    }

    if (estimate >= END_THRESHOLD)
    {
        cout << "Selected Policy : Policy 1\n";
        return policy1Search(arr, target);
    }

    cout << "Selected Policy : Policy 1\n";
    return policy1Search(arr, target);
}

//--------------------------------------------------
// Main
//--------------------------------------------------

int main()
{
    int n;
    cout << "Enter Array Size : ";
    cin >> n;

    vector<int> arr;

    for (int i = 1; i <= n; i++)
        arr.push_back(i);

    int target;

    cout << "Enter Target : ";
    cin >> target;

    int ans = policy3Search(arr, target);

    if (ans == -1)
        cout << "\nTarget Not Found\n";
    else
        cout << "\nTarget Found at Index : " << ans << '\n';

    return 0;
}