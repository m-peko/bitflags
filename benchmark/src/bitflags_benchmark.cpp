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

BEGIN_BITFLAGS(Flags)
    FLAG(none)
    FLAG(flag_a)
    FLAG(flag_b)
    FLAG(flag_c)
END_BITFLAGS(Flags)

void OperatorNot(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        flags = ~Flags::none;
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(OperatorNot);

void OperatorAnd(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        flags &= Flags::flag_a;
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(OperatorAnd);

void OperatorOr(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        flags |= Flags::flag_a;
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(OperatorOr);

void OperatorXor(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        flags ^= Flags::flag_a;
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(OperatorXor);

void Empty(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        flags = Flags::empty();
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(Empty);

void All(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        flags = Flags::all();
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(All);

void IsEmpty(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        [[maybe_unused]] bool is_empty = flags.is_empty();
        benchmark::DoNotOptimize(flags);
        benchmark::DoNotOptimize(is_empty);
    }
}

BENCHMARK(IsEmpty);

void IsAll(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        [[maybe_unused]] bool is_all = flags.is_all();
        benchmark::DoNotOptimize(flags);
        benchmark::DoNotOptimize(is_all);
    }
}

BENCHMARK(IsAll);

void Set(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        flags.set(Flags::flag_a);
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(Set);

void Remove(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        flags.remove(Flags::flag_a);
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(Remove);

void Toggle(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        flags.toggle(Flags::flag_a);
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(Toggle);

void Clear(benchmark::State& state) {
    Flags flags;

    for (auto _ : state) {
        flags.clear();
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(Clear);

BENCHMARK_MAIN();