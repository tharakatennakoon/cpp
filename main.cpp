#include <iostream>
#include <variant>
#include <string>

int main()
{
    std::variant<int, float> v,w;

    v = 42;

    try
    {
        int i = std::get<int>(v);
        std::cout << "I : " << i << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    try
    {
        float f = std::get<float>(v);
        std::cout << "F : " << f << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
