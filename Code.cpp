#include <iostream>
#include <stdio.h>
#include <string.h>
#include "mpi.h" // message passing interface
using namespace std;

// New compile and run commands for MPI!
// mpicxx -o blah file.cpp
// mpirun -q -np 32 blah

class Node {
	Node * parent;
	int value[6];
	Node * child[6];
	public:
	Node(int val); // constructor
	bool numChildren();
	void absorb(Node * newChild);
	void discard(Node * removeChild);
}

class Tree {
	Node * root;
	void print(Node * start);
	public:
	Tree(); // constructor
	Node * search(int valToFind);
	bool insert(int valToAdd);
	bool delete(int valToKill);
	void print();
}

int main (int argc, char * argv[]) {

	int my_rank;			// my CPU number for this process
	int p;					// number of CPUs that we have
	int source;				// rank of the sender
	int dest;				// rank of destination
	int tag = 0;			// message number
	char message[100];		// message itself
	MPI_Status status;		// return status for receive
	
	// Start MPI
	MPI_Init(&argc, &argv);
	
	// Find out my rank!
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	// Find out the number of processes!
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	// THE REAL PROGRAM IS HERE
    cout << my_rank << endl;

	// Shut down MPI
	MPI_Finalize();

	return 0;
}
