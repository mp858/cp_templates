#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
class SCCmaker
{
    //DAG is final directed acycliic graph 
    //info is the sum of each SCC
    vector<vector<ll>> DAG;
    vector<ll> info;
    ll number_of_nodes;

    void dfs(ll node, vector<vector<ll>> &adj, vector<ll> &vis, vector<ll> &order)
    {
        vis[node] = 1;
        for (auto &i : adj[node])
        {
            if (vis[i] != 1)
            {
                dfs(i, adj, vis, order);
            }
        }
        order.push_back(node);
    }
    void dfs2(ll node, vector<vector<ll>> &revadj, vector<ll> &temp, vector<ll> &vis)
    {
        vis[node] = 1;
        temp.push_back(node);
        for (auto &i : revadj[node])
        {
            if (vis[i] == 0)
            {
                dfs2(i, revadj, temp, vis);
            }
        }
    }

public:
    SCCmaker(vector<vector<ll>> &adj, vector<ll> &information, ll (*combine)(vector<ll> &temp, vector<ll> &information), vector<pair<ll, ll>> &edges, ll n)
    {
        //infromation is information about each node (e.g node value)
        // combine is just a function used in this question for getting sum of node values of each rhe SCC
        //revadj is the reversed graph
        vector<ll> order;
        vector<ll> vis(n + 1, 0);
        for (ll i = 1; i <= n; i++)
        {
            if (!vis[i])
                dfs(i, adj, vis, order);
        }
        reverse(order.begin(), order.end());
        vector<ll> vis2(n + 1, 0);
        vector<vector<ll>> revadj(n + 1);
        for (auto &i : edges)
        {
            revadj[i.second].push_back(i.first);
        }
        vector<ll> parentset(n + 1, 0);
        ll c = 0;
        for (auto &i : order)
        {
            if (!vis2[i])
            {
                vector<ll> temp;
                dfs2(i, revadj, temp, vis2);
                ll z = temp.size();
                for (ll j = 0; j < z; j++)
                {
                    parentset[temp[j]] = c;
                }
                ll sum = combine(temp, information);
                info.push_back(sum);
                c++;
            }
        }
        DAG.resize(c);
        number_of_nodes = c;
        for (auto &i : edges)
        {
            if (parentset[i.first] != parentset[i.second])
            {
                DAG[parentset[i.first]].push_back(parentset[i.second]);
            }
        }
    }
    vector<vector<ll>> getDAG()
    {
        return DAG;
    }
    vector<ll> getinfo()
    {
        return info;
    }
    ll get_numberofnodes()
    {
        return number_of_nodes;
    }
};
ll combine(vector<ll> &temp, vector<ll> &information)
{
    ll sum = 0;
    for (auto &i : temp)
    {
        sum += information[i - 1];
    }
    return sum;
}


void solve()
{
    int n,m;
    cin>>n>>m;
    vector<int> val(n);
    for(int i=0;i<n;i++){
        cin>>val[i];
    }
    vector<vector<int>> adj(n+1);
    vector<pair<int,int>> edges;
    while(m--){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        edges.push_back({a,b});
    }
    SCCmaker sc(adj,val,combine,edges,n);
    auto dg=sc.getDAG();
    int num=sc.get_numberofnodes();
    auto inf=sc.getinfo();
    
}
signed main(){
   ios::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
  solve();
  return 0;
}

