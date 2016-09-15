#include<cstdio>  
#include<cstring>  
#include<climits>  
#include<algorithm>  
using namespace std;  
const int MAXN=55555,INF=1<<30;  
struct ARC{  
    int last,next,data;  
    void init(){  
        next=last=0;  
        data=INF;  
    }  
}arc[MAXN];  
void in(int &cnt)  
{  
    arc[cnt].next=cnt+1;  
    arc[cnt+1].last=cnt;  
    scanf("%d",&arc[++cnt].data);  
}  
void del(int u)  
{  
    arc[arc[u].last].next=arc[u].next;  
    arc[arc[arc[u].last].next].last=arc[u].last;  
}  
void reinsert(int x,int u)  
{  
    for(int i=arc[u].last;;i=arc[i].last) if(arc[i].data>x)  
    {  
        arc[u].last=i;  
        arc[u].data=x;  
        arc[u].next=arc[i].next;  
        arc[arc[u].next].last=u;  
        arc[i].next=u;  
        return;  
    }  
}  
void work(int n)  
{  
    int ans=0,cnt=0;  
    for(int i=0;i<=n+1;i++) arc[i].init();  
    for(int i=1;i<=n;i++) in(cnt);  
    for(int i=1;i<n;i++) for(int j=arc[0].next;j;j=arc[j].next)  
    {  
        int l=arc[j].last,r=arc[j].next;  
        if(arc[l].data<=arc[r].data)  
        {  
            del(l);  
            del(j);   
            int weight=arc[l].data+arc[j].data;  
            ans+=weight;  
            reinsert(weight,j);  
            break;  
        }  
    }  
    printf("%d\n",ans);  
    return;  
}  
int main()  
{  
    int n;  
    while(scanf("%d",&n)!=EOF&&n) work(n);  
}  
