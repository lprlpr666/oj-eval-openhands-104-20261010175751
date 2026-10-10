#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

vector<int> bfs(const vector<vector<int>>& a, int n, int m, pair<int,int> src) {
    const int INF = 1e9;
    vector<int> d(n*m, INF);
    queue<pair<int,int>> q;
    d[src.first*n + src.second] = 0;
    q.push(src);
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while(!q.empty()) {
        auto cur = q.front(); q.pop();
        int x = cur.first;
        int y = cur.second;
        for(auto &dr : dirs) {
            int nx = x + dr[0];
            int ny = y + dr[1];
            if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            if(a[nx][ny] == 1) continue;
            if(d[nx * n + ny] == INF) {
                d[nx * n + ny] = d[x * n + y] + 1;
                q.emplace(nx, ny);
            }
        }
    }
    return d;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; if(!(cin>>n>>m)) return 0;
    vector<vector<int>> a(m, vector<int>(n));
    pair<int,int> s{-1,-1}, t{-1,-1};
    vector<pair<int,int>> umb;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int v;cin>>v;a[i][j]=v;
            if(v==2) s={i,j};
            else if(v==3) t={i,j};
            else if(v==4) umb.emplace_back(i,j);
        }
    }
    if(s.first==-1||t.first==-1||umb.empty()){
        cout<<-1<<"\n";return 0;
    }
    vector<int> ds = bfs(a, n, m, s);
    vector<int> dt = bfs(a, n, m, t);
    const int INF = 1e9;
    int ans = INF;
    for(auto &p: umb){
        int d1 = ds[p.first*n + p.second];
        int d2 = dt[p.first*n + p.second];
        if(d1!=INF && d2!=INF) ans = min(ans, d1+d2);
    }
    if(ans==INF) cout<<-1<<"\n"; else cout<<ans<<"\n";
    return 0;
}
