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
    BEGIN_RAW_BITFLAGS(RawFlags)
        RAW_FLAG(none)
        RAW_FLAG(flag_a)
        RAW_FLAG(flag_b)
        RAW_FLAG(flag_c)
    END_RAW_BITFLAGS(RawFlags)

    BEGIN_BITFLAGS(Flags)
        FLAG(none)
        FLAG(flag_a)
        FLAG(flag_b)
        FLAG(flag_c)
    END_BITFLAGS(Flags)
};

TEST_F(BitflagsTest, Bits) {
#if __cplusplus >= 201402L
    // raw flags (without string representation)
    EXPECT_EQ(0b0000U, RawFlags::none.bits);
    EXPECT_EQ(0b0001U, RawFlags::flag_a.bits);
    EXPECT_EQ(0b0010U, RawFlags::flag_b.bits);
    EXPECT_EQ(0b0100U, RawFlags::flag_c.bits);

    // flags (with string representation)
    EXPECT_EQ(0b0000U, Flags::none.bits);
    EXPECT_EQ(0b0001U, Flags::flag_a.bits);
    EXPECT_EQ(0b0010U, Flags::flag_b.bits);
    EXPECT_EQ(0b0100U, Flags::flag_c.bits);
#else
    // raw flags (without string representation)
    EXPECT_EQ(0x00U, RawFlags::none.bits);
    EXPECT_EQ(0x01U, RawFlags::flag_a.bits);
    EXPECT_EQ(0x02U, RawFlags::flag_b.bits);
    EXPECT_EQ(0x04U, RawFlags::flag_c.bits);

    // flags (with string representation)
    EXPECT_EQ(0x00U, Flags::none.bits);
    EXPECT_EQ(0x01U, Flags::flag_a.bits);
    EXPECT_EQ(0x02U, Flags::flag_b.bits);
    EXPECT_EQ(0x04U, Flags::flag_c.bits);
#endif
}

TEST_F(BitflagsTest, Name) {
#if __cplusplus >= 201703L
    EXPECT_EQ("none", Flags::none.name);
    EXPECT_EQ("flag_a", Flags::flag_a.name);
    EXPECT_EQ("flag_b", Flags::flag_b.name);
    EXPECT_EQ("flag_c", Flags::flag_c.name);
#else
    EXPECT_STREQ("none", Flags::none.name);
    EXPECT_STREQ("flag_a", Flags::flag_a.name);
    EXPECT_STREQ("flag_b", Flags::flag_b.name);
    EXPECT_STREQ("flag_c", Flags::flag_c.name);
#endif
}

TEST_F(BitflagsTest, CastToUnderlyingType) {
#if __cplusplus >= 201402L
    // raw flags (without string representation)
    EXPECT_EQ(0b0000U, static_cast<RawFlags::underlying_type>(RawFlags::none));
    EXPECT_EQ(0b0001U, static_cast<RawFlags::underlying_type>(RawFlags::flag_a));
    EXPECT_EQ(0b0010U, static_cast<RawFlags::underlying_type>(RawFlags::flag_b));
    EXPECT_EQ(0b0100U, static_cast<RawFlags::underlying_type>(RawFlags::flag_c));

    // flags (with string representation)
    EXPECT_EQ(0b0000U, static_cast<Flags::underlying_type>(Flags::none));
    EXPECT_EQ(0b0001U, static_cast<Flags::underlying_type>(Flags::flag_a));
    EXPECT_EQ(0b0010U, static_cast<Flags::underlying_type>(Flags::flag_b));
    EXPECT_EQ(0b0100U, static_cast<Flags::underlying_type>(Flags::flag_c));
#else
    // raw flags (without string representation)
    EXPECT_EQ(0x00U, static_cast<RawFlags::underlying_type>(RawFlags::none));
    EXPECT_EQ(0x01U, static_cast<RawFlags::underlying_type>(RawFlags::flag_a));
    EXPECT_EQ(0x02U, static_cast<RawFlags::underlying_type>(RawFlags::flag_b));
    EXPECT_EQ(0x04U, static_cast<RawFlags::underlying_type>(RawFlags::flag_c));

    // flags (with string representation)
    EXPECT_EQ(0x00U, static_cast<Flags::underlying_type>(Flags::none));
    EXPECT_EQ(0x01U, static_cast<Flags::underlying_type>(Flags::flag_a));
    EXPECT_EQ(0x02U, static_cast<Flags::underlying_type>(Flags::flag_b));
    EXPECT_EQ(0x04U, static_cast<Flags::underlying_type>(Flags::flag_c));
#endif
}

