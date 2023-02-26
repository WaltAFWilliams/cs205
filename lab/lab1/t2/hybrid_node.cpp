#include <iostream>
#include <mpi.h>
#include <omp.h>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

// return cpu and numa node id
// https://stackoverflow.com/questions/16862620/numa-get-current-node-core
unsigned long tacc_rdtscp(int *core, int *node)
{
    unsigned long a, d, c;
    __asm__ volatile("rdtscp" : "=a"(a), "=d"(d), "=c"(c));
    *node = (c & 0xFFF000) >> 12;
    *core = c & 0xFFF;
    return ((unsigned long)a) | (((unsigned long)d) << 32);
    ;
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int myrank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int nThreads;
#pragma omp parallel
    {
#pragma omp master
        nThreads = omp_get_num_threads();
    }

    vector<string> messages(nThreads);

#pragma omp parallel
    {
        const int tid = omp_get_thread_num();

        int cpuid, nodeid;
        tacc_rdtscp(&cpuid, &nodeid);

        string hostname(1024, '\0');
        gethostname(&hostname.front(), hostname.size());

#pragma omp critical
        {
            ostringstream mystream;
            mystream << "[rank=" << myrank << "/" << size;
            mystream << "\tthread=" << tid << "/" << nThreads << "]\t";
            mystream << "Running on host " << hostname.c_str() << "\tCPU "
                     << cpuid << "\tNUMA NODE " << nodeid;
            messages[tid] = mystream.str();
        }
    }

    for (int i = 0; i < size; ++i) {
        if (i == myrank) {
            for (const string &message : messages)
                cout << message << endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
