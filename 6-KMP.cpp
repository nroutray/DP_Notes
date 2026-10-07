// String : a a b a a  c  a a b a a  d
// LPS    : 0 1 0 1 2  0  1 2 3 4 5  0
// String : a a b #  a a b  a a b  a a b
// LPS    : 0 1 0 0  1 2 3  1 2 3  1 2 3
// Prefix that matches any subtsring of the string
// Largest prefix that matches a suffix

#include <bits/stdc++.h>
using namespace std;
class KMP {
public:
    // Compute the LPS (Longest Prefix Suffix) array
    vector<int> computeLPS(const string &pattern) {
        int n = pattern.size();
        vector<int> lps(n, 0);
        for (int i = 1; i < n; i++) {
            int prev_idx = lps[i - 1];
            while (prev_idx > 0 && pattern[i] != pattern[prev_idx]) {
                prev_idx = lps[prev_idx - 1];
            }
            lps[i] = prev_idx + (pattern[i] == pattern[prev_idx] ? 1 : 0);
        }
        return lps;
    }
    // KMP Search: Returns starting indices of all occurrences of `pattern` in `text
    vector<int> searchPattern(const string &text, const string &pattern) {
        string combined = pattern + "#" + text;  // Combine pattern and text using a separator
        vector<int> lps = computeLPS(combined);
        vector<int> occurrences;
        for (int i = pattern.size(); i < lps.size(); i++) {
            if (lps[i] == pattern.size()) {
                int startIdx = i - 2 * pattern.size();
                if (startIdx >= 0) {
                    occurrences.push_back(startIdx);
                }
            }
        }
        return occurrences;
    }
};
int main() {
    string s = "aabaab";      // Input string
    string pattern = "aaba";  // Pattern to search
    KMP kmp;
    vector<int> positions = kmp.searchPattern(s, pattern);
    
    cout << "Pattern found at indices: ";
    for (int idx : positions) {
        cout << idx << " ";
    }
    cout << endl;
    return 0;
}