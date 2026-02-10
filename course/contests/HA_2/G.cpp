#include <iostream>
#include <vector>
#include <algorithm>

struct Property {
    long long mass;
    long long volume;
    double density;
    int id;
};

int main() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<Property> properties(n);
    for (int i = 0; i != n; ++i) {
        long long m, v;
        std::cin >> m >> v;
        properties[i].mass = m;
        properties[i].volume = v;
        properties[i].density = static_cast<double>(m) / v;
        properties[i].id = i;
    }
    
    std::stable_sort(properties.begin(), properties.end(), 
              [](const Property& a, const Property& b) {
                  return a.density > b.density;
              });

    std::vector<int> selected_ids;
    for (int i = 0; i < k; ++i) {
        selected_ids.push_back(properties[i].id);
    }
    std::sort(selected_ids.begin(), selected_ids.end());
    
    // Output in input order
    for (int id : selected_ids) {
        std::cout << id + 1 << std::endl;
    }
    
    return 0;
}