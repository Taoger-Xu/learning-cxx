#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段
    static int num_a;

    A() {
        ++num_a;
    }
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};
// 在类定义中使用时，final 指定此类不可被继承
struct B final : public A {
    // TODO: 正确初始化静态字段
    static int num_b;

    // 在调用 B 的构造函数之前，首先调用了 A 的构造函数
    B() {
        ++num_b;
    }

    // 如果基类的析构函数被声明为虚函数，
    // 那么所有派生类的析构函数自动成为虚函数，即使没有显式使用 virtual 关键字。这种继承机制确保了正确的析构函数调用链
    ~B() {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};
int A::num_a = 0;
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;// 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    
    B* bb = dynamic_cast<B*>(ab);
    ASSERT(bb->name() == 'B', "Fill in the correct value for bb->name()");
    // std::cout << B::num_b << std::endl;
    // std::cout << B::num_a << std::endl;

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
