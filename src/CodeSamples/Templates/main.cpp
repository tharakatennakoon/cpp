#include <iostream>
#include <iomanip>

// Variable Templates
template<class T>
inline constexpr T pi = T(3.1415926535897932385L);

template<class T>
T circle_area(T r) { return pi<T> * r * r; }

int main()
{
    std::cout << "Variable Templates" << std::endl;

    std::cout << std::setprecision(13);
    std::cout << "Circle Area Int r = 10 is " << circle_area(10) << std::endl;
    std::cout << "Circle Area Float r = 10.0 is " << circle_area<float>(10.0f) << std::endl;
    std::cout << "Circle Area Double r = 10.0 is " << circle_area<double>(10.00) << std::endl;

    return 0;
}