TEST_F(BitflagsTest, OperatorNot) {
    // raw flags (without string representation)
    RawFlags raw_flags = ~RawFlags::none;

    EXPECT_TRUE(raw_flags & RawFlags::flag_a);
    EXPECT_TRUE(raw_flags & RawFlags::flag_b);
    EXPECT_TRUE(raw_flags & RawFlags::flag_c);

    // flags (with string representation)
    Flags flags = ~Flags::none;

    EXPECT_TRUE(flags & Flags::flag_a);
    EXPECT_TRUE(flags & Flags::flag_b);
    EXPECT_TRUE(flags & Flags::flag_c);
}

TEST_F(BitflagsTest, OperatorAnd) {
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::flag_a | RawFlags::flag_b;

    EXPECT_TRUE(raw_flags & RawFlags::flag_a);
    EXPECT_TRUE(raw_flags & RawFlags::flag_b);
    EXPECT_FALSE(raw_flags & RawFlags::flag_c);

    // flags (with string representation)
    Flags flags = Flags::flag_a | Flags::flag_b;

    EXPECT_TRUE(flags & Flags::flag_a);
    EXPECT_TRUE(flags & Flags::flag_b);
    EXPECT_FALSE(flags & Flags::flag_c);
}

TEST_F(BitflagsTest, OperatorOr) {
#if __cplusplus >= 201402L
    // raw flags (without string representation)
    EXPECT_EQ(0b0011U, RawFlags::flag_a | RawFlags::flag_b);
    EXPECT_EQ(0b0111U, RawFlags::flag_a | RawFlags::flag_b | RawFlags::flag_c);

    // flags (with string representation)
    EXPECT_EQ(0b0011U, Flags::flag_a | Flags::flag_b);
    EXPECT_EQ(0b0111U, Flags::flag_a | Flags::flag_b | Flags::flag_c);
#else
    // raw flags (without string representation)
    EXPECT_EQ(0x03U, RawFlags::flag_a | RawFlags::flag_b);
    EXPECT_EQ(0x07U, RawFlags::flag_a | RawFlags::flag_b | RawFlags::flag_c);

    // flags (with string representation)
    EXPECT_EQ(0x03U, Flags::flag_a | Flags::flag_b);
    EXPECT_EQ(0x07U, Flags::flag_a | Flags::flag_b | Flags::flag_c);
#endif
}

TEST_F(BitflagsTest, OperatorXor) {
#if __cplusplus >= 201402L
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::flag_a;

    EXPECT_EQ(0b0001U, raw_flags.bits());

    raw_flags ^= RawFlags::flag_a;
    EXPECT_EQ(0b0000U, raw_flags.bits());

    raw_flags ^= RawFlags::flag_a;
    EXPECT_EQ(0b0001U, raw_flags.bits());

    // flags (with string representation)
    Flags flags = Flags::flag_a;

    EXPECT_EQ(0b0001U, flags.bits());

    flags ^= Flags::flag_a;
    EXPECT_EQ(0b0000U, flags.bits());

    flags ^= Flags::flag_a;
    EXPECT_EQ(0b0001U, flags.bits());
#else
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::flag_a;

    EXPECT_EQ(0x01U, raw_flags.bits());

    raw_flags ^= RawFlags::flag_a;
    EXPECT_EQ(0x00U, raw_flags.bits());

    raw_flags ^= RawFlags::flag_a;
    EXPECT_EQ(0x01U, raw_flags.bits());

    // flags (with string representation)
    Flags flags = Flags::flag_a;

    EXPECT_EQ(0x01U, flags.bits());

    flags ^= Flags::flag_a;
    EXPECT_EQ(0x00U, flags.bits());

    flags ^= Flags::flag_a;
    EXPECT_EQ(0x01U, flags.bits());
#endif
}

