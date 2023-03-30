#include <iostream>
#include <variant>
#include <string>
#include <type_traits>

class base 
{
public:
    base(){ std::cout << "base()" << std::endl; };
    ~base(){ std::cout << "~base()" << std::endl; };
    int foo(){ std::cout << "base::foo()" << std::endl; };
};

class derived : base
{
public:
    derived(){ std::cout << "derived()" << std::endl; }
    ~derived(){ std::cout << "~derived()" << std::endl; }
    int foo(){ std::cout << "derived::foo()" << std::endl; }
};

class baseVirtual
{
public:
    //http://www.stroustrup.com/bs_faq2.html#virtual-ctor
    //virtual baseVirtual(){}; // Compile error, cannot add virtual to constructor
    baseVirtual(){ std::cout << "baseVirtual()" << std::endl; };
    virtual ~baseVirtual(){ std::cout << "~baseVirtual()" << std::endl; };
}



int main()
{
    //TestVariant();

    //TestLabmda();

    std::cout << "main" << std::endl;

    return 0;
}
