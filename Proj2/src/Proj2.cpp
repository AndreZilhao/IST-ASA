/* Andre Zilhao @ ist.utl.pt
ASA Project - Part 2
April 2015
Description: Ansi C++ Program that given an input, finds the least cost path for all nodes in the graph built by input,
from a source. Supports negative weights on brances, and detects negative cycles (they become flagged as "I" in output).
Unreachable nodes get flagged with "U" in output.
Input is as follows:
N C
S
[C]lines with the format: u v p
Where:
N - Number of Vertices
C - Number of Brances
S - Starting Location
u - Start of the Branch (vertex)
v - Destination of the Branch (vertex)
p - Cost of Branch.
*/
#include <iostream>
#include <list>
#include <limits.h>
using namespace std;


class Arc 
{
    int weight;     
    int vertexO;     
    int vertexD;
public: Arc (int _vertexO, int _vertexD, int _peso) 
	{
		weight = _peso; 
		vertexO = _vertexO;     
		vertexD = _vertexD; 
	};

	int getVertexO(); 
	int getVertexD();
	int getPeso(); 
};

int Arc::getVertexO()
{
	return vertexO;
}

int Arc::getVertexD()
{
	return vertexD;
}

int Arc::getPeso()
{
	return weight;
}

class Graph
{
	int V;						 
	std::list<Arc> *adj;
public:
 	Graph(int V);
	void newArc(int v, int u, int weight);		 
	void costAnalisis(int s);	 
	void traceAnalisis(int arrayWeights[], char arrayStatus[]);			         
	bool relaxGraph(int arrayWeights[], char arrayStatus[], list<int> validVertices);
	void negativeCycleCheck(int arrayWeights[], char arrayStatus[], list<int> validVertices);
	list<int> optimizeGraph(int source, bool visited[]); 		
};  
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<Arc>[V];
}
							 
void Graph::newArc(int v, int u, int weight)
{
	Arc a(v, u, weight);
	adj[v].push_back(a);
}

/* Graph->costAnalisis: This function uses the Bellman-Ford algorithm as a base. Fristly the auxiliary variables are
initialized, then the graph runs an optimization function to only run relaxation steps on reachable vertices.
Finally, a series of relaxation steps are applied, and a final relaxation step is used to check for negative
cycles. Lastly, the trace function is called for output.*/
void Graph::costAnalisis(int _source)
{
	//INITIALIZATION STEP
	int arrayWeights[V];
	int v = _source;
	char arrayStatus[V];
	bool *visited = new bool[V];
	bool relaxedGraph = false;
	list<int> validVertices; 
	for(int i = 0; i < V; i++)
	{
		arrayWeights[i] = INT_MAX;
		arrayStatus[i] = 'U';
		visited[i] = false;
	}
	arrayWeights[v] = 0;
	arrayStatus[v] = 'V';
	visited[v] = true;
	validVertices = this->optimizeGraph(v, visited);
	relaxedGraph = this->relaxGraph(arrayWeights, arrayStatus, validVertices);
	if (!relaxedGraph)
	{
		this->negativeCycleCheck(arrayWeights, arrayStatus, validVertices);
	}
	this->traceAnalisis(arrayWeights, arrayStatus);
	
}

/* Graph->optimizeGraph: This function returns a list of vertices reachable from "source". Further operations are then
applied on a smaller subset of vertices for increased performance.*/
list<int> Graph::optimizeGraph(int source, bool visited[])
{
	int v = source;
	list<int> queue;
	list<Arc>::iterator it;
	list<int> validVertices;
	queue.push_back(v);
	validVertices.push_back(v);
	while(!queue.empty())
	{
		v = queue.front();
		queue.pop_front();
		for(it = adj[v].begin(); it != adj[v].end(); it++)
		{
			if(!visited[it->getVertexD()])
			{
				visited[it->getVertexD()] = true;
				queue.push_back(it->getVertexD());
				validVertices.push_back(it->getVertexD());
			}
		}
	}
	return validVertices;
}

/* Graph->relaxGraph: This function runs a series of relaxation steps on the list of valid vertices. This is the
heaviest runtime function of the program, with a worst case complexity of O(VE). However, the use of an optimization
flag greatly reduces the actual number of checks needed to run in most non-negative cycle graphs. The function returns
true if the graph has been fully relaxed, false otherwise.*/
bool Graph::relaxGraph(int arrayWeights[], char arrayStatus[], list<int> validVertices)
{
	int flagOptimization = true;
	list<int>::iterator itr2; 
	list<int>::iterator itr; 
	list<Arc>::iterator it;
	for(itr = validVertices.begin(); itr != validVertices.end(); itr++) 
	{
		flagOptimization = true;
		for(itr2 = validVertices.begin(); itr2 != validVertices.end(); itr2++) 
		{
			for (it = adj[*itr2].begin(); it != adj[*itr2].end(); it++)
			{
				if (arrayWeights[it->getVertexD()] > arrayWeights[*itr2] + it->getPeso())
				{
					arrayStatus[it->getVertexD()] = 'V';
					arrayWeights[it->getVertexD()] = arrayWeights[*itr2] + it->getPeso();
					flagOptimization = false;
				}
			}
		}
		if (flagOptimization == true) return true;
	}
	return false;
}
/* Graph->negativeCycleCheck: This function runs a final relaxation step on the list of valid vertices. If any
vertices are updated, then a negative cycle has been found, and all changed vertices are flagged as 'I' for output.*/
void Graph::negativeCycleCheck(int arrayWeights[], char arrayStatus[], list<int> validVertices)
{
	list<int>::iterator itr;
	list<Arc>::iterator it;
	int backuparrayWeights[V];
	for(itr = validVertices.begin(); itr != validVertices.end(); itr++)  
	{
		backuparrayWeights[*itr] = arrayWeights [*itr];
	}
	for(itr = validVertices.begin(); itr != validVertices.end(); itr++)  
	{
		for (it = adj[*itr].begin(); it != adj[*itr].end(); it++)
		{
			if (arrayWeights[it->getVertexD()] > arrayWeights[*itr] + it->getPeso())
			{
				arrayWeights[it->getVertexD()] = arrayWeights[*itr] + it->getPeso();
			}
		}
	}
	for(itr = validVertices.begin(); itr != validVertices.end(); itr++)  
	{
		if (backuparrayWeights[*itr] != arrayWeights[*itr])
		{
				arrayStatus[*itr] = 'I';
		}
	}
}
/* Graph->traceAnalisis: This function prints a list of V vertices with the analized output. I for negative cycle
vertices, U for unreachable vertices, and a cost number for non-negative-cycle vertices.*/
void Graph::traceAnalisis(int arrayWeights[], char arrayStatus[])
{
	for(int i = 0; i < V; i++)
		 {
		 	if (arrayStatus[i] == 'V')
		 	{	
				cout << arrayWeights[i] << "\n";
			} else 
			{
				cout << arrayStatus[i] << "\n";
			}
		 }
}
/* Main: This function recieves the input as stated in the initial comment section, creates a graph and populates
it, and calls the function costAnalisis.*/
int main()
{
	int w = 0, v = 0, weight = 0, nLocations = 0, source = 0, nBranches = 0;
	cin >> nLocations;
 	Graph locations(nLocations);
	cin >> nBranches;
	cin >> source;
	while(nBranches>0)
	{
		cin >> w >> v >> weight;
		locations.newArc(w-1, v-1, weight);
		--nBranches;
	}
	locations.costAnalisis(source-1);
	return 0;
}

