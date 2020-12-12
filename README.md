# utf8string

A header only, drop in replacement for std::string with full support for UTF-8.

## Usage

```c++
    // you can put the header in your 'include' folder
    #import <utf8string.h>
    ...
    ryuk::utf8string str0; // empty string
    ryuk::utf8string str1("Hello, world!"); // from c-string
    str0 = "Hello, world!"; // from c-string
    str1 = str0; // from another ryuk::utf8string
    str0 += 'A'; // append char
    str0 += U'\x645'; // append unicode code point
    str0 += "appended"; // append c-string
    str1 += str0; // append another ryuk::utf8string

    for (auto c : str1) {
        // iterate over the string
    }

    size_t capacity = str1.capacity(); // capacity
    size_t size = str1.size(); // octet count
    size_t count = str1.count(); // actual code point count
```

## Remarks

* ```utf8string::capacity()``` returns the actual capacity minus 1, because we always need to be able to store the null terminator.

* ```utf8string::size()``` returns only the octet count, which if you are only using ascii characters will be the actual character count. This of course execludes the null terminator.

* ```utf8string::count()``` returns the actual character count, but it is costly, because we can't simply count the bytes so we have to count them every time. This behavior might change in the future, because we may simply store character count and return that instead.

* This class employs small string optimization (SSO), with the SSO buffer having the size 32 by default, you can change this simply by creating a different template of the class: ```using myutf8string = ryuk::basic_utf8string<YOUR_SSO_LENGTH>;```. This should create a specialization of the class with your own SSO buffer length.

* This class only supports c++11 and above at the mooment.

## Contribution
* All contributions are welcome, feel free to submit a PR anytime.

## Acknowledgement

The original UTF-8 support code was created by [Nemanja Trifunovic](https://github.com/nemtrif/utfcpp), I only modified it to fit my coding style, and took the parts that I needed for this implementation.
