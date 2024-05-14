#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n, INT_MAX);
    }

    void update(int idx, int value, int node = 1, int start = 0, int end = -1) {
        if (end == -1) end = n - 1;
        if (start == end) {
            tree[node] = value;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(idx, value, 2 * node, start, mid);
            } else {
                update(idx, value, 2 * node + 1, mid + 1, end);
            }
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }

    int query(int L, int R, int node = 1, int start = 0, int end = -1) {
        if (end == -1) end = n - 1;
        if (R < start || L > end) return INT_MAX;
        if (L <= start && end <= R) return tree[node];
        int mid = (start + end) / 2;
        return min(query(L, R, 2 * node, start, mid), query(L, R, 2 * node + 1, mid + 1, end));
    }
};

int main() {
    int N, L, R;
    cin >> N >> L >> R;

    vector<int> X(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i];
    }

    vector<int> dp(N, INT_MAX);
    dp[0] = 0;

    SegmentTree seg(N);
    seg.update(0, 0);

    for (int i = 1; i < N; i++) {
        int left = lower_bound(X.begin(), X.end(), X[i] - R) - X.begin();
        int right = upper_bound(X.begin(), X.end(), X[i] - L) - X.begin() - 1;
        if (left <= right) {
            int min_jump = seg.query(left, right);
            if (min_jump != INT_MAX) {
                dp[i] = min_jump + 1;
            }
        }
        seg.update(i, dp[i]);
    }

    cout << dp[N - 1] << endl;

    return 0;
}
