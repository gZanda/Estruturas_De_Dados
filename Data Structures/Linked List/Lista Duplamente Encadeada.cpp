// Na lógica de lista DUPLAMENTE encadeada, cada nói tem um ponteiro para o pŕoximo e para o anterior
// Esse anterior é uma mão na roda para remover no final, etc

#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado;

class noh{
  friend class listadup;
  private:
    const Dado dado; // poderia ser outro tipo de variável (é const para não ser alterado)
    noh* proximo;
    noh* anterior;

  public:
    noh (Dado d = 0); // Cosntrutor padrão
};

noh::noh(Dado d) : dado(d){		// tem que usar esse "dado(d)" porque é ponteiro; Assim é mais rápido e pq é const;
// Mas é como se fosse um "dado = d";
  proximo = NULL;
  anterior = NULL;
}

// lista duplamente encadeada
class listadup {
  private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos (); // remove todos os elementos da lista

  public:
    // construtores e destrutor
    listadup();
    listadup(const listadup& umalLista);   // construtor de cópia
    ~listadup();
    // sobrecarga do operador de atribuição
    listadup& operator=(const listadup& umalista);
    // inserção, remoção e procura
    inline void insere(Dado dado);
    void insereNoFim(Dado dado);
    void insereNoInicio(Dado dado);
    void insereNaPosicao(int posicao, Dado dado);
    int procura(Dado valor); // retorna a posição do nó com determinado valor
    // métodos adicionais (impressão, vazia)
    void imprime();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
    void removeValor(Dado valor);
};

