#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

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
    double estimatedPosition;
    string algorithmUsed;
};

//--------------------------------------------------
// Test Case Structure
//--------------------------------------------------

struct TestCase
{
    int arraySize;
    int target;
};

//==================================================
// Policy 0
// Binary Search Engine (BSE)
//==================================================

Result binarySearchEngine(const vector<int>& arr, int target)
{
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
            return {mid, iterations, comparisons, 0.0, ""};

        comparisons++;
        if(arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return {-1, iterations, comparisons, 0.0, ""};
}

//==================================================
// Tail-Oriented Search Policy (TOP)
//==================================================

int tailPolicyProbe(int low,int high,int originalSize)
{
    int remaining = high - low + 1;

    double progress =
        1.0 - (double)remaining / originalSize;

    double jumpPercentage =
        1.0 - progress;

    int jump =
        max(
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

    int iterations = 0;
    int comparisons = 0;

    while(low <= high)
    {
        iterations++;

        int probe =
            tailPolicyProbe(
                low,
                high,
                originalSize
            );

        comparisons++;
        if(arr[probe] == target)
            return {probe,iterations,comparisons,0.0,""};

        comparisons++;
        if(arr[probe] < target)
            low = probe + 1;
        else
            high = probe - 1;
    }

    return {-1,iterations,comparisons,0.0,""};
}

//==================================================
// Head-Oriented Search Policy (HOP)
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

    int iterations = 0;
    int comparisons = 0;

    while(low <= high)
    {
        iterations++;

        int probe =
            headPolicyProbe(low,high);

        comparisons++;
        if(arr[probe] == target)
            return {probe,iterations,comparisons,0.0,""};

        comparisons++;
        if(arr[probe] < target)
            low = probe + 1;
        else
            high = probe - 1;
    }

    return {-1,iterations,comparisons,0.0,""};
}

//==================================================
// Relative Position Estimator (RPE)
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

    if(estimatedPosition <= START_POLICY_THRESHOLD)
    {
        Result result =
            headOrientedSearchPolicy(arr,target);

        result.estimatedPosition =
            estimatedPosition;

        result.algorithmUsed =
            "Policy 2 (Head-Oriented Search)";

        return result;
    }

    if(estimatedPosition >= END_POLICY_THRESHOLD)
    {
        Result result =
            tailOrientedSearchPolicy(arr,target);

        result.estimatedPosition =
            estimatedPosition;

        result.algorithmUsed =
            "Policy 1 (Tail-Oriented Search)";

        return result;
    }

    Result result =
        binarySearchEngine(arr,target);

    result.estimatedPosition =
        estimatedPosition;

    result.algorithmUsed =
        "Policy 0 (Binary Search Engine)";

    return result;
}
//==================================================
// Experimental Evaluation
//==================================================

int main()
{
    vector<TestCase> tests =
    {
        {100,1},
        {100,25},
        {100,50},
        {100,75},
        {100,100},

        {1000,10},
        {1000,250},
        {1000,500},
        {1000,750},
        {1000,1000},

        {10000,100},
        {10000,2500},
        {10000,5000},
        {10000,7500},
        {10000,10000}
    };

    int passed = 0;

    int headPolicyCount = 0;
    int binaryPolicyCount = 0;
    int tailPolicyCount = 0;

    long long totalIterations = 0;
    long long totalComparisons = 0;

    cout << fixed << setprecision(2);

    cout << "\n===============================================================================================\n";
    cout << "                     Algorithm OF 1032 - Experimental Evaluation\n";
    cout << "===============================================================================================\n\n";

    cout << left
         << setw(6)  << "Test"
         << setw(12) << "Size"
         << setw(10) << "Target"
         << setw(12) << "Expected"
         << setw(13) << "Estimated"
         << setw(34) << "Algorithm"
         << setw(12) << "Iter"
         << setw(12) << "Comp"
         << "Correct\n";

    cout << string(120,'-') << "\n";

    for(size_t i=0;i<tests.size();i++)
    {
        int size = tests[i].arraySize;
        int target = tests[i].target;

        vector<int> arr;

        for(int j=1;j<=size;j++)
            arr.push_back(j);

        Result result =
            policyManager(arr,target);

        double expectedPosition =
            (double)target /
            size * 100.0;

        bool correct =
            (result.index == target-1);

        if(correct)
            passed++;

        totalIterations += result.iterations;
        totalComparisons += result.comparisons;

        if(result.algorithmUsed.find("Policy 0") != string::npos)
            binaryPolicyCount++;

        if(result.algorithmUsed.find("Policy 1") != string::npos)
            tailPolicyCount++;

        if(result.algorithmUsed.find("Policy 2") != string::npos)
            headPolicyCount++;

        cout << left
             << setw(6)  << i+1
             << setw(12) << size
             << setw(10) << target
             << setw(12) << expectedPosition
             << setw(13) << result.estimatedPosition*100
             << setw(34) << result.algorithmUsed
             << setw(12) << result.iterations
             << setw(12) << result.comparisons
             << (correct ? "Yes" : "No")
             << endl;
    }

    cout << "\n===============================================================================================\n";
    cout << "Summary\n";
    cout << "===============================================================================================\n\n";
    
        cout << "Total Test Cases     : "
         << tests.size() << "\n";

    cout << "Passed               : "
         << passed << "\n";

    cout << "Failed               : "
         << tests.size() - passed << "\n\n";

    cout << "Policy Usage\n";
    cout << "------------\n";

    cout << "Policy 0 (Binary Search Engine)      : "
         << binaryPolicyCount << "\n";

    cout << "Policy 1 (Tail-Oriented Search)      : "
         << tailPolicyCount << "\n";

    cout << "Policy 2 (Head-Oriented Search)      : "
         << headPolicyCount << "\n\n";

    cout << "Average Iterations   : "
         << (double)totalIterations / tests.size()
         << "\n";

    cout << "Average Comparisons  : "
         << (double)totalComparisons / tests.size()
         << "\n";

    cout << "\n===============================================================================================\n";
    cout << "Experimental Evaluation Completed Successfully\n";
    cout << "===============================================================================================\n";

    return 0;
}