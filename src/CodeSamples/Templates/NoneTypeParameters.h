#include <algorithm>

template<typename T, size_t N>
class SizedArray
{
    constexpr static size_t array_size = N;
    T m_data[N];

public:
    SizedArray()
    {
        std::fill(m_data, m_data + array_size, 0);
    }

    void setElemAtIndex(int pos, T data)
    {
        m_data[pos] = data;
    }

    T getElementAtIndex(int pos)
    {
        return m_data[pos];
    }

    size_t getSize()
    {
        return array_size;
    }
};