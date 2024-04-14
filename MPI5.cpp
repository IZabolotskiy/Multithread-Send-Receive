#include <cstdio>
#include <iostream>
#include "mpi.h"
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
int main(int argc, char** argv)
{
	int numtasks, rank, a = 0;
	bool gotit;
	ifstream file("input.txt");
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	string line;
	char cline[1024];
	char cgetline[1024], timegetline[1024];
	int getmessagelength = 0;
	if (rank == 0) {
		while (getline(file, line)) {
			int slength = line.length();
			int digits = ceil(std::log10(slength + 1));
			string strslength = to_string(slength);
			cline[0] = digits;
			for (int i = 0; i < digits; i++)
				cline[1 + i] = strslength[i];
			for (int i = 0; i < slength; i++)
				cline[i + 1 + digits] = line[i];
			MPI_Send(&cline, slength + 1 + digits, MPI_CHAR, rank + 1, 1, MPI_COMM_WORLD);
			a++;
		}
	}
	else {
		while (1) {
			MPI_Recv(&timegetline, 1024, MPI_CHAR, rank - 1, 1, MPI_COMM_WORLD, &status);
			cgetline[rank + 12] = rank;
			if (rank == numtasks - 1)
			{
				int digits = timegetline[0];
				int clength2 = 0;
				for (int i = 0; i < digits; i++) {
					clength2 = clength2 + (timegetline[i + 1] - 48) * pow(10, digits - i - 1);
				}
				for (int i = 1 + digits; i < clength2 + 1 + digits; i++)
					cout << timegetline[i];
				cout << endl;
			}
			else {
				MPI_Send(&timegetline, 1024, MPI_CHAR, rank + 1, 1, MPI_COMM_WORLD);
			}
		}
	}
	MPI_Finalize();
}


