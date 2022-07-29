#include <iostream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;
int N;
struct PROC{
    int r;
    int c;
    int v;
};

vector<vector<int> > map;
vector<vector<int> > visited;
deque<PROC> proc;
int MIN_CNT=INT_MAX;


void debug(){
    /* debug start */
    cout << "--------------------------\n";
    for(int i=0; i<map.size();i++){
        for(int j=0; j<map[i].size(); j++){
            cout << map[i][j] << ' ';
        }
        cout << "   ";
        for(int j=0; j<visited[i].size(); j++){
            if(visited[i][j]==-1){
                cout << 'X' << ' ';
            } else {
                cout << visited[i][j] << ' ';
            }
        }
        cout << '\n';
    }
    cout << "--------------------------\n";
    /* debug end */
}

bool check(int r,int c,int k){
    if(k==0){
        // k == 0 -> up
        for(int i=r; i>=0; i--){
            if(i==r)
                continue;
            if(visited[i][c] == 1)
                return false;
        }
    } else if(k==1){
        // k == 1 -> down
        for(int i=r; i<N; i++){
            if(i==r)
                continue;
            if(visited[i][c] == 1)
                return false;
        }
    } else if(k==2){
        // k == 2 -> left
        for(int j=c; j>=0; j--){
            if(j==c)
                continue;
            if(visited[r][j] == 1)
                return false;
        }
    } else if(k==3){
        // k == 3 -> right
        for(int j=c; j<N; j++){
            if(j==c)
                continue;
            if(visited[r][j] == 1)
                return false;
        }
    }
    return true;
}

void filler(int r,int c,int k){
    if(k==0){
        // k == 0 -> up
        for(int i=r; i>=0; i--){
            if(i==r)
                continue;
            visited[i][c]=1;
        }
    } else if(k==1){
        // k == 1 -> down
        for(int i=r; i<N; i++){
            if(i==r)
                continue;
            visited[i][c]=1;
        }
    } else if(k==2){
        // k == 2 -> left
        for(int j=c; j<N; j++){
            if(j==c)
                continue;
            visited[r][j]=1;
        }
    } else if(k==3){
        // k == 3 -> right
        for(int j=c; j<N; j++){
            if(j==c)
                continue;
            visited[r][j]=1;
        }
    }
}

void remover(int r,int c,int k){
    if(k==0){
        // k == 0 -> up
        for(int i=r; i>=0; i--){
            if(i==r)
                continue;
            visited[i][c]=0;
        }
    } else if(k==1){
        // k == 1 -> down
        for(int i=r; i<N; i++){
            if(i==r)
                continue;
            visited[i][c]=0;
        }
    } else if(k==2){
        // k == 2 -> left
        for(int j=c; j<N; j++){
            if(j==c)
                continue;
            visited[r][j]=0;
        }
    } else if(k==3){
        // k == 3 -> right
        for(int j=c; j<N; j++){
            if(j==c)
                continue;
            visited[r][j]=0;
        }
    }
}

bool isAllProcVisited(){
    int proc_visited_cnt=0;
    for(int i=0;i<proc.size();i++){
        if(proc[i].v==1){
            proc_visited_cnt++;
        }
    }
    if(proc_visited_cnt == proc.size())
        return true;
    return false;
}

void lineCnt(){
    int linecnt=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(visited[i][j] ==1 && map[i][j]==0){
                linecnt++;
            }
        }
    }

    if(MIN_CNT > linecnt){
        MIN_CNT = linecnt;
    }
}

void dfs(){
    if(isAllProcVisited()){
        cout << "All visited\n";
        debug();
        lineCnt();
        cout << MIN_CNT << '\n';
        return;
    }
    int r,c;
    for(int i=0;i<proc.size();i++){
        if(proc[i].v==0){
            r = proc[i].r;
            c = proc[i].c;
            proc[i].v = 1;
            visited[r][c]=1;
            for(int k=0;k<4;k++){
                if(check(r,c,k)){
                    filler(r,c,k);
                    dfs();
                    remover(r,c,k);
                }
            }
            proc[i].v = 0;
            visited[r][c]=0;
        }
    }
}


int main(void){
    freopen("input.txt","r",stdin);
    cin >> N;
    map.resize(N);
    visited.resize(N);

    for(int i=0; i<N; i++){
        map[i].resize(N);
        visited[i].resize(N);
        for(int j=0; j<N;j++){
            cin >> map[i][j];
            if(map[i][j]==1){
                visited[i][j]=1;
                if(i==0 || j==0 || i==N-1 || j==N-1)
                    proc.push_back({i,j,1});
                else
                    proc.push_back({i,j,0});
            }
        }
    }

    debug();

    // 2. Check not visited processor
    int r;
    int c;
    for(int i=0; i<proc.size(); i++){
        if(proc[i].v == 0){
            // processor isn't touched
            r = proc[i].r;
            c = proc[i].c;
            proc[i].v = 1;
            visited[r][c] = 1;
            for(int k=0;k<4;k++){
                if(check(r,c,k)){
                    filler(r,c,k);
                    dfs();
                    remover(r,c,k);
                }
            }
            proc[i].v = 0;
            visited[r][c]=0;
        }
    }
    cout << "min line " << MIN_CNT << '\n';
    return 0;
}