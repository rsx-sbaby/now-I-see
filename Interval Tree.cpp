#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
#define size 666
#define fake ll 
const int Maxn=100001;
struct TreeNode{
	fake l,r,sum,lazy;
}tree[Maxn*4];
fake n,m,a[Maxn];
fake read(){
	fake x=0;
	bool f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=1;
		ch=getchar();
	}
	while(ch<='9'&&ch>='0'){
		x=(x<<1)+(x<<3)+(ch-'0');
		ch=getchar();
	}
	return f?-x:x;
}
fake ls(fake p){return p<<1;}
fake rs(fake p){return p<<1|1;}
void update(fake k){tree[k].sum=tree[ls(k)].sum+tree[rs(k)].sum;}
void build(fake l,fake r,fake k){
	tree[k].l=l,tree[k].r=r;
	if(l==r){tree[k].sum=a[l];return ;}
	fake mid=(l+r)>>1;
	build(l,mid,ls(k));
	build(mid+1,r,rs(k));
	update(k);
	return ;
}
void f(fake k,fake x){
	tree[k].sum+=(tree[k].r-tree[k].l+1)*x;
	tree[k].lazy+=x;
}
void push_down(fake k){
	fake mid=(tree[k].l+tree[k].r)>>1;
	f(ls(k),tree[k].lazy);
	f(rs(k),tree[k].lazy);
	tree[k].lazy=0;
}
void chS(fake k,fake l,fake r,fake x){
//当前到了编号为k的节点，要把[l..r]区间中的所有元素的值+x
	if(tree[k].l>=l&&tree[k].r<=r){
		tree[k].sum+=(tree[k].r-tree[k].l+1)*x;
		tree[k].lazy+=x;
		return ;
	}
	push_down(k);
	fake mid=(tree[k].l+tree[k].r)>>1;
	if(l<=mid) chS(ls(k),l,r,x);
	if(r>mid) chS(rs(k),l,r,x);
	update(k);
}
fake query(fake l,fake r,fake k){
	fake res=0;
	if(l<=tree[k].l&&tree[k].r<=r) return tree[k].sum;
	fake mid=(tree[k].l+tree[k].r)>>1;
	push_down(k);
	if(l<=mid) res+=query(l,r,ls(k));
	if(r>mid) res+=query(l,r,rs(k));
	return res;
}
fake w,b,c,d;
int main(){
	freopen("Interval Tree.in","r",stdin);
	n=read();m=read();
	for(int i=1;i<=n;i++){a[i]=read();}
	build(1,n,1);
	for(int i=1;i<=m;i++){
		w=read();b=read();c=read();
		if(w==2) printf("%lld\n",query(b,c,1));
		if(w==1){
			d=read();
			chS(1,b,c,d);
		}
	}
	return 0;
}
