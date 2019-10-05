#include<bits/stdc++.h>
using namespace std;
int a[] = {-1,6,8,9,10,11,12,12,13};
using ll = long long;

int main(){
    int n;
    cin >> n;
    // scanf("%d",&n);
    if(n < 9) cout << a[n] << endl;
    else {
        ll l = 1, r = 10000000;
        ll len;
        while(l <= r){
            ll mid = l + r >> 1;
            ll tmp = (3 + 3 * mid) * mid + 1;
            if(tmp <= n){
                len = mid + 1;
                l = mid + 1;
            } else r = mid - 1;
        }     
        // cout << "len = " << len << endl;
        ll ans = (len - 2) * 6LL + a[7];
        // cout << "ans = " << ans << endl;
        n -= (3 + 3 * (len-1)) * (len-1) + 1;
        // cout << "n = " << n << endl;
        if(n == 0) cout << ans << endl;
        else {
            for(int i=1;i<=6;i++){
                if(n < i * len) {
                    cout << ans + i << endl;
                    break;
                }
            }
        }
    }
}
