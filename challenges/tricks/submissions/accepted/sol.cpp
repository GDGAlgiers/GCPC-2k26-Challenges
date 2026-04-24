#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
#define endl '\n'

ll rev(ll x) {
    for (ll i = 0; i < 16; i++) {
        ll tmp = x & (1LL<<(31-i));
        if (x & (1LL<<(i))) {
            x |= (1LL<<(31-i));
        }
        else {
            if (x & (1LL<<(31-i))) {
                x = x^(1LL<<(31-i));
            }
        }


        if (tmp) {
            x |= (1LL<<i);
        }
        else {
            if (x & (1LL<<i)) {
                x = x^(1LL<<i);
            }
        }
    }
    return x;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //______________________________
    ll q; cin >> q;
    multiset<ll> st1, st2;
    ll sum1 = 0, sum2 = 0;
    bool bl = true;
    while (q--) {
        ll typ; cin >> typ;
        if (typ == 1) {
            ll x; cin >> x;
            ll x2 = rev(x);
            if (bl) {
                st1.insert(x);
                st2.insert(x2);
                sum1 += x;
                sum2 += x2;
            }
            else {
                st2.insert(x);
                st1.insert(x2);
                sum2 += x;
                sum1 += x2;
            }
        }
        else if (typ == 2) {
            if (bl) {
                ll men = sum1/st1.size();
                auto idx = st1.upper_bound(men);
                idx--;

                cout << *(idx) << endl;
                sum1 -= *(idx);
                ll x2 = rev(*(idx));
                st1.erase(idx);
                auto idx2 = st2.lower_bound(x2);
                sum2 -= *(idx2);
                st2.erase(idx2);
            }
            else {
                ll men = sum2/st2.size();

                auto idx = st2.upper_bound(men);
                idx--;
                cout << *(idx) << endl;
                sum2 -= *(idx);
                ll x2 = rev(*(idx));
                st2.erase(idx);
                auto idx2 = st1.lower_bound(x2);
                sum1 -= *(idx2);
                st1.erase(idx2);
            }
        }
        else if (typ == 3) {
            bl = !bl;
        }
    }
    
    return 0;
}