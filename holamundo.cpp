#include <iostream>
#include <omp.h>

using namespace std;
int main()
{
#pragma omp parallel
    cout << "Hello world!! from thread: " << omp_get_thread_num() << endl;

    cout << "Total num of threads: " << omp_get_max_threads() << endl;

    return 0;
}