#include <algorithm>
#include <gtest/gtest.h>
#include "../include/segtree.h"
#include <bits/stdc++.h>
#include <numeric>
using ll = long long;

TEST (segtree_test_sum, single) {
  int k = 10000;
  std::vector<ll> tree(k, 0);
  SegTree<SUM> t(k);

  for (int i = 0; i < k; i++) {
    int rd = std::rand() % 100000;
    tree[i] += rd;
    t.add(i, rd);
  }

  int iter = 10000;
  for (int i = 0; i < iter; i++) {
    int l = std::rand() % k;
    int r = std::rand() % k;
    if (l > r) {
      std::swap(l, r);
    }
    EXPECT_EQ(t.query(l, r), std::accumulate(tree.begin() + l, tree.begin() + r + 1, 0LL));
  }
}

TEST (segtree_test_sum, multi) {
  int k = 10000;
  std::vector<ll> tree(k, 0);
  SegTree<SUM> t(k);

  for (int i = 0; i < k; i++) {
    ll rd = std::rand() % 100000;
    int l = std::rand() % k;
    int r = std::rand() % k;
    if (l > r) {
      std::swap(l, r);
    }
    for (int j = l; j <= r; j++) {
      tree[j] += rd;
    }
    t.add(l, r, rd);
  }

  int iter = 10000;
  for (int i = 0; i < iter; i++) {
    int l = std::rand() % k;
    int r = std::rand() % k;
    if (l > r) {
      std::swap(l, r);
    }
    EXPECT_EQ(t.query(l, r), std::accumulate(tree.begin() + l, tree.begin() + r + 1, 0LL));
  }
}

TEST (segtree_test_max, single) {
  int k = 10000;
  std::vector<ll> tree(k, 0);
  SegTree<MAX> t(k);

  for (int i = 0; i < k; i++) {
    int rd = std::rand() % 100000;
    tree[i] += rd;
    t.add(i, rd);
  }

  int iter = 10000;
  for (int i = 0; i < iter; i++) {
    int l = std::rand() % k;
    int r = std::rand() % k;
    if (l > r) {
      std::swap(l, r);
    }
    EXPECT_EQ(t.query(l, r), *std::max_element(tree.begin() + l, tree.begin() + r + 1));
  }
}

TEST (segtree_test_max, multi) {
  int k = 10000;
  std::vector<ll> tree(k, 0);
  SegTree<MAX> t(k);

  for (int i = 0; i < k; i++) {
    ll rd = std::rand() % 100000;
    int l = std::rand() % k;
    int r = std::rand() % k;
    if (l > r) {
      std::swap(l, r);
    }
    for (int j = l; j <= r; j++) {
      tree[j] += rd;
    }
    t.add(l, r, rd);
  }

  int iter = 10000;
  for (int i = 0; i < iter; i++) {
    int l = std::rand() % k;
    int r = std::rand() % k;
    if (l > r) {
      std::swap(l, r);
    }
    EXPECT_EQ(t.query(l, r), *std::max_element(tree.begin() + l, tree.begin() + r + 1));
  }
}
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
