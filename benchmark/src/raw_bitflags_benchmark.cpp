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

#include <benchmark/benchmark.h>
#include <bitflags/bitflags.hpp>

BEGIN_RAW_BITFLAGS(RawFlags)
    RAW_FLAG(none)
    RAW_FLAG(flag_a)
    RAW_FLAG(flag_b)
    RAW_FLAG(flag_c)
END_RAW_BITFLAGS(RawFlags)

void OperatorNot(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        raw_flags = ~RawFlags::none;
        benchmark::DoNotOptimize(raw_flags);
    }
}

BENCHMARK(OperatorNot);

void OperatorAnd(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        raw_flags &= RawFlags::flag_a;
        benchmark::DoNotOptimize(raw_flags);
    }
}

BENCHMARK(OperatorAnd);

void OperatorOr(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        raw_flags |= RawFlags::flag_a;
        benchmark::DoNotOptimize(raw_flags);
    }
}

BENCHMARK(OperatorOr);

void OperatorXor(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        raw_flags ^= RawFlags::flag_a;
        benchmark::DoNotOptimize(raw_flags);
    }
}

BENCHMARK(OperatorXor);

void Empty(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        raw_flags = RawFlags::empty();
        benchmark::DoNotOptimize(raw_flags);
    }
}

BENCHMARK(Empty);

void All(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        raw_flags = RawFlags::all();
        benchmark::DoNotOptimize(raw_flags);
    }
}

BENCHMARK(All);

void IsEmpty(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        [[maybe_unused]] bool is_empty = raw_flags.is_empty();
        benchmark::DoNotOptimize(raw_flags);
        benchmark::DoNotOptimize(is_empty);
    }
}

BENCHMARK(IsEmpty);

void IsAll(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        [[maybe_unused]] bool is_all = raw_flags.is_all();
        benchmark::DoNotOptimize(raw_flags);
        benchmark::DoNotOptimize(is_all);
    }
}

BENCHMARK(IsAll);

void Set(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        raw_flags.set(RawFlags::flag_a);
        benchmark::DoNotOptimize(raw_flags);
    }
}

BENCHMARK(Set);

void Remove(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        raw_flags.remove(RawFlags::flag_a);
        benchmark::DoNotOptimize(raw_flags);
    }
}

BENCHMARK(Remove);

void Toggle(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        raw_flags.toggle(RawFlags::flag_a);
        benchmark::DoNotOptimize(raw_flags);
    }
}

BENCHMARK(Toggle);

void Clear(benchmark::State& state) {
    RawFlags raw_flags;

    for (auto _ : state) {
        raw_flags.clear();
        benchmark::DoNotOptimize(raw_flags);
    }
}

BENCHMARK(Clear);

BENCHMARK_MAIN();