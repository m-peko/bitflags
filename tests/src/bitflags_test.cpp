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

#include <gtest/gtest.h>
#include <bitflags/bitflags.hpp>

struct BitflagsTest : testing::Test {
    struct Flags : bf::bitflags<uint32_t> {
        using bitflags<uint32_t>::bitflags;

        BITFLAG(0x00000000, none);
        BITFLAG(0x00000001, flag_a);
        BITFLAG(0x00000010, flag_b);
        BITFLAG(0x00000100, flag_c);
    };
};

TEST_F(BitflagsTest, Bits) {
    EXPECT_EQ(Flags::none.bits, 0x00000000U);
    EXPECT_EQ(Flags::flag_a.bits, 0x00000001U);
    EXPECT_EQ(Flags::flag_b.bits, 0x00000010U);
    EXPECT_EQ(Flags::flag_c.bits, 0x00000100U);
}

TEST_F(BitflagsTest, Name) {
    EXPECT_STREQ(Flags::none.name.data(), "none");
    EXPECT_STREQ(Flags::flag_a.name.data(), "flag_a");
    EXPECT_STREQ(Flags::flag_b.name.data(), "flag_b");
    EXPECT_STREQ(Flags::flag_c.name.data(), "flag_c");
}

TEST_F(BitflagsTest, CastToUnderlyingType) {
    EXPECT_EQ(static_cast<Flags::underlying_type>(Flags::none), 0x00000000U);
    EXPECT_EQ(static_cast<Flags::underlying_type>(Flags::flag_a), 0x00000001U);
    EXPECT_EQ(static_cast<Flags::underlying_type>(Flags::flag_b), 0x00000010U);
    EXPECT_EQ(static_cast<Flags::underlying_type>(Flags::flag_c), 0x00000100U);
}

TEST_F(BitflagsTest, OperatorNot) {
    Flags flags = ~Flags::none;

    EXPECT_TRUE(flags & Flags::flag_a);
    EXPECT_TRUE(flags & Flags::flag_b);
    EXPECT_TRUE(flags & Flags::flag_c);
}

TEST_F(BitflagsTest, OperatorAnd) {
    Flags flags = Flags::flag_a | Flags::flag_b;

    EXPECT_TRUE(flags & Flags::flag_a);
    EXPECT_TRUE(flags & Flags::flag_b);
    EXPECT_FALSE(flags & Flags::flag_c);
}

TEST_F(BitflagsTest, OperatorOr) {
    EXPECT_EQ(0x00000011U, Flags::flag_a | Flags::flag_b);
    EXPECT_EQ(0x00000111U, Flags::flag_a | Flags::flag_b | Flags::flag_c);
}

TEST_F(BitflagsTest, OperatorXor) {
    Flags flags = Flags::flag_a;

    EXPECT_EQ(0x00000001U, flags);

    flags ^= Flags::flag_a;
    EXPECT_EQ(0x00000000U, flags);

    flags ^= Flags::flag_a;
    EXPECT_EQ(0x00000001U, flags);
}

TEST_F(BitflagsTest, Empty) {
    Flags flags = Flags::empty();

    EXPECT_TRUE(flags.is_empty());
    EXPECT_FALSE(flags.is_all());
    EXPECT_FALSE(flags & Flags::flag_a);
    EXPECT_FALSE(flags & Flags::flag_b);
    EXPECT_FALSE(flags & Flags::flag_c);
}

TEST_F(BitflagsTest, All) {
    Flags flags = Flags::all();

    EXPECT_FALSE(flags.is_empty());
    EXPECT_TRUE(flags.is_all());
    EXPECT_TRUE(flags & Flags::flag_a);
    EXPECT_TRUE(flags & Flags::flag_b);
    EXPECT_TRUE(flags & Flags::flag_c);
}

TEST_F(BitflagsTest, Contains) {
    Flags flags = Flags::flag_a | Flags::flag_b;

    EXPECT_TRUE(flags.contains(Flags::none));
    EXPECT_TRUE(flags.contains(Flags::flag_a));
    EXPECT_TRUE(flags.contains(Flags::flag_b));
    EXPECT_FALSE(flags.contains(Flags::flag_c));

    EXPECT_TRUE(flags.contains(Flags::none, Flags::flag_a, Flags::flag_b));
    EXPECT_FALSE(flags.contains(Flags::none, Flags::flag_a, Flags::flag_c));
}

TEST_F(BitflagsTest, Set) {
    Flags flags = Flags::none;

    EXPECT_FALSE(flags.contains(Flags::flag_a));
    EXPECT_FALSE(flags.contains(Flags::flag_b));
    EXPECT_FALSE(flags.contains(Flags::flag_c));

    flags.set(Flags::flag_a);
    flags.set(Flags::flag_b);

    EXPECT_TRUE(flags.contains(Flags::flag_a));
    EXPECT_TRUE(flags.contains(Flags::flag_b));
    EXPECT_FALSE(flags.contains(Flags::flag_c));
}

TEST_F(BitflagsTest, Remove) {
    Flags flags = Flags::flag_a | Flags::flag_b;

    EXPECT_TRUE(flags.contains(Flags::flag_a));
    EXPECT_TRUE(flags.contains(Flags::flag_b));
    EXPECT_FALSE(flags.contains(Flags::flag_c));

    flags.remove(Flags::flag_a);
    flags.remove(Flags::flag_b);

    EXPECT_FALSE(flags.contains(Flags::flag_a));
    EXPECT_FALSE(flags.contains(Flags::flag_b));
    EXPECT_FALSE(flags.contains(Flags::flag_c));
}

TEST_F(BitflagsTest, Toggle) {
    Flags flags = Flags::flag_a | Flags::flag_b;

    EXPECT_TRUE(flags.contains(Flags::flag_a));
    EXPECT_TRUE(flags.contains(Flags::flag_b));
    EXPECT_FALSE(flags.contains(Flags::flag_c));

    flags.toggle(Flags::flag_a);
    flags.toggle(Flags::flag_c);

    EXPECT_FALSE(flags.contains(Flags::flag_a));
    EXPECT_TRUE(flags.contains(Flags::flag_b));
    EXPECT_TRUE(flags.contains(Flags::flag_c));

    flags.toggle(Flags::flag_a);
    flags.toggle(Flags::flag_b);

    EXPECT_TRUE(flags.contains(Flags::flag_a));
    EXPECT_FALSE(flags.contains(Flags::flag_b));
    EXPECT_TRUE(flags.contains(Flags::flag_c));
}

TEST_F(BitflagsTest, Clear) {
    Flags flags = Flags::flag_a | Flags::flag_b;

    EXPECT_TRUE(flags.contains(Flags::flag_a));
    EXPECT_TRUE(flags.contains(Flags::flag_b));
    EXPECT_FALSE(flags.contains(Flags::flag_c));

    flags.clear();

    EXPECT_TRUE(flags.is_empty());
    EXPECT_FALSE(flags.contains(Flags::flag_a));
    EXPECT_FALSE(flags.contains(Flags::flag_b));
    EXPECT_FALSE(flags.contains(Flags::flag_c));
}