#include "containers.hpp"

int main() {
    containers::MyContainer<int> ic;
    ic.add(1);
    ic.add(2);
    ic.add(5);
    ic.add(6);
    ic.add(7);
    ic.add(3);
    ic.add(4);

    std::cout << ic << std::endl;

    std::cout << "or ";
    for (auto it = ic.begin_order(); it != ic.end_order(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "dsc ";
    for (auto it = ic.begin_descending_order(); it != ic.end_descending_order(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "mo ";
    for (auto it = ic.begin_middle_out_order(); it != ic.end_middle_out_order(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "sc ";
    for (auto it = ic.begin_side_cross_order(); it != ic.end_side_cross_order(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    containers::MyContainer<float> fc;
    fc.add(1.0);
    fc.add(2.05);
    fc.add(3.14);
    fc.add(-0.56);
    for (auto it = fc.begin_order(); it != fc.end_order(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    for (auto it = fc.begin_descending_order(); it != fc.end_descending_order(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    for (auto it = fc.begin_middle_out_order(); it != fc.end_middle_out_order(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    containers::MyContainer<std::string> sc;
    sc.add("Hello");
    sc.add("World");
    sc.add("Business");
    sc.add("As");
    sc.add("Usual");
    sc.add("Bossman");
    for (auto it = sc.begin_order(); it != sc.end_order(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    for (auto it = sc.begin_descending_order(); it != sc.end_descending_order(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    for (auto it = sc.begin_middle_out_order(); it != sc.end_middle_out_order(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
}
