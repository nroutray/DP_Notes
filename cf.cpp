#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pb push_back
 
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
 
 
vector<int> predictAnswer(vector<int>& stockData, vector<int>& queries) {
    int n = stockData.size();
    vector<int> pse(n, -1), nse(n, -1);
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && stockData[st.top()] >= stockData[i]) {
            st.pop();
        }
        if (!st.empty()) {
            pse[i] = st.top();
        }
        st.push(i);
    }

    while (!st.empty()) st.pop();

    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && stockData[st.top()] >= stockData[i]) {
            st.pop();
        }
        if (!st.empty()) {
            nse[i] = st.top();
        }
        st.push(i);
    }

    vector<int> res;
    for (int query : queries) {
        int i = query - 1;
        int left = pse[i];
        int right = nse[i];

        if (left == -1 && right == -1) {
            res.push_back(-1);
        } else if (left == -1) {
            res.push_back(right + 1);
        } else if (right == -1) {
            res.push_back(left + 1); 
        } else {
            int dl = abs(i - left);
            int dr = abs(i - right);
            if (dl <= dr) {
                res.push_back(left + 1); 
            } else {
                res.push_back(right + 1);
            }
        }
    }

    return res;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    vector<int> stockData = {2, 1, 3};
    vector<int> queries = {2, 1};
    vector<int> res=predictAnswer(stockData,queries);

    for(auto it:res) cout<<it<<" ";


    return 0;
}