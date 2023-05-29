#include "fmt/core.h"
#include <memory>

class Rule0
{
    private:
        char    charArray[10];
        char     c;
        std::shared_ptr<char[]> sp;

        // std::unique_ptr<char[]> up; //this is not allowed as copy constructor implicitly deleted
        // char*   charBuffer; // Bad idea, only pointer value is getting copied

    public:
        Rule0()
        {
            c = 0;
            memset(charArray, 0, sizeof(charArray));
            //charBuffer = nullptr;
        };

        void setArray(char c)
        {
            this->c = c;
            memset(charArray, c, sizeof(charArray)-1);
            sp = std::make_shared<char[sizeof(charArray)]>(c);
            //up = std::make_unique<char[]>(sizeof(charArray));
            //charBuffer = new char[sizeof(charArray)];
            //memcpy(charBuffer, charArray, sizeof(charArray));
        };

        void Print()
        {
            fmt::println("Object address    {}", static_cast<void*>(this));
            fmt::println("Char              {}", this->c);
            fmt::println("Chars Array       {}", this->charArray);
            fmt::println("Chars A Pointer   {}", static_cast<void*>(this->charArray));

            //fmt::println("Chars Buffer      {}", this->charBuffer);
            //fmt::println("Chars B Pointer   {}", static_cast<void*>(this->charBuffer));

            fmt::println("Shared char       {}",  static_cast<void*>(this->sp.get()));

            //fmt::println("Unique char {}",  static_cast<void*>(this->up.get()));
        };
};

int main()
{
    fmt::println("============== Test RuleOf 0 3 5 ==============");

    Rule0 r0;
    r0.setArray('B');

    Rule0 r01 = r0;

    fmt::println("------------------- r0 -------------------");
    r0.Print();

    fmt::println("------------------- r01 -------------------");
    r01.Print();

    return 1;
}