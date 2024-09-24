#include<bits/stdc++.h>

//structure of each node of segment tree
struct Node {
  long long minVal;
  Node() {
    minVal = 1e9;
  }
  Node(long long val) {
    minVal = val;
  }
};

Node merge(Node a, Node b) {
  Node res;
  res.minVal = min(a.minVal, b.minVal);
  return res;
}

class SegmentTree {
private:
  vector<Node> t;
  long long n;
  void build(vector<long long> &arr, long long id, long long l, long long r) {
    if(l == r) {
      t[id] = Node(arr[l]);
      return;
    }
    long long mid = (l + r) / 2;
    build(arr, id << 1, l, mid);
    build(arr, id << 1 | 1, mid + 1, r);
    t[id] = merge(t[id << 1], t[id << 1 | 1]);
  }
  void update(long long id, long long l, long long r, long long ind, long long val) {
    if(ind < l || ind > r) {
      return;
    }
    if(l == r) {
      t[id] = Node(val);
      return;
    }
    long long mid = (l + r) >> 1;
    update(id << 1, l, mid, ind, val);
    update(id << 1 | 1, mid + 1, r, ind, val);
    t[id] = merge(t[id << 1], t[id << 1 | 1]);
  }
  Node query(long long id, long long l, long long r, long long lq, long long rq) {
    if(l > rq || lq > r) {
      return Node();
    }
    if(lq <= l && r <= rq) {
      return t[id];
    }
    long long mid = (l + r) >> 1;
    Node res = merge(query(id << 1, l, mid, lq, rq), query(id << 1 | 1, mid + 1, r, lq, rq));
    return res;
  }
public:
  SegmentTree(vector<long long> &arr) {
    n = arr.size();
    t.resize(4 * n);
    build(arr, 1, 0, n - 1);
  }
  void update(long long ind, long long val) {
    update(1, 0, n - 1, ind, val);
  }
  Node query(long long lq, long long rq) {
    return query(1, 0, n - 1, lq, rq);
  }
};
