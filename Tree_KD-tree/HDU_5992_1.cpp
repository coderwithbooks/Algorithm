/*
  AC code for HDU 5992 [374MS	11396K]
  kd树
      1.构建: 使用前两维; 维护每个点代表的空间
      2.查询:
      3.剪枝: 使用到分割平面距离
 */

#include <stdio.h>
#include <algorithm>

using namespace std;
#define ll long long
const ll maxn = 2e5+10;
const ll INF = 1e16;

int n, m, cmp_d, root;
int query_data[3];

ll jl , ans ;

struct node {
    int l , r ;
    int d[3] , Max[3] , Min[3] ;
    int c ;
    int id ;
}a[maxn];
bool cmp(node a , node b ){
    return a.d[cmp_d] < b.d[cmp_d] ;
}
void up(int p , int k ) {
    for(int i = 0; i < 3 ; i ++ ){
        a[p].Min[i] = min(a[p].Min[i] , a[k].Min[i]) ;
        a[p].Max[i] = max(a[p].Max[i] , a[k].Max[i]) ;
    }
}
ll build(int l, int r , int D) {
    cmp_d = D;
    int mid = (l+r)/2 ;
    nth_element(a+l,a+mid,a+1+r,cmp); //
    for(int i = 0 ;i < 3 ; i ++) a[mid].Min[i] = a[mid].Max[i] = a[mid].d[i] ;
    if(l != mid) a[mid].l = build(l,mid-1,(D+1)%2) ; else a[mid].l = 0 ;
    if(r != mid) a[mid].r = build(mid+1,r,(D+1)%2) ; else a[mid].r = 0 ;
    if(a[mid].r)up(mid,a[mid].r);
    if(a[mid].l)up(mid,a[mid].l);

    return mid ;

}


ll getdis_2(int p, int dim){

    // 计算查询点距离某一个子树的距离

    ll res_dis = 0;
    res_dis = 1ll*(query_data[dim]-a[p].d[dim])*(query_data[dim]-a[p].d[dim]); //计算出到划分超平面的距离

    return res_dis;


}
void ask(int p, int dep=0) {
    // 根据p和划分线的距离判定
    ll d0 = 0 ;
    ll dl , dr;
    int dim = dep%2;
    if(a[p].d[2] > query_data[2])d0 += INF ;
    if(d0 == 0) {
        d0 += 1ll*((a[p].d[0]) - query_data[0]) * ((a[p].d[0]) - query_data[0]) + 1ll*((a[p].d[1]) - query_data[1]) * ((a[p].d[1]) - query_data[1]);
        if(d0 < jl){
            ans = p ;
            jl = d0 ;
        }
        else if(d0 == jl) {
            if(a[p].id < a[ans].id) {
                ans = p;
            }
        }
    }

    if(a[p].l && query_data[dim] < a[p].d[dim]){
        ask(a[p].l, dep+1) ;
        if(a[p].r)dr = getdis_2(p, dim); else dr = INF + 1 ;
        if(a[p].r && dr < jl) ask(a[p].r, dep+1) ;
    }
    else if(a[p].r){
        ask(a[p].r, dep+1) ;
        if(a[p].l)dl = getdis_2(p, dim); else dl = INF + 1 ;
        if(a[p].l && dl < jl) ask(a[p].l, dep+1) ;
    }

}

int main(){
    int t;
    scanf("%d",&t);
    while(t-- ) {
        scanf("%d%d",&n,&m) ;
        for(int i=1;i<=n;i++){
            for(int k=0;k<3;k++)scanf("%d",&a[i].d[k]) ;
            a[i].l = a[i].r = 0 ;
            a[i].id = i ;
        }

        root = build(1,n,0);

        for(int i=1;i<=m;i++){
            scanf("%d%d%d",query_data,query_data+1,query_data+2);
            jl = INF ;
            ans = -1 ;
            ask(root);
            printf("%d %d %d\n",a[ans].d[0],a[ans].d[1],a[ans].d[2]) ;
        }

    }
}
