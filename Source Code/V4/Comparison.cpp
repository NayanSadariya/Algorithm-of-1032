#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const double START_THRESHOLD = 0.50;
const double END_THRESHOLD = 0.50;

struct Result
{
    int index;
    int iterations;
    int comparisons;
};

//--------------------------------------------------
// Binary Search
//--------------------------------------------------

Result binarySearch(const vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size() - 1;

    int iterations = 0;
    int comparisons = 0;

    while (low <= high)
    {
        iterations++;

        int mid = low + (high - low) / 2;

        comparisons++;
        if (arr[mid] == target)
            return {mid, iterations, comparisons};

        comparisons++;

        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return {-1, iterations, comparisons};
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

Result policy1Search(const vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size() - 1;
    int originalSize = arr.size();

    int iterations = 0;
    int comparisons = 0;

    while (low <= high)
    {
        iterations++;

        int current = selectionPolicy1(low, high, originalSize);

        comparisons++;
        if (arr[current] == target)
            return {current, iterations, comparisons};

        comparisons++;

        if (arr[current] < target)
            low = current + 1;
        else
            high = current - 1;
    }

    return {-1, iterations, comparisons};
}

//--------------------------------------------------
// Policy 2 Search
//--------------------------------------------------

Result policy2Search(const vector<int>& arr, int target)
{
    int low = 0;
    int high = arr.size() - 1;

    int iterations = 0;
    int comparisons = 0;

    while (low <= high)
    {
        iterations++;

        int current = selectionPolicy2(low, high);

        comparisons++;
        if (arr[current] == target)
            return {current, iterations, comparisons};

        comparisons++;

        if (arr[current] < target)
            low = current + 1;
        else
            high = current - 1;
    }

    return {-1, iterations, comparisons};
}

//--------------------------------------------------
// Estimate Relative Position
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

Result policy3Search(const vector<int>& arr, int target)
{
    double estimate = estimatePosition(arr, target);

    cout << "\n=====================================\n";
    cout << "Selection Policy 3\n";
    cout << "=====================================\n";

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

    Result binary = binarySearch(arr, target);
    Result adaptive = policy3Search(arr, target);

    cout << "\n\n===========================================\n";
    cout << "        Algorithm OF 1032 Analysis\n";
    cout << "===========================================\n";

    cout << "\nArray Size : " << n << endl;
    cout << "Target     : " << target << endl;

    cout << "\n-------------------------------------------\n";
    cout << "Binary Search\n";
    cout << "-------------------------------------------\n";

    cout << "Found Index : " << binary.index << endl;
    cout << "Iterations  : " << binary.iterations << endl;
    cout << "Comparisons : " << binary.comparisons << endl;

    cout << "\n-------------------------------------------\n";
    cout << "Algorithm OF 1032\n";
    cout << "-------------------------------------------\n";

    cout << "Found Index : " << adaptive.index << endl;
    cout << "Iterations  : " << adaptive.iterations << endl;
    cout << "Comparisons : " << adaptive.comparisons << endl;

    cout << "\n-------------------------------------------\n";
    cout << "Analysis\n";
    cout << "-------------------------------------------\n";

    if (binary.index == adaptive.index)
        cout << "Correct Result        : YES\n";
    else
        cout << "Correct Result        : NO\n";

    int iterationDifference =
        adaptive.iterations - binary.iterations;

    int comparisonDifference =
        adaptive.comparisons - binary.comparisons;

    cout << "Iteration Difference  : "
         << iterationDifference << endl;

    cout << "Comparison Difference : "
         << comparisonDifference << endl;

    cout << "\nWinner (Iterations)   : ";

    if (adaptive.iterations < binary.iterations)
        cout << "Algorithm OF 1032";
    else if (adaptive.iterations > binary.iterations)
        cout << "Binary Search";
    else
        cout << "Tie";

    cout << endl;

    cout << "Winner (Comparisons)  : ";

    if (adaptive.comparisons < binary.comparisons)
        cout << "Algorithm OF 1032";
    else if (adaptive.comparisons > binary.comparisons)
        cout << "Binary Search";
    else
        cout << "Tie";

    cout << "\n\n===========================================\n";

    return 0;
}