#include "boost/container_hash/hash.hpp"
#include "clhash.h"
#include "fmt/format.h"
#include <benchmark/benchmark.h>
#include <functional>

// farmhash header
#define XXH_INLINE_ALL
#include "xxhash.h"

const std::string test_string =
    "We hold these truths to be self-evident, that all men are created equal, that they are "
    "endowed by their Creator with certain unalienable Rights, "
    "that among these are Life, Liberty and the pursuit of Happiness. "
    "That to secure these rights, Governments are instituted among Men, deriving their just "
    "powers from the consent of the governed, "
    "That whenever any Form of Government becomes destructive of these ends, it is the Right "
    "of the People to alter or to abolish it, "
    "and to institute new Government, laying its foundation on such principles and organizing "
    "its powers in such form, as to them shall "
    "seem most likely to effect their Safety and Happiness. Prudence, indeed, will dictate "
    "that Governments long established should not "
    "be changed for light and transient causes; and accordingly all experience hath shewn, "
    "that mankind are more disposed to suffer, "
    "while evils are sufferable, than to right themselves by abolishing the forms to which "
    "they are accustomed. But when a long train "
    "of abuses and usurpations, pursuing invariably the same Object evinces a design to reduce "
    "them under absolute Despotism, it is their "
    "right, it is their duty, to throw off such Government, and to provide new Guards for "
    "their future security.";

// hash functions
void std_hash_string(benchmark::State &state) {
    std::hash<std::string> h;
    for (auto _ : state) { benchmark::DoNotOptimize(h(test_string)); }
}
// Register the function as a benchmark
BENCHMARK(std_hash_string);

void clhash_string(benchmark::State &state) {
    util::CLHash clhash;
    for (auto _ : state) {
        benchmark::DoNotOptimize(clhash(test_string.data(), test_string.size()));
    }
}
// Register the function as a benchmark
BENCHMARK(clhash_string);

void boost_hash_string(benchmark::State &state) {
    boost::hash<std::string> h;
    for (auto _ : state) { benchmark::DoNotOptimize(h(test_string)); }
}
// Register the function as a benchmark
BENCHMARK(boost_hash_string);

BENCHMARK_MAIN();
