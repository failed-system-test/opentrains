#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int c[maxn];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",c+i);
    sort(c,c+n);
    double ans = 1e9;
    for(int i=0;i<n;i++){
        if(c[i] > i + 1){
            ans = -1;
            break;
        }
        ans = min(ans, 1.0 * c[i] / (i + 1));
    }
    if(ans < 0) puts("impossible");
    else printf("%.6f\n",ans);
}
