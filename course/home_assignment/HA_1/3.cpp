#include <vector>
#include <algorithm>
#include <iostream>

struct Interval{
    double start;
    double end;
};

int main(){
    std::vector<Interval> intervals = {{1.0, 3.0}, {2.0, 4.0}, {5.0, 7.0}, {6.0, 8.0}};

    std::sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b){
        return a.end < b.end;
    });

    std::vector<Interval> ans = {intervals[0]};

    for(size_t i = 1; i < intervals.size(); ++i){
        if(intervals[i].start > ans.back().end){
            ans.push_back(intervals[i]);
        }
    }

    for (const Interval& interval : ans){
        std::cout << "[" << interval.start << ", " << interval.end << "] ";
    }
}