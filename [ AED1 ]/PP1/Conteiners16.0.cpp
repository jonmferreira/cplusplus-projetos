#include<iostream>
#include<cstdio>

using namespace std;

template <class T>
class No{

private:
	T item;
	No<T> *prox_fila = NULL;
	No<T> *prox_pilha = NULL;

public:
    
	No() {}
    No<T>* getProx_Pilha(){
		return this->prox_pilha;
	}
	No<T>* getProx_Fila(){
		return this->prox_fila;
	}
    T getItem(){
		return this->item;
	}
	void setProx_Pilha(No<T>* pProx){
		this->prox_pilha = pProx;
	}
	void setProx_Fila(No<T>* pProx){
		this->prox_fila = pProx;
	}
	void setItem(T pItem  ){
		this->item = pItem;
	}
};
template<class T>
class PilhaDE{
private:
	No<T> *fundo;
	No<T> *topo;
	int tamanho;

public:
    
	PilhaDE(){
		this->fundo = new No<T>();
		this->fundo->setProx_Fila(NULL);
		this->fundo->setProx_Pilha(NULL);
		this->topo = this->fundo;
		this->tamanho = 0;
	}
	int size(){
		
		return this->tamanho;
	}
	
	bool vazia(){
		return this->fundo == this->topo;
	}
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
		return -1;
	}
	
	No<T>* get(int id){

		if( id < this->tamanho){
			No<T>  *aux = this->topo->getProx_Pilha();

			while(id--) aux= aux->getProx_Pilha();

			return aux;
		}
		 else return this->fundo->getProx_Pilha();

	}
	
	void empilha(T pElem){
		
		this->topo->setItem(pElem);
		No<T> *aux  = new No<T>();
		
		aux->setProx_Fila(NULL);
		this->topo->setProx_Fila(aux);

		aux->setProx_Pilha(this->topo);
		this->topo = aux;
		this->tamanho++;
	}
	
	T Topo(){
		return this->topo->getProx_Pilha()->getItem();
	}
	
	void desempilha(){
		if(!this->vazia())
		{
			No<T> *aux = this->topo;
			this->topo= this->topo->getProx_Pilha();
			delete aux;
			this->tamanho -=1;
		}
	}

	No<T>* getTopo(){
		return this->topo;
	}
	No<T>* getFundo(){
		return this->fundo;
	}
	void clear(){
		while(!this->vazia())
			this->desempilha();
	}
	typedef No<T>* pInterador;
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
	
	int size(){
		return this->tamanho;
	}
	
	bool vazia(){
		return this->atras== this->inicio;
	}
	
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
		return -1; 
	}
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
	void enfilera(T pItem){
		
		this->atras->setItem(pItem);

		No<T> *aux = new  No<T>();
		
		aux->setProx_Pilha(this->atras);
		aux->setProx_Fila(NULL);

		this->atras->setProx_Fila(aux);
		this->atras = aux;

		this->tamanho = this->tamanho+1;
	}
	T Inicio(){
		return this->inicio->getItem();
	}
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
	
	No<T>* getInicio(){
		return this->inicio;
	}
	No<T>* getAtras(){
		return this->atras;
	}
	typedef No<T>* fInterador;
	void clear(){
		while(!this->vazia())
			this->desenfilera();
	}
};
template <class T>
class Container
{
	private :
		T carga;
	public:
		Container(){} 
		void setCarga(T pCarga) {
			this->carga = pCarga;
		}
		T getCarga(){
			return this->carga;
		}
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

template <class T>
istream& operator>>(istream &Entrada, Container<T> &p)
{
    T i;
    cin >> i;
    p.setCarga(i);
    return Entrada;

}

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
typedef int Chave;
typedef Container<Chave> Containers;
typedef PilhaDE<Chave> PilhasChaves;
typedef PilhaDE<Containers> PilhasContainer;
typedef FilaDE<PilhasContainer>  E1;
typedef FilaDE<PilhasChaves>  E2;
void coletarLixo(E1* alfa,E2* omega);
void lerSequenciaE1(E1* alfa);
void lerSequenciaE2(E2* omega);
int gerarSP(E1* alfa,E2* omega);
void gps(E1 *alfa , E1::fInterador *D, E1::fInterador *T, E1::fInterador *O, Containers id);
void ArrumarD(E1 *alfa, E2::fInterador *it, E1::fInterador *D,E1::fInterador *T,E1::fInterador *O, int *cont, Containers id);
void ArrumarO(E1::fInterador *O,E1::fInterador *T, int *cont, Containers id);
void ForjarD(E1::fInterador *D, E1::fInterador *O, int *trocas);
void Fila_de_Pilha_Show(E1 *alfa);
int main(){
	E1 alfa;
	E2 omega;
	
	lerSequenciaE1(&alfa);
    lerSequenciaE2(&omega);
    
    int totaldetrocas = gerarSP(&alfa,&omega);
	Fila_de_Pilha_Show(&alfa);
	return 0;
}

void lerSequenciaE1(E1* alfa){
	Containers carga;
	cin >> carga;
	do
	{
      
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

void lerSequenciaE2(E2* omega){
	Chave num;
	cin >>num;
	do
	{
        
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
int gerarSP(E1* alfa,E2* omega){

	E1::fInterador D;
	E1::fInterador T;
	E1::fInterador O;
	E2::fInterador it;

	int trocas=0;

	for( int i =0; i < omega->size(); i++ ){
		
		D = alfa->get(i);
		
		it = omega->get(i);
		PilhasChaves pit = it->getItem();
		
		for(int j=pit.size()-1; j >=0; j--){
			
			Containers ch;
			ch.setCarga( pit.get(j)->getItem());
			
			gps(alfa,&D,&T,&O,ch);
			
			if( j== (pit.size()-1))
			{
				
				ArrumarD(alfa,&it,&D,&T,&O,&trocas,ch);
				
				
				gps(alfa,&D,&T,&O,ch);
				
			}
			
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
void gps(E1 *alfa , E1::fInterador *D, E1::fInterador *T, E1::fInterador *O, Containers id)
{
		
		E1::fInterador fit;
		
		for(fit = alfa->getInicio(); fit != alfa->getAtras(); fit= fit->getProx_Fila() ){
			PilhasContainer p = fit->getItem();
			int k = p.getIndex(id);
			if(k== -1) continue;

			*O = fit;
			break;
		}
		
		*T = alfa->getAtras();
		for(fit = alfa->getInicio(); fit != alfa->getAtras(); fit= fit->getProx_Fila() ){
			PilhasContainer p = fit->getItem();
			int k = p.getIndex(id);
			if(k!= -1 || fit == (*D)) continue;

			*T = fit;

			break;
		}

}
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
	
	
}
void ArrumarO(E1::fInterador *O,E1::fInterador *T, int *cont, Containers id){
	PilhasContainer pt = (**T).getItem();
	PilhasContainer po = (**O).getItem();			
	
	while( po.Topo() != id){
		*cont = *cont +1;
		pt.empilha(po.Topo());
		po.desempilha();
	}
	(**O).setItem(po);
	(**T).setItem(pt);
}
void ForjarD(E1::fInterador *D, E1::fInterador *O, int *trocas){
	PilhasContainer pd = (**D).getItem();
	PilhasContainer po = (**O).getItem();	
	
	pd.empilha(po.Topo());
	po.desempilha();
	*trocas = *trocas +1;
	
	(**D).setItem(pd);
	(**O).setItem(po);
}
void Fila_de_Pilha_Show(E1 *alfa){
	int tamMax=0;
	
	string numspace=" ";
	E1::fInterador it;
	int num=2;
	
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
