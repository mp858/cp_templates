vector<long long> t(4*200010),v;  //size if t should be 4*n

void build(int n,int s,int e){
  if(s==e){
    t[n]=v[s];
    return;
  }
  long long m=s+(e-s)/2;
  build(2*n,s,m);
  build(2*n+1,m+1,e);
  t[n]=t[2*n]+t[2*n+1];
}
void update(long long n,long long s,long long e,long long i,long long x){
  if(s==e){
    t[n]=x;
    return;
  }
  long long m=(s+e)/2;
  if(i<=m)
  update(2*n,s,m,i,x);
  else
  update(2*n+1,m+1,e,i,x);
  t[n]=t[2*n]+t[2*n+1];
  return;
}
long long query(long long n,long long s,long long e,long long ql,long long qr){
  if(s>=ql&&e<=qr)
  return t[n];
  if(s>qr||e<ql)
  return 0;
  long long m=s+(e-s)/2;
  return (query(2*n,s,m,ql,qr)+query(2*n+1,m+1,e,ql,qr));
}