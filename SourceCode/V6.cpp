#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

//==================================================
// Algorithm OF 1032 - Version 6
// An Adaptive Multi-Policy Search Framework
//==================================================

//--------------------------------------------------
// Framework Configuration
//--------------------------------------------------

constexpr double START_POLICY_THRESHOLD = 0.35;
constexpr double END_POLICY_THRESHOLD   = 0.65;

//--------------------------------------------------
// Result Structure
//--------------------------------------------------

struct Result
{
    int index;
    int iterations;
    int comparisons;
};

//==================================================
// Policy 0
// Binary Search Engine (BSE)
//==================================================

Result binarySearchEngine(const vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size() - 1;

    while(low <= high)
    {
        int mid = low + (high - low) / 2;

        if(arr[mid] == target)
            return {mid,0,0};

        if(arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return {-1,0,0};
}

//==================================================
// Tail-Oriented Search Policy (TOP)
//
// Formerly:
// Selection Policy 1
//==================================================

int tailPolicyProbe(int low,int high,int originalSize)
{
    int remaining = high - low + 1;

    double progress = 1.0 -
        (double)remaining / originalSize;

    double jumpPercentage = 1.0 - progress;

    int jump = max(
        1,
        (int)(remaining * jumpPercentage)
    );

    int probe = low + jump - 1;

    if(probe > high)
        probe = high;

    return probe;
}

Result tailOrientedSearchPolicy(
    const vector<int>& arr,
    int target)
{
    int low = 0;
    int high = arr.size()-1;
    int originalSize = arr.size();

    while(low <= high)
    {
        int probe =
            tailPolicyProbe(
                low,
                high,
                originalSize
            );

        if(arr[probe] == target)
            return {probe,0,0};

        if(arr[probe] < target)
            low = probe + 1;
        else
            high = probe - 1;
    }

    return {-1,0,0};
}

//==================================================
// Head-Oriented Search Policy (HOP)
//
// Formerly:
// Selection Policy 2
//==================================================

int headPolicyProbe(int low,int high)
{
    int remaining = high - low + 1;

    int jump =
        max(
            1,
            (int)sqrt(remaining)
        );

    int probe = low + jump - 1;

    if(probe > high)
        probe = high;

    return probe;
}

Result headOrientedSearchPolicy(
    const vector<int>& arr,
    int target)
{
    int low = 0;
    int high = arr.size()-1;

    while(low <= high)
    {
        int probe =
            headPolicyProbe(low,high);

        if(arr[probe] == target)
            return {probe,0,0};

        if(arr[probe] < target)
            low = probe + 1;
        else
            high = probe - 1;
    }

    return {-1,0,0};
}
//==================================================
// Relative Position Estimator (RPE)
//
// Interpolation-based estimator
//==================================================

double relativePositionEstimator(
    const vector<int>& arr,
    int target)
{
    if(arr.front() == arr.back())
        return 0.5;

    double estimate =
        (double)(target - arr.front()) /
        (arr.back() - arr.front());

    estimate =
        max(
            0.0,
            min(1.0,estimate)
        );

    return estimate;
}

//==================================================
// Policy Manager
//
// Decides which search policy should execute.
//==================================================

Result policyManager(
    const vector<int>& arr,
    int target)
{
    double estimatedPosition =
        relativePositionEstimator(
            arr,
            target
        );

    if(estimatedPosition
        <= START_POLICY_THRESHOLD)
    {
        return headOrientedSearchPolicy(
            arr,
            target
        );
    }

    if(estimatedPosition
        >= END_POLICY_THRESHOLD)
    {
        return tailOrientedSearchPolicy(
            arr,
            target
        );
    }

    return binarySearchEngine(
        arr,
        target
    );
}

//==================================================
// Demonstration
//==================================================

int main()
{
    int n;

    cout << "Enter Array Size : ";
    cin >> n;

    vector<int> arr;

    for(int i=1;i<=n;i++)
        arr.push_back(i);

    int target;

    cout << "Enter Target : ";
    cin >> target;

    Result result =
        policyManager(arr,target);

    if(result.index==-1)
        cout<<"Target Not Found\n";
    else
        cout<<"Target Found At Index : "
            <<result.index<<endl;

    return 0;
}