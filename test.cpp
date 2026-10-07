#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

long findOptimumMinSum(vector<int>& centers) {
    int n = centers.size();
    if (n == 0) return 0;

    // Sort the centers
    sort(centers.begin(), centers.end());

    // Prefix sum array
    vector<long> prefixSum(n);
    prefixSum[0] = centers[0];
    for (int i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + centers[i];
    }

    // Function to calculate the sum of distances for a segment [l, r]
    auto sumDistances = [&](int l, int r, int pos) {
        long sum = 0;
        if (pos < centers[l]) {
            sum = prefixSum[r] - (l > 0 ? prefixSum[l - 1] : 0) - (r - l + 1) * pos;
        } else if (pos > centers[r]) {
            sum = (r - l + 1) * pos - (prefixSum[r] - (l > 0 ? prefixSum[l - 1] : 0));
        } else {
            int mid = lower_bound(centers.begin() + l, centers.begin() + r + 1, pos) - centers.begin();
            sum = (mid - l) * pos - (prefixSum[mid - 1] - (l > 0 ? prefixSum[l - 1] : 0));
            sum += (prefixSum[r] - prefixSum[mid - 1]) - (r - mid + 1) * pos;
        }
        return sum;
    };

    // Dynamic programming table
    // dp[i][j]: minimum sum of distances for the first j+1 centers using i warehouses
    vector<vector<long>> dp(3, vector<long>(n, LONG_MAX));

    // Base case: 0 warehouses (invalid, set to infinity)
    for (int j = 0; j < n; j++) {
        dp[0][j] = LONG_MAX;
    }

    // Fill the table for 1 warehouse
    for (int j = 0; j < n; j++) {
        dp[1][j] = sumDistances(0, j, centers[j]);
    }

    // Fill the table for 2 warehouses
    for (int j = 1; j < n; j++) {
        for (int k = 0; k < j; k++) {
            long sum = sumDistances(k + 1, j, centers[j]);
            dp[2][j] = min(dp[2][j], dp[1][k] + sum);
        }
    }

    return dp[2][n - 1];
}

int main() {
    vector<int> centers = {1, 2, 3};
    cout << findOptimumMinSum(centers) << endl; // Output: 1
    return 0;
}