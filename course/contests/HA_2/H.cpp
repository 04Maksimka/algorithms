#include <vector>
#include <algorithm>
#include <iostream>

struct Team {
    int id;
    int problems_solved;
    int penalty_time;
};

int main() {
    int n;
    std::cin >> n;
    
    std::vector<Team> teams(n);
    for (int i = 0; i != n; ++i) {
        int p, t;
        std::cin >> p >> t;
        teams[i].id = i + 1;
        teams[i].problems_solved = p;
        teams[i].penalty_time = t;
    }

    std::stable_sort(teams.begin(), teams.end(),
              [](const Team& a, const Team& b) {
                  if (a.problems_solved != b.problems_solved) {
                      return a.problems_solved > b.problems_solved;
                  }
                  if (a.penalty_time != b.penalty_time) {
                      return a.penalty_time < b.penalty_time;
                  }
                  return a.id < b.id;
              });
    
    for (int i = 0; i != n; ++i) {
        std::cout << teams[i].id << " ";
    }
    
    return 0;
}