#include<bits/stdc++.h>
using namespace std;

class Z_Function{
    public:
    vector<int> Z_algo(string &s){
        int n=s.size();
        vector<int> Z(n);
        int left=0,right=0;
        for(int i=1;i<n;i++){
            if(i>right){
                left=right=i;
                while(right<n&&s[right]==s[right-left]){
                    right++;
                }
                right--;
                Z[i]=right-left+1;
            }
            else{
                int idx=i-left;
                if(Z[idx]<=right-i){
                    Z[i]=Z[idx];
                }
                else{
                    left=i;
                    while(right<n&&s[right]==s[right-left]){
                        right++;
                    }
                    right--;
                    Z[i]=right-left+1;
                }
            }
        }
        return Z;
    }
};