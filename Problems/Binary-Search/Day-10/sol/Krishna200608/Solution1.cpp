/*
Submission Link:
https://codeforces.com/contest/2169/submission/356454662
*/

/*
Problem: Removal of a Sequence (Easy Version)
Link: https://codeforces.com/contest/2169/problem/D1
Author: Krishna200608

Short Problem Statement:
Find min integer n such that after x operations (v -= v/y), the result is >= k.

Approach:
     Binary Search on Answer. The function is monotonic.
     Simulate the process for a given start value to check validity.
     Search range [1, 10^12].

Time Complexity: O(T *x *log(N))
Space : O(1)
*/

#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
const int M = 1e9+7;
const double PI = acos(-1.0);
#define INF 1e18
#define pb push_back
#define ppb pop_back
#define ll long long
#define no cout << "NO" << endl;
#define yes cout << "YES" << endl;
#define ff first
#define ss second
#define inn(x) int x; std::cin >> x;
#define ill(x) ll x; std::cin >> x;
#define all(x) x.begin(),x.end()
#define in(a) for(int i = 0; i<a.size(); i++) cin>>a[i];
#define out(a) for(int i = 0; i<a.size(); i++) cout<<a[i]<< " " ;
typedef vector<int> vi;
typedef vector<ll> vll;

ll survivors_after_x(ll v, int x, ll y){
    ll s = v;
    for(int i=0;i<x && s>0;i++){
        s -= s / y;
    }
    return s;
}

void solve(){
    int T;
    if(!(cin>>T)) return;
    const ll NMAX = 1000000000000LL;
    while(T--){
        int x;
        ll y, k;
        cin >> x >> y >> k;
        
        // Optimization: check upper bound first
        if(survivors_after_x(NMAX, x, y) < k){
            cout << -1 << '\n';
            continue;
        }
        
        ll lo = 1, hi = NMAX;
        while(lo < hi){
            ll mid = lo + (hi - lo) / 2;
            if(survivors_after_x(mid, x, y) >= k) hi = mid;
            else lo = mid + 1;
        }
        cout << lo << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
    auto begin = std::chrono::high_resolution_clock::now();
    
    solve(); // solve handles the test cases loop internally as per your code
    
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-6 << "ms";
    return 0;
}