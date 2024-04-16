#pragma once
#ifndef ODT_H
#define ODT_H

#include <cstdint>
#include <set>

class odt {
  using ll = long long;

public:
  odt(ll l, ll r, ll v) : val(std::set<node>{node{l, r, v}}) {}

  void assign(ll l, ll r, ll v) {
    auto it1 = split(l);
    auto it2 = split(r + 1);
    val.erase(it1, it2);
    val.insert(node{l, r, v});
  }

  ll sum(ll l, ll r) {
    ll sum = 0;
    auto it1 = split(l);
    auto it2 = split(r + 1);
    for (; it1 != it2; ++it1) {
      sum += it1->v * (it1->r - it1->l + 1);
    }
    return sum;
  }

  ll max(ll l, ll r) {
    ll max = INT64_MIN;
    auto it1 = split(l);
    auto it2 = split(r + 1);
    for (; it1 != it2; ++it1) {
      max = std::max(max, it1->v);
    }
    return max;
  }

private:
  struct node {
    ll l, r, v;
    bool operator<(const node &rhs) const { return l < rhs.l; }
  };

  std::set<node> val;

  std::set<node>::iterator split(ll x) {
    auto it = --val.upper_bound(node{x, 0, 0});
    if (it->l == x) {
      return it;
    }
    auto [l, r, v] = *it;
    if (x > r) {
      return val.end();
    }
    val.erase(it);
    val.insert(node{l, x - 1, v});
    return val.insert(node{x, r, v}).first;
  }
};

#endif
