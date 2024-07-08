#include <bits/stdc++.h>
using namespace std;
int N=1e4+1,M=1e4+1;
void prefix_sum(vector<vector<int>> mat){
   
    vector<vector<int>> pref(N+1,vector<int>(M+1,0));
    int n=mat.size(),m=mat[0].size();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            pref[i][j]+=pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1]+mat[i-1][j-1];
        }
    }
    int t;
    cin>>t;
    while(t--){
        int i,j,p,q;
        cin>>i>>j>>p>>q;
    //to get sum bw i,j and p,q
    int ans;
    ans=pref[p][q]-pref[p][j-1]-pref[i-1][q]+pref[i-1][j-1];
    cout<<ans<<endl;
    }
}
void prefix_sum(vector<vector<int>> mat){
    int n=mat.size(),m=mat[0].size();
    vector<vector<int>> partial(N+1,vector<int>(M+1,0));
    int que;
    cin>>que;
    while(que--){
        int i,j,p,q,x;
        cin>>i>>j>>p>>q>>x;
    //    building partial sum bw i,j and p,q
    partial[i][j]+=x;
    partial[p+1][q+1]+=x;
    partial[p+1][j]-=x;
    partial[i][q+1]-=x;
    }
    //now get prefix sum of partial array by 2d prefix_sum
    //and print final prefix_sum array
   
}
signed main(){
   ios::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
    
  return 0;
}