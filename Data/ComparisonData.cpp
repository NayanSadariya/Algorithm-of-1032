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
    double estimatedPosition;
    string algorithmUsed;
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
            return {probe, iterations, comparisons, 0.0, ""};

        comparisons++;
        if(arr[probe] < target)
            low = probe + 1;
        else
            high = probe - 1;
    }

    return {-1, iterations, comparisons, 0.0, ""};
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

    int iterations = 0;
    int comparisons = 0;

    while(low <= high)
    {
        iterations++;

        int probe =
            headPolicyProbe(low,high);

        comparisons++;
        if(arr[probe] == target)
            return {probe, iterations, comparisons, 0.0, ""};

        comparisons++;
        if(arr[probe] < target)
            low = probe + 1;
        else
            high = probe - 1;
    }

    return {-1, iterations, comparisons, 0.0, ""};
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

    if(estimatedPosition <= START_POLICY_THRESHOLD)
    {
        Result result =
            headOrientedSearchPolicy(arr, target);

        result.estimatedPosition = estimatedPosition;
        result.algorithmUsed = "Policy 2 (Head-Oriented Search)";

        return result;
    }

    if(estimatedPosition >= END_POLICY_THRESHOLD)
    {
        Result result =
            tailOrientedSearchPolicy(arr, target);

        result.estimatedPosition = estimatedPosition;
        result.algorithmUsed = "Policy 1 (Tail-Oriented Search)";

        return result;
    }

    Result result =
        binarySearchEngine(arr, target);

    result.estimatedPosition = estimatedPosition;
    result.algorithmUsed = "Policy 0 (Binary Search Engine)";

    return result;
}

//==================================================
// Demonstration
//==================================================

#include <iomanip>


struct TestCase{
    int arraySize;
    int target;
};

int main()
{
    vector<TestCase> tests={
        {100,1},{100,25},{100,50},{100,75},{100,100},
        {1000,10},{1000,250},{1000,500},{1000,750},{1000,1000},
        {10000,100},{10000,2500},{10000,5000},{10000,7500},{10000,10000}
    };

    int binaryWins=0, aoWins=0, ties=0;
    long long totalBinIter=0,totalBinComp=0,totalAoIter=0,totalAoComp=0;

    cout<<fixed<<setprecision(2);

    cout<<"====================================================================================================================\n";
    cout<<"                 Binary Search vs Algorithm OF 1032\n";
    cout<<"====================================================================================================================\n\n";

    cout<<left
        <<setw(6)<<"Test"
        <<setw(10)<<"Size"
        <<setw(10)<<"Target"
        <<setw(10)<<"Est(%)"
        <<setw(12)<<"BinIter"
        <<setw(12)<<"BinComp"
        <<setw(12)<<"AoIter"
        <<setw(12)<<"AoComp"
        <<setw(12)<<"Winner"
        <<"Policy\n";
    cout<<string(120,'-')<<"\n";

    for(size_t i=0;i<tests.size();++i){
        vector<int> arr;
        for(int j=1;j<=tests[i].arraySize;++j) arr.push_back(j);

        Result b=binarySearchEngine(arr,tests[i].target);
        Result a=policyManager(arr,tests[i].target);

        totalBinIter+=b.iterations;
        totalBinComp+=b.comparisons;
        totalAoIter+=a.iterations;
        totalAoComp+=a.comparisons;

        string winner;
        if(a.iterations<b.iterations){winner="Ao1032";aoWins++;}
        else if(a.iterations>b.iterations){winner="Binary";binaryWins++;}
        else{winner="Tie";ties++;}

        cout<<left
            <<setw(6)<<i+1
            <<setw(10)<<tests[i].arraySize
            <<setw(10)<<tests[i].target
            <<setw(10)<<a.estimatedPosition*100
            <<setw(12)<<b.iterations
            <<setw(12)<<b.comparisons
            <<setw(12)<<a.iterations
            <<setw(12)<<a.comparisons
            <<setw(12)<<winner
            <<a.algorithmUsed<<"\n";
    }

    cout<<"\n==================== SUMMARY ====================\n";
    cout<<"Binary Wins      : "<<binaryWins<<"\n";
    cout<<"Ao1032 Wins      : "<<aoWins<<"\n";
    cout<<"Ties             : "<<ties<<"\n\n";
    cout<<"Avg Bin Iter     : "<<(double)totalBinIter/tests.size()<<"\n";
    cout<<"Avg Ao Iter      : "<<(double)totalAoIter/tests.size()<<"\n";
    cout<<"Avg Bin Comp     : "<<(double)totalBinComp/tests.size()<<"\n";
    cout<<"Avg Ao Comp      : "<<(double)totalAoComp/tests.size()<<"\n";
    return 0;
}