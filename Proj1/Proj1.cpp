#include <iostream>
#include <list>
using namespace std;
 
// Classe Grafo com constructor, adição de Ramos (informação guardada no grafo), e algoritmo de pesquisa.
class Grafo
{
	int V; // Numero de Vertices.
	list<int> *adj;    // Lista de Adjacentes.
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
	//int temp = 0;
	int w2[V];
	for(int i = 0; i < V; i++)
		 {
		 	w2[i] = 0;
		 }
	//Coloca pesos de viagem a 0, e marca todos os colaboradores como nao visitados.
	for(int i = 0; i < V; i++)
		visited[i] = false;
	for(int i = 0; i < V; i++)
		weight[i] = 0;
	// Criar a queue e a lista de pesos de viagem.
	list<int> queue;
	//list<int> weightSum;
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
		//Por fim, incrementar a ultima posicao da lista de pesos com a ocorrencia.
		for(i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			if(!visited[*i])
			{
				/*if (weight[s]+1>maxWeight)
					 {
						maxWeight = weight[s]+1;
						weightSum.push_back(0);

					 }*/
				visited[*i] = true;
				weight[*i] = weight[v]+1;
				queue.push_back(*i);
				if (w2[weight[v]+1] == 0)
				{
					maxWeight++;
				}
				w2[weight[v]+1]++;
				
				/*temp = weightSum.back();
				weightSum.pop_back();
				weightSum.push_back(temp+1);*/
				


			}
		}
	}
	// Print de "M"
	//cout << maxWeight << "\n";
	/*
	while(!weightSum.empty())
	{
		//Print de M linhas [1..M]
		cout << weightSum.front() << "\n";
		weightSum.pop_front();
	} */
	cout << maxWeight << "\n";
	for(int i = 0; i < V; i++)
		 {
		 	if (w2[i] != 0) 
		 		{
		 			cout << w2[i] << "\n";

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