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

// Assessment 01 Q6; see 题面.pdf.
namespace aim::q6 {
struct Target { int id; int x; int y; int hp; bool visible; };

// BEGIN IMPLEMENTATION
int select_target(const std::vector<Target>& targets, int max_range) { 
    //最多 100000 个目标；id 非负且互不相同，x、y 绝对值 ≤106，hp∈[-100,100]，visible 为 bool。
    //如果 targets 为空或 max_range 小于 0，返回 -1。
    if(targets.empty() || max_range<0){
        return -1;
    }
    const long long r2 = 1LL * max_range * max_range;
    std::vector<Target> AVAILABLE;
    for(int i=0;i<(int)targets.size();i++){
        const long long dx = targets[i].x;
        const long long dy = targets[i].y;
        if(targets[i].visible && targets[i].hp>0 && dx*dx+dy*dy<=r2){
            AVAILABLE.push_back(targets[i]);
        }
    }
    std::vector<Target> minIdx; 
    std::vector<Target> minIdx2;
    int ans = -1;

    if (AVAILABLE.empty()) {
        return -1;
    }

    // 2. 找最低血量，并收集所有最低血量的目标
    int minHp = INT_MAX;
    for (const auto& t : AVAILABLE) {
        if (t.hp < minHp) {
            minHp = t.hp;
        }
    }

    for (int i = 0; i < (int)AVAILABLE.size(); ++i) {
        if (AVAILABLE[i].hp == minHp) {
            minIdx.push_back(AVAILABLE[i]);
        }
    }

    // 3. 在最低血量的目标中，寻找最近的距离平方
    long long mindistance = LLONG_MAX;
    for (const auto& t : minIdx) {
        const long long dx = t.x;
        const long long dy = t.y;
        const long long dist_sq = dx*dx + dy*dy;
        if (dist_sq < mindistance) {
            mindistance = dist_sq;
        }
    }
    // 4. 收集距离平方等于最小值的候选
    for (const auto& t : minIdx) {
        const long long dx = t.x;
        const long long dy = t.y;
        const long long dist_sq = dx*dx + dy*dy;
        if (dist_sq == mindistance) {
            minIdx2.push_back(t);
        }
    }

    // 5. 在距离相同的候选中，选择最小 id
    int minid = INT_MAX;
    for (const auto& t : minIdx2) {
        if (t.id < minid) {
            minid = t.id;
        }
    }
    for (const auto& t : minIdx2) {
        if (t.id == minid) {
            ans = t.id;
        }
    }

    return ans;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q6;
int main() {
    try {
        { CHECK(select_target({{7,3,4,20,true},{2,0,5,20,true}},5)==2); }
        { CHECK(select_target({},5)==-1); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