// constrói uma lista inicialmente vazia
listadup::listadup(){
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

// construtor de cópia (Insere no fim tudo que veio da outra lista)
listadup::listadup(const listadup& umalista){   // umalista = lista que será copiada
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;

  // percorre a lista recebida como parâmetro, copiando os dados
  noh* aux = umalista.primeiro;
  
  while (aux != NULL) {
    insereNoFim(aux->dado);
    aux = aux->proximo;
  }
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup(){
  removeTodos();
}

// remove todos os elementos da lista
void listadup::removeTodos(){
  noh* aux = primeiro;
  noh* temp;

  while(aux != NULL){
     temp = aux;
     aux = aux->proximo;
     delete temp;
  }
  // redirecionando ponteiros (Pois agora tudo foi deletado)
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

// sobrecarga do operador de atribuição   (Diferentemente do contrutor de cópia, REMOVE todos os elementos antes de copiar e retorna uma referência)
listadup& listadup::operator=(const listadup& umalista){
  // limpa a lista atual
  removeTodos();
  // percorre a lista recebida como parâmetro, copiando os dados
  noh* aux = umalista.primeiro;
  while (aux != NULL){
    insereNoFim(aux->dado);
    aux = aux->proximo;
  }
  return *this;   // Retorna a referência do objeto atual
}

// insere por padrão no final da lista
void listadup::insere(Dado dado) {
  insereNoFim(dado);
}

void listadup:: insereNoFim(Dado dado) {
  // * primeiro criamos o novo nó
  noh* novo = new noh(dado);

  // * agora inserimos o nó na lista
  // se a lista estiver vazia, inserimos o primeiro nó
  if(vazia()){ // ou (primeiro == NULL) ou (tamanho ==0 )
    primeiro = novo;
    ultimo = novo;
  }
  else { // já tem elementos na lista, insere no final
    ultimo->proximo = novo;
    novo->anterior = ultimo;	// DIFERENÇA COM A DINAMICAMENTE ENCADEADA
    ultimo = novo;
  }
  tamanho++;
}

// insere no início da lista
void listadup::insereNoInicio(Dado dado) {
  // * primeiro criamos o novo nó
  noh* novo = new noh(dado);

  // * agora inserimos o nó na lista
  // se a lista estiver vazia, inserimos o primeiro nó
  if( vazia()){ // ou (primeiro == NULL) ou (tamanho == 0)
    primeiro = novo;
    ultimo = novo;
  }
  else{ // já tem elementos na lista, insere no inicio
    novo->proximo = primeiro;
    primeiro->anterior = novo;
    primeiro = novo;    // Primeiro (da lista mesmo) aponta para esse novo
  }
  tamanho++;
}

// insere em uma determinada posição da lista
void listadup::insereNaPosicao(int posicao, Dado dado){
  // * primeiro criamos o novo nó
  noh* novo = new noh(dado);

  // * agora inserimos o nó na lista
  // verificamos antes se é possível inserir na posição
  if ((posicao <= tamanho) and (posicao >= 0)) {
    if ( vazia()){ // ou (primeiro == NULL) ou (tamanho ==0))
      primeiro = novo;
      ultimo = novo;
    }
    else if (posicao == 0){ // Insere no Início
      novo-> proximo = primeiro;
      primeiro->anterior = novo;	// Diferença
      primeiro = novo;
    }
    else if (posicao == tamanho){ // Insere no Fim
      ultimo->proximo = novo;
      novo->anterior = ultimo;
      ultimo = novo;
    }
    else{ // insere no meio da lista
      noh* aux = primeiro;
      int posAux = 0;

      // chegando na posicao da lista
      while ( posAux < (posicao-1) ) {   // Enquanto não chegar na posição ANTERIOR à que quer inserção
        aux = aux->proximo;
        posAux++;
      }
      novo->proximo = aux->proximo;
      aux->proximo->anterior = novo;	// Diferença
      aux->proximo = novo;
      novo->anterior = aux;	// Diferença
    }
    tamanho++;
  }
  else {
  cerr << "Posição Inexistente!" << endl;
  exit(EXIT_FAILURE);
  }
}

int listadup::procura(Dado valor){
  noh* aux = primeiro;
  int posAux = 0;
  while ((aux != NULL) and (aux->dado != valor)){
    posAux++;
    aux = aux->proximo;
  }
  if(aux == NULL){
    posAux = -1;  // -1 = não encontrado
  }
  return posAux;
}

//método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void listadup:: imprime(){
  noh* aux = primeiro;

  while (aux != NULL) {
    cout << aux->dado << ' ';
    aux = aux->proximo;
  }
  cout << endl;
  
  // Imprime reverso (para mostrar o uso de duplo encadeamento)
  aux = ultimo;
  while(aux != NULL){
	cout << aux->dado << ' ';
	aux = aux-> anterior;
  }
  cout << endl;
}

// Verifica se a lista está vazia
inline bool listadup::vazia(){
  return (tamanho == 0);
}

// Remove no início
void listadup::removeNoInicio(){
  if(vazia()){ // verifica lista vazia
    cerr << "Remoção em lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  noh* removido = primeiro;
  primeiro = primeiro -> proximo;
  if(primeiro != NULL){  
	primeiro->anterior = NULL;
  }
  delete removido;
  tamanho--;

  // se a lista ficou vazia
  if(vazia()){
    ultimo = NULL;
  }
}

// Remove no Fim
void listadup::removeNoFim(){
  if(vazia()){ // verifica lista vazia
    cerr << "Remoção em lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  noh* removido = ultimo;
  ultimo = ultimo -> anterior;
  if(ultimo != NULL){
	ultimo->proximo = NULL;
  }
  delete removido;
  tamanho--;

  // se a lista ficou vazia
  if(vazia()){
    ultimo = NULL;
  }
}

void listadup::removeValor(Dado valor){
  // Código de busca primeiro
  noh* aux = primeiro;
  while ((aux != NULL) and (aux->dado != valor)){
    aux = aux->proximo;
  }
  if(aux == NULL){
    cerr << "valor não encontrado" << endl;
    exit(EXIT_FAILURE);
  }
  else{
	noh* anterior = aux->anterior;
	noh* proximo = aux->proximo;
	if(anterior != NULL){
	anterior->proximo = proximo;
	}
	if(proximo!=NULL){
	proximo->anterior = anterior;
	}
	delete aux;  
  }
  tamanho--;
  if(vazia()){
	primeiro = NULL;
	ultimo = NULL;
  }
}

int main(){
	listadup minhalista;
	cout << "*** Teste da Lista ***" << endl;
	
	minhalista.insere(5);
	minhalista.insere(3);
	minhalista.insere(1);
	minhalista.insere(0);
	minhalista.insere(6);
	minhalista.insereNoInicio(18);
	minhalista.insereNaPosicao(3,25);
	minhalista.imprime();
	
	cout << minhalista.procura(3) << endl;
	cout << minhalista.procura(50) << endl;
	cout << minhalista.procura(6) << endl;
	
	// construtor de cópia
  cout << "Sobrecarga do construtor de cópia" << endl;    // Copia a lista
  listadup outraLista(minhalista);
  outraLista.insereNoInicio(99);
  outraLista.insereNoFim(10);
  
  // sobrecarga de operador de atribuição
  cout << "Sobrecarga do operador de atribuição" << endl;   // Copia a lista
  listadup maisUmaLista;   // Cria uma nova lista
  maisUmaLista = outraLista;    // Essa nova lista Recebe o conteúdo de outra lista
  maisUmaLista.insereNoInicio(31);
  maisUmaLista.insereNoFim(13);
  
  // Impressão das 3 listas diferentes
  cout << endl;
  minhalista.imprime();
  outraLista.imprime();
  maisUmaLista.imprime();
  
  // Teste da remoção
  cout << "Após a remoção:" << endl;
  minhalista.removeNoFim();
  minhalista.removeNoInicio();
  minhalista.removeNoFim();
  minhalista.removeNoInicio();
  minhalista.removeNoFim();
  minhalista.removeNoInicio();
  minhalista.imprime();
  minhalista.removeValor(25);
  cout << "Depois de tirar o 25:" << endl;
  minhalista.imprime();
  
  return 0;
  
 }
 
 // PAROU NO 22:07
