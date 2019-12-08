#include <bits/stdc++.h>

typedef long long i64;
typedef unsigned long long u64;

const int MOD = 1000000007;
const int MAXQ = 301000;

struct Item {
    
    int left = 0;
    int right = 0;
    
    int offset = 0;
    int offsetMul = 1;
    int offsetAdd = 0;
    int stride = 1;
    int strideMul = 1;
    
};

int q, g;
int cnt[MAXQ];
int last[MAXQ], last2[MAXQ];
i64 dist[MAXQ];

Item st[MAXQ * 2 + 100];
int stc;

int ai() { ++stc; return stc; }
void init() { stc = 0; }
void push(int N) {
    
    if(!st[N].left) st[N].left = ai();
    if(!st[N].right) st[N].right = ai();
    int L = st[N].left, R = st[N].right;
    {
    int x = st[N].offsetMul;
    if(x != 1) {
        
        st[L].offset = i64(st[L].offset) * x % MOD;
        st[L].offsetMul = i64(st[L].offsetMul) * x % MOD;
        st[L].offsetAdd = i64(st[L].offsetAdd) * x % MOD;
        st[R].offset = i64(st[R].offset) * x % MOD;
        st[R].offsetMul = i64(st[R].offsetMul) * x % MOD;
        st[R].offsetAdd = i64(st[R].offsetAdd) * x % MOD;
        st[N].offsetMul = 1;
        
    }
    }
    if(int x = st[N].offsetAdd) {
        
        st[L].offset = (st[L].offset + x) % MOD;
        st[L].offsetAdd = (st[L].offsetAdd + x) % MOD;
        st[R].offset = (st[R].offset + x) % MOD;
        st[R].offsetAdd = (st[R].offsetAdd + x) % MOD;
        st[N].offsetAdd = 0;
        
    }
    {
    int x = st[N].strideMul;
    if(x != 1) {
        
        st[L].stride = i64(st[L].stride) * x % MOD;
        st[L].strideMul = i64(st[L].strideMul) * x % MOD;
        st[R].stride = i64(st[R].stride) * x % MOD;
        st[R].strideMul = i64(st[R].strideMul) * x % MOD;
        st[N].strideMul = 1;
        
    }
    }
    
}
void add(int l, int r, int x, int N = 0, int L = 0, int R = MAXQ - 1) {
    
    if(l <= L && R <= r) {
        
        st[N].offset = (st[N].offset + x) % MOD;
        st[N].offsetAdd = (st[N].offsetAdd + x) % MOD;
        return;
        
    }
    push(N);
    int M = (L + R) / 2;
    if(M >= l) add(l, r, x, st[N].left, L, M);
    if(M < r) add(l, r, x, st[N].right, M + 1, R);
    
}
void mul(int l, int r, int x, int N = 0, int L = 0, int R = MAXQ - 1) {
    
    if(l <= L && R <= r) {
        
        st[N].offset = i64(st[N].offset) * x % MOD;
        st[N].offsetMul = i64(st[N].offsetMul) * x % MOD;
        st[N].offsetAdd = i64(st[N].offsetAdd) * x % MOD;
        st[N].stride = i64(st[N].stride) * x % MOD;
        st[N].strideMul = i64(st[N].strideMul) * x % MOD;
        return;
        
    }
    push(N);
    int M = (L + R) / 2;
    if(M >= l) mul(l, r, x, st[N].left, L, M);
    if(M < r) mul(l, r, x, st[N].right, M + 1, R);
    
}
void set(int g, int offset, int stride, int N = 0, int L = 0, int R = MAXQ - 1) {
    
    if(L == R) {
        
        st[N].offset = offset;
        st[N].stride = stride;
        return;
        
    }
    push(N);
    int M = (L + R) / 2;
    if(g <= M) set(g, offset, stride, st[N].left, L, M);
    else set(g, offset, stride, st[N].right, M + 1, R);
    
}
int query(int g, int x, int N = 0, int L = 0, int R = MAXQ - 1) {
    
    if(L == R) {
        
        return (st[N].offset + st[N].stride * i64(x - 1)) % MOD;
        
    }
    push(N);
    int M = (L + R) / 2;
    if(g <= M) return query(g, x, st[N].left, L, M);
    else return query(g, x, st[N].right, M + 1, R);
    
}


int main() {
    
    std::scanf("%d", &q);
    cnt[0] = 0, last[0] = 0, last2[0] = 0, dist[0] = 0;
    init();
    set(0, 0, 1);
    for(int qu = 0; qu < q; ++qu) {
        
        int op;
        std::scanf("%d", &op);
        switch(op) {
        case 1: {
            
            std::scanf("%d", &cnt[++g]);
            if(cnt[g]) {
                
                add(0, g - 1, cnt[g]);
                set(g, 0, 1);
                last[g] = last[g - 1];
                last2[g] = g;
                dist[g] = dist[g - 1] + cnt[g];
                
            } else {
                
                mul(0, g - 1, 2);
                set(g, 1, 2);
                last[g] = g;
                last2[g] = last2[g - 1];
                dist[g] = 0;
                
            }
            break;
            
        }
        case 2: {
            
            int x, y;
            std::scanf("%d%d", &x, &y);
            int result = query(x, y);
            std::printf("%d\n", result);
            break;
            
        }
        case 3: {
            
            int x;
            std::scanf("%d", &x);
            int result = 0;
            for(int i = g; i > 0; ) {
                
                if(cnt[i]) {
                    
                    if(x < cnt[i]) { result = i; break; }
                    if(x >= dist[i]) {
                        
                        x -= dist[i];
                        i = last[i];
                        
                    } else {
                        
                        int l = last[i] + 1, r = i;
                        while(l < r) {
                            
                            int mid = (l + r) / 2;
                            i64 d = x - (dist[i] - dist[mid]);
                            if(d < 0) l = mid + 1;
                            else r = mid;
                            
                        }
                        result = l;
                        break;
                        
                    }
                    
                } else {
                    
                    if(x & 1) { result = i; break; }
                    if(!x) i = last2[i];
                    else {
                        
                        x /= 2;
                        --i;
                        
                    }
                    
                }
                
            }
            std::printf("%d\n", result);
            break;
            
        }
        }
        
    }
    
}
