template<int I>
constexpr int fibonanchi()
{
    return fibonanchi<I-1>() + fibonanchi<I-2>();
}

template<>
constexpr int fibonanchi<1>()
{
    return 1;
}

template<>
constexpr int fibonanchi<0>()
{
    return 0;
}

template<int i>
constexpr int fib = fib<i-2> + fib<i-1>;

template<>
constexpr int fib<0> = 0;

template<>
constexpr int fib<1> = 1;
