template<typename T, T I>
constexpr T fibonanchi()
{
    return fibonanchi<T, I-1>() + fibonanchi<T, I-2>();
}

template<>
constexpr int fibonanchi<int, 1>()
{
    return 1;
}

template<>
constexpr int fibonanchi<int, 0>()
{
    return 0;
}

template<>
constexpr long fibonanchi<long, 1>()
{
    return 1;
}

template<>
constexpr long fibonanchi<long, 0>()
{
    return 0;
}

template<typename T, T i>
constexpr T fib = fib<T, i-2> + fib<T, i-1>;

template<>
constexpr int fib<int, 0> = 0;

template<>
constexpr int fib<int, 1> = 1;

// This gives compile errors
// template<typename T>
// constexpr T fib<T, 0> = 0;

// template<typename T>
// constexpr T fib<T, 1> = 1;