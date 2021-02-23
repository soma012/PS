#include <bits/stdc++.h>
#define arr_size 1000001

using namespace std;
typedef long long ll;

struct Tree{
    ll value, lazy = 0;
};
Tree tree[arr_size * 4];
vector<ll> arr;

ll init(int start, int end, int node)
{
    if(start == end) return tree[node].value = arr[start];
    return tree[node].value = init(start, (start+end)/2, node*2) + init((start+end)/2+1, end, node*2+1);
}
void propagation(int start, int end, int node)
{
    ll lazy = tree[node].lazy;
    if(lazy != 0) {
        tree[node].value += (ll)(end-start+1) * lazy;
        if(start != end) {
            tree[node*2].lazy += lazy;
            tree[node*2+1].lazy += lazy;
        }
        tree[node].lazy = 0;
    }
}
void update(int start, int end, int node, int left, int right, ll diff)
{
    propagation(start, end, node);
    if(end < left || right < start) return;
    if(left <= start && end <= right) {
        tree[node].value += (ll)(end-start+1) * diff;
        if(start != end) {
            tree[node*2].lazy += diff;
            tree[node*2+1].lazy += diff;
        }
        return;
    }
    int mid = (start + end) / 2;

    update(start, mid, node*2, left, right, diff);
    update(mid+1, end, node*2+1, left, right, diff);
    tree[node].value = tree[node*2].value + tree[node*2+1].value;
}
ll sum(int start, int end, int node, int left, int right) /// left~right ±¸°£ÇÕ
{
    propagation(start, end, node);
    if(end < left || right < start) return 0;
    if(left <= start && end <= right) return tree[node].value;

    int mid = (start + end) / 2;
    return sum(start, mid, node*2, left, right) + sum(mid+1, end, node*2+1, left, right);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    arr.resize(n+1);
    for(int i = 0; i < n; i++) cin >> arr[i];
    init(0, n-1, 1);

    m += k;
    while(m--) {
        int code, s, e;
        cin >> code >> s >> e;
        if(code == 1) {
            ll diff;
            cin >> diff;
            update(0, n-1, 1, s-1, e-1, diff);
        }
        else {
            cout << sum(0, n-1, 1, s-1, e-1) << '\n';
        }
    }
}
