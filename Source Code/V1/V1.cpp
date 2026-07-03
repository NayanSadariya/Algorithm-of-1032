#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const double PARTITION_FACTOR = 0.75;
const int BINARY_THRESHOLD = 10;

int binarySearch(const vector<int>& arr, int low, int high, int target)
{
    while(low <= high)
    {
        int mid = low + (high - low) / 2;

        if(arr[mid] == target)
            return mid;

        if(arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int calculatePartition(int low, int high)
{
    int remaining = high - low + 1;

    int jump = max(1, (int)(remaining * PARTITION_FACTOR));

    return min(jump, remaining - 1);
}

int AdaptivePartitionSearch(const vector<int>& arr, int target)
{
    if(arr.empty())
        return -1;

    if(target < arr.front() || target > arr.back())
        return -1;

    int low = 0;
    int high = arr.size() - 1;

    while(low <= high)
    {
        int remaining = high - low + 1;

        if(remaining <= BINARY_THRESHOLD)
            return binarySearch(arr, low, high, target);

        int partition = calculatePartition(low, high);

        int current = low + partition;

        if(arr[current] == target)
            return current;

        if(arr[current] < target)
            low = current + 1;
        else
            high = current - 1;
    }

    return -1;
}

int main()
{
    vector<int> arr =
    {
        1,2,3,4,5,6,7,8,9,10,
        11,12,13,14,15,16,17,18,19,20,
        21,22,23,24,25,26,27,28,29,30
    };

    int target;

    cout << "Enter Target : ";
    cin >> target;

    int ans = AdaptivePartitionSearch(arr, target);

    if(ans == -1)
        cout << "Target Not Found\n";
    else
        cout << "Target Found at Index : " << ans << endl;

    return 0;
}