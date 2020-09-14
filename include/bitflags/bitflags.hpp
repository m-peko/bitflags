/*
 * Copyright (c) 2020, Marin Peko
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BITFLAGS_HPP
#define BITFLAGS_HPP

#include <cstdint>
#include <string_view>

namespace bf {

namespace internal {

template <typename TagT, typename T>
struct flag;

/**
 * Comparison operators overloads
 *
 *     flag<TagT, T> <op> flag<TagT, T>
 */

template <typename TagT, typename T>
[[nodiscard]] constexpr bool operator==(flag<TagT, T> const& lhs, flag<TagT, T> const& rhs) noexcept;

template <typename TagT, typename T>
[[nodiscard]] constexpr bool operator!=(flag<TagT, T> const& lhs, flag<TagT, T> const& rhs) noexcept;

/**
 * Bitwise operators overloads
 *
 *     <op> flag<TagT, T>
 *
 *     flag<TagT, T> <op> flag<TagT, T>
 */

template <typename TagT, typename T>
[[nodiscard]] constexpr flag<TagT, T> operator~(flag<TagT, T> const& rhs) noexcept;

template <typename TagT, typename T>
[[nodiscard]] constexpr flag<TagT, T> operator&(flag<TagT, T> const& lhs, flag<TagT, T> const& rhs) noexcept;

template <typename TagT, typename T>
[[nodiscard]] constexpr flag<TagT, T> operator|(flag<TagT, T> const& lhs, flag<TagT, T> const& rhs) noexcept;

template <typename TagT, typename T>
[[nodiscard]] constexpr flag<TagT, T> operator^(flag<TagT, T> const& lhs, flag<TagT, T> const& rhs) noexcept;

/**
 * struct flag
 *
 * Represents a single flag in a collection of multiple flags.
 * This structure is for internal use only.
 */
template <typename TagT, typename T = uint8_t>
struct flag {
    T bits;
    std::string_view name;

    constexpr flag() = default;
    constexpr flag(flag&& rhs) = default;
    constexpr flag(flag const& rhs) = default;

    constexpr flag(T bits) noexcept
        : bits(bits)
    {}

    constexpr flag(T bits, std::string_view name) noexcept
        : bits(bits)
        , name(name)
    {}

    flag& operator=(flag&& rhs) = default;
    flag& operator=(flag const& rhs) = default;

    ~flag() = default;

    [[nodiscard]] explicit constexpr operator T() const noexcept {
        return bits;
    }

    /**
     * Comparison operators overloads
     *
     *     flag<TagT, T> <op> flag<TagT, T>
     */

    [[nodiscard]] friend constexpr bool operator==(flag const& lhs, flag const& rhs) noexcept {
        return lhs.bits == rhs.bits;
    }

    [[nodiscard]] friend constexpr bool operator!=(flag const& lhs, flag const& rhs) noexcept {
        return lhs.bits != rhs.bits;
    }

    /**
     * Bitwise operators overloads
     *
     *     <op> flag<TagT, T>
     *
     *     flag<TagT, T> <op> flag<TagT, T>
     *
     *     flag<TagT, T> <op>= flag<TagT, T>
     */

    [[nodiscard]] friend constexpr flag operator~(flag const& rhs) noexcept {
        return ~rhs.bits;
    }

    [[nodiscard]] friend constexpr flag operator&(flag const& lhs, flag const& rhs) noexcept {
        return lhs.bits & rhs.bits;
    }

    [[nodiscard]] friend constexpr flag operator|(flag const& lhs, flag const& rhs) noexcept {
        return lhs.bits | rhs.bits;
    }

    [[nodiscard]] friend constexpr flag operator^(flag const& lhs, flag const& rhs) noexcept {
        return lhs.bits ^ rhs.bits;
    }

    constexpr flag& operator&=(flag const& rhs) noexcept {
        bits &= rhs.bits;
        return *this;
    }

    constexpr flag& operator|=(flag const& rhs) noexcept {
        bits |= rhs.bits;
        return *this;
    }

    constexpr flag& operator^=(flag const& rhs) noexcept {
        bits ^= rhs.bits;
        return *this;
    }
};

/**
 * struct min
 *
 * Provides member typedef type which is defined as minimal unsigned
 * integral type capable of storing N integers.
 * This structure is for internal use only.
 */
