#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define fr(i,n) for (ll i=0;i<n;i++)
#define fr1(i,n) for (ll i=1;i<n;i++)
#define fr2(i,st,ed) for (ll i=st;i<ed;i++)
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define lb lower_bound
#define ub upper_bound
#define all(v) v.begin(), v.end()
#define sum(v) accumulate(all(v), 0LL)
#define lcm(a,b) (a*b)/gcd(a,b)
#define pop_count(n) __builtin_popcount(n)
#define vin(v) for(auto &it:v) cin>>it;
#define vout(v) for(auto &it:v) cout<<it;
#define int long long
struct hasher{
    vector<int> pref_hash,suf_hash,pref_hash1,suf_hash1,power_p;
    int p=31,mod=(int)1e9+7,n;
       hasher(string &s,int _p,int _m){
        n=s.length();
        pref_hash.resize(n);
        suf_hash.resize(n);
        power_p.resize(n);
        p=_p;
        mod=_m;
        pref_hash[0]=s[0]-'a'+1;
        power_p[0]=1;
        for(int i=1;i<n;i++){
            pref_hash[i]=(pref_hash[i-1]*p+(s[i]-'a'+1))%mod;
            power_p[i]=(power_p[i-1]*p)%mod;
        }
        suf_hash[n-1]=s[n-1]-'a'+1;
        for(int i=n-2;i>=0;i--){
            suf_hash[i]=(suf_hash[i+1]*p+(s[i]-'a'+1))%mod;
        }

    }
    int get_forwardhash(int l,int r){
        if(l==0)
        return pref_hash[r];
        return ((pref_hash[r]-pref_hash[l-1]*power_p[r-l+1])%mod +mod)%mod;
    }
    int get_reversehash(int l,int r){
        if(r==n-1)
        return suf_hash[l];
        return ((suf_hash[l]-suf_hash[r+1]*power_p[r-l+1])%mod +mod)%mod;
    }
};
void solve(){
    string s;
    cin>>s;
    hasher hs(s,31,1e9+7);
    for(int i=0;i<s.length();i++){
        for(int j=i;j<s.length();j++){
            cout<<hs.get_forwardhash(i,j)<<" "<<hs.get_reversehash(s.length()-j-1,s.length()-i-1)<<endl;
        }
    }
}
signed main(){
   ios::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
  solve();
  return 0;
}