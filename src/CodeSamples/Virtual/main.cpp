#include <iostream>
#include <variant>
#include <string>
#include <type_traits>

// void TestLabmda() {
//     auto l = [](auto arg) {
//         std::cout << arg << ' ';

//         return std::type_identity<void>{};
//     };

//     auto log = [&l] (auto... args) {
//         (l(args) = ...);
//     };

//     log(1,"2",3.0);
// }

// void TestVariant() {
//     std::variant<int, float> v,w;

//     v = 42;

//     try
//     {
//         int i = std::get<int>(v);
//         std::cout << "I : " << i << std::endl;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
    
//     try
//     {
//         float f = std::get<float>(v);
//         std::cout << "F : " << f << std::endl;
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//     }
// }

int main()
{
    //TestVariant();

    //TestLabmda();

    std::cout << "main" << std::endl;

    return 0;
}
