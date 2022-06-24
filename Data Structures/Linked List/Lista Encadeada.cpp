#include <iostream>
#include <cstdlib>
using namespace std;

typedef int Dado; // Typedef permite criar novos tipos a partir de outros (criamos basicamente um "apelido" para int)

class noh{
  friend class lista;
  private:
    const Dado dado; // poderia ser outro tipo de variável (é const para não ser alterado)
    noh* proximo;

  public:
    noh (Dado d = 0); // Cosntrutor padrão
};

noh::noh(Dado d) : dado(d){
  proximo = NULL;
}

// lista dinamicamente encadeada
class lista {
  private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos (); // remove todos os elementos da lista
    void imprimeReversoAux(noh* umNoh); // imprime reverso a partir de um nó -> exemplo de uso de recursão

  public:
    // construtores e destrutor
    lista();
    lista(const lista& umalLista);   // construtor de cópia
    ~lista();
    // sobrecarga do operador de atribuição
    lista& operator=(const lista& umalista);
    // inserção, remoção e procura
    inline void insere(Dado dado);
    void insereNoFim(Dado dado);
    void insereNoInicio(Dado dado);
    void insereNaPosicao(int posicao, Dado dado);
    int procura(Dado valor); // retorna a posição do nó com determinado valor
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};

// constrói uma lista inicialmente vazia
lista::lista(){
  tamanho = 0;
  primeiro = NULL;
  ultimo = NULL;
}

// construtor de cópia (Insere no fim tudo que veio da outra lista)
lista::lista(const lista& umalista){   // umalista = lista que será copiada
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
lista::~lista(){
  removeTodos();
}

// remove todos os elementos da lista
void lista::removeTodos(){
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
lista& lista::operator=(const lista& umalista){
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
void lista::insere(Dado dado) {
  insereNoFim(dado);
}

void lista:: insereNoFim(Dado dado) {
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
    ultimo = novo;
  }
  tamanho++;
}

// insere no início da lista
void lista::insereNoInicio(Dado dado) {
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
    primeiro = novo;    // Primeiro (da lista mesmo) aponta para esse novo
  }
  tamanho++;
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, Dado dado){
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
      primeiro = novo;
    }
    else if (posicao == tamanho){ // Insere no Fim
      ultimo->proximo = novo;
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
      aux->proximo = novo;
    }
    tamanho++;
  }
  else {
  cerr << "Posição Inexistente!" << endl;
  exit(EXIT_FAILURE);
  }
}

int lista::procura(Dado valor){
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
void lista:: imprime(){
  noh* aux = primeiro;

  while (aux != NULL) {
    cout << aux->dado << ' ';
    aux = aux->proximo;
  }
  cout << endl;
}

// Para imprimir REVERSO, usaremos PILHA DE RECURSÃO
// Para isso, precisa de uma função auxiliar
void lista::imprimeReverso(){
  imprimeReversoAux(primeiro);
  cout << endl;
}

void lista::imprimeReversoAux(noh* umNoh){
  if(umNoh != NULL) {
    imprimeReversoAux(umNoh->proximo);  // Cada nó chama a impressão do próximo antes de se imprimir
    cout << umNoh->dado << ' ';
  }
}

// Verifica se a lista está vazia
inline bool lista::vazia(){
  return (primeiro == NULL);
}

void lista::removeNoFim(){
  if(vazia()){ // verifica lista vazia
    cerr << "Remoção em lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  noh* aux =  primeiro;
  noh* anterior;
  while(aux->proximo != NULL){  // Aux para no ULTIMO
    anterior = aux;
    aux = aux->proximo;
  }
  delete ultimo;  // apagou aquele que aux aponta
  anterior -> proximo = NULL;
  ultimo = anterior;

  if(vazia()){  // Verifica se a lista ficou vazia com isso
    primeiro = NULL;
  }
  tamanho--;
}

void lista::removeNoInicio(){
  if(vazia()){ // verifica lista vazia
    cerr << "Remoção em lista vazia" << endl;
    exit(EXIT_FAILURE);
  }

  noh* removido = primeiro;
  primeiro = primeiro -> proximo;
  delete removido;
  tamanho--;

  // se a lista ficou vazia
  if(tamanho == 0){
    ultimo = NULL;
  }
}

// CASO FOR FAZER REMOÇÃO DE UM VALOR, USAR O MÉTODO "BUSCA()" E RESGUARFAR ANTES DE DELETAR (assim como na remoção no início, salva o anterior)

int main() {
  lista minhalista;

  cout << "*** Teste da Lista ***" << endl;
  cout << "Quantidade de walores a inserir: " << endl;

  int valor;
  int num;
  cin >> num;

  for (int i = 0; i < num; i++) {
    cin >> valor;
    minhalista.insere(valor);
  }
  minhalista.imprime();

  minhalista.insereNoInicio(18);
  minhalista.insereNaPosicao(3,25);
  minhalista.imprime();
  minhalista.imprimeReverso();

  cout << minhalista.procura(0) << endl;
  cout << minhalista.procura(50) << endl;
  cout << minhalista.procura(12) << endl;

  // construtor de cópia
  cout << "Sobrecarga do construtor de cópia" << endl;    // Copia a lista
  lista outraLista(minhalista);
  outraLista.imprime();
  outraLista.imprimeReverso();

  // sobrecarga de operador de atribuição
  cout << "Sobrecarga do operador de atribuição" << endl;   // Copia a lista
  lista maisUmaLista;   // Cria uma nova lista
  maisUmaLista = outraLista;    // Essa nova lista Recebe o conteúdo de outra lista

  maisUmaLista.imprime();
  maisUmaLista.imprimeReverso();

  // Remover no fim alguns elementos
  cout << "Após remocao no fim:" << endl;
  maisUmaLista.removeNoFim();
  maisUmaLista.removeNoFim();

  maisUmaLista.imprime();
  maisUmaLista.imprimeReverso();

  // Remover no fim alguns elementos
  maisUmaLista.removeNoInicio();
  maisUmaLista.removeNoInicio();

  maisUmaLista.imprime();
  maisUmaLista.imprimeReverso();

  return 0;
}
