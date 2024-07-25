#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);// TODO: 正确调用构造函数
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    ASSERT(sizeof(vec) == sizeof(std::vector<bool>), "Fill in the correct value.");
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        // 将每个 bool 元素压缩成一个位（bit）来存储。
        // 这种优化导致了 operator[] 返回的并不是一个直接的 bool& 引用，而是一个代理对象（proxy object）

        /**
         * 这个对象封装了对底层位的访问和修改能力。因此，当我们写 auto ref = vec[30]; 时，
         * ref 实际上是一个代理对象的实例，而不是直接的 bool 值
         * 这个代理对象实现了赋值操作符（operator=），因此当我们对 ref 进行赋值操作时，实际上是通过这个代理对象修改了底层的位
         */
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`");
        ref = false;
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}
