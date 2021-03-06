#pragma once

#include <assert.h>

namespace un {
class Union5 {
public:
    Union5(int count) : count_(count) {
        parent_ = new int[count_];
        rank_ = new int[count_];
        for (int i = 0; i < count_; ++i) {
            parent_[i] = i;
            rank_[i] = 1;
        }
    }
    ~Union5() {
        delete[] parent_;
        delete[] rank_;
    }

    int find(int p) {
        assert(p >= 0 && p < count_);
        while (p != parent_[p]) {
            parent_[p] = parent_[parent_[p]];  // 进行路径压缩
            p = parent_[p];
        }
        return p;

        // 路径压缩到一层
        // if (p != parent_[p])
        //     parent_[p] = find(parent_[p]);
        // return parent_[p];
    }

    bool is_connected(int p, int q) {
        return find(p) == find(q);
    }

    void join_union(int p, int q) {
        int p_root = find(p);
        int q_root = find(q);

        if (p_root == q_root) {
            return;
        }
        if (rank_[p_root] <= rank_[q_root]) {
            parent_[p_root] = q_root;
        } else {
            parent_[q_root] = p_root;
        }
        if (rank_[p_root] == rank_[q_root]) {
            rank_[q_root]++;
        }
    }

private:
    int* parent_;
    int* rank_;
    int count_;
};
}  // namespace un