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

// Assessment 01 Q1; see 题面.pdf.
namespace aim::q1 {


// BEGIN IMPLEMENTATION
long long ratio(long long hp, long long max_hp) {
    if (max_hp <= 0) return -1;                      // 最大值无效，不除法
    if (hp < 0) hp = 0;                              // 负血量先归零
    if (hp > max_hp) hp = max_hp;                    // 超过上限先夹到上限
    return hp * 100 / max_hp;                        // 整数部分，截断不四舍五入
}

std::string report(int id, long long hp, long long max_hp, int battery) {
    std::string hp_field;
    if (max_hp <= 0) {
        hp_field = "INVALID";                        // 最大血量无效时 HP 写 INVALID
    } else {
        hp_field = std::to_string(ratio(hp, max_hp));// 否则写整数百分比
    }
    int b = battery;                                 // 局部副本，不改动入参
    if (b < 0) b = 0;                                // 电量夹到 [0,100]
    if (b > 100) b = 100;
    std::string state;
    if (b >= 60) state = "OK";                       // >=60 OK
    else if (b >= 20) state = "WARNING";             // 20..59 WARNING
    else state = "LOW";                              // <20 LOW
    return "ID=" + std::to_string(id) + ";HP=" + hp_field + ";BAT=" + std::to_string(b) + ";STATE=" + state;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q1;
int main() {
    try {
        { CHECK(ratio(2,3)==66); }
        { CHECK(report(7,2,3,20)=="ID=7;HP=66;BAT=20;STATE=WARNING"); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
