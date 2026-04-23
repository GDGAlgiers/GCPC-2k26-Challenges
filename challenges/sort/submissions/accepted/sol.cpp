#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define Algerian ios::sync_with_stdio(false);
#define OI cin.tie(0);

void Solve(){
    int n,k; cin >> n >> k;
    vector<int> a(n);
    for(auto &i : a) cin >> i;
    vector<int> vec;
    int ans = 0;
    vec.push_back(1);
    for (int i = 1; i < n; ++i){
        if(a[i]*2>a[i-1]){
            vec.back()++;
        }
        else{
            vec.push_back(1);
        }
    }
    for(auto x : vec) ans += max(x-k,0);
    cout << ans << '\n';
}

int main(){
    Algerian OI
    Solve();
}
