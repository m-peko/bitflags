<div align="center">

<img src="img/logo.png" height="120px"/>

Single-header C++17 library for easily managing type-safe set of flags.

[![License](https://img.shields.io/badge/license-MIT-brightgreen.svg?style=flat)](https://github.com/m-peko/bitflags/blob/master/LICENSE)
[![Build Status](https://travis-ci.org/m-peko/bitflags.svg?branch=master)](https://travis-ci.org/m-peko/bitflags)
[![Codecov](https://codecov.io/gh/m-peko/bitflags/branch/master/graph/badge.svg)](https://codecov.io/gh/m-peko/bitflags)
[![Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Compiler explorer](https://img.shields.io/badge/compiler_explorer-online-blue.svg)](https://godbolt.org/z/4n4GsP)

</div>

## Quick start

```cpp
#include <bitflags/bitflags.hpp>

BITFLAGS(
    Flags, std::uint8_t,
        BITFLAG(0b0000, none)
        BITFLAG(0b0001, flag_a)
        BITFLAG(0b0010, flag_b)
        BITFLAG(0b0100, flag_c)
)

int main() {
    Flags flags = Flags::flag_a | Flags::flag_b;

    if (flags & Flags::flag_a) {
        std::cout << "flag_a is set" << std::endl;
    } else {
        std::cout << "flag_a is not set" << std::endl;
    }

    flags.toggle(Flags::flag_a);

    // ...

    return 0;
}
```

## Table of Contents

* [Getting Started](#getting-started)
    * [What's a BITFLAGS macro?](#whats-a-bitflags-macro)
    * [What's a BITFLAG macro?](#whats-a-bitflag-macro)
    * [Bits and Names](#bits-and-names)
    * [Bitwise Operators](#bitwise-operators)
    * [Is Specific Flag Set?](#is-specific-flag-set)
    * [All or Empty](#all-or-empty)
    * [Set and Remove Specific Flag](#set-and-remove-specific-flag)
    * [Toggle Flags](#toggle-flags)
    * [Clear Flags](#clear-flags)
* [Building Samples and Tests](#building-samples-and-tests)
* [Compiler Compatibility](#compiler-compatibility)
* [Contributing](#contributing)
* [License](#license)

## Getting Started

`bitflags` is a single-header header-only C++17 library.

### What's a BITFLAGS macro?

`BITFLAGS` macro is a helper that hides kind of "ugly" declaration syntax of creating a `struct` that contains all the flags. In other words, following code snippet:

```cpp
BITFLAGS(
    Flags, std::uint8_t,
        BITFLAG(0b0000, none)
        BITFLAG(0b0001, flag_a)
        BITFLAG(0b0010, flag_b)
        BITFLAG(0b0100, flag_c)
)
```

expands to:

```cpp
struct Flags : bf::bitflags<Flags, std::uint8_t> {
    using bitflags<Flags, std::uint8_t>::bitflags; // inherit constructors

    BITFLAG(0b0000, none)
    // ...
};
```

### What's a BITFLAG macro?

`BITFLAG` macro is a helper that creates a static constexpr member of an internal `flag` type. In other words, following code snippet:

```cpp
struct Flags : bf::bitflags<Flags, std::uint8_t> {
    using bitflags<Flags, std::uint8_t>::bitflags;

    BITFLAG(0b0000, none);
    // ...
};
```

is translated into:

```cpp
struct Flags : bf::bitflags<Flags, std::uint8_t> {
    using bitflags<Flags, std::uint8_t>::bitflags;

    static constexpr flag none{ 0b0000, "none" };
    // ...
};
```

### Bits and Names

Once the flags are specified, it is possible to get bits representing each flag as well as string representation of each flag:

```cpp
BITFLAGS(
    Flags, std::uint8_t,
        BITFLAG(0b0000, none)
        BITFLAG(0b0001, flag_a)
        BITFLAG(0b0010, flag_b)
)

std::cout << Flags::flag_a.bits << " - " << Flags::flag_a.name << std::endl;
```

### Bitwise Operators

The following binary operators are implemented for the generated flags:

* NOT (`~`) operator
* AND (`&`) operator
* OR (`|`) operator
* XOR (`^`) operator

### Is Specific Flag Set?

In case we want to check whether specific flag is set or not, we have 2 options:

1. use AND operator

```cpp
BITFLAGS(
    Flags, std::uint8_t,
        BITFLAG(0b0000, none)
        BITFLAG(0b0001, flag_a)
        BITFLAG(0b0010, flag_b)
)

Flags flags = Flags::flag_a;

std::cout << static_cast<bool>(flags & Flags::flag_a) << std::endl; // true
std::cout << static_cast<bool>(flags & Flags::flag_b) << std::endl; // false
```

2. use `contains` member function

```cpp
BITFLAGS(
    Flags, std::uint8_t,
        BITFLAG(0b0000, none)
        BITFLAG(0b0001, flag_a)
        BITFLAG(0b0010, flag_b)
        BITFLAG(0b0100, flag_c)
)

Flags flags_1 = Flags::flag_a;

std::cout << flags_1.contains(Flags::flag_a) << std::endl; // true
std::cout << flags_1.contains(Flags::flag_b) << std::endl; // false

Flags flags_2 = Flags::flag_a | Flags::flag_b;

std::cout << flags_2.contains(Flags::flag_a, Flags::flag_b) << std::endl; // true
std::cout << flags_2.contains(Flags::flag_a, Flags::flag_c) << std::endl; // false
```

### All or Empty

Following member functions are available for setting all the flags or setting no flag:

1. `all` / `is_all`

```cpp
BITFLAGS(
    Flags, std::uint8_t,
        BITFLAG(0b0000, none)
        BITFLAG(0b0001, flag_a)
        BITFLAG(0b0010, flag_b)
)

Flags flags = Flags::all();

std::cout << flags.is_all() << std::endl;                // true
std::cout << flags.contains(Flags::flag_a) << std::endl; // true
std::cout << flags.contains(Flags::flag_b) << std::endl; // true
std::cout << flags.is_empty() << std::endl;              // false
```

2. `empty` / `is_empty`

```cpp
BITFLAGS(
    Flags, std::uint8_t,
        BITFLAG(0b0000, none)
        BITFLAG(0b0001, flag_a)
        BITFLAG(0b0010, flag_b)
)

Flags flags = Flags::empty();

std::cout << flags.is_all() << std::endl;                // false
std::cout << flags.contains(Flags::flag_a) << std::endl; // false
std::cout << flags.contains(Flags::flag_b) << std::endl; // false
std::cout << flags.is_empty() << std::endl;              // true
```

### Set and Remove Specific Flag

Not only that one can set and remove specific flag by using bitwise operators, but there are also special member functions `set` and `remove` that have the same purpose.

```cpp
BITFLAGS(
    Flags, std::uint8_t,
        BITFLAG(0b0000, none)
        BITFLAG(0b0001, flag_a)
        BITFLAG(0b0010, flag_b)
)

Flags flags = Flags::empty();

std::cout << flags.contains(Flags::flag_a) << std::endl; // false
std::cout << flags.contains(Flags::flag_b) << std::endl; // false

flags.set(Flags::flag_a);
flags.set(Flags::flag_b);

std::cout << flags.contains(Flags::flag_a) << std::endl; // true
std::cout << flags.contains(Flags::flag_b) << std::endl; // true

flags.remove(Flags::flag_a);

std::cout << flags.contains(Flags::flag_a) << std::endl; // false
std::cout << flags.contains(Flags::flag_b) << std::endl; // true
```

### Toggle Flags

It is possible to toggle specific flag, i.e. if the flag is not already set, it will be set. On the other hand, if the flag is already set, it will be unset.

```cpp
BITFLAGS(
    Flags, std::uint8_t,
        BITFLAG(0b0000, none)
        BITFLAG(0b0001, flag_a)
        BITFLAG(0b0010, flag_b)
)

Flags flags = Flags::flag_a;

std::cout << flags.contains(Flags::flag_a) << std::endl; // true
flags.toggle(Flags::flag_a);
std::cout << flags.contains(Flags::flag_a) << std::endl; // false

std::cout << flags.contains(Flags::flag_b) << std::endl; // false
flags.toggle(Flags::flag_b);
std::cout << flags.contains(Flags::flag_b) << std::endl; // true
```

### Clear Flags

In order to clear all the flags currently set, one can use `clear` member function.

```cpp
BITFLAGS(
    Flags, std::uint8_t,
        BITFLAG(0b0000, none)
        BITFLAG(0b0001, flag_a)
        BITFLAG(0b0010, flag_b)
        BITFLAG(0b0100, flag_c)
)

Flags flags = Flags::flag_a | Flags::flag_b;

std::cout << flags.contains(Flags::flag_a) << std::endl; // true
std::cout << flags.contains(Flags::flag_b) << std::endl; // true
std::cout << flags.contains(Flags::flag_c) << std::endl; // false

flags.clear();

std::cout << flags.contains(Flags::flag_a) << std::endl; // false
std::cout << flags.contains(Flags::flag_b) << std::endl; // false
std::cout << flags.contains(Flags::flag_c) << std::endl; // false
```

## Building Samples and Tests

```bash
$ git clone https://github.com/m-peko/bitflags
$ cd bitflags

$ # create the build directory
$ mkdir build
$ cd build

$ # configure the project
$ cmake -DBITFLAGS_BUILD_SAMPLES=ON -DBITFLAGS_BUILD_TESTS=ON ..

$ # compile
$ make

$ # compile tests
$ make tests

$ # run tests
$ make test
```

## Compiler Compatibility

* Clang/LLVM >= 5
* MSVC++ >= 14.11 / Visual Studio >= 2017
* GCC >= 7.3

There are no 3<sup>rd</sup> party dependencies.

## Contributing

Feel free to contribute.

If you find that any of the tests **fail**, please create a ticket in the issue tracker indicating the following information:

* platform
* architecture
* library version
* minimal reproducible example

## License

The project is available under the [MIT](https://opensource.org/licenses/MIT) license.