TEST_F(BitflagsTest, Empty) {
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::empty();

    EXPECT_TRUE(raw_flags.is_empty());
    EXPECT_FALSE(raw_flags.all_set());
    EXPECT_FALSE(raw_flags & RawFlags::flag_a);
    EXPECT_FALSE(raw_flags & RawFlags::flag_b);
    EXPECT_FALSE(raw_flags & RawFlags::flag_c);

    // flags (with string representation)
    Flags flags = Flags::empty();

    EXPECT_TRUE(flags.is_empty());
    EXPECT_FALSE(flags.all_set());
    EXPECT_FALSE(flags & Flags::flag_a);
    EXPECT_FALSE(flags & Flags::flag_b);
    EXPECT_FALSE(flags & Flags::flag_c);
}

TEST_F(BitflagsTest, All) {
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::flag_a | RawFlags::flag_b | RawFlags::flag_c;

    EXPECT_FALSE(raw_flags.is_empty());
    EXPECT_TRUE(raw_flags.all_set());
    EXPECT_TRUE(raw_flags & RawFlags::flag_a);
    EXPECT_TRUE(raw_flags & RawFlags::flag_b);
    EXPECT_TRUE(raw_flags & RawFlags::flag_c);    
    
    // flags (with string representation)
    Flags flags = Flags::flag_a | Flags::flag_b | Flags::flag_c;

    EXPECT_FALSE(flags.is_empty());
    EXPECT_TRUE(flags.all_set());
    EXPECT_TRUE(flags & Flags::flag_a);
    EXPECT_TRUE(flags & Flags::flag_b);
    EXPECT_TRUE(flags & Flags::flag_c);
}

TEST_F(BitflagsTest, Contains) {
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::flag_a | RawFlags::flag_b;

    EXPECT_TRUE(raw_flags.is_set(RawFlags::none));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_a));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_b));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_c));

    EXPECT_TRUE(raw_flags.is_set(RawFlags::none, RawFlags::flag_a, RawFlags::flag_b));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::none, RawFlags::flag_a, RawFlags::flag_c));

    // flags (with string representation)
    Flags flags = Flags::flag_a | Flags::flag_b;

    EXPECT_TRUE(flags.is_set(Flags::none));
    EXPECT_TRUE(flags.is_set(Flags::flag_a));
    EXPECT_TRUE(flags.is_set(Flags::flag_b));
    EXPECT_FALSE(flags.is_set(Flags::flag_c));

    EXPECT_TRUE(flags.is_set(Flags::none, Flags::flag_a, Flags::flag_b));
    EXPECT_FALSE(flags.is_set(Flags::none, Flags::flag_a, Flags::flag_c));
}

TEST_F(BitflagsTest, Set) {
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::none;

    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_a));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_b));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_c));

    raw_flags.set(RawFlags::flag_a);
    raw_flags.set(RawFlags::flag_b);

    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_a));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_b));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_c));

    // flags (with string representation)
    Flags flags = Flags::none;

    EXPECT_FALSE(flags.is_set(Flags::flag_a));
    EXPECT_FALSE(flags.is_set(Flags::flag_b));
    EXPECT_FALSE(flags.is_set(Flags::flag_c));

    flags.set(Flags::flag_a);
    flags.set(Flags::flag_b);

    EXPECT_TRUE(flags.is_set(Flags::flag_a));
    EXPECT_TRUE(flags.is_set(Flags::flag_b));
    EXPECT_FALSE(flags.is_set(Flags::flag_c));
}

