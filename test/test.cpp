#include "../src/utf8string.h"
#include "test_commons.h"

using namespace ryuk;

namespace {
    constexpr const char *hello_world = "Hello, world!";
    constexpr size_t hello_world_length = 13;
    constexpr const char *bye_world = "Goodbye, world.";
    constexpr size_t bye_world_length = 15;
    constexpr const char *hello_world_u8 = "مرحباً بالعالم!";
    constexpr size_t hello_world_u8_length = 28;
    constexpr size_t hello_world_u8_count = 15;
    constexpr const char *bye_world_u8 = "وداعاً أيها العالم.";
    constexpr size_t bye_world_u8_length = 35;
    constexpr size_t bye_world_u8_count = 19;
};

const char *utf8_string_construct_with_constcharp_sso() {
    utf8string string(hello_world);

    test_assert(string.size() == hello_world_length, "invalid size");
    test_assert(string.count() == hello_world_length, "invalid count");

    // we get the actual capacity - 1 because we always want to keep a space for
    // the null terminator.
    test_assert(string.capacity() == utf8string::sso_capacity - 1, "invalid capacity");

    test_assert(string == hello_world, "invalid content");

    utf8string other_equals(hello_world);
    test_assert(string == other_equals, "equal strings are not equal");

    utf8string other_not_equals(bye_world);
    test_assert(string != other_not_equals, "unequal strings are equal");

    return nullptr;
}

const char *utf8_string_append_constcharp_sso() {
    utf8string string;
    string += hello_world;

    test_assert(string.size() == hello_world_length, "invalid size");
    test_assert(string.count() == hello_world_length, "invalid count");

    // we get the actual capacity - 1 because we always want to keep a space for
    // the null terminator.
    test_assert(string.capacity() == utf8string::sso_capacity - 1, "invalid capacity");

    test_assert(string == hello_world, "invalid content");

    utf8string other_equals(hello_world);
    test_assert(string == other_equals, "equal strings are not equal");

    utf8string other_not_equals(bye_world);
    test_assert(string != other_not_equals, "unequal strings are equal");

    return nullptr;
}

const char *utf8_string_append_char_sso() {
    utf8string string;
    string += '1';

    test_assert(string.size() == 1, "invalid size");
    test_assert(string.count() == 1, "invalid count");

    // we get the actual capacity - 1 because we always want to keep a space for
    // the null terminator.
    test_assert(string.capacity() == utf8string::sso_capacity - 1, "invalid capacity");

    test_assert(string == "1", "invalid content");

    return nullptr;
}

const char *utf8_string_construct_with_u8constcharp_sso() {
    utf8string string(hello_world_u8);

    test_assert(string.size() == hello_world_u8_length, "invalid size");
    test_assert(string.count() == hello_world_u8_count, "invalid count");

    // we get the actual capacity - 1 because we always want to keep a space for
    // the null terminator.
    test_assert(string.capacity() == utf8string::sso_capacity - 1, "invalid capacity");

    test_assert(string == hello_world_u8, "invalid content");

    utf8string other_equals(hello_world_u8);
    test_assert(string == other_equals, "equal strings are not equal");

    utf8string other_not_equals(bye_world_u8);
    test_assert(string != other_not_equals, "unequal strings are equal");

    return nullptr;
}

const char *utf8_string_append_u8constcharp_sso() {
    utf8string string;
    string += hello_world_u8;

    test_assert(string.size() == hello_world_u8_length, "invalid size");
    test_assert(string.count() == hello_world_u8_count, "invalid count");

    // we get the actual capacity - 1 because we always want to keep a space for
    // the null terminator.
    test_assert(string.capacity() == utf8string::sso_capacity - 1, "invalid capacity");

    test_assert(string == hello_world_u8, "invalid content");

    utf8string other_equals(hello_world_u8);
    test_assert(string == other_equals, "equal strings are not equal");

    utf8string other_not_equals(bye_world_u8);
    test_assert(string != other_not_equals, "unequal strings are equal");

    return nullptr;
}

const char *utf8_string_append_u8char_sso() {
    utf8string string;
    string += U'\x645';

    test_assert(string.size() == 2, "invalid size");
    test_assert(string.count() == 1, "invalid count");

    // we get the actual capacity - 1 because we always want to keep a space for
    // the null terminator.
    test_assert(string.capacity() == utf8string::sso_capacity - 1, "invalid capacity");

    test_assert(string == "م", "invalid content");

    return nullptr;
}

#define run_test(func) tests::run_test((#func), (func))

int main() {
    run_test(utf8_string_construct_with_constcharp_sso);
    run_test(utf8_string_append_constcharp_sso);
    run_test(utf8_string_append_char_sso);
    run_test(utf8_string_construct_with_u8constcharp_sso);
    run_test(utf8_string_append_u8constcharp_sso);
    run_test(utf8_string_append_u8char_sso);
}
