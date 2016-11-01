#include<iostream>
#include<vector>


using namespace std;

/*
tamanho de um grafo representa a sua quantidade de arestas

Ordem de um grafo é o número de vértices.
*/

class Vertice{

	public :
		vector<int> lst_adj;
		
		Vertice(){
		}
		Vertice(int ordem){
			lst_adj.assign(ordem,0);
		}
};

class Grafo{
	public:
		vector<Vertice> vertices;
		int qtdVertices;
		Grafo(){
		
		}
		Grafo( int n ){
		
				qtdVertices = n;
				vertices.assign( n, Vertice(n));
		}
		
		void print(){
			cout<< "Grafo:\nquantidade de vertices: "<<vertices.size()
			<<endl<<"Limite da lista de adj do vertice 0: "
			<< vertices[0].lst_adj.size()<<endl;
		}
};

class StarTrek_PP1_Desfecho {
	private:
		static StarTrek_PP1_Desfecho *desenlace;
		StarTrek_PP1_Desfecho(){
		}
		void posExecute(){
			grafo->print(); 
		}
	public:

		int ordem;
		Grafo *grafo;
		
		/**
			Exemplo usando um paradigma fodastico.
			Ele garante que tenha apenas uma única instancia da classe;
			Veja que no main, na solucao2 chama uma novaInstancia,
			Mas ele acaba por ter apenas uma.//vide ln 87.	
		*/
		static StarTrek_PP1_Desfecho * novaInstancia(){
			if( StarTrek_PP1_Desfecho::desenlace == NULL){	
				StarTrek_PP1_Desfecho::desenlace  = new StarTrek_PP1_Desfecho;	
				return StarTrek_PP1_Desfecho::desenlace;
			}
			else return StarTrek_PP1_Desfecho::desenlace;
		}
		void execute(){
			cout << "qual a ordem do grafo? ";
			cin>> ordem;
			grafo = new Grafo(ordem);
			posExecute();
		}
		
};

StarTrek_PP1_Desfecho* StarTrek_PP1_Desfecho::desenlace = NULL;

int main(){	

	StarTrek_PP1_Desfecho *solucao = StarTrek_PP1_Desfecho::novaInstancia();
	StarTrek_PP1_Desfecho *solucao2 = StarTrek_PP1_Desfecho::novaInstancia();
	solucao->execute();
	cout<<"hue >> : "<<solucao2->ordem<<endl;
	return 0;
}
/***/
