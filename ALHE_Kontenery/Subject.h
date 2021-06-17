#include <iostream>
#include <vector>
#include <cstdlib>

#include "Container.h"

using namespace std;

class Subject
{
	private:
		int n;
		int value;

		vector <Container> packList;
		vector <Container> freeSpaceList;
		vector <Container> packedList;
		Container container;

	public:
		vector <int> chromosome;

		Subject();
		Subject(vector <int> chromosome, vector <Container> packListIn, Container container);
		vector <int> createChromosome(int n); 
		vector <int> mutate(); 
		int numberOfMutations(); 
		vector <Container> packListInOrder(vector <int> chromosome, vector <Container> packListIn);
		int calcValue();
		bool putContainer(Container container);
		int getValue();
		void print();
};

