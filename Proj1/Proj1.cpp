 /* Andre Zilhao @ ist.utl.pt
 Projecto de Algoritmos e Sintese de Dados - Parte 1
 March 23 2015
 Description: Program that given an input, finds the distance between point 'Erdos' and all the nodes in a graph
 and returns the longest distance, followed by a list of ocurrences for every distance shorter than the longest.
 */
#include <iostream>
#include <list>
using namespace std;

// Classe Grafo com constructor, adição de Ramos (informação guardada no grafo), e algoritmo de pesquisa.
class Grafo
{
	int V; // Numero de Vertices.
	std::list<int> *adj;    // Lista de Adjacentes.
public:
 	Grafo(int V);  
	void novoRamo(int v, int w); // funcao para adicionar ramos.
	void findErdos(int s);  // algoritmo de pesquisa.
};
  
  Grafo::Grafo(int V)
{
	this->V = V;
	adj = new list<int>[V];
}
 
 // Adicionar novo ramo entre 2 colaboradores, visto que o grafo nao é direccional.
void Grafo::novoRamo(int v, int w)
{
	adj[v-1].push_back(w-1);
	adj[w-1].push_back(v-1);
}
 
void Grafo::findErdos(int s)
{
	int v = s-1;
	bool *visited = new bool[V];
	int *weight = new int[V];
	int maxWeight = 0;
	int arrayPesos[V];
	for(int i = 0; i < V; i++)
		 {
		 	arrayPesos[i] = 0;
		 }
	//Coloca pesos de viagem a 0, e marca todos os colaboradores como nao visitados.
	for(int i = 0; i < V; i++)
		visited[i] = false;
	for(int i = 0; i < V; i++)
		weight[i] = 0;
	// Criar a queue
	list<int> queue;
	// Caso 1
	visited[v] = true;
	queue.push_back(v);
	// Criacao de Iteradores para queue e weightSum.
	list<int>::iterator i;
	list<int>::iterator y;
	while(!queue.empty())
	{
		// Colaborador seguinte
		v = queue.front();
		queue.pop_front();
		//Percore todas as adjacencias de um Colaborador. Se um colaborador nao foi visitado, assinalar como tal e
		//assinalar-lhe um peso. Se o peso assinalado for o mais alto, criar um novo elemento na lista de pesos.
		//Por fim, incrementar a posicao da array de pesos com a ocorrencia.
		for(i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			if(!visited[*i])
			{
				visited[*i] = true;
				weight[*i] = weight[v]+1;
				queue.push_back(*i);
				if (arrayPesos[weight[v]+1] == 0)
				{
					maxWeight++;
				}
				arrayPesos[weight[v]+1]++;
			}
		}
	}
	// Print de "M"
	cout << maxWeight << "\n";
	for(int i = 0; i < V; i++)
		 {
		 	if (arrayPesos[i] != 0) 
		 		{
		 			//Print de M linhas [1..M]
		 			cout << arrayPesos[i] << "\n";

		 		}
		 	else
		 		{}
		 }

}
int main()
{
	int w = 0, v = 0, nCollab= 0,Erdos = 0,nRamos = 0;
	cin >> nCollab;
 	Grafo colaboradores(nCollab);
	cin >> nRamos;
	cin >> Erdos;
	if(nRamos >= 0)
	{
		while(nRamos>0)
		{
			cin >> w >> v;
			colaboradores.novoRamo(w, v);
			--nRamos;
		}
	}
	colaboradores.findErdos(Erdos);
	return 0;
}