#include <vector>
#include <iostream>
#include <string>

using namespace std;

vector<int> computePrefixFunction(string pattern) {
    int m = pattern.length();
    vector<int> pi(m);
    pi[0] = 0;
    int k = 0;
    for (int i = 1; i < m; i++) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = pi[k-1];
        }
        if (pattern[k] == pattern[i]) {
            k++;
        }
        pi[i] = k;
    }
    return pi;
}

void KMP(string S, string W) {
    int n = S.length(), m = W.length();
    vector<int> pi = computePrefixFunction(W);
    int q = 0;
    for (int i = 0; i < n; i++) {
        while (q > 0 && W[q] != S[i]) {
            q = pi[q-1];
        }
        if (W[q] == S[i]) {
            q++;
        }
        if (q == m) {
            cout << "Pattern occurs with shift " << i - m + 1 << endl;
            q = pi[q-1];
        }
    }
}

int main() {
    string S = "ABABDABACDABABCABAB";
    string W = "ABABCABAB";
    KMP(S, W);
    return 0;
}