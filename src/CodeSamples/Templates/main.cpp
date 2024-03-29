#include <iostream>
#include <iomanip>
#include <fmt/core.h>

#include "NoneTypeParameters.h"
#include "TemplateTemplateParameters.h"
#include "Fibonanchi.h"
#include "Fold.h"

// Variable Templates
template <class T>
inline constexpr T pi = T(3.1415926535897932385L);

template <class T>
T circle_area(T r) { return pi<T> * r * r; }

int main()
{
    std::cout << "\n\n====================== Variable Templates ======================" << std::endl;
    std::cout << std::setprecision(13);
    std::cout << "Circle Area Int r = 10 is " << circle_area(10) << std::endl;
    std::cout << "Circle Area Float r = 10.0 is " << circle_area<float>(10.0f) << std::endl;
    std::cout << "Circle Area Double r = 10.0 is " << circle_area<double>(10.00) << std::endl;
    std::cout << std::setprecision(6);

    std::cout << "\n\n====================== Non Type Templates ======================" << std::endl;
    SizedArray<int, 10> sa;
    SizedArray<int, 11> sb;
    SizedArray<float, 12> sc;

    sa.setElemAtIndex(3, 10);

    std::cout << sa.getElementAtIndex(3) << std::endl;
    std::cout << "sb Size" << sb.getSize() << std::endl;
    std::cout << "sa Size" << sa.getSize() << std::endl;
    std::cout << "sc Size" << sc.getSize() << std::endl;

    std::cout << "\n\n====================== Template Templates ======================" << std::endl;
    Adaptor<int, std::vector> a1;
    Adaptor<long, std::list> a2;

    a1.push_back(10);
    a2.push_back(2.0);

    std::cout << "\n\n====================== Fibonanchi ======================" << std::endl;
    constexpr int i = fibonanchi<int, 10>();
    std::cout << "Fibonanchi Func 10 : " << i << std::endl;

    // maximum limit is 26 since constexpr used
    constexpr long cl = fibonanchi<long, 26>();
    std::cout << "Fibonanchi Func 26 : " << cl << std::endl;

    // for larger values gives stack errors
    // long l = fibonanchi<long, 50>();
    // std::cout << "Fibonanchi Func 50 : " << l << std::endl;

    constexpr int b = fib<int, 10>;
    std::cout << "Fibonanchi Variable 10 : " << b << std::endl;

    fmt::println("\n\n====================== Fold ======================");
    printer(1, 2, 3, "abc");
    adds(1, 2, 3.0, 4, 6.0);
    adds_reverse(1, 2, 3.0, 4, 6.0);

    return 0;
}
