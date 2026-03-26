// Element query using binary search
#include <iostream>
#include <vector>

int Query(std::vector<int> data, int key) {
    int n = (int)data.size();
    if (key > data[n - 1] || key < data[0]) {
        return - 1;
    }

    int l = 0;
    int u = n - 1;

    while(l <= u) {
        if (u - l == 1 && key > data[l] && key < data[u]) {
            return -1;
        }

        int m = (l + u) / 2;
        if (data[m] < key) {
            l = m;
        }
        else if (data[m] > key) {
            u = m;
        }
        else {
            return m;
        }
    }
}

int main () {
    std::vector<int> data = {7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

    int key1 = 23;
    int key2 = 38;

    std::cout << "Key1 = " << Query(data, key1) << ", Key2 = " << Query(data, key2);


}
