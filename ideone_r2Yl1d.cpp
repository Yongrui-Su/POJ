#include <bits/stdc++.h>

using namespace std;

#define left afafa
#define right afafga

const int maxn = 1e6 + 42, sigma = 26;
int len[maxn], link[maxn], up[maxn];
int to[maxn][sigma];
int s[maxn];
int n, sz, left, right;

void init()
{
    n = -1;
    len[1] = -1;
    link[0] = 1;
    s[++n] = -1;
    sz = 2;
}

int get_link(int v)
{
    while(s[n] != s[n - len[v] - 1])
        v = link[v];
    return v;
}

int cnt[maxn];

set<pair<int, int>> mx;
int check[maxn];
int ln;

int gar[maxn];

void go_right(char c)
{
    ln++;
    s[++n] = c - 'a';
    right = get_link(right);
    if(!to[right][c])
    {
        link[sz] = to[get_link(link[right])][c];
        len[sz] = len[right] + 2;
        up[sz] = right;
        to[right][c] = sz++;
    }
    right = to[right][c];
    if(cnt[right] == 0)
        check[link[right]]++;
    cnt[right]++;
    mx.insert({len[right], right});
    if(len[right] == ln)
        left = right;
    if(len[right] > len[gar[n - len[right] + 1]])
        gar[n - len[right] + 1] = right;
}

int to_sub[maxn];

void go_left()
{
    if(len[left] == ln)
        right = link[right];
    ln--;
    int old_left = left;
    to_sub[left]++;
    while(check[left] == 0 && to_sub[left] == cnt[left])
    {
        check[link[left]]--;
        mx.erase({len[left], left});
        cnt[left] = to_sub[left] = 0;
        left = link[left];
    }
    if(len[right] == ln)
        left = right;
    else if(len[link[old_left]] + 1 == len[old_left])
        left = link[old_left];
    else
        left = up[old_left];
    if(len[gar[n - ln + 1]] > len[left])
        left = gar[n - ln + 1];
}

void solve()
{
    init();
    int n;
    cin >> n;
    string s;
    cin >> s;
    for(auto c: s)
        go_right(c);
    for(int i = 0; i < n; i++)
    {
        cout << prev(mx.end())->first << "\n";
        ::s[i + 1] = -1;
        go_left();
        go_right(s[i]);
        
    }
}

signed main()
{
    //freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while(t--)
        solve();
    return 0;
}
