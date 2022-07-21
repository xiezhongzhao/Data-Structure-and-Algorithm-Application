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

class dp{
public:
    void bagProblem(){
        vector<int> weight = {1, 3, 4};
        vector<int> value = {15, 20, 30};
        int bagweight = 4;

        vector<vector<int>> dp(weight.size(), vector<int>(bagweight+1, 0));

        for(int j=weight[0]; j<=bagweight; j++){
            dp[0][j] = value[0];
        }

        for(int i=1; i<weight.size(); i++){
            for(int j=0; j<=bagweight; j++){
                if(j < weight[i])
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i]]+value[i]);
            }
        }
        cout << dp[weight.size()-1][bagweight] << endl;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

//    vector<int> a = {1,2,3};
//    Solution s;
//    vector<vector<int>> res = s.permute(a);
//
//    for(int i=0; i<res.size(); i++){
//        for(int j=0; j<res[0].size(); j++){
//            cout << res[i][j] << ", ";
//        }
//        cout << "\n";
//    }

    dp bag;
    bag.bagProblem();
    return 0;
}



