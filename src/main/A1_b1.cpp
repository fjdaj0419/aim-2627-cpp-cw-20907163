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

// Assessment 01 B1; see 题面.pdf.
namespace aim::b1 {


// BEGIN IMPLEMENTATION
using namespace std;
bool parse_i32(const std::string& text, int& output) { throw std::runtime_error("TODO"); }
int ratio (int hp, int max_hp) { 
    if (hp<=0 || max_hp<=0) {
        return -1;
    }
    max_hp = max(0,max_hp);
    
    return hp*100/max_hp; }

    string report(int id, long long hp, long long max_hp, int battery) { 
    battery = max(0,battery);
    battery = min(100,battery);
    if (battery>=60) {
        cout << "ID=" << id << ";" <<"HP=" << hp << ";" <<"BAT=" << battery << ";" <<"BATTERY=" << "OK" << ";" <<endl;
    }
    else if (battery>=20 && battery<60) {
        cout << "ID=" << id << ";" <<"HP=" << hp << ";" <<"BAT=" << battery << ";" <<"BATTERY=" << "WARNING" << ";" <<endl;
    }
    else {
        cout << "ID=" << id << ";" <<"HP=" << hp << ";" <<"BAT=" << battery << ";" <<"BATTERY=" << "CRITICAL" << ";" <<endl;
    }
   
   
   
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::b1;
int main() {
    try {
        { int x=9; CHECK(parse_i32("-12",x) && x==-12); }
        { int x=9; CHECK(!parse_i32("12x",x) && x==9); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
