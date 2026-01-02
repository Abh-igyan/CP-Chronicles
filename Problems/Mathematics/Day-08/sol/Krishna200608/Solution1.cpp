/*
Problem: Sasha and the Apartment Purchase
Link: https://codeforces.com/problemset/problem/2098/B
Author: Krishna Sikheriya (Krishna200608)

Short Problem Statement:
There are n bars at positions a_1, ..., a_n. Sasha wants to buy a house at x.
x is suitable if we can close at most k bars such that x minimizes the sum of distances 
to the remaining bars (i.e., x is a median of the remaining bars).
Find the number of suitable integer positions for x.

Approach:
1. Sort the array of bar positions.
2. The point minimizing the sum of distances for a set of points is their median.
3. If the number of remaining bars (sz) is odd, the median is unique (1 point).
4. If sz is even, any point in the interval between the two middle elements is optimal.
5. To maximize options, we prefer even-sized subsets.
   - If k=0 and n is odd, we must keep all n (odd). Answer is 1.
   - Otherwise, calculate the target even size 'sz'.
     If (n-k) is even, sz = n-k.
     If (n-k) is odd, we keep one more bar (remove k-1), so sz = n-k+1.
6. For a fixed even size 'sz', considering all subsets of this size (subsequences) is complex, 
   but since we want the range of medians, we essentially look at the "leftmost" valid median 
   and the "rightmost" valid median achievable by removing k bars.
   - The range of valid medians is [ a[sz/2 - 1], a[n - sz/2] ] (using 0-based indexing).
7. The answer is the number of integers in this range: upper_bound - lower_bound + 1.

Time Complexity: O(N log N) due to sorting.
Space Complexity: O(N) to store input.

Example I/O:
Input:
4
4 0
1 2 3 4
5 2
7 6 6 7 1
3 1
6 7 9
6 2
5 1 9 10 13 2

Output:
2
2
4
9
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    long long k;
    if (!(cin >> n >> k)) return;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    // Case 1: We cannot remove any bars, and n is odd.
    // The median is unique.
    if (k == 0 && n % 2 != 0) {
        cout << 1 << "\n";
        return;
    }

    // Determine the optimal size of the subset of bars to keep.
    // We want an even number to get a continuous range of medians.
    // We can remove at most k bars.
    long long rem = n - k;
    long long sz;

    if (rem % 2 == 0) {
        sz = rem;       // Already even
    } else {
        sz = rem + 1;   // Make it even (remove k-1 bars instead of k)
    }

    // With 0-based indexing:
    // The median interval for a contiguous subarray of length 'sz' starts at index (sz/2 - 1)
    // relative to the start of the subarray.
    // The smallest median range starts at a[sz/2 - 1].
    // The largest median range ends at a[n - sz/2].
    
    int l_idx = sz / 2 - 1;
    int r_idx = n - sz / 2;

    long long ans = a[r_idx] - a[l_idx] + 1;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}

/*
SUBMISSION LINK:
https://codeforces.com/contest/2098/submission/356144063
*/