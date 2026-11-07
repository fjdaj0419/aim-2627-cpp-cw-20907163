#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q5; see 题面.pdf.
namespace aim::q5 {


// BEGIN IMPLEMENTATION
std::vector<std::vector<int>> risk(const std::vector<std::string>& grid) { 
    if(grid.empty()){
        return {};
    }

    //检查每一行:
        //如果某一行为空，抛 invalid_argument
    for(int i=0;i<grid.size();i++){
        if(grid[i].empty()){
            throw std::invalid_argument("grid is empty");
        }
    }
    //如果某一行长度和第一行不同，抛 invalid_argument
    for(int i=0;i<grid.size();i++){
        if(grid[i].size()!=grid[0].size()){
            throw std::invalid_argument("grid is not a rectangle");
        }
    }
    // 如果某个字符不是 '.' 也不是 '#'，抛 invalid_argument
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            if(grid[i][j]!='.' && grid[i][j]!='#'){
                throw std::invalid_argument("grid contains invalid character");
            }
        }
    }
    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<int>> ans(rows);
    for (int r = 0; r < rows; ++r) {
        ans[r].assign(cols, 0);
    }  
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '#') {
                ans[r][c] = -1;
            }else {
                ans[r][c] = 0;
                int count = 0;
                if (r-1 >= 0 && grid[r-1][c] == '#') {
                        count++;
                    }
                    if (r+1 < rows && grid[r+1][c] == '#') {
                        count++;
                    }
                    if (c-1 >= 0 && grid[r][c-1] == '#') {
                        count++;
                    }

                    if (c+1 < cols && grid[r][c+1] == '#') {
                        count++;
                    }

                ans[r][c] = count;
            }        
        }            
    }              

    return ans;      
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q5;
int main() {
    try {
        { CHECK((risk({".#",".."})==std::vector<std::vector<int>>{{1,-1},{0,1}})); }
        { CHECK(risk({}).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
