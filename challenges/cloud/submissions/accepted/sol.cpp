#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define Algerian ios::sync_with_stdio(false);
#define OI cin.tie(0);

ll sz(ll n, ll k){
    if(k>n) return 0;
    if(n==1) return 1;
    if(n%2==0) return 2 * sz(n/2,k);
    else return 1 + 2 * sz(n/2,k);
}

ll f(ll n, ll k){
    if(k>n) return 0;
    if(n==1) return 1;
    if(n%2==0) return 2 * f(n/2,k) + (n/2)*sz(n/2,k);
    else return ((n+1)/2) + 2 * f(n/2,k) + ((n+1)/2)*sz(n/2,k);
}

int main(){
    Algerian OI
    int n,k,N,K;
    cin >> n >> k >> N >> K;
    ll Raouf = f(n,k), Hachem = f(N,K);
    if(Raouf > Hachem) cout << "Raouf\n" ;
    else if(Raouf < Hachem) cout << "Hachem\n";
    else cout << "Tie\n";
}