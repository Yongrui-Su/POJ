class NumMatrix {
private:
    vector<vector<int> > tree;
    vector<vector<int> > num;
public:
    NumMatrix(vector<vector<int>> &matrix) {
        if(matrix.size()==0||matrix[0].size()==0)return;
        tree = vector<vector<int> >(matrix.size()+1,vector<int>(matrix[0].size()+1,0));
        num = vector<vector<int> >(matrix.size(),vector<int>(matrix[0].size(),0));
        for(int i = 1;i <= matrix.size();i++)
        for(int j = 1;j <= matrix[0].size();j++){
            update(i-1,j-1,matrix[i-1][j-1]);
        }
    }

    void update(int row, int col, int val) {
        int diff = val - num[row][col];
        for(int i= row+1;i <tree.size();i+=i&(-i))
        for(int j= col+1;j < tree[0].size();j += j&(-j)){
            tree[i][j] += diff;
        }
        num[row][col] = val;
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return get_sum(row2,col2)+get_sum(row1-1,col1-1)-get_sum(row1-1,col2)-get_sum(row2,col1-1);
    }
    int get_sum(int row,int col){
        int res = 0;
        for(int i = row+1;i >0;i -= i&(-i))
        for(int j = col+1;j >0;j -= j&(-j)){
            res += tree[i][j];
        }
        return res;
    }
};


// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.update(1, 1, 10);
// numMatrix.sumRegion(1, 2, 3, 4);
