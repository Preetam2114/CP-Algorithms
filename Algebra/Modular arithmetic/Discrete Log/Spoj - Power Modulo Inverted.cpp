/*
 * File: Spoj - Power Modulo Inverted
 * Algorithm: Discrete Log
 * Created Date: Thursday August 6th 2020
 * Author: preetam rane
 */


#include <bits/stdc++.h>

#define MOD 123456
using namespace std;

typedef long long ll;
const int HashMod=123456;

struct node{
	struct Line{int val,id,nex;}e[100000];
	int h[HashMod],cnt;
	void add(int x,int y,int k)
	{
		e[++cnt]=(Line){x,y,h[k]};
		h[k]=cnt;
	} 
	void clear(){memset(h,-1,sizeof(h));cnt=0;} 
	void insert(int x,int y)
	{
		int k=x%HashMod;
		add(x,y,k);
	}
	int find(int x)
	{
		int k=x%HashMod;
		for(int i=h[k];i!=-1;i=e[i].nex)
			if(e[i].val==x)
				return e[i].id;
		return -1;
	}
}Hash;

int gcd(int a, int b) {
    if (!a || !b)
        return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b)
            swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}

ll qsm(ll a,ll b,ll p)
{
	ll t=1;
	while(b>0)
	{
		if(b&1)
		{
			t=t*a%p;
		}
		a=a*a%p;
		b>>=1;
	}
	return t%p;
}

int ex_BSGS(int a,int b,int p)
{
	if(b==1) return 0;
	int k=0,ac=1;
	while(1)
	{
		int d=gcd(a,p);
		if(d==1) break;
		if(b%d) return -1;
		b/=d;p/=d;k++;
		ac=1ll*ac*a/d%p;
		if(b==ac)return k;
	}
	Hash.clear();
	int m=sqrt(p)+1;
	ll t=b;
	for(int i=0;i<m;i++){
		Hash.insert(t,i);
		t=t*a%p;
	}
	ll tt=qsm(a,m,p);
	t=ac*tt%p;
	for(int i=1;i<=m;i++) 
	{
		int j=Hash.find(t);
		t=t*tt%p;
		if(j==-1) continue;
		return i*m-j+k;
	}
	return -1;
}

int main()
{
	int a,b,p;
	while(scanf("%d%d%d",&a,&p,&b),a+b+p) 
	{
		int ans=ex_BSGS(a,b,p);
		if(ans==-1) puts("No Solution");
		else printf("%d\n",ans);
	}
	
	return 0;
}

