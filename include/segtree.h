#pragma once
#ifndef SEGTREE_H
#define SEGTREE_H

#include <stdint.h>

#include <vector>

#define SUM 1
#define MAX 2

template <std::size_t OPERATION>
class segtree {
public:
    using ll = long long;

    segtree(std::size_t n) : n_{n}, v_{std::vector<ll>(4 * n + 1, 0)} {
        static_assert(OPERATION == SUM || OPERATION == MAX);
    }

    void add(int index, ll val) { add1(1, 0, n_ - 1, index, val); }

    void add(int l, int r, ll val) { add2(1, 0, n_ - 1, l, r, val); }

    ll query(int l, int r) {
        return lz_.size() == 0 ? query1(1, 0, n_ - 1, l, r)
                               : query2(1, 0, n_ - 1, l, r);
    }

private:
    std::size_t n_{0};
    std::vector<ll> v_{std::vector<ll>()};
    std::vector<ll> lz_{std::vector<ll>()};

    void add1(int o, int l, int r, int index, ll val) {
        if (l == r) {
            v_[o] += val;
            return;
        }
        int mid = (l + r) >> 1;
        if (index <= mid) {
            add1(2 * o, l, mid, index, val);
        } else {
            add1(2 * o + 1, mid + 1, r, index, val);
        }
        if constexpr (OPERATION == SUM) {
            v_[o] = v_[2 * o] + v_[2 * o + 1];
        } else if constexpr (OPERATION == MAX) {
            v_[o] = std::max(v_[2 * o], v_[2 * o + 1]);
        }
    }

    ll query1(int o, int l, int r, int L, int R) {
        if (l >= L && r <= R) {
            return v_[o];
        }
        int mid = (l + r) >> 1;

        if constexpr (OPERATION == SUM) {
            ll sum = 0;
            if (L <= mid) {
                sum += query1(2 * o, l, mid, L, R);
            }
            if (R > mid) {
                sum += query1(2 * o + 1, mid + 1, r, L, R);
            }
            return sum;
        }

        ll mx = INT64_MIN;
        if (L <= mid) {
            mx = std::max(query1(2 * o, l, mid, L, R), mx);
        }
        if (R > mid) {
            mx = std::max(query1(2 * o + 1, mid + 1, r, L, R), mx);
        }
        return mx;
    }

    void add2(int o, int l, int r, int L, int R, ll val) {
        if (lz_.size() == 0) {
            lz_.assign(4 * n_ + 1, 0);
        }

        if (l >= L && r <= R) {
            if constexpr (OPERATION == SUM) {
                v_[o] += val * (r - l + 1);
            } else if constexpr (OPERATION == MAX) {
                v_[o] += val;
            }
            lz_[o] += val;
            return;
        }

        int mid = (l + r) >> 1;
        if (lz_[o] != 0) {
            if constexpr (OPERATION == SUM) {
                v_[2 * o] += (mid - l + 1) * lz_[o];
                v_[2 * o + 1] += (r - mid) * lz_[o];
            } else if constexpr (OPERATION == MAX) {
                v_[2 * o] += lz_[o];
                v_[2 * o + 1] += lz_[o];
            }
            lz_[2 * o] += lz_[o];
            lz_[2 * o + 1] += lz_[o];
            lz_[o] = 0;
        }
        if (L <= mid) {
            add2(2 * o, l, mid, L, R, val);
        }
        if (R > mid) {
            add2(2 * o + 1, mid + 1, r, L, R, val);
        }
        if constexpr (OPERATION == SUM) {
            v_[o] = v_[2 * o] + v_[2 * o + 1];
        } else if constexpr (OPERATION == MAX) {
            v_[o] = std::max(v_[2 * o], v_[2 * o + 1]);
        }
    }

    ll query2(int o, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return v_[o];
        }

        int mid = (l + r) >> 1;
        if (lz_[o] != 0) {
            if constexpr (OPERATION == SUM) {
                v_[2 * o] += (mid - l + 1) * lz_[o];
                v_[2 * o + 1] += (r - mid) * lz_[o];
            } else if constexpr (OPERATION == MAX) {
                v_[2 * o] += lz_[o];
                v_[2 * o + 1] += lz_[o];
            }
            lz_[2 * o] += lz_[o];
            lz_[2 * o + 1] += lz_[o];
            lz_[o] = 0;
        }

        if constexpr (OPERATION == SUM) {
            ll sum = 0;
            if (L <= mid) {
                sum += query2(2 * o, l, mid, L, R);
            }
            if (R > mid) {
                sum += query2(2 * o + 1, mid + 1, r, L, R);
            }
            return sum;
        }

        ll mx = INT64_MIN;
        if (L <= mid) {
            mx = std::max(query2(2 * o, l, mid, L, R), mx);
        }
        if (R > mid) {
            mx = std::max(query2(2 * o + 1, mid + 1, r, L, R), mx);
        }
        return mx;
    }
};

#endif  // !SEGTREE_H
#define SEGTREE_H
