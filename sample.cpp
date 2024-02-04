//#include <benchmark/benchmark.h>
//
//// Define your benchmarking function
//static void BM_CacheWarm(benchmark::State& state) {
//    const int kSize = 10000; // Define the size of your data array
//    int data[kSize]; // Define your data array
//
//    // Warm cache by accessing data in sequential order
//    int sum_warm = 0;
//    for (int i = 0; i < kSize; ++i) {
//        benchmark::DoNotOptimize(sum_warm += data[i]);
//    }
//    benchmark::ClobberMemory();
//
//    // Run the benchmark
//    for (auto _ : state) {
//        int sum = 0;
//        // Access data in sequential order again
//        for (int i = 0; i < kSize; ++i) {
//            benchmark::DoNotOptimize(sum += data[i]);
//        }
//        benchmark::ClobberMemory();
//    }
//}
//
//// Register the benchmark
//BENCHMARK(BM_CacheWarm);
//
//// Run the benchmark
//BENCHMARK_MAIN();

#include <cstdio>
#include <cstdint>

int main() {
    double x = 100;
    const auto orig_x = x;
    auto x_as_ui = reinterpret_cast<uint64_t*>(&x);
    *x_as_ui |= 0x8000000000000000;
    printf("orig_x: %0.2f x: %0.2f &x: %p &x_as_ui: %p\n",
           orig_x, x, static_cast<void*>(&x), static_cast<void*>(x_as_ui));
    return 0;
}

