#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class maze2d{
	vector<vector<int> > grid;
	vector<vector<bool> > visited;
	int xdir[4] = {1,0,-1,0};
	int ydir[4] = {0,1,0,-1};
	int dd[4] = {1,2,4,8};   //1: South 2: East  4: North  8:West
	int m,n;
public:
	void generate(int _x,int _y){
		if(_x<0||_x>=m||_y<0||_y>=n){
			cout<<"invalid input!"<<endl;
			return;
		}
		pair<int,int> cur;
		stack<pair<int,int> > st;
		st.push({_x,_y});
		while(!st.empty()){
			cur = st.top();
			visited[cur.first][cur.second] = true;
			//cout<<cur.first<<" "<<cur.second<<endl;
			vector<int> dir;
			for(int i = 0;i <4;i++){
				int nx = cur.first+xdir[i];
				int ny = cur.second+ydir[i];
				if(nx >=0&&nx<m&&ny>=0&&ny<n&&visited[nx][ny]==false){
					dir.push_back(i);
				}
			}
			if(!dir.empty()){
				int ir = rand()%dir.size();
				grid[cur.first][cur.second] |= dd[dir[ir]];
				st.push({cur.first+xdir[dir[ir]],cur.second+ydir[dir[ir]]});
			}else{
				st.pop();
			}
		}
		
	}
	maze2d(int _m,int _n){
		grid = vector<vector<int> >(_m,vector<int>(_n,0));
		visited = vector<vector<bool> >(_m,vector<bool>(_n,false));
		m = _m;
		n = _n;
	}
	void display(){
		for(int i = 0;i < m;i++){
			for(int j = 0;j < n;j++){
				cout<<grid[i][j]<<" ";
			}	
			cout<<endl;
		}	
		cout<<endl;	
	}
	
};


int main(){
	int m,n;
	while(cin>>m>>n&&m&&n){
		maze2d mz(m,n);
		mz.generate(0,0);
		mz.display();
	}
}
