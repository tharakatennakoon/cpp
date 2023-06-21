#include <fmt/core.h>
#include <functional>

void increment(int &i)
{
    i++;
}

int main()
{
    int num = 0;

    increment(num);
    increment(num);
    fmt::println("Ref Count {}", num);

    auto bound_increment_fun = std::bind(increment, num);
    bound_increment_fun();
    bound_increment_fun();
    fmt::println("Bound Count {}", num);

    auto bound_increment_fun_reference_wrap = std::bind(increment, std::ref(num));
    bound_increment_fun_reference_wrap();
    bound_increment_fun_reference_wrap();
    fmt::println("Bound Reference Wrap Count {}", num);
}