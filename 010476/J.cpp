#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+5;
int n;
using ll = long long;

int G[maxn][maxn];
int main(){
    scanf("%d",&n);
    int m = n * (n - 1) / 2;
    for(int i=0,u,v,w;i<m;i++) {
        scanf("%d%d%d",&u,&v,&w);
        G[u][v] = G[v][u] = w;
    }
    ll ans = 0;
    for(int i=1;i<=n;i++){
        vector<int> tmp;
        for(int j=1;j<=n;j++)
            if(j != i) tmp.push_back(G[i][j]);
        sort(tmp.begin(), tmp.end());
        for(int i=1;i<tmp.size();i+=2)
            ans += tmp[i];
    }
    printf("%lld\n",ans);
}
/*
5
4 5 4
1 3 4
1 2 4 
3 2 3
3 5 2
1 4 3
4 2 2
1 5 4
5 2 4
3 4 2
*/
