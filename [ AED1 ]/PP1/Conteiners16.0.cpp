#include<iostream>
#include<cstdio>

using namespace std;

/***
*Declarando classes:
*/
///-------
/***
*No: apontador de elementos;
*/
template <class T>
class No{

private:
	T item;
	No<T> *prox_fila = NULL;
	No<T> *prox_pilha = NULL;

public:
    ///Contrutor
	No() {}
    /***
    *@return *No<T>:
    */
	No<T>* getProx_Pilha(){
		return this->prox_pilha;
	}
	/***
    *@return *No<T>:
    */
    No<T>* getProx_Fila(){
		return this->prox_fila;
	}
    /***
    *@return T: Elemento
    */
	T getItem(){
		return this->item;
	}
	/***
    *@param pProx: &No do sucessor[PILHA]
    */
	void setProx_Pilha(No<T>* pProx){
		this->prox_pilha = pProx;
	}
	/***
    *@param pProx: &No do sucessor[FILA]
    */
	void setProx_Fila(No<T>* pProx){
		this->prox_fila = pProx;
	}
	/***
    *@param pItem: Elemento
    */
	void setItem(T pItem  ){
		this->item = pItem;
	}
};
/***
*PilhaDE: Pilha Duplamente Encadeada
*/
template<class T>
class PilhaDE{
private:
	No<T> *fundo;
	No<T> *topo;
	int tamanho;

public:
    ///construtor
	PilhaDE(){
		this->fundo = new No<T>();
		this->fundo->setProx_Fila(NULL);
		this->fundo->setProx_Pilha(NULL);
		this->topo = this->fundo;
		this->tamanho = 0;
	}
	/***
	*@return int:quantidade de elementos da pilha.
	*/
	int size(){
		
		return this->tamanho;
	}
	/***
	*@return bool:verifica se a pilha ta vazia
	*/
	bool vazia(){
		return this->fundo == this->topo;
	}
	/***
	*@return int :indice do elemento referente a ordem de prioridade
	*/
	int getIndex(T elem){
		No<T>  *aux = this->topo->getProx_Pilha();
		int i= 0;
		while(aux != this->fundo->getProx_Pilha())
		{
			if( aux->getItem() == elem)
				return  i;
			else {
				i++;
				aux= aux->getProx_Pilha();
			}
		}
		return -1; // caso o elemento não exista na pilha;
	}
	/***
	*@return T:elemento em dada posição na pilha.
	*/
	No<T>* get(int id){

		if( id < this->tamanho){
			No<T>  *aux = this->topo->getProx_Pilha();

			while(id--) aux= aux->getProx_Pilha();

			return aux;
		}
		 else return this->fundo->getProx_Pilha();

	}
	///push
	void empilha(T pElem){
		///padrao
		this->topo->setItem(pElem);
		No<T> *aux  = new No<T>();
		///fila
		aux->setProx_Fila(NULL);
		this->topo->setProx_Fila(aux);
		///pilha
		aux->setProx_Pilha(this->topo);
		this->topo = aux;
		this->tamanho++;
	}
	///top
	T Topo(){
		return this->topo->getProx_Pilha()->getItem();
	}
	///pop
	void desempilha(){
		if(!this->vazia())
		{
			No<T> *aux = this->topo;
			this->topo= this->topo->getProx_Pilha();
			delete aux;
			this->tamanho -=1;
		}
	}
	void mostra(){
        No<T> *aux = this->topo;
        cout << "Pilha:\n";
        if(!this->vazia()){
	        aux = aux->getProx_Pilha();
	        while(aux != this->fundo->getProx_Pilha())
	        {
	            T a = aux->getItem();
	            cout << a <<endl;
	            aux = aux->getProx_Pilha();
	        }
	        cout <<endl;	
		}
        
	}
	/***
	*@return No<T>*:interador do topo
	*/
	No<T>* getTopo(){
		return this->topo;
	}
	/***
	*@return No<T>*:interador do fundo
	*/
	No<T>* getFundo(){
		return this->fundo;
	}
	/***
	*Esvazia a fila
	*/
	void clear(){
		while(!this->vazia())
			this->desempilha();
	}
	/***
	*Usado na interacao de ponteiros:
	*/
	typedef No<T>* pInterador;
	/***
	*
	*/
	bool operator!=(PilhaDE<T> a)
	{
			 if(this->size() != a.size()) return true;
			 else
			 {
			 	pInterador pti= this->getTopo()->getProx_Pilha();
			 	pInterador ptj = a.getTopo()->getProx_Pilha();
			 	while ( pti != this->fundo->getProx_Pilha())
				 {
				 	if ( pti->getItem() != ptj->getItem() )	
				 	{
			
					  	return true;
					}
				 	pti= pti->getProx_Pilha();
				 	ptj = ptj->getProx_Pilha();	
				 }
				 return false;
			 }
	}
};
/***
*Fila: Fila
*/
template<class T>
class FilaDE{
private:
	No<T> *inicio = NULL;
	No<T> *atras= NULL;
	int tamanho;
public:
	FilaDE(){
        this->inicio = new No<T>();
		this->inicio->setProx_Fila(NULL);
		this->inicio->setProx_Pilha(NULL);
		this->atras = this->inicio;
		this->tamanho = 0;
	}
	/***
	*@return int: quantidade de elementos da fila.
	*/
	int size(){
		return this->tamanho;
	}
	/***
	*@return bool: se estar vazia
	*/
	bool vazia(){
		return this->atras== this->inicio;
	}
	/***
	*@return int :indice do elemento referente a ordem de insercao
	*/
	int getIndex(T elem){
		No<T>  *aux = this->inicio;
		int i= 0;
		while(aux != this->atras)
		{
			if( aux->getItem() == elem)
				return  i;
			else {
				i++;
				aux= aux->getProx_Fila();
			}
		}
		return -1; // caso o elemento não exita na fila;
	}
	/***
	*@return T:elemento em dada posição na fila.
	*/
	No<T>* get(int id){

			No<T>  *aux= this->inicio;
			No<T> *parada =this->atras;
			while( aux != parada && id>0 )
			{
				id--;
				aux=aux->getProx_Fila();
			}

			if(id== 0  && aux != parada)
				return aux;
			else return parada;
	}
	/***
	*@param T: elemento
	*/
	void enfilera(T pItem){
		
		this->atras->setItem(pItem);

		No<T> *aux = new  No<T>();
		
		aux->setProx_Pilha(this->atras);
		aux->setProx_Fila(NULL);

		this->atras->setProx_Fila(aux);
		this->atras = aux;

		this->tamanho = this->tamanho+1;
	}
	/***
	*@return T: elemento em prioridade na fila
	*/
	T Inicio(){
		return this->inicio->getItem();
	}
	//pop
	void desenfilera(){
		if(!this->vazia())
		{
			No<T> *aux = this->inicio;

			this->inicio= this->inicio->getProx_Fila();
			this->inicio->setProx_Pilha(NULL);
			delete aux;
			this->tamanho=this->tamanho-1;
		}
	}
	//pop
	void desenfileraPilha(){
		if(!this->vazia())
		{
			No<T> *aux = this->atras;

			this->atras= this->atras->getProx_Pilha();
			this->atras->setProx_Fila(NULL);
			delete aux;
			this->tamanho=this->tamanho-1;
		}
	}
	void mostra(){
        No<T> *aux = this->inicio;
        cout << "Fila:\n";
        while(aux != this->atras)
        {
            cout << aux->getItem() << " ";
            aux = aux->getProx_Fila();
        }
        cout << endl;
	}
	/***
	*@return No<T>*:interador do topo
	*/
	No<T>* getInicio(){
		return this->inicio;
	}
	/***
	*@return No<T>*:interador do fundo
	*/
	No<T>* getAtras(){
		return this->atras;
	}
	/***
	*Usado na interacao de ponteiros:
	*/
	typedef No<T>* fInterador;
	/***
	*Esvazia a fila
	*/
	void clear(){
		while(!this->vazia())
			this->desenfilera();
	}
};
///talvez não precise usar esta classe
/***
*Container: Eh uma caixa gigante de aço ou ferro?
*/
template <class T>
class Container
{
	private :
		T carga;
	public:
		Container(){} ///Contrutor
		void setCarga(T pCarga) {
			this->carga = pCarga;
		}
		T getCarga(){
			return this->carga;
		}
		/***
		*Sobrecarga de operadores:
		*usado para facilitar escrita e comparações;
		*/
		bool operator==(Container a){
			return this->carga == a.carga;
		}
		bool operator!=(Container &a){
			return this->carga != a.carga;
		}
		bool operator==(int a){
			return this.carga == a;
		}
		bool operator!=(int a){
			return (this->carga != a);
		}
		void mostraCarga(){
            cout << this->carga;
		}
};
///Fim declacao de classes
/***
*Sobrecarga de operadores
*serve para facilitar leitura e escrita de classes
*cin pertence a classe istream
*cout pertence a classe ostream
*/
///cin
template <class T>
istream& operator>>(istream &Entrada, Container<T> &p)
{
    T i;
    cin >> i;
    p.setCarga(i);
    return Entrada;

}
///cout
template <class T>
ostream& operator<<(ostream &Saida, Container<T> c)
{
    c.mostraCarga();
    return Saida;
}
template <class T>
ostream& operator<<(ostream &Saida, PilhaDE<T> p)
{
    p.mostra();
    return Saida;
}
/**
*Usado para simplificar declaracao e
*evitar certos bugs de compilacao
*/
typedef int Chave;
typedef Container<Chave> Containers;
typedef PilhaDE<Chave> PilhasChaves;
typedef PilhaDE<Containers> PilhasContainer;
typedef FilaDE<PilhasContainer>  E1;
typedef FilaDE<PilhasChaves>  E2;
///**  prototipagem das funcoes auxiliares */
/***
*limpa espaço de memoria criado
*/
void coletarLixo(E1* alfa,E2* omega);
/***
*Processa primeira entrada
*/
void lerSequenciaE1(E1* alfa);
/***
*Processa segunda entrada
*/
void lerSequenciaE2(E2* omega);
/***
*@return int: Quantidade de trocas minimas
*/
int gerarSP(E1* alfa,E2* omega);
/**
*Localiza os ponteiros a serem processados;
*/
void gps(E1 *alfa , E1::fInterador *D, E1::fInterador *T, E1::fInterador *O, Containers id);
/***
*Preprara a pilha D
*/
void ArrumarD(E1 *alfa, E2::fInterador *it, E1::fInterador *D,E1::fInterador *T,E1::fInterador *O, int *cont, Containers id);
/***
*Preprara a pilha O
*@param O: Pilha objeto
*@param T: Pilha temporaria
*/
void ArrumarO(E1::fInterador *O,E1::fInterador *T, int *cont, Containers id);
/***
*ForjarD
*Preprara a pilha O
*@param D: Pilha dominio
*@param O: Pilha objeto
*@param trocas: contador 
*/
void ForjarD(E1::fInterador *D, E1::fInterador *O, int *trocas);
/***
*Exibe as pilhas sob o formato especificado
*/
void Fila_de_Pilha_Show(E1 *alfa);
///Fim prototipagem
int main(){
	//E1 *alfa = new E1();
	//E2 *omega = new E2();
	E1 alfa;
	E2 omega;
	
	lerSequenciaE1(&alfa);
    lerSequenciaE2(&omega);
    
    int totaldetrocas = gerarSP(&alfa,&omega);
	Fila_de_Pilha_Show(&alfa);
	
	//coletarLixo(&alfa,&omega);	
	return 0;
}
///** Implemenacoes das funcoes de apoio*/
/***
*Processa primeira entrada
*/
void lerSequenciaE1(E1* alfa){
	Containers carga;
	cin >> carga;
	do
	{
      //  PilhasContainer *Pi = new PilhasContainer();
        PilhasContainer Pi;
        while(carga != -1 )
        {
            Pi.empilha(carga);
            cin >> carga;
        }
        alfa->enfilera(Pi);	
        cin >> carga;
	}while(carga != -1);
}
/***
*Processa segunda entrada
*/
void lerSequenciaE2(E2* omega){
	Chave num;
	cin >>num;
	do
	{
        //PilhasChaves *Pi = new PilhasChaves();
        PilhasChaves Pi;
        while(num != -1 )
        {
            Pi.empilha(num);
            cin >> num;
        }
        omega->enfilera(Pi);
		cin >> num;
	}while(num != -1 );
}
/***
*@return int: Quantidade de trocas minimas
*/
int gerarSP(E1* alfa,E2* omega){

	/*Ponteiros para as pilhas trabalhas;*/
	E1::fInterador D;
	E1::fInterador T;
	E1::fInterador O;
	E2::fInterador it;///Indica a pilha de chaves trabalhada

	int trocas=0;

	for( int i =0; i < omega->size(); i++ ){
		///seleciono a pilha de containers [D]
		D = alfa->get(i);
		///isolo a pilha de chaves referente a pilha [D]
		it = omega->get(i);
		PilhasChaves pit = it->getItem();
		/// percerro as chaves organizando a pilha [D][i]
		for(int j=pit.size()-1; j >=0; j--){
			///isolo o id do container;
			Containers ch;
			ch.setCarga( pit.get(j)->getItem());
			///localizando os & de [O] e [T]:
			gps(alfa,&D,&T,&O,ch);
			
			if( j== (pit.size()-1))
			{
				///Arruma a pilha D;	
				ArrumarD(alfa,&it,&D,&T,&O,&trocas,ch);
				///atualiza os & de [O] e [T]:
				
				gps(alfa,&D,&T,&O,ch);
				
			}
			///Arruma a pilha O;
			if( O != D)
			{
				ArrumarO(&O,&T,&trocas,ch);
				ForjarD(&D,&O,&trocas);	
			}
			
		}
	}
	int numdif =  alfa->size() - omega->size();
	while(numdif--) {
		alfa->desenfileraPilha();
	}
	return trocas;
}
/**
*Localiza os ponteiros a serem processados;
*/
void gps(E1 *alfa , E1::fInterador *D, E1::fInterador *T, E1::fInterador *O, Containers id)
{
		
		E1::fInterador fit;
		///localizando pilha que está o elemento procurado [O]
		for(fit = alfa->getInicio(); fit != alfa->getAtras(); fit= fit->getProx_Fila() ){
			PilhasContainer p = fit->getItem();
			int k = p.getIndex(id);
			if(k== -1) continue;//elemento não está nesta pilha

			*O = fit;
			break;
		}
		///localizando pilha temporária [T]
		*T = alfa->getAtras();
		for(fit = alfa->getInicio(); fit != alfa->getAtras(); fit= fit->getProx_Fila() ){
			PilhasContainer p = fit->getItem();
			int k = p.getIndex(id);
			if(k!= -1 || fit == (*D)) continue;/// pilha que não é O nem D

			*T = fit;

			break;
		}

}
/***
*Preprara a primeira pilha
*/
void ArrumarD(E1 *alfa, E2::fInterador *it, E1::fInterador *D,E1::fInterador *T,E1::fInterador *O, int *cont, Containers id){
    PilhasContainer pt = (**T).getItem();
	PilhasContainer pd = (**D).getItem();
	
	if( (*O) == (*D))
	{
		bool operar= false;
		operar= (**D).getItem().size() !=  (**it).getItem().size();
				for(int i =0 ; i< (**it).getItem().size() && !operar;i++)
				{

					Containers c1 =(**D).getItem().get(i)->getItem();
					Chave c2 = (**it).getItem().get(i)->getItem();
					if( (c1 != c2))
					{
						operar = true;	
						break;
					} 
				}
		if( operar)
		{
			if( !(**D).getItem().vazia() ){
				do
				{
					*cont = *cont +1;
					pt.empilha(pd.Topo());
					pd.desempilha();
				}while(pt.Topo() != id);
				(**D).setItem(pd);
				(**T).setItem(pt);		
				gps(alfa,D,T,O,id);
				ArrumarD(alfa,it,D,T,O,cont,id);		
			}
			
		}
		
	}
	else
	{
		while( !pd.vazia() )
		{
			*cont = *cont +1;
			pt.empilha(pd.Topo());
			pd.desempilha();
		}	
		(**D).setItem(pd);
		(**T).setItem(pt);
	}
	//dá pra otimizar aqui!
	
}
/***
*Preprara a pilha O
*/
void ArrumarO(E1::fInterador *O,E1::fInterador *T, int *cont, Containers id){
	PilhasContainer pt = (**T).getItem();
	PilhasContainer po = (**O).getItem();			
	//dá pra otimizar aqui!
	///enquanto o container procurado não estiver acessível:
	while( po.Topo() != id){
		*cont = *cont +1;
		pt.empilha(po.Topo());
		po.desempilha();
	}
	(**O).setItem(po);
	(**T).setItem(pt);
}
/***
*ForjarD
*Preprara a pilha O
*@param D: Pilha dominio
*@param O: Pilha objeto
*@param trocas: contador 
*/
void ForjarD(E1::fInterador *D, E1::fInterador *O, int *trocas){
	PilhasContainer pd = (**D).getItem();
	PilhasContainer po = (**O).getItem();	
	
	pd.empilha(po.Topo());
	po.desempilha();
	*trocas = *trocas +1;
	
	(**D).setItem(pd);
	(**O).setItem(po);
}
/***
*Exibe as pilhas sob o formato especificado
*/
void Fila_de_Pilha_Show(E1 *alfa){
	int tamMax=0;
	
	string numspace=" ";
	E1::fInterador it;
	int num=2;
	///localiza maior indice
	for(it = alfa->getInicio();it != alfa->getAtras(); it = it->getProx_Fila())
	{
			if(!it->getItem().vazia())
			{
				if(it->getItem().size()  > tamMax)
				{
					tamMax = it->getItem().size();
					num = it->getItem().Topo().getCarga();
				}		
			}
	}
	///verifica quantidade de espaços
	
	num=num/10;
	while(num>0){
		numspace+=" ";
		num=num/10;
	}
	
	for(int i= 0;i< tamMax; i++){
		
		for(it = alfa->getInicio();it != alfa->getAtras(); it = it->getProx_Fila())
		{
			int indice = (  it->getItem().size() + i )  - tamMax ;
			if(indice >=0)
			{
				PilhasContainer::pInterador  cit = it->getItem().get(indice);
				Containers c= cit->getItem();
				cout << c<< " ";
			}
			else cout <<numspace <<" ";
		}	
		cout<<endl;
		
	}
	 
}
/***
*limpa espaço de memoria criado
*/
void coletarLixo(E1* alfa,E2* omega){
	alfa->clear();
	omega->clear();
	// usa delete apenas com ponteiros
	//delete alfa
	//delete omega
}
///Fim implementacao
