/*Function that creates color outputs to be used in used in graph creation and visualization with graphviz. 
Recieves a list of NVERTICES vertices as input.*/ 
#include <stdlib.h>
#include <iostream>
#define NVERTICES 2100
using namespace std;

int main()
{
	string a;
	for (int i = 1; i <= NVERTICES; i++)
	{
		cin >> a;
		if ( a == "I")
		{
			cout << i << " [style=filled, fillcolor=red];" << "\n";
		} else 
		{
			cout << i << " [style=filled, fillcolor=blue];" << "\n";
		}
	}
	return 0;
}
