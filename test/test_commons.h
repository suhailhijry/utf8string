#ifndef RYUK_TEST_COMMONS_H
#define RYUK_TEST_COMMONS_H


#include "../src/utf8string.h"
#include <iostream>

namespace ryuk {
    namespace tests {
        typedef const char *(*test_func)();

        template<typename T>
        inline void do_not_optimize(T &var) {
        #if __llvm__
            asm volatile ("": "+r,m" (var) : : "memory");
        #else
            const volatile char *temp = reinterpret_cast<const volatile char *>(var);
        #endif
        }

        template<typename T>
        inline void do_not_optimize(const T &var) {
        #if __llvm__
            asm volatile ("": "+r,m" (var) : : "memory");
        #else
            const volatile char *temp = reinterpret_cast<const volatile char *>(var);
        #endif
        }
        
        void run_test(const char *name, test_func func) {
            assert(name);
            assert(func);
            utf8string result(name);
            const char *testResult = func();
            if (testResult != nullptr) {
                result += " failed due to: ";
                result += testResult;
                result += '\n';
            } else {
                result += " passed.\n";
            }

            std::cout << result;
        }
    };
};

#endif
