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

// Assessment 01 Q8; see 题面.pdf.
namespace aim::q8 {
struct Telemetry { int id; int hp; };
struct Summary { int valid; int duplicate; int invalid; long long total_hp; std::vector<int> ids; };

// BEGIN IMPLEMENTATION
Summary summarize(const std::vector<Telemetry>& frames) { int valid = 0;
    int duplicate = 0;
    int invalid = 0;
    long long total_hp = 0;

    std::vector<bool> seen(10000, false);
    std::vector<int> ids;

    for (const Telemetry& f : frames) {
        // 第一步：范围验证
        if (f.id < 0 || f.id > 9999 || f.hp < -1000 || f.hp > 1000) {
            invalid++;
            continue;  // 非法记录直接结束本条
        }

        // 到这里 id 一定在 [0,9999]，可以安全访问 seen[f.id]
        if (seen[f.id]) {
            // 合法但重复
            duplicate++;
            continue;
        }

        // 首次合法
        valid++;
        seen[f.id] = true;
        ids.push_back(f.id);

        // hp 夹到 [0,100]
        int normalized = f.hp;
        if (normalized < 0) normalized = 0;
        if (normalized > 100) normalized = 100;

        total_hp += normalized;
    }

    // ids 升序：可以排序，也可以最后扫描 seen
    std::sort(ids.begin(), ids.end());

    return Summary{valid, duplicate, invalid, total_hp, ids};
} 
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q8;
int main() {
    try {
        { aim::q8::Summary r=summarize({{2,200},{1,-5},{2,10},{-1,30}}); CHECK(r.valid==2 && r.duplicate==1 && r.invalid==1 && r.total_hp==100 && (r.ids==std::vector<int>{1,2})); }
        { aim::q8::Summary r=summarize({{1,-1001},{1,30},{1,1001}}); CHECK(r.valid==1 && r.duplicate==0 && r.invalid==2 && r.total_hp==30 && (r.ids==std::vector<int>{1})); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
