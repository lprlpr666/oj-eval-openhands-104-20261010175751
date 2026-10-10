#include <iostream>
#include <vector>
#include <deque>
#include <utility>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m; // n columns, m rows
    if(!(cin>>n>>m)) return 0;
    vector<vector<int>> grid(m, vector<int>(n));
    pair<int,int> start{-1,-1}, home{-1,-1};
    vector<pair<int,int>> umbrellas;
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            int v;cin>>v;grid[i][j]=v;
            if(v==2) start={i,j};
            else if(v==3) home={i,j};
            else if(v==4) umbrellas.emplace_back(i,j);
        }
    }
    const int INF = 1e9;
    auto bfs = [&](pair<int,int> src){
        vector<int> dist(m*n, INF);
        deque<pair<int,int>> q;
        int si=src.first, sj=src.second;
        dist[si*n+sj]=0;
        q.emplace_back(si,sj);
        int dirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        while(!q.empty()){
            auto cur = q.front(); q.pop_front();
            int i = cur.first;
            int j = cur.second;
            int d = dist[i*n + j];
            for(auto &dr: dirs){
                int ni = i + dr[0];
                int nj = j + dr[1];
                if(ni < 0 || ni >= m || nj < 0 || nj >= n) continue;
                if(grid[ni][nj] == 1) continue; // blocked
                if(dist[ni*n + nj] == INF){
                    dist[ni*n + nj] = d + 1;
                    q.emplace_back(ni, nj);
                }
            }
        }
        return dist;
    };
    if(start.first==-1||home.first==-1||umbrellas.empty()){
        cout<<-1<<"\n"; // no solution
        return 0;
    }
    auto dist_start = bfs(start);
    auto dist_home = bfs(home);
    int ans=INF;
    for(auto &p:umbrellas){
        int d1 = dist_start[p.first*n + p.second];
        int d2 = dist_home[p.first*n + p.second];
        if(d1!=INF && d2!=INF) ans = min(ans, d1+d2);
    }
    if(ans==INF) cout<<-1<<"\n"; else cout<<ans<<"\n";
    return 0;
}
