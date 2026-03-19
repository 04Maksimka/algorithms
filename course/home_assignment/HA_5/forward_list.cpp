#include <iostream>
#include <forward_list>

struct Term {
    int degree;
    double coefficient;
};

void addPolynomialsInPlace(
    std::forward_list<Term>& p1,
    std::forward_list<Term>& p2)
{
    auto prev1 = p1.before_begin();
    auto it1 = p1.begin();
    auto it2 = p2.begin();

    while (it1 != p1.end() && it2 != p2.end()) {

        if (it1->degree == it2->degree) {
            it1->coefficient += it2->coefficient;

            prev1 = it1;

            ++it1;
            ++it2;
        }
        else if (it1->degree < it2->degree) {
            prev1 = it1;
            ++it1;
        }
        else {
            p1.insert_after(prev1, *it2);
            ++prev1;
            ++it2;
        }
    }

    // add remaining terms from p2
    while (it2 != p2.end()) {
        p1.insert_after(prev1, *it2);
        ++prev1;
        ++it2;
    }
}

void printPolynomial(const std::forward_list<Term>& poly) {
    for (auto it = poly.begin(); it != poly.end(); ++it) {
        std::cout << it->coefficient << "x^" << it->degree;
        auto next = it;
        ++next;
        if (next != poly.end())
            std::cout << " + ";
    }
    std::cout << std::endl;
}

int main() {
    std::forward_list<Term> poly1 = { {1, 3}, {3, 5} };   // 3x^1 + 5x^3
    std::forward_list<Term> poly2 = { {2, 4}, {3, 2} };   // 4x^2 + 2x^3

    addPolynomialsInPlace(poly1, poly2);

    printPolynomial(poly1);

    return 0;
}
