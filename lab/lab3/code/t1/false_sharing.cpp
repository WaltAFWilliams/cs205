#include <cstring>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <string>

// Here we define the maximum stride for our experiment.  Since we use double
// types below (=8 byte) we have 8 * 8 = 64 byte and 2 * 64 = 128 byte, that is
// a maximum stride that is two cache lines wide (one cache line is 64 byte).
#define _MAX_STRIDE_ 8 * 2

// This is specific for the architecture.  We use one compute node on the
// cluster, allocate with:
// salloc -N1 -c32 -t 1:00:00
// NOTE: when you try to run the code on your laptop, change the maximum number
// of threads below to what your architecture supports.  It should be a power of
// two.
#define _MAX_THREADS_ 32

// maximum number of array elements
#define _ARRAY_SIZE_ (_MAX_THREADS_ * (_MAX_STRIDE_ + 1))

int main(void)
{
    // integration steps and interval width
    const size_t nsteps = 1 << 27;
    const double dx = 1.0 / static_cast<double>(nsteps);

    // thread local pi array (using arrays for thread local data is usually
    // dangerous w/r/t false sharing, just create thread local variables in a
    // parallel region).  This array is large enough to be used with the target
    // number of threads and we ensure it is aligned at 64 byte boundaries,
    // i.e., guaranteed to be aligned with cache lines.  The volatile specifier
    // is used to enforce false sharing in this example.
    alignas(64) volatile double tpi[_ARRAY_SIZE_];

    for (int stride = 1; stride <= _MAX_STRIDE_; stride *= 2) {
        // create result file for this stride experiment
        std::ofstream fout("stride" + std::to_string(stride * sizeof(double)) +
                           "byte.dat");
        double t1 = 1.0; // single-threaded wall time

        // run different numbers of threads (powers of two)
        for (int threads = 1; threads <= _MAX_THREADS_; threads *= 2) {
            // global pi (for the thread reduction)
            double gpi = 0.0;

            // set array elements to zero
            std::memset((void *)tpi, 0, _ARRAY_SIZE_ * sizeof(double));

            // start computation and measure wall time
            const double t0 = omp_get_wtime();

            // create parallel region with the required number of threads
            // TODO: there is a clause missing here.  We spawn a parallel region
            // and we must ensure the team of threads has exactly `threads`
            // members (this is the loop variable of the enclosing loop).  What
            // is the right clause?
#pragma omp parallel num_threads(threads)// clause missing here
            {
                // compute thread id used to index into the shared array
                // TODO: here we compute the thread ID `tid`.  The experiment
                // consists of scaling this thread ID to investigate at which
                // scale false sharing is observed or not.  Below the scaling
                // factor is hard coded by `1`, replace it with the correct
                // scaling factor for this experiment.
                const int tid = stride * omp_get_thread_num();

#pragma omp for nowait schedule(static)
                for (size_t i = 0; i < nsteps; ++i) {
                    const double x = (i + 0.5) * dx;
                    // the following line causes false sharing if the read and
                    // writes are from the L1 cache!  We enforce these L1 memory
                    // reads by using the volatile type specifier for `tpi`
                    // above.  The volatile specifier means that the compiler is
                    // not allowed to cache the data in registers and therefore
                    // must perform the L1 memory operations.  For this code an
                    // optimizing compiler would use registers for which we
                    // would not run into false sharing.  It may not be the case
                    // for more complex code in real applications.
                    tpi[tid] += 4.0 / (1.0 + x * x);
                }

                // TODO: here we perform a reduction into the global `gpi`
                // variable which will hold the result (pi) eventually.
                // Something is wrong here.
#pragma omp for reduction(+:gpi) schedule(static)
                for (int i = 0; i < threads * stride; ++i) {
                    gpi += tpi[i];
                }
            }
            const double dt = omp_get_wtime() - t0; // elapsed time
            const double res = gpi * dx;            // result (pi)
            t1 = (1 == threads) ? dt : t1;

            // write experiment data to file
            fout << std::scientific << res << '\t' << threads << '\t' << dt
                 << '\t' << t1 / dt << '\n';
        }
    }
    return 0;
}
