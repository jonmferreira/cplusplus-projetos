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
	
	private:
		
		int			vertice;
		double		peso;
		
	public:
		
		
		Aresta(){}


		Aresta(int pDest, double pPeso){
			
			vertice = pDest;
			peso = pPeso;
		}
		
		
		int getVertice(){
			
			return vertice;
		}
		
		
		double getPeso(){
			
			return peso;
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
		
		vector<Aresta>	arestasAdjacentes;

	public :


		Vertice(){
		}
		
		
		vector<Aresta> getArestasAdjacentes(){
			
			return arestasAdjacentes;
		}


		void addVisinho(int visinho, double peso){
			
			Aresta		aresta( visinho, peso );
			arestasAdjacentes.push_back( aresta );
			stable_sort( arestasAdjacentes.begin(),arestasAdjacentes.end(), comp );
		}


		void print(){
			
			for(int i=0;i< (int)arestasAdjacentes.size();i++){
				
				cout << arestasAdjacentes[i].getVertice() << " ";
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

		int					qtdVertices;
		int					qtdArestas;
		vector< Vertice >	vertices;

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
                int dimensao = (int) planeta.getArestasAdjacentes().size();
                for( int i=0; i< dimensao ;i++){
                	
                    Aresta caminho = planeta.getArestasAdjacentes()[i];
                    if( not visitado[ caminho.getVertice() ] ){
                    	
                        custoTotalDFS += caminho.getPeso();
                        dfs( caminho.getVertice() , visitado );
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
               	cout << "rodou um dfs nos vertices: ";
                dfs(1, visitados);
                cout<< endl;
            }
        }

	public:
		

		Grafo( int n , int m ){
			
				Grafo();
				qtdVertices = n;
				qtdArestas = m;
				vertices.assign( qtdVertices + 1, Vertice());
		}
		
        
        int getOrdem(){
        	
        	return qtdVertices;
		}
		
		
		int getTamanho(){
			
			return qtdArestas;
		}
		
		
		vector<Vertice> getArrayVertices(){
			
			return vertices;
		}


		void insereAresta( int origem, int destino, double peso ){
			
			if( origem < (int)vertices.size() and destino < (int)vertices.size() ){

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
			
			for(int i=1;i< (int)vertices.size();i++){
				
				cout << i <<": ";
				vertices [i].print();
				cout<< "\n------\n";
			}
		}


		void limparMemoria(){
			
			for(int i=0 ;i< (int)vertices.size();i++){
				
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


		void fazExploracao(){
			
			custoMenor = 0 ;
			int dimensao = ( int ) visitado.size(); 
			for( int i = 0; i < dimensao ;i++ ){
				
				Grafo* sistema = &sistemasPlanetarios[ visitado[i] ];
				cout<< "vizitando sistema : "<< visitado[i] <<endl;
				custoMenor += (sistema->getCustoDFS());
			}
		}


		bool ehAmigo(int sistemaID){

			bool ehAliado = true;
			int dimensao = (int) sistemasInimigos.size();
			for(int i=0; i <  dimensao and ehAliado ; i++ ){

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
				int 		sistemaAtual;
				fila.desenfileira(aresta);
				sistemaAtual = aresta.getVertice();
				if( not foiVisitado(sistemaAtual) and ehAmigo(sistemaAtual) ){

					visitado.push_back(sistemaAtual);
					//fazExploracao();
					//fezexploracao = true;
					Vertice 	u = grafoGalaxia->getArrayVertices() [ sistemaAtual ];
					int 		dimensao = (int) u.getArestasAdjacentes().size();
					for( int i = 0; i< dimensao; i++) {

						Aresta	adj = u.getArestasAdjacentes()[ i ];
						int		comprimentoAtual =  distancia[ sistemaAtual ] + 1 ;
						if( distancia[ adj.getVertice() ] > comprimentoAtual ){

							distancia[ adj.getVertice() ] = comprimentoAtual;
							fila.enfileira( adj );
						}
					}
				}
			}
		}


		void bfs(){

			distancia.assign( grafoGalaxia->getOrdem() + 1, infinito );
			distancia[posicaoAtual] = 0;
			
			Fila < Aresta > fila;
			fila.enfileira( Aresta( posicaoAtual, distancia[ posicaoAtual ] ) );
			bfsBFS( fila );
			fazExploracao();
		}


		double getMenorCusto(){
			
			bfs();
			return custoMenor;
		}

		void mapearGrafo(Grafo& grafo){
			
			int origem, destino;
			for(int i=1 ; i <= grafo.getTamanho(); i++ ){

				cin >> origem >> destino;
				grafo.insereAresta( origem, destino, 0 );
			}
		}


		void mapearGrafoPonderado(Grafo& grafo){
			
			int		origem;
			int 	destino;
			double 	peso;

			for(int i=1 ; i <= grafo.getTamanho(); i++ ){
				
				cin >> origem >> destino >> peso;
				grafo.insereAresta( origem, destino, peso );
			}

		}


		void processaEntrada_Galaxia(){
			
			int 	numVertices;
			int		quantidadeArestas;
			cin >> numVertices >> quantidadeArestas;

			grafoGalaxia = new Grafo( numVertices, quantidadeArestas );
			mapearGrafo(*grafoGalaxia);
		}


		void processaEntrada_Inimigos(){

			int		nInimigos;
			cin >>  nInimigos;
			for(int i=0;i<nInimigos;i++){
				
				int 	inimigo;
				cin >> inimigo;
				sistemasInimigos.push_back(inimigo);
			}
		}


		void processaEntrada_1aEtapa(){

			processaEntrada_Galaxia();
			processaEntrada_Inimigos();
			cin >> posicaoAtual >> posicaoDestino ;
		}


		void processaEntrada_2aEtapa(){

			Grafo grafozero(0,0);
			sistemasPlanetarios.push_back(grafozero);
			for(int i=0; i < grafoGalaxia->getOrdem(); i++ ){
				
				int 	ordem;
				int		tamanho;
				cin >> ordem >> tamanho;
				Grafo *grafo = new Grafo(ordem, tamanho);
				
				mapearGrafoPonderado(*grafo);
				cout << "\nsistema: "<<i+1<<" | custo:" <<grafo->getCustoDFS()<<endl;
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

			for(int i=0; i < (int) sistemasPlanetarios.size() ; i++){

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
