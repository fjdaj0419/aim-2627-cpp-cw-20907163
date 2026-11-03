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

// Assessment 01 Q3; see 题面.pdf.
namespace aim::q3 {


// BEGIN IMPLEMENTATION
std::vector<int> alarms(const std::vector<int>& values, int k, long long threshold) { 
  if (values.empty()) return {};
    if (k < 1 || k > static_cast<int>(values.size())) return {};
    std::vector<int> number;
    long long sum = 0;
    for (int j = 0; j < k; ++j) {
        sum += values[j];
    }
    if (sum > threshold) number.push_back(k - 1);
    for (int i = 1; i + k - 1 < static_cast<int>(values.size()); ++i) {
        sum += static_cast<long long>(values[i + k - 1])  
             - static_cast<long long>(values[i - 1]);     
        if (sum > threshold) number.push_back(i + k - 1);
    }
    return number;
    }
 }

// END IMPLEMENTATION


#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q3;
int main() {
    try {
        { CHECK((alarms({1,2,3,4},2,4)==std::vector<int>{2,3})); }
        { CHECK(alarms({},1,0).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
