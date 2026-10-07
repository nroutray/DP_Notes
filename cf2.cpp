#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pb push_back
 
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
 
 
struct Segment {
    int start;   
    int end;    
    int mx;      
};

int maxBalancedShipments(std::vector<int>& weight) {
    const int n = static_cast<int>(weight.size());
    if (n < 2) return 0;                 

    std::vector<Segment> segs;           
    int start = 0;
    int curMax = weight[0];

    for (int i = 1; i < n; ++i) {
        curMax = std::max(curMax, weight[i]);

        if (weight[i] < curMax) {
            segs.push_back({start, i, curMax});
            start = i + 1;               
            if (start < n) curMax = weight[start];
        }
    }

    if (start < n)
        segs.push_back({start, n - 1, curMax});

    while (!segs.empty()) {
        Segment& last = segs.back();
        if (last.mx > weight[last.end]) break; 

        segs.pop_back();
        if (segs.empty()) return 0;              

        Segment& prev = segs.back();
        prev.end = last.end;
        prev.mx  = std::max(prev.mx, last.mx);   
    }

    return static_cast<int>(segs.size());
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    vector<int> weight = { 8, 5, 4, 7, 2};

    int res=maxBalancedShipments(weight);

    cout<<"ans: "<<res;


    return 0;
}