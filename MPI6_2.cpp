#include <iostream>
#include "mpi.h"
#include <string>
#include <cmath>
#include <chrono>
#include <random>
using namespace std;
int A[65536], min2 = MAX_INT, countofe = 65536, sended = 0, globmin = 0;
int main(int argc, char** argv)
{
	int numtasks, rank, a = 0;
	bool gotit;
	for (int i = 0; i < countofe; i++)
	A[i] = -1000 + rand();
	auto start_time = std::chrono::steady_clock::now();
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	MPI_Op op{};
	int localmin = MAX_INT, localmini;
	for (int i = 65536 / 8 * rank; i < 65536 / 8 * (rank + 1); i++)
		if (A[i] < localmin) {
			localmin = A[i];
			localmini = i;
		}
	MPI_Barrier;
	MPI_Reduce(&localmin, &globmin, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	if (rank != 0) {
	}
	else {
		int localmin2 = 0;
		cout << globmin;
		auto end_time = std::chrono::steady_clock::now();
		auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
		cout << endl;
		std::cout << elapsed_ns.count() << " ns\n";
	}
	MPI_Finalize();
}