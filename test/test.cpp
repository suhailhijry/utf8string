#include "../src/utf8string.h"
#include "test_commons.h"

using namespace ryuk;

const char *utf8_string_test() {
    utf8string string;

    string += "hello world!";

    if (string.size() != 12) {
        return "invalid size after appending const char *.";
    }

    return nullptr;
}

int main() {
    tests::run_test("utf8string Test", utf8_string_test);
}
