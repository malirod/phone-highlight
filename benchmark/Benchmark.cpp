// Copyright [2019] <Malinovsky Rodion> (rodionmalino@gmail.com)
#include "UtfUtils.h"
#include "UtfUtilsIcu.h"

#include <benchmark/benchmark.h>

namespace {

const std::vector<std::string> UFT8_STRINGS = { "Hello", u8"ℵ", u8"zß水", "\u00A0" };

} // namespace

static void BM_UTF8ToUTF32(benchmark::State& state)
{
    for (auto _ : state)
        const auto result = rms::UTF8ToUTF32(UFT8_STRINGS[state.range(0)]);
}
BENCHMARK(BM_UTF8ToUTF32)->Arg(0)->Arg(1)->Arg(2)->Arg(3);

static void BM_UTF8ToUTF32ICU(benchmark::State& state)
{
    for (auto _ : state)
        const auto result = rms::UTF8ToUTF32ICU(UFT8_STRINGS[state.range(0)]);
}
BENCHMARK(BM_UTF8ToUTF32ICU)->Arg(0)->Arg(1)->Arg(2)->Arg(3);

BENCHMARK_MAIN();