template <std::size_t N>
struct min {
    using type = typename std::conditional_t<
        (N <= 8), std::uint8_t,
        typename std::conditional_t<
            (N <= 16), std::uint16_t,
            typename std::conditional_t<
                (N <= 32), std::uint32_t, std::uint64_t
            >
        >
    >;
};

template <std::size_t N>
using min_t = typename min<N>::type;

/**
 * Shifts integer of type T by specified offset.
 * If the offset is less than 0, 0 is returned.
 * This function is for internal use only.
 *
 * @param offset Offset to be used for shifting
 *
 * @return Result
 */
template <typename T>
constexpr T shift(int const offset) {
    if (offset < 0) {
        return static_cast<T>(0);
    } else {
        return static_cast<T>(1U << offset);
    }
}

} // internal

template <typename ImplT, typename T>
class bitflags;

/**
 * Bitwise operators overloads
 *
 *     <op> bitflags<ImplT, T>
 *
 *     bitflags<ImplT, T> <op> flag<ImplT, T>
 */

template <typename ImplT, typename T>
[[nodiscard]] constexpr T operator~(bitflags<ImplT, T> const& rhs) noexcept;

template <typename ImplT, typename T>
[[nodiscard]] constexpr T operator&(bitflags<ImplT, T> const& lhs, internal::flag<ImplT, T> const& rhs) noexcept;

template <typename ImplT, typename T>
[[nodiscard]] constexpr T operator|(bitflags<ImplT, T> const& lhs, internal::flag<ImplT, T> const& rhs) noexcept;

template <typename ImplT, typename T>
[[nodiscard]] constexpr T operator^(bitflags<ImplT, T> const& lhs, internal::flag<ImplT, T> const& rhs) noexcept;

/**
 * class bitflags
 *
 * Represents a typesafe bitmask flag generator that manages a set of flags.
 * The flags should only be defined for integral types.
 */
template <typename ImplT, typename T = internal::min_t<ImplT::end_ - ImplT::begin_ + 1>>
class bitflags : public ImplT {
public:
    using underlying_type = T;

    constexpr bitflags() = default;
    constexpr bitflags(bitflags&& rhs) = default;
    constexpr bitflags(bitflags const& rhs) = default;

    constexpr bitflags(internal::flag<ImplT, T>&& rhs) noexcept
        : curr_(std::move(rhs))
    {}

    constexpr bitflags(internal::flag<ImplT, T> const& rhs) noexcept
        : curr_(rhs)
    {}

    constexpr bitflags(T bits) noexcept
        : curr_(bits)
    {}

    constexpr bitflags(T bits, std::string_view name) noexcept
        : curr_(bits, name)
    {}

    bitflags& operator=(bitflags&& rhs) = default;
    bitflags& operator=(bitflags const& rhs) = default;

    bitflags& operator=(T bits) noexcept {
        curr_.bits = bits;
        curr_.name = "";
        return *this;
    }

    bitflags& operator=(internal::flag<ImplT, T>&& rhs) noexcept {
        curr_ = std::move(rhs);
        return *this;
    }

    bitflags& operator=(internal::flag<ImplT, T> const& rhs) noexcept {
        curr_ = rhs;
        return *this;
    }

    ~bitflags() = default;

    [[nodiscard]] constexpr operator T() const noexcept {
        return curr_.bits;
    }

    [[nodiscard]] constexpr bool operator==(internal::flag<ImplT, T> const& rhs) const noexcept {
        return curr_ == rhs;
    }

    [[nodiscard]] constexpr bool operator!=(internal::flag<ImplT, T> const& rhs) const noexcept {
        return curr_ != rhs;
    }

    /**
     * Bitwise operators overloads
     *
     *     <op> bitflags<ImplT, T>
     *
     *     bitflags<ImplT, T> <op> flag<ImplT, T>
     *
     *     bitflags<ImplT, T> <op>= flag<ImplT, T>
     */

    [[nodiscard]] friend constexpr bitflags operator~(bitflags const& rhs) noexcept {
        return ~rhs.curr_;
    }

    [[nodiscard]] friend constexpr bitflags operator&(bitflags const& lhs, internal::flag<ImplT, T> const& rhs) noexcept {
        return lhs.curr_ & rhs;
    }

    [[nodiscard]] friend constexpr bitflags operator|(bitflags const& lhs, internal::flag<ImplT, T> const& rhs) noexcept {
        return lhs.curr_ | rhs;
    }

