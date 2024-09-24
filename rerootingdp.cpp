#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve()
{
    int n;
    cin>>n;
    vector<vector<int>> adj(n+1);
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    //answer contain final answer of problem
    // sub sontain partial solution of each node
    //cnt contain contribution of each node to its parent in first go
   vector<int> ans(n+1,0),sub(n+1,0),cnt(n+1,0);

   //function to add a child partial answer and contribution to a node
   auto add=[&](int node,int child){
    sub[node]+=sub[child]+cnt[child];
    cnt[node]+=cnt[child];
   };
   //function to removing  a child partial answer and contribution to a node
   auto remove=[&](int node,int child){
    sub[node]-=sub[child]+cnt[child];
    cnt[node]-=cnt[child];
   };

   //nodemal dfs function for calculating the partial solution of all the node in the first go
   function <void(int,int)> dfs=[&](int node,int p){
    cnt[node]=1;
    sub[node]=0;
    for(auto j:adj[node]){
        if(j!=p){
            dfs(j,node);
            add(node,j);
        }
    }
   };
   //function to change root from a perti ulor node to its one of the child and updation the answer
   auto changeroot=[&](int node,int child){
    remove(node,child);
    add(child,node);
   };

   //normal dfs function to make eachh node root one by one and calculating their answer
   function <void(int,int)> reroot=[&](int node,int p){
    ans[node]=sub[node];
    for(auto j:adj[node]){
        if(j!=p){
            changeroot(node,j);
            reroot(j,node);
            changeroot(j,node);
        }
    }
   };
   dfs(1,-1);
   reroot(1,-1);

for(int i=1;i<=n;i++)
cout<<ans[i]<<" ";
   
  
}
signed main(){
   ios::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
  solve();
  return 0;
}