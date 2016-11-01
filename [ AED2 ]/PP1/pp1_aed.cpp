#include<bits/stdc++.h>//tirar depois
#include<iostream>
#include<vector>
#include<climits>

#define infinito INT_MAX
using namespace std;

/*
tamanho de um grafo representa a sua quantidade de arestas
Ordem de um grafo sao o numero de vertices.
*/


class Aresta{
	public:
		int			vertice;
		double		peso;
		Aresta(){}


		Aresta(int pDest, double pPeso){
			vertice = pDest;
			peso = pPeso;
		}
		
		
		bool operator<(Aresta b){
			return this->vertice < b.vertice;
		}
};

bool comp( Aresta a, Aresta b){
	return a < b;
}


class Vertice{
	private:
	
		

	public :


		vector<Aresta>	arestasAdjacentes;


		Vertice(){
		}


		void addVisinho(int visinho, double peso){
			Aresta		aresta( visinho, peso );
			arestasAdjacentes.push_back( aresta );
			stable_sort( arestasAdjacentes.begin(),arestasAdjacentes.end(), comp );
		}


		void print(){
			for(int i=0;i< arestasAdjacentes.size();i++){
				cout << arestasAdjacentes[i].vertice << " ";
			}
		}


		void limparMemoria(){
			arestasAdjacentes.clear();
		}
};


template < class T >
class Posicao{

private:

	T dado;
	Posicao *prox;

public:


	Posicao(){
		prox = NULL;
	}


	T getValor(){
	
    	return this->dado;
	}


	Posicao *getProx(){
	
    	return this->prox;
	}


	void setValor(T valor){
	
		dado = valor;
	}


	void setProx(Posicao<T>* prox){
	
    	this->prox=prox;
	}
};


template <class T>
class Fila{

private:

	Posicao<T>*		frente;
	Posicao<T>*		tras;

public:

	Fila(){
	
    	frente = new Posicao<T>;
    	tras = frente;
	}


	bool filaVazia(){
	
    	return (frente == tras);
	}


	void enfileira(T valor ){
	
    	tras->setValor( valor );
    	tras->setProx( new Posicao<T> );
    	tras = tras->getProx();
	}


	void desenfileira( T &x){
	
    	if( not filaVazia() ){
    		
    		Posicao<T> *aux = frente;
    		x = frente->getValor();
        	frente = frente->getProx();
        	delete aux;
    	}
	}
};



class Grafo{
	private:

        double custoTotalDFS;
        bool fezBuscaDFS;


        Grafo() {

                fezBuscaDFS = false;
                custoTotalDFS = -1;
        }


        void dfs( int origem, vector<bool>& visitado ){

            if( not visitado[origem] ){
                cout << " "<<origem<<" ";
                visitado[origem] = true;
                Vertice planeta = vertices[origem];
                for( int i=0; i< planeta.arestasAdjacentes.size();i++){
                    Aresta caminho = planeta.arestasAdjacentes[i];
                    //cout<< "testando visinho de vertice: "<< caminho.vertice<< " de peso "<< caminho.peso <<endl;
                    if( not visitado[ caminho.vertice ] ){
                        //cout << "		ok! visinho nao visitado!\n		vamos visitar!\n";
                        //cout << "custo acumulado deste sistema ate aqui::"<< custoTotalDFS <<endl;
                        custoTotalDFS += caminho.peso;
                        //cout<<"custo passa a ser : "<< custoTotalDFS<<endl;
                        dfs( caminho.vertice, visitado );
                    }
                }
            }
        }


        void dfs(){

            if ( not fezBuscaDFS ){

                vector<bool> 	visitados;
                visitados.assign( qtdVertices + 1 , false );
                fezBuscaDFS = true;
                custoTotalDFS=0;
                //cout <<"\npassei por aqui"<<endl;
               	cout << "rodou um dfs nos vertices: ";
                dfs(1, visitados);
                cout<< endl;
            }
        }

	public:

		int					qtdVertices;
		int					qtdArestas;
		vector< Vertice >	vertices;


		Grafo( int n , int m ){
				Grafo();
				qtdVertices = n;
				qtdArestas = m;
				vertices.assign( qtdVertices + 1, Vertice());
		}


		void insereAresta( int origem, int destino, double peso ){
			if( origem < vertices.size() and destino < vertices.size() ){

				vertices[origem].addVisinho(destino, peso );
				vertices[destino].addVisinho(origem, peso );
				fezBuscaDFS = false;

			}
			else{
				cout <<	"Erro!!!\n	Parametros invalidos\n";
			}
		}

		double getCustoDFS(){

			dfs();
			return custoTotalDFS;

		}


		void print(){
			for(int i=1;i<vertices.size();i++){
				cout << i <<": ";
				vertices [i].print();
				cout<< "\n------\n";
			}
		}


		void limparMemoria(){
			for(int i=0 ;i< vertices.size();i++){
				vertices[i].limparMemoria();
			}
			vertices.clear();
		}
};


class StarTrek_PP1_Desfecho {

	private:

		int 				posicaoAtual;
		int 				posicaoDestino;
		Grafo*				grafoGalaxia;
		vector<Grafo>		sistemasPlanetarios;
		vector<int>			sistemasInimigos;
		double 				custoMenor;
		
		vector<int>			visitado;
		vector<int>			distancia;


