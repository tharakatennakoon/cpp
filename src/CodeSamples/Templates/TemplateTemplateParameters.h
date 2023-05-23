#include <vector>
#include <list>

template<typename T, template<typename U, typename A = std::allocator<U>> typename C>
struct Adaptor
{
    C<T> my_data;
    void push_back(T const& t) {my_data.push_back(t);}

    T get(int pos);
};

