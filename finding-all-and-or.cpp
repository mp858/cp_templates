/*
we can find count of all the subarrays having and/OR k(where k can be any value) 
if we count the occurence of k throu all su arrays and we can do manny things like sum of all and values or sum square of all and values etc...
same apply for finding all the value of gcd of all the sub arrays
*/


#include <bits/stdc++.h>
using namespace std;
void help(auto &nums){
    map<int,int> cur_mp;
       map<int,long long> and_freq;
  /* 
  at any point cur_mp[x]=i represents that starting from certain index we can get and value x max to max till index i
  */
    int n=nums.size();
     for(int i=n-1;i>=0;i--){
      map<int,int> temp_mp;
      for(auto v:cur_mp){
       // v=> (x,y) i.e starting from index i we can obtain and value x max to max till index y
        //from index i we can obtain and value x&nums[i] till index y.
        temp_mp[v.first&nums[i]]=max(temp_mp[v.first&nums[i]],v.second);
      }
      temp_mp[nums[i]]=max(temp_mp[nums[i]],i);//storing the current value as and and value starting at i and ending at i
     cur_mp=temp_mp;
      vector<pair<int,int>> ranges(temp_mp.begin(),temp_mp.end());
      reverse(ranges.begin(),ranges.end());
    //   cout<<"startinng at index i";
      for(int en=0;en<ranges.size();en++){
        if(en==0){  //means starting from index i if we end anywhere bw (i to ranges[en].second) the and will be ranges[en].first;
         
          and_freq[ranges[en].first]+=ranges[en].second-i+1;// count of  occurence of all the sub arrays starting from i which have and ranges[en].first
            // cout<<" ending between"<<i<<" "<<ranges[en].second<<" :"<<ranges[end].first;
        }
        else{  //means from index i if we end any where bw (ranges[en-1].second to ranges[en].second) and value will be ranges[en].first
         
        and_freq[ranges[en].first]+=ranges[en].second-ranges[en-1].second;
        //  cout<<" ending between"<<ranges[en-1].second+1<<" "<<ranges[en].second<<" :"<<ranges[end].first;
        }
      }
      
     }
    //  return and_freq[k];
     for(auto i:and_freq){
      cout<<i.first<<" "<<i.second<<endl;
     }
}
signed main(){
   
  return 0;
}