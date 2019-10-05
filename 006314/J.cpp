#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(vector<ll> &a, ll up) {
    ll val = a[0], num = 1, sum = 0;
    for(int i=1;i<a.size();i++){
        __int128 diff = val - (sum + a[i]);
        __int128 loop = __lg(num) + 1;
        __int128 delt = (loop - 1) * diff;
        if(val + delt > up) break;
        sum += loop * diff;
        num++;
        val += delt;
    }
    ll loop = __lg(num) + 1;
    // cerr << "loop = " << loop << endl;
    ll tmp = (up - val) / (loop - 1) * loop + (up - val) % (loop - 1);
    return sum + tmp;
}

int main(){
    // freopen("1.in", "r", stdin);
    // freopen("2.out", "w", stdout);

    int n;
    scanf("%d",&n);
    vector<ll> a;
    ll x, up;
    for(int i=0;i<n;i++){
        scanf("%lld",&x);
        if(i) a.push_back(x);
        else up = x;
    }
    sort(a.begin(), a.end(), greater<ll>());
    printf("%lld\n", solve(a,up));
    
}
