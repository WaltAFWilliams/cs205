#include <iostream>
#include <omp.h>

class Counter
{
public:
    Counter() : count_(0) {}

    void increment() { ++count_; }
    unsigned int get_count() const { return count_; }

private:
    unsigned int count_;
};

int main(void)
{
    // shared counter
    Counter counter;

    // get number of threads
    int nthreads;
#pragma omp parallel
    {
#pragma omp master // only primary thread here (could also use omp single)
        nthreads = omp_get_num_threads();
    }

    // measure time
    double t0, t1;
    t0 = omp_get_wtime();

#pragma omp parallel for
    for (int i = 0; i < 1000000; ++i) {
	# pragma omp critical
        counter.increment(); // perform task in critical section
    }

    t1 = omp_get_wtime();
    std::cout << "Count:   " << counter.get_count() << '\n'
              << "Threads: " << nthreads << '\n'
              << "Elapsed: " << t1 - t0 << " seconds\n";
    return 0;
}