		void fazExploracao(vector<int>& visitado){
			custoMenor = 0 ;
			for( int i = 0; i < visitado.size(); i++){
				if( visitado[i] == true or i == posicaoDestino){
					Grafo* sistema = &sistemasPlanetarios[i];
					//cout << "somando custos:\n sistema a ser analisado: "<< i<<endl;
					//cout <<"custo ate aqui da galaxia: "<<custoMenor;
					cout<< "vizitando sistema : "<< i<<endl;
					custoMenor += (sistema->getCustoDFS());
					//cout << "\n O custo apos analise:: "<< custoMenor<<endl;
				}
			}
		}


		bool ehAmigo(int sistemaID){

			bool ehAliado = true;

			for(int i=0; i < sistemasInimigos.size()  and ehAliado ; i++ ){

				ehAliado = ( sistemaID != sistemasInimigos[ i ] ) and ehAliado;
			}
			return ehAliado;
		}
		
		
		bool foiVisitado(int elem){
			
			bool foi = false;
			int dimensaoVisitado = (int)visitado.size();
			for( int i=0; i < dimensaoVisitado and not foi;i++ ){
				
				foi = ( visitado[i] == elem ) and not foi;
			}
			return foi;
		}


		void bfsBFS( Fila< Aresta >& fila){

			bool fezexploracao = false;
			while( not fila.filaVazia() and not fezexploracao ){

				Aresta 		aresta;
				fila.desenfileira(aresta);
				int 		sistemaAtual = aresta.vertice;
				if( not foiVisitado(sistemaAtual) and ehAmigo(sistemaAtual) ){

					visitado.push_back(sistemaAtual);
					if( sistemaAtual == posicaoDestino){

						fazExploracao(visitado);
						fezexploracao = true;
					}
					else{

						Vertice 		u = grafoGalaxia->vertices [ sistemaAtual ];
						for(int i = 0; i< u.arestasAdjacentes.size(); i++) {

							Aresta		adj = u.arestasAdjacentes[ i ];
							int			comprimentoAtual =  distancia[ sistemaAtual ] + 1 ;
							if( distancia[ adj.vertice ] > comprimentoAtual ){

								distancia[ adj.vertice ] = comprimentoAtual;
								fila.enfileira( adj );
							}
						}
					}
				}
			}
		}


		void bfs(){

			distancia.assign( grafoGalaxia->qtdVertices + 1, infinito );
			distancia[posicaoAtual] = 0;
			
			Fila < Aresta > fila;
			fila.enfileira( Aresta( posicaoAtual, distancia[ posicaoAtual ] ) );
			bfsBFS( fila );
		}

		double getMenorCusto(){
			bfs();
			return custoMenor;
		}

		void mapearGrafo(Grafo& grafo){
			int origem, destino;
			for(int i=1 ; i <= grafo.qtdArestas; i++ ){

				cin >> origem >> destino;
				grafo.insereAresta( origem, destino, 0 );
			}
		}


		void mapearGrafoPonderado(Grafo& grafo){
			int		origem;
			int 	destino;
			double 	peso;

			for(int i=1 ; i <= grafo.qtdArestas; i++ ){
				cin >> origem >> destino >> peso;
				grafo.insereAresta( origem, destino, peso );
			}

		}


		void processaEntrada_Galaxia(){
			//cout << "Lendo Galaxia\n";
			int 	numVertices;
			int		quantidadeArestas;
			//cout << "Qual a ordem e o tamanho do grafo? ";
			cin >> numVertices >> quantidadeArestas;

			grafoGalaxia = new Grafo( numVertices, quantidadeArestas );
			mapearGrafo(*grafoGalaxia);
		}


		void processaEntrada_Inimigos(){

			//cout << "Quantos inimigos temos? e Quem sao? ";
			int		nInimigos;
			cin >> nInimigos;

			for(int i=0;i<nInimigos;i++){
				int 	inimigo;
				cin >> inimigo;
				sistemasInimigos.push_back(inimigo);
			}
		}


		void processaEntrada_1aEtapa(){

			processaEntrada_Galaxia();
			processaEntrada_Inimigos();

			//cout << "onde voce esta e pra onde quer ir?"<<endl;
			cin >> posicaoAtual >> posicaoDestino ;
		}


		void processaEntrada_2aEtapa(){

			Grafo grafozero(0,0);

			sistemasPlanetarios.push_back(grafozero);

			for(int i=0; i < grafoGalaxia->qtdVertices; i++ ){
				int 	ordem;
				int		tamanho;

				//cout << "sistema "<<i+1 <<":"<< endl;
				cin >> ordem >> tamanho;

				Grafo *grafo = new Grafo(ordem, tamanho);
				mapearGrafoPonderado(*grafo);

				sistemasPlanetarios.push_back(*grafo);
			}

		}

	public:


		StarTrek_PP1_Desfecho(){
			custoMenor= infinito;
		}



		void processaEntrada(){

			processaEntrada_1aEtapa();
			processaEntrada_2aEtapa();
		}



		void posExecute(){
			grafoGalaxia->print();
			cout << getMenorCusto() <<endl;
			limparMemoria();
		}


		void execute(){

			processaEntrada();
			posExecute();
		}


		void limparMemoria(){

			for(int i=0; i < sistemasPlanetarios.size() ; i++){

				sistemasPlanetarios[i].limparMemoria();
			}
			grafoGalaxia->limparMemoria();
			delete grafoGalaxia;
			sistemasInimigos.clear();
			sistemasPlanetarios.clear();
		}

};


int main(){

	StarTrek_PP1_Desfecho solucao ;
	solucao.execute();

	return 0;
}
