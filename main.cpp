//
// Created by ASUS on 2022/5/18.
//
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

class Solution {
public:
//输入：nums = [1,2,3]
//输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
    vector<vector<int>> res;
    vector<int> path;
    void backtracking(vector<int>& nums, vector<bool>& used){
        if(path.size() == nums.size()){
            res.push_back(path);
            return ;
        }

        for(int i=0; i<nums.size(); i++){
            if(used[i] == true)
                continue;
            used[i] = true;
            path.push_back(nums[i]);
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        res.clear();
        path.clear();

        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return res;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<int> a = {1,2,3};
    Solution s;
    vector<vector<int>> res = s.permute(a);

    for(int i=0; i<res.size(); i++){
        for(int j=0; j<res[0].size(); j++){
            cout << res[i][j] << ", ";
        }
        cout << "\n";
    }
    return 0;
}



