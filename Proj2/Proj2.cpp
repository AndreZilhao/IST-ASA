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
	int vertice;					 // Vértice
public:
	Arco (int _vertice, int _peso)
{	
	peso = _peso;
	vertice = _vertice;
};
	int getVertice ();
	int getPeso ();
};

int Arco::getVertice()
{
	return vertice;
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
	void traceGrafo(int array[], int source, char negCheck[]);			         // Função de Print do grafo para testes.
	void relaxGrafo(int array[]);
	void negativeCycleCheck(int array[], int source);

};
  
  Grafo::Grafo(int V)
{
	this->V = V;
	adj = new list<Arco>[V];
}
 
 							 // Adicionar novo ramo entre 2 colaboradores, para um grafo direcional.
void Grafo::novoArco(int v, int u, int peso)
{
	Arco a(u, peso);
	adj[v].push_back(a);
}
 
void Grafo::analiseCustos(int source)
{
	//Passos de Inicialização Belman-Ford
	int arrayPesos[V];
	//int flagOptimizacao = false; 
	for(int i = 0; i < V; i++)
	{
		arrayPesos[i] = INFINITOSUP;
	}
	arrayPesos[source] = 0;
	//
	for(int i = 0; i < V; i++)
	{
		this->relaxGrafo(arrayPesos);
	}
	this->negativeCycleCheck(arrayPesos, source);
	//this->traceGrafo(arrayPesos,source);
	
}

void Grafo::relaxGrafo(int array[])
{
	list<Arco>::iterator it;
	for(int i = 0; i < V; i++)
	{
		if (array[i] != INFINITOSUP)
		{
			{	
				for (it = adj[i].begin(); it != adj[i].end(); it++)
				{
					if (array[it->getVertice()] > array[i] + it->getPeso())
					{
						array[it->getVertice()] = array[i] + it->getPeso();
					}
				}
			}
		}
	}
}

void Grafo::negativeCycleCheck(int array[], int source)
{//TODO
	char negCheck[V];
	int backupArray[V];
      	for (int i = 0; i < V; i++)
		backupArray[i] = array[i];
	list<Arco>::iterator it;
	for (int j = 0; j < V; j++)
	{
		for (int i = 0; i < V; i++)
		{
			if (array[i]== INFINITOSUP) 
			{
				negCheck[i] = 'U';
			} else 
			{
				negCheck[i] = 'V';
			}
		
			for (it = adj[i].begin(); it != adj[i].end(); it++)
			{
				if (array[it->getVertice()] > array[i] + it->getPeso())
				{
					array[it->getVertice()] = array[i] + it->getPeso();
				}
			}
		}
		for (int i = 0; i < V; i++)
		{
			if (backupArray[i] != array[i])
			{
				negCheck[i] = 'I';
			}
		}
	}
	this->traceGrafo(backupArray, source, negCheck);
}

void Grafo::traceGrafo(int array[], int source, char negCheck[])
{
	for(int i = 0; i < V; i++)
		 {
		 	if (negCheck[i] == 'V')			 // IMPORTANTE: Adicionar possivel verificação para casos nulos ou remover 'if'.
		 	{	
				cout << array[i] << "\n";
			} else 
			{
				cout << negCheck[i] << "\n";
			}


				
			/*	cout << "___VERTICE: " << i+1 << "\n";
		 		list<Arco> queue = adj[i];
				while(!queue.empty())
				{
					cout << "Filho: " << queue.front().getVertice()+1 << "\n";
					cout << "Peso Filho: " << queue.front().getPeso() << "\n";
					queue.pop_front();
				}
				cout << "Distancia da source: " << array[i] << "\n";
				
		 	}
		 	else
		 		{}
				*/
		 }

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
