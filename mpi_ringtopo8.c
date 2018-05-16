#include "mpi.h"
	#include <stdio.h>
	#include <stdlib.h>
	

	int main (int argc, char *argv[])
	{
	int numtasks, rank, next, prev, buf[4], tag1=1, tag2=2, tag3=3, tag4=4;
	MPI_Request reqs[8];
	MPI_Status stats[8];
	

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	

	prev = rank-1;
	next = rank+1;
	if (rank == 0)  prev = numtasks - 1;
	if (rank == (numtasks - 1))  next = 0;
	

	MPI_Irecv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD, &reqs[0]);
	MPI_Irecv(&buf[1], 1, MPI_INT, prev, tag2, MPI_COMM_WORLD, &reqs[1]);
	MPI_Irecv(&buf[2], 1, MPI_INT, next, tag3, MPI_COMM_WORLD, &reqs[2]);
        MPI_Irecv(&buf[3], 1, MPI_INT, next, tag4, MPI_COMM_WORLD, &reqs[3]);

	MPI_Isend(&rank, 1, MPI_INT, prev, tag4, MPI_COMM_WORLD, &reqs[4]);
	MPI_Isend(&rank, 1, MPI_INT, prev, tag3, MPI_COMM_WORLD, &reqs[5]);
        MPI_Isend(&rank, 1, MPI_INT, next, tag2, MPI_COMM_WORLD, &reqs[6]);
        MPI_Isend(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD, &reqs[7]);
	

	MPI_Waitall(8, reqs, stats);
	printf("Task %d communicated with tasks %d & %d & %d & %d\n",rank,prev,next);
	

	MPI_Finalize();
	}
