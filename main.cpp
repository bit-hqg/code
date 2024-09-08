#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Task {
    int dep;
    int r;
    int s;
};

int maxScore(int N,int R, vector<Task>& tasks) {
    vector<int> inDegree(N,0);
    vector<vector<int>> adj(N);

    for (int i=0;i<N;++i) {
        if (tasks[i].dep!=-1) {
            adj[tasks[i].dep].push_back(i);
            inDegree[i]++;
        }
    }

    vector<int> topoOrder;
    queue<int> q;
    for (int i=0;i<N;++i) {
        if (inDegree[i]==0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        for (int v:adj[u]) {
            inDegree[v]--;
            if (inDegree[v]==0) {
                q.push(v);
            }
        }
    }
    vector<int> dp(R+1,0);

    for(int task:topoOrder) {
        int r = tasks[task].r;
        int s = tasks[task].s;

        for (int j=R;j>=r;--j) {
            dp[j]=max(dp[j],dp[j-r]+s);
        }
    }
    return *max_element(dp.begin(),dp.end());
}

int main() {
    int N,R;
    cin>>N>>R;

    vector<Task> tasks(N);
    for (int i=0;i<N;++i) {
        cin>>tasks[i].dep>>tasks[i].r>>tasks[i].s;
        
    }

    cout<<maxScore(N,R,tasks)<<endl;
    return 0;
}