#pragma once
#ifndef DSU_H
#define DSU_H

#include <vector>

class dsu {
public:
  dsu(int n) : f_{std::vector<int>(n)}, s_{std::vector<int>(n, 1)} {
    for (int i = 0; i < n; i++) {
      f_[i] = i;
    }
  }

  int find(int x) {
    if (f_[x] == x) {
      return x;
    }
    return f_[x] = find(f_[x]);
  }

  void merge(int a, int b) {
    int x = find(a), y = find(b);
    if (x == y) {
      return;
    }
    if (s_[x] < s_[y]) {
      std::swap(x, y);
    }
    f_[y] = x;
    s_[x] += f_[y];
  }

private:
  std::vector<int> f_;
  std::vector<int> s_;
};

#endif // !DEBUG
