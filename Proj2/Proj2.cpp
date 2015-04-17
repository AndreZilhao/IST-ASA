/* Andre Zilhao @ ist.utl.pt
Projecto de Algoritmos e Sintese de Dados - Parte 2
April 2015
Description: Program that given an input, finds the least cost path for all nodes in the graph built by input.
Must support negative weights on brances, and detects negative cycles (become flagged as "I" in output). Unreachable nodes
get flagged with "U" in output.
Input is as follows:
N C
S
[C]lines with the format: u v p
__
Where:
N - Number of Vertices
C - Number of Brances
S - Starting Location
u - Start of the Branch (vertice)
v - Destination of the Branch (vertice)
p - Cost of Branch.
*/
#include <iostream>
#include <list>
#include <limits.h>
#define INFINITOSUP INT_MAX
using namespace std;



// Classe Grafo com constructor, adição de Ramos (informação guardada no grafo), e algoritmo de pesquisa.

class Arco
{
	int peso;					 // Peso do Aro
	int verticeO;				 // Vértice Origem
	int verticeD;				 // Vértice Destino
public:
	Arco (int _verticeO, int _verticeD, int _peso)
{	
	peso = _peso;
	verticeO = _verticeO;
	verticeD = _verticeD;
	cout << "VerticeO: " << verticeO << " VerticeD: " << verticeD  << "\n";
};
	int getVerticeO();
	int getVerticeD();
	int getPeso();
};

int Arco::getVerticeO()
{
	return verticeO;
}

int Arco::getVerticeD()
{
	return verticeO;
}

int Arco::getPeso()
{
	return peso;
}

class Grafo
{
	int V;						 // Numero de Vertices.
	std::list<Arco> *adj;   			 // Lista de Adjacentes.
public:
 	Grafo(int V);  
	void novoArco(int v, int w, int peso);		 // Funcao para adicionar ramos ao grafo. (Vertice origem, Vertice Destino, Peso)
	void analiseCustos(int s); 			 // Algoritmo de analise do problema. (Belman-Ford Modificado)
//	void traceGrafo(int arrayPesos[], int source, char negCheck[]);			         // Função de Print do grafo para testes.
//	void relaxGrafo(int arrayPesos[]);
//	void negativeCycleCheck(int arrayPesos[], int source);

};
  
  Grafo::Grafo(int V)
{
	this->V = V;
	adj = new list<Arco>[V];
}
 
 							 // Adicionar novo ramo entre 2 colaboradores, para um grafo direcional.
void Grafo::novoArco(int v, int u, int peso)
{
	Arco a(v, u, peso);
	adj[v].push_back(a);
}
 
void Grafo::analiseCustos(int _source)
{
	//Passos de Inicialização Belman-Ford
	int arrayPesos[V];
	//int backuparrayPesos[V];
	char negCheck[V];
	bool *visited = new bool[V];
	int v = _source;
	list<int> validVertices;
	list<int> queue;
	list<Arco>::iterator it;
	validVertices.push_back(v);
	for(int i = 0; i < V; i++)
		visited[i] = false;
	//int flagOptimizacao = false; 
	for(int i = 0; i < V; i++)
	{
		arrayPesos[i] = INFINITOSUP;
		negCheck[i] = 'U';
	}
	visited[v] = true;
	queue.push_back(v);
	while(!queue.empty())
	{
		for (int j = 0; j < V; j++)
			{
				cout << visited[j] << "\n";
				cout << "----\n";
			}
		v = queue.front();
		queue.pop_front();
		for(it = adj[v].begin(); it != adj[v].end(); it++)
		{
			cout << "vertice:" << v << "\n";
			cout << "Aro a ser Verificado: " << "\n";
			cout << it->getVerticeO();
			cout << it->getVerticeD();
			cout << " " << visited[it->getVerticeD()] << "\n"; 
			cout << visited[it->getVerticeD()] << "<--- devia ser 0\n";
			if(!visited[it->getVerticeD()])
			{
				visited[it->getVerticeD()] = true;
				cout << "vertice adicinado: " << it->getVerticeD() << "\n";
				queue.push_back(it->getVerticeD());
				validVertices.push_back(it->getVerticeD());
			}
		}
	}

	list<int>::iterator itr;
	for (itr = validVertices.begin(); itr != validVertices.end(); itr++)
	{
		cout << "List of Valid Vertices:" << "\n";
		cout << *itr << "\n";
	}

	//arrayPesos[source] = 0;
	//RELAX
	/*
	list<Arco>::iterator it;

	for(int i = 0; i < V; i++)
	{
		for(int i = 0; i < V; i++)
		{
			if (arrayPesos[i] < INFINITOSUP) // caso possivel
			{
				for (it = adj[i].begin(); it != adj[i].end(); it++)
				{
					if (arrayPesos[it->getVertice()] > arrayPesos[i] + it->getPeso())
					//
					{
						negCheck[it->getVertice()] = 'V';
						arrayPesos[it->getVertice()] = arrayPesos[i] + it->getPeso();
					}
				}
			}
		}
	}
	//NEGCHECK
	for (int i = 0; i < V; i++)
	{
		backuparrayPesos[i] = arrayPesos [i];
	}
	//for (int j = 0; j < V; j++)
	for (int i = 0; i < V; i++)
		{
			for (it = adj[i].begin(); it != adj[i].end(); it++)
			{
				if (arrayPesos[it->getVertice()] > arrayPesos[i] + it->getPeso())
				{
					arrayPesos[it->getVertice()] = arrayPesos[i] + it->getPeso();
				}
			}
		}
		for (int i = 0; i < V; i++)
		{
			if (backuparrayPesos[i] != arrayPesos[i])
			{
				if (negCheck[i] != 'U') negCheck[i] = 'I';

			}
		}
	
	//TRACE
	for(int i = 0; i < V; i++)
		 {
		 	if (negCheck[i] == 'V')			 // IMPORTANTE: Adicionar possivel verificação para casos nulos ou remover 'if'.
		 	{	
				cout << arrayPesos[i] << "\n";
			} else 
			{
				cout << negCheck[i] << "\n";
			}


				
				cout << "___VERTICE: " << i+1 << "\n";
		 		list<Arco> queue = adj[i];
				while(!queue.empty())
				{
					cout << "Filho: " << queue.front().getVertice()+1 << "\n";
					cout << "Peso Filho: " << queue.front().getPeso() << "\n";
					queue.pop_front();
				}
				cout << "Distancia da source: " << arrayPesos[i] << "\n";
				
		 	}
		 	else
		 		{}
			
		 }
		 */

}
int main()
{
	int w = 0, v = 0, peso = 0, nLocalidades = 0, sedeEmpresa = 0,nCustos = 0;
	cin >> nLocalidades;
 	Grafo localidades(nLocalidades);
	cin >> nCustos;
	cin >> sedeEmpresa;
	if(nCustos >= 0)
	{
		while(nCustos>0)
		{
			cin >> w >> v >> peso;
			localidades.novoArco(w-1, v-1, peso);
			--nCustos;
		}
	}
	localidades.analiseCustos(sedeEmpresa-1);
				 //Analise de custos (Bellman-Ford modificado) apartir da sede de empresa.
return 0;
}
