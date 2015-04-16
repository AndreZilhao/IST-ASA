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
	void traceGrafo(); 				 // Função de Print do grafo para testes.

};
  
  Grafo::Grafo(int V)
{
	this->V = V;
	adj = new list<Arco>[V];
}
 
 							 // Adicionar novo ramo entre 2 colaboradores, para um grafo direcional.
void Grafo::novoArco(int v, int u, int peso)
{
	Arco a(u-1, peso);
	int tst = a.getPeso();
	adj[v-1].push_back(a);
}
 
void Grafo::analiseCustos(int s)
{//TODO
}

void Grafo::traceGrafo()
{
	for(int i = 0; i < V; i++)
		 {
		 	if (true)			 // IMPORTANTE: Adicionar possivel verificação para casos nulos ou remover 'if'.
		 	{	
				cout << "___VERTICE: " << i+1 << "\n";
		 		list<Arco> queue = adj[i];
				while(!queue.empty())
				{
					cout << "Filho: " << queue.front().getVertice()+1 << "\n";
					cout << "Peso Filho: " << queue.front().getPeso() << "\n";
					queue.pop_front();
				}
				
		 	}
		 	else
		 		{}
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
			localidades.novoArco(w, v, peso);
			--nCustos;
		}
	}
	localidades.traceGrafo();			 //Analise de custos (Bellman-Ford modificado) apartir da sede de empresa.
	return 0;
}
