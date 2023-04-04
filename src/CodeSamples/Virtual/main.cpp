#include <iostream>
#include <variant>
#include <string>
#include <type_traits>

class base 
{
public:
    base(){ std::cout << "base()" << static_cast<void*>(this) << std::endl; };
    base(const base&){std::cout << "base(base&)" << static_cast<void*>(this) << std::endl;}
    base& operator=(const base&){std::cout << "base& base=" << static_cast<void*>(this) << std::endl; return *this; }

    ~base(){ std::cout << "~base()" << static_cast<void*>(this) << std::endl; };
    int foo(){ std::cout << "base::foo() this :" << static_cast<void*>(this) << std::endl; return 0; };
};

class derived_0 : public base
{
public:
    derived_0(){ std::cout << "derived_0()" << static_cast<void*>(this) << std::endl; }
    derived_0(const derived_0&){std::cout << "derived_0(derived_0&)" << static_cast<void*>(this) << std::endl;}
    derived_0& operator=(const derived_0&){std::cout << "derived_0& operator=" << static_cast<void*>(this) << std::endl; return *this; }

    ~derived_0(){ std::cout << "~derived_0()" << static_cast<void*>(this) << std::endl; }
    int foo(){ std::cout << "derived_0::foo()" << static_cast<void*>(this) << std::endl; return 0; }
};

class derived_1 : public derived_0
{
private:
    char* test = new char[100];

public:
    derived_1(){ std::cout << "derived_1()" << static_cast<void*>(this) << std::endl; }
    derived_1(const derived_1&){std::cout << "derived_1(derived_1&)" << static_cast<void*>(this) << std::endl;}
    derived_1& operator=(const derived_1&){std::cout << "derived_1& operator=" << static_cast<void*>(this) << std::endl; return *this; }    

    ~derived_1(){ delete[](test); std::cout << "~derived_1()" << static_cast<void*>(this) << std::endl; }
    int foo() { std::cout << "derived_1::foo()" << static_cast<void*>(this) << std::endl; return 0; }
};

class baseVirtual
{
public:
    //http://www.stroustrup.com/bs_faq2.html#virtual-ctor
    //virtual baseVirtual(){}; // Compile error, cannot add virtual to constructor
    //virtual baseVirtual(const baseVirtual&){std::cout << "baseVirtual(baseVirtual&)" << static_cast<void*>(this) << std::endl;}

    baseVirtual(){ std::cout << "baseVirtual()" << static_cast<void*>(this) << std::endl; };
    baseVirtual(const baseVirtual&){std::cout << "baseVirtual(baseVirtual&)" << static_cast<void*>(this) << std::endl;}
    virtual baseVirtual& operator=(const baseVirtual&){std::cout << "baseVirtual& baseVirtual=" << static_cast<void*>(this) << std::endl; return *this; }

    virtual ~baseVirtual(){ std::cout << "~baseVirtual()" << static_cast<void*>(this) << std::endl; };
    virtual int foo() { std::cout << "baseVirtual::foo()" << static_cast<void*>(this) << std::endl; return 0; }
};

class derivedVirtual_0 : public baseVirtual
{
public:
    derivedVirtual_0(){ std::cout << "derivedVirtual_0()" << static_cast<void*>(this) << std::endl; }
    derivedVirtual_0(const derivedVirtual_0&){std::cout << "derivedVirtual_0(derivedVirtual_0&)" << static_cast<void*>(this) << std::endl;}
    virtual derivedVirtual_0& operator=(const derivedVirtual_0&){std::cout << "derivedVirtual_0& derivedVirtual_0=" << static_cast<void*>(this) << std::endl; return *this; }

    ~derivedVirtual_0(){ std::cout << "~derivedVirtual_0()" << static_cast<void*>(this) << std::endl; }
    int foo(){ std::cout << "derivedVirtual_0::foo()" << static_cast<void*>(this) << std::endl; return 0; }
};

class derivedVirtual_1 : public derivedVirtual_0
{
public:
    derivedVirtual_1(){ std::cout << "derivedVirtual_1()" << static_cast<void*>(this) << std::endl; }
    derivedVirtual_1(const derivedVirtual_1&){std::cout << "derivedVirtual_1(derivedVirtual_1&)" << static_cast<void*>(this) << std::endl;}
    virtual derivedVirtual_1& operator=(const derivedVirtual_1&){std::cout << "derivedVirtual_1& derivedVirtual_1=" << static_cast<void*>(this) << std::endl; return *this; }

    ~derivedVirtual_1(){ std::cout << "~derivedVirtual_1()" << static_cast<void*>(this) << std::endl; }
    int foo() { std::cout << "derivedVirtual_1::foo()" << static_cast<void*>(this) << std::endl; return 0; }
};

void testNonVertualClassPointers()
{
    std::cout << " ======= Casting Non Vertual Class Pointers ======= " << std::endl;
    derived_1* d_1 = new derived_1();
    derived_0* d_0 = static_cast<derived_0*>(d_1);
    base* b = static_cast<base*>(d_1);

    std::cout << "-----" << std::endl;

    d_1->foo();
    d_0->foo();
    b->foo();

    std::cout << "-----" << std::endl;

    delete(d_1);
    //delete(d_0); // -> this will call ~derived_0 and ~base - Cause memory leaks
    //delete(b); // -> this will only call ~base ~ Cause memory leaks

    std::cout << "=================================================== " << std::endl << std::endl;
}

void testNonVirtualClassObjects()
{
    std::cout << "======= Casting Non Vertual Class Objects ======= " << std::endl;

    derived_1 d_1;
    d_1.foo();

    std::cout << "-----" << std::endl;

    derived_0 d_0 = static_cast<derived_0>(d_1);
    d_0.foo();

    std::cout << "============================================ " << std::endl;
}

void testVirtualClassPointers()
{
    std::cout << "======= Casting Vertual Class Pointers ======= " << std::endl;
    derivedVirtual_1* dv_1 = new derivedVirtual_1();
    derivedVirtual_0* dv_0 = static_cast<derivedVirtual_0*>(dv_1);
    baseVirtual* bv0 = static_cast<baseVirtual*>(dv_1);
    baseVirtual* bv1 = static_cast<baseVirtual*>(dv_0);

    std::cout << "-----" << std::endl;

    dv_1->foo();
    dv_0->foo();
    bv0->foo();
    bv1->foo();

    std::cout << "-----" << std::endl;

    delete(bv1); // Since this is virtual all destructors will get called

    std::cout << " =================================== " << std::endl << std::endl;
}

void testVirtualClassObjects()
{
    std::cout << "======= Casting Vertual Class Objects ======= " << std::endl;

    derivedVirtual_1 dv_1;
    dv_1.foo();

    std::cout << "-----" << std::endl;

    derivedVirtual_0 dv_0 = static_cast<derivedVirtual_0>(dv_1);
    dv_0.foo();

    std::cout << "============================================ " << std::endl;
}

int main()
{
    testNonVertualClassPointers();
    std::cout << "============================================ " << std::endl;
    testVirtualClassPointers();
    std::cout << "============================================ " << std::endl;
    testNonVirtualClassObjects();
    std::cout << "============================================ " << std::endl;
    testVirtualClassObjects();
    std::cout << "============================================ " << std::endl;
    
    return 0;
}