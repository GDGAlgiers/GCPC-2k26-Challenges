#include <stdio.h>

typedef long long ll;

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
    long long n, k, N, K;
    if(scanf("%lld %lld %lld %lld", &n, &k, &N, &K) != 4) return 0;
    ll Raouf = f(n,k), Hachem = f(N,K);
    if(Raouf > Hachem) printf("Raouf\n");
    else if(Raouf < Hachem) printf("Hachem\n");
    else printf("Tie\n");
    return 0;
}