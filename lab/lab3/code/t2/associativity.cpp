#include <chrono>
#include <fstream>
#include <string>

// the number of bytes in a cache block or cache line (see the file
// `coherency_line_size` in /sys/devices/system/cpu/cpu0/cache for this number)
#define _CACHEBLOCK_BYTES_ 64

// L1 cache size on Intel Xeon E5-2680/83 v4: 1 << 15 = 32768 bytes (32kB)
#define _CACHE_SIZE_ (1 << 15)

void measure_flops(const int m, const int k, std::ostream &stream)
{
    // allocate coalesced memory buffer for experiment and initialize to some
    // values
    const int n_elem = m * k; // total number of array elements
    volatile double *buffer = new double[n_elem];
    for (int i = 0; i < n_elem; ++i) {
        buffer[i] = 0.999 + 1e-10 * i;
    }

    // we repeat the measurement a couple of times to smooth out noise (we do
    // more repetitions for fewer arrays k as this is associated with less work)
    const int repeat = 2000 / k;
    auto t0 = std::chrono::steady_clock::now();
    for (int r = 0; r < repeat; ++r) {
        // TODO: figure out the correct loop bounds
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < k; ++j) {
                buffer[i * k + j] += 1.0123;
            }
        }
    }
    auto t1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> tdiff = t1 - t0;

    // free the memory
    delete[] buffer;

    // write measurement results
    double time = tdiff.count();
    double Gflops = static_cast<double>(repeat) * m * k * 1.0e-9 / time;
    stream << std::scientific << m << '\t' << k << '\t' << Gflops << '\n';
}

void run(const int m, const int n_arrays, const std::string fname)
{
    std::ofstream fout(fname);

    // write header
    fout << "# m\tk\tGflop/s\n";

    // loop over number of arrays k
    for (int k = 1; k <= n_arrays; ++k) {
        measure_flops(m, k, fout);
    }
}

int main()
{
    // test array size m (this must be an integer multiple of the L1 cache size)
    const int m = 1 * _CACHE_SIZE_ / sizeof(double);

    // how many arrays we want to use (should be at least the number of
    // associativity in the cache you target)
    const int n_arrays = 32; // usually L1 caches are 8-way associative today

    // array size is an integer multiple of the cache size: prone to cache
    // thrashing!  This is the bad scenario.
    run(m, n_arrays, "thrashing.dat");

    // adding one cache block size to the array size has a padding effect and
    // shifts associativities to the next set.  This is the good scenario.
    run(m + _CACHEBLOCK_BYTES_ / sizeof(double), n_arrays, "padded.dat");

    return 0;
}
