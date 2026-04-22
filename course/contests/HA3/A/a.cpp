// Cartesian tree implementation with additionalk structure
#include <utility>
#include <random>
#include <chrono>
#include <iostream>

using namespace std;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    long long key, sum;
    int priority;
    Node *l;
    Node *r;
    Node(long long key) : key(key), sum(key), priority(rng()), l(nullptr), r(nullptr) {}
};

long long getsum(Node* t) { 
    return t ? t->sum : 0;
}

void upd(Node* t) {
    if (t) t->sum = t->key + getsum(t->l) + getsum(t->r);
}

pair<Node*, Node*> split(Node* t, long long key) {
    if (!t) return {nullptr, nullptr};

    if (t->key <= key) {
        auto [l, r] = split(t->r, key);
        t->r = l; upd(t);
        return {t, r};
    } else {
        auto [l, r] = split(t->l, key);
        t->l = r; upd(t);
        return {l, t};
    }
}

Node* merge(Node* l, Node* r) {
    if (!l || !r) return l ? l : r;

    if (l->priority > r->priority) {
        l->r = merge(l->r, r); upd(l); return l;
    } else {
        r->l = merge(l, r->l); upd(r); return r;
    }
}

Node* insert(Node* t, long long key) {
    auto [l, r] = split(t, key - 1);
    auto [l2, mid] = split(r, key);

    if (mid) return merge(
        merge(l, mid),
        r
    );

    return merge(
        merge(l, new Node(key)),
        merge(l2, mid)
    );
}


bool find(Node* t, long long key) {
    if (!t) return false;
    if (key == t->key) return true;
    return key < t->key ? find(t->l, key) : find(t->r, key);
}

Node* add(Node* t, long long key) {
    if (find(t, key)) return t;
    auto [l, r] = split(t, key - 1);

    return merge(
        merge(l, new Node(key)),
        r
    );
}

long long sum(Node* t, long long l, long long r) {
    auto [t1, t2] = split(t, l - 1);
    auto [t3, t4] = split(t2, r);   
    long long ans = getsum(t3);

    t = merge(t1, merge(t3, t4));

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Node* root = nullptr;
    bool lastWasQuery = false;
    long long lastAns = 0;

    while (n--) {
        char op;
        cin >> op;
        if (op == '+') {
            long long x;
            cin >> x;
            if (lastWasQuery)
                x = (x + lastAns) % 1000000000LL;
            root = add(root, x);
            lastWasQuery = false;
        } else {
            long long l, r;
            cin >> l >> r;
            // sum query — нужно split/merge и вернуть root
            auto [t1, t2] = split(root, l - 1);
            auto [t3, t4] = split(t2, r);
            lastAns = getsum(t3);
            root = merge(t1, merge(t3, t4));
            cout << lastAns << '\n';
            lastWasQuery = true;
        }
    }
}