#include<bits/stdc++.h>
#include<queue>
using namespace std;
typedef unordered_map<int, int> umii;
typedef unordered_map<long long, long long> umll;
typedef unordered_map<char, long long> umci;
typedef vector<pair<int, int>> vpi;
typedef vector<int> vi;
typedef long long ll;
typedef vector<long long> vll;
typedef unordered_map<int , bool> umib;
#define sum(v) accumulate(v.begin(), v.end(), 0)
#define endl '\n'
#define f0(i, n) for(long long i = 0; i < n; i++)
#define f1(i, n) for(long long i = 1; i < n; i++)
#define as(v) sort(v.begin(), v.end())
#define all(x) (x).begin(), (x).end()
#define pb push_back
template<class T> umll frequency(vector<T> &v) {umll freq;for(auto &x:v) freq[x]++; return freq;}
template<class T> umci S_frequency(vector<T> &v) {umci freq;for(auto &x:v) freq[x]++; return freq;}
template <class T> void input(vector<T> &v){for(auto &x:v)cin>>x;}
ll power(ll x, ll y){ ll res = 1; while (y > 0){ if (y & 1) res = (ll)(res*x); y = y>>1; x = (ll)(x*x); } return res; }
void pvll(const vector<long long> &arr){for(auto it : arr){cout << it << " ";}cout << endl;}
void pvi(const vector<int> &arr){for(auto it : arr){cout << it << " ";}cout << endl;}


void solve(){

//-------------INPUT-------------
    ll n; 
    cin >> n;

    vector<tuple<ll,ll,ll>>intervals;

    f0(i,n)
    {
        ll a,b;
        cin >> a >> b;
        intervals.pb({a,b,i});
    }
    sort(all(intervals));

    auto[a,b,idx] = intervals[0]; 
    
    vll room(n);
    multiset<pair<ll,ll>>st;
    room[idx] = 1;
    st.emplace(b,1);

    for(ll i=1;i<n;i++)
    {
        auto[a,b,idx] = intervals[i]; 

        auto[smallest_b,rid] = *begin(st);

        if(smallest_b<a)
        {
            st.erase(st.begin());
            room[idx] = rid;
            st.emplace(b,rid);
        }
        else
        {
            room[idx] =st.size() +1;
            st.emplace(b,room[idx]);
        }
        
    }
    cout << *max_element(all(room)) << endl;
    for(auto room :room )
    {
        cout << room << " ";
    }

    // submission link https://cses.fi/problemset/result/15786598/
    // time complexity o(nlogn)
    // used multiset as data structure 

    // keep the condition if current begin is greter or small than smallest end upto now if the curr start time is less than the ending time upto now checked using multiset so at that time add new room if not so assigned the same room

    

//-------------CODE--------------
    


}


int main(){
    //int tt; cin >> tt; while(tt--)
{solve();};
}
