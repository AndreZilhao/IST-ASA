#include <iostream>
#include <list>
using namespace std;
 
// This class represents a directed graph using adjacency list representation
class Graph
{
	int V;    // No. of vertices
	list<int> *adj;    // Pointer to an array containing adjacency lists
public:
	Graph(int V);  // Constructor
	void addEdge(int v, int w); // function to add an edge to graph
	void BFS(int s);  // prints BFS traversal from a given source s
};
 
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V+1];
}
 
void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
}
 
void Graph::BFS(int s)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	int *weight = new int[V];
	int maxWeight = 0;
	int temp = 0;
	for(int i = 1; i <= V; i++)
		visited[i] = false;
	// Mark all the weights as zero.
	for(int i = 1; i <= V; i++)
		weight[i] = 0;
	// Create a queue for BFS
	list<int> queue;
	list<int> weightSum;
 
	// Mark the current node as visited and enqueue it
	visited[s] = true;
	queue.push_back(s);
 
	// 'i' will be used to get all adjacent vertices of a vertex
	list<int>::iterator i;
	list<int>::iterator y;
 
	while(!queue.empty())
	{
		// Dequeue a vertex from queue and print it
		s = queue.front();
		/*cout << s << " ";
		cout << weight[s] << " |";*/
		queue.pop_front();
 
		// Get all adjacent vertices of the dequeued vertex s
		// If a adjacent has not been visited, then mark it visited
		// and enqueue it
		for(i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if(!visited[*i])
			{
				if (weight[s]+1>maxWeight)
					 {
						maxWeight = weight[s]+1;
						weightSum.push_back(0);

					 }
				visited[*i] = true;
				weight[*i] = weight[s]+1;
				queue.push_back(*i);

				temp = weightSum.back();
				weightSum.pop_back();
				weightSum.push_back(temp+1);
				


			}
		}
	}
	cout << maxWeight << " <-MaxWeight|";
	while(!weightSum.empty())
	{
		cout << weightSum.front() << "<WeightSum ";
		weightSum.pop_front();
	}

}
int main()
{
	// Create a graph given in the above diagram
	Graph g(8);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 2);
	g.addEdge(2, 5);
	g.addEdge(5, 6);
	g.addEdge(6, 7);
	g.addEdge(7, 5);
	g.addEdge(4, 8);

	cout << "Following is Breadth First Traversal (starting from vertex 2) \n";
	g.BFS(1);
 
	return 0;
}