TEST_F(BitflagsTest, Remove) {
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::flag_a | RawFlags::flag_b | RawFlags::flag_c;

    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_a));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_b));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_c));

    raw_flags.clear(RawFlags::flag_a);
    raw_flags.clear(RawFlags::flag_b);

    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_a));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_b));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_c));

    // flags (with string representation)
    Flags flags = Flags::flag_a | Flags::flag_b | Flags::flag_c;

    EXPECT_TRUE(flags.is_set(Flags::flag_a));
    EXPECT_TRUE(flags.is_set(Flags::flag_b));
    EXPECT_TRUE(flags.is_set(Flags::flag_c));

    flags.clear(Flags::flag_a);
    flags.clear(Flags::flag_b);

    EXPECT_FALSE(flags.is_set(Flags::flag_a));
    EXPECT_FALSE(flags.is_set(Flags::flag_b));
    EXPECT_TRUE(flags.is_set(Flags::flag_c));
}

TEST_F(BitflagsTest, Toggle) {
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::flag_a | RawFlags::flag_b;

    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_a));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_b));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_c));

    raw_flags.toggle(RawFlags::flag_a);
    raw_flags.toggle(RawFlags::flag_c);

    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_a));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_b));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_c));

    raw_flags.toggle(RawFlags::flag_a);
    raw_flags.toggle(RawFlags::flag_b);

    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_a));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_b));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_c));

    // flags (with string representation)
    Flags flags = Flags::flag_a | Flags::flag_b;

    EXPECT_TRUE(flags.is_set(Flags::flag_a));
    EXPECT_TRUE(flags.is_set(Flags::flag_b));
    EXPECT_FALSE(flags.is_set(Flags::flag_c));

    flags.toggle(Flags::flag_a);
    flags.toggle(Flags::flag_c);

    EXPECT_FALSE(flags.is_set(Flags::flag_a));
    EXPECT_TRUE(flags.is_set(Flags::flag_b));
    EXPECT_TRUE(flags.is_set(Flags::flag_c));

    flags.toggle(Flags::flag_a);
    flags.toggle(Flags::flag_b);

    EXPECT_TRUE(flags.is_set(Flags::flag_a));
    EXPECT_FALSE(flags.is_set(Flags::flag_b));
    EXPECT_TRUE(flags.is_set(Flags::flag_c));
}

TEST_F(BitflagsTest, Clear) {
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::flag_a | RawFlags::flag_b;

    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_a));
    EXPECT_TRUE(raw_flags.is_set(RawFlags::flag_b));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_c));

    raw_flags.clear();

    EXPECT_TRUE(raw_flags.is_empty());
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_a));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_b));
    EXPECT_FALSE(raw_flags.is_set(RawFlags::flag_c));

    // flags (with string representation)
    Flags flags = Flags::flag_a | Flags::flag_b;

    EXPECT_TRUE(flags.is_set(Flags::flag_a));
    EXPECT_TRUE(flags.is_set(Flags::flag_b));
    EXPECT_FALSE(flags.is_set(Flags::flag_c));

    flags.clear();

    EXPECT_TRUE(flags.is_empty());
    EXPECT_FALSE(flags.is_set(Flags::flag_a));
    EXPECT_FALSE(flags.is_set(Flags::flag_b));
    EXPECT_FALSE(flags.is_set(Flags::flag_c));
}

TEST_F(BitflagsTest, OnlySet) {
    // raw flags (without string representation)
    RawFlags raw_flags = RawFlags::flag_a | RawFlags::flag_b;

    EXPECT_FALSE(raw_flags.only_set(RawFlags::flag_a));
    EXPECT_FALSE(raw_flags.only_set(RawFlags::flag_b));
    
    EXPECT_FALSE(raw_flags.only_set(RawFlags::flag_b));
    raw_flags.clear(RawFlags::flag_b);

    EXPECT_TRUE(raw_flags.only_set(RawFlags::flag_a));

    raw_flags.set(RawFlags::flag_c);
    EXPECT_FALSE(raw_flags.only_set(RawFlags::flag_a));
}
