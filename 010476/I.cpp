#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+5;
int a[maxn], b[maxn];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",a+i);
    for(int i=0;i<n;i++) scanf("%d",b+i);
    int ans = -1;
    for(int i=0;i<n;i++){
        int tmp = 2e9+5;
        for(int j=0;j<n;j++){
            tmp = min(tmp, abs(a[i] - b[j]));
        }
        ans = max(ans, tmp);
    }
    printf("%d\n",ans);
}
