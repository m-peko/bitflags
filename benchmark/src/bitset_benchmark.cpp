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

#include <bitset>
#include <benchmark/benchmark.h>

void OperatorNot(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        flags = ~0b0000;
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(OperatorNot);

void OperatorAnd(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        flags &= 0b0001;
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(OperatorAnd);

void OperatorOr(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        flags |= 0b0001;
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(OperatorOr);

void OperatorXor(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        flags ^= 0b0001;
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(OperatorXor);

void Empty(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        flags.reset();
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(Empty);

void All(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        flags.set();
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(All);

void IsEmpty(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        [[maybe_unused]] bool is_empty = flags.none();
        benchmark::DoNotOptimize(flags);
        benchmark::DoNotOptimize(is_empty);
    }
}

BENCHMARK(IsEmpty);

void IsAll(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        [[maybe_unused]] bool is_all = flags.all();
        benchmark::DoNotOptimize(flags);
        benchmark::DoNotOptimize(is_all);
    }
}

BENCHMARK(IsAll);

void Set(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        flags.set(0);
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(Set);

void Remove(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        flags.reset(0);
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(Remove);

void Toggle(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        flags.flip(0);
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(Toggle);

void Clear(benchmark::State& state) {
    std::bitset<8> flags;

    for (auto _ : state) {
        flags.reset();
        benchmark::DoNotOptimize(flags);
    }
}

BENCHMARK(Clear);

BENCHMARK_MAIN();