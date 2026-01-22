#include <vector>
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, -4 , 2, 6, -5, -4, 3};

    size_t first_ind;
    size_t second_ind;

    // case when s_1 > 0, s_2 > 0
    {
        int s_1 = 0;
        int s_2 = 0;

        for (size_t i = 0; i < vec.size(); ++i) {
            s_1 += vec[i];
            if (s_1 > 0){
                first_ind = i;
                break;
            }
        }
        for (size_t i = first_ind + 1; i < vec.size(); ++i) {
            s_2 += vec[i];
            if (s_2 > 0){
                second_ind = i;
                break;
            }
        }
    }
    //case when s_1 > 0, s_3 > 0
    {
        int s_1 = 0;
        int s_3 = 0;

        for (size_t i = 0; i < vec.size(); ++i) {
            s_1 += vec[i];
            if (s_1 > 0){
                first_ind = i;
                break;
            }
        }
        for (size_t i = vec.size() - 1; i > first_ind; --i) {
            s_3 += vec[i];
            if (s_3 > 0){
                second_ind = i;
                break;
            }
        }
    }
    //case when s_2 > 0, s_3 > 0
    {
        int s_2 = 0;
        int s_3 = 0;

        for (size_t i = vec.size() - 1; i > 0; --i) {
            s_3 += vec[i];
            if (s_3 > 0){
                second_ind = i;
                break;
            }
        }
        for (size_t i = second_ind - 1; i > 0; --i) {
            s_2 += vec[i];
            if (s_2 > 0){
                first_ind = i;
                break;
            }
        }
    }

    std::cout << first_ind << " " << second_ind << std::endl;
}