    [[nodiscard]] friend constexpr bitflags operator^(bitflags const& lhs, internal::flag<ImplT, T> const& rhs) noexcept {
        return lhs.curr_ ^ rhs;
    }

    constexpr bitflags& operator&=(internal::flag<ImplT, T> const& rhs) noexcept {
        curr_ &= rhs;
        return *this;
    }

    constexpr bitflags& operator|=(internal::flag<ImplT, T> const& rhs) noexcept {
        curr_ |= rhs;
        return *this;
    }

    constexpr bitflags& operator^=(internal::flag<ImplT, T> const& rhs) noexcept {
        curr_ ^= rhs;
        return *this;
    }

    /**
     * Gets an underlying bits of current set of flags.
     *
     * @return Underlying bits
     */
    [[nodiscard]] constexpr T bits() const noexcept {
        return curr_.bits;
    }

    /**
     * Gets an empty set of flags.
     *
     * @return Empty set of flags
     */
    [[nodiscard]] static constexpr internal::flag<ImplT, T> empty() noexcept {
        return T{};
    }

    /**
     * Gets the set of all defined flags.
     *
     * @return Set of all defined flags
     */
    [[nodiscard]] static constexpr internal::flag<ImplT, T> all() noexcept {
        return ~T{};
    }

    /**
     * Checks whether no flag is currently set.
     *
     * @return True if no flag is currently set, otherwise false
     */
    [[nodiscard]] constexpr bool is_empty() const noexcept {
        return curr_ == T{};
    }

    /**
     * Checks whether all flags are currently set.
     *
     * @return True if all flags are currently set, otherwise false
     */
    [[nodiscard]] constexpr bool is_all() const noexcept {
        return curr_ == ~T{};
    }

    /**
     * Checks whether specified flag is contained within the current
     * set of flags. Zero flags are treated as always present.
     *
     * @param rhs Flag to check
     *
     * @return True if the specified flags is contained within the
     *         current set of flags, otherwise false
     */
    [[nodiscard]] constexpr bool contains(internal::flag<ImplT, T> const& rhs) const noexcept {
        return static_cast<T>(curr_ & rhs) || rhs == empty();
    }

    /**
     * Checks whether all the specified flags are contained within the
     * current set of flags. Zero flags are treated as always present.
     *
     * @param rhs_1 First flag to check
     * @param rhs_n Other flags to check
     *
     * @return True if all the specified flags are contained within the
     *         current set of flags, otherwise false
     */
    template <typename ... U>
    [[nodiscard]] constexpr bool contains(internal::flag<ImplT, T> const& rhs_1, U const& ... rhs_n) const noexcept {
        return contains(rhs_1) && contains(rhs_n...);
    }

    /**
     * Sets specified flag.
     *
     * @param rhs Flag to be set
     */
    constexpr void set(internal::flag<ImplT, T> const& rhs) noexcept {
        curr_ |= rhs;
    }

    /**
     * Unsets specified flag.
     *
     * @param rhs Flag to be unset
     */
    constexpr void remove(internal::flag<ImplT, T> const& rhs) noexcept {
        curr_ &= ~rhs;
    }

    /**
     * Sets specified flag if not already present. Otherwise, unsets the specified flag.
     *
     * @param rhs Flag to be toggled
     */
    constexpr void toggle(internal::flag<ImplT, T> const& rhs) noexcept {
        curr_ ^= rhs;
    }

    /**
     * Clears all flags currently set.
     */
    constexpr void clear() noexcept {
        curr_ = T{};
    }

private:
    internal::flag<ImplT, T> curr_;
};

} // bf

#define BEGIN_BITFLAGS(NAME)                            \
    template <typename T>                               \
    struct NAME##Impl {                                 \
        using flag = bf::internal::flag<NAME##Impl, T>; \
        static constexpr int begin_ = __LINE__;

#define END_BITFLAGS(NAME)                    \
        static constexpr int end_ = __LINE__; \
    };                                        \
    using NAME = bf::bitflags<                \
        NAME##Impl<                           \
            bf::bitflags<                     \
                NAME##Impl<std::uint8_t>      \
            >::underlying_type                \
        >                                     \
    >;                                        \

#define FLAG(NAME) \
    static constexpr flag NAME{ bf::internal::shift<T>(__LINE__ - begin_ - 2), #NAME };

#endif // BITFLAGS_HPP