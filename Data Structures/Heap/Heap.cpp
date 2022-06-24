#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef int dado;

class MaxHeap{
  private:
    dado* Heap;
    int Capacidade;
    int Tamanho;
    inline int Pai(int i);
    inline int Esquerdo(int i);
    inline int Direito(int i);
    void Arruma();    // heapify (constroi o heap e arruma com corrige descendo da metade pra cima)   // auxiliar
    void CorrigeDescendo(int i);  // auxiliar
    void CorrigeSubindo(int i);   // auxiliar

  public:
    MaxHeap(int cap);   // construtor que apenas cria o heap
    MaxHeap(dado vet[], int tam);   // construtor com tamanho
    ~MaxHeap();
    void Imprimir();    // Imprimir o vetor do heap "ESSA É APENAS DIDÁTICA"
    dado EspiaRaiz();
    dado RetiraRaiz();
    void insere(dado d);
};

MaxHeap::MaxHeap(int cap){
  Capacidade = cap;
  Heap = new dado[cap];
  Tamanho = 0;
}

MaxHeap::MaxHeap(dado vet[], int tam){
  Capacidade = tam;
  Heap = new dado[Capacidade];

  memcpy(Heap, vet, tam*sizeof(dado));

  /*
  for(int i = 0; i<tam; i++){   // for de copia  "memcpy" faz a cópia mais eficientemente
    Heap[i] = vet[i];
  }
  */

  Tamanho = tam;
  Arruma();
}

MaxHeap::~MaxHeap(){
  delete[] Heap;
}

void MaxHeap::Arruma(){
  for(int i = (Tamanho/2-1); i >= 0; i--){    // COMEÇA EM 0, ou seja, RAIZ = 0
    CorrigeDescendo(i);
  }
}

int MaxHeap::Pai(int i){  // método que retorna o pai
  return (i-1)/2;

}

int MaxHeap::Esquerdo(int i){   // método que retorna esquerdo
  return 2*i+1;
}

int MaxHeap::Direito(int i){    // método que retorna o direito
  return 2*i+2;
}

void MaxHeap::CorrigeDescendo(int i){   // método CorrigeDescendo
  int esq = Esquerdo(i);
  int dir = Direito(i);
  int maior = i;

  if(( esq < Tamanho ) and ( Heap[esq] > Heap[maior] )){    // verifica o tamanho primeiro pra não acessar memória indevida
    maior = esq;
  }

  if(( dir < Tamanho ) and ( Heap[dir] > Heap[maior] ) ){   // verifica o tamanho primeiro pra não acessar memória indevida
    maior = dir;
  }

  if (maior != i){
    swap(Heap[i], Heap[maior]);   // usa swap para trocar sem ter q usar variável auxiliar (vem da cstlib);
    CorrigeDescendo(maior);
  }
}

void MaxHeap::CorrigeSubindo(int i){    // método corrige subindo
  int p = Pai(i);
  if(Heap[i] > Heap[p]){
    swap(Heap[i],Heap[p]);
    CorrigeSubindo(p);
  }
}

dado MaxHeap::EspiaRaiz(){
  return Heap[0];
}

dado MaxHeap::RetiraRaiz(){
  if( Tamanho == 0 ){
    cerr << "Erro ao retirar raiz" << endl;
    exit( EXIT_FAILURE);
  }
  dado aux = Heap[0];
  swap(Heap[0], Heap[Tamanho-1]);
  Tamanho--;    // tem que decrementar o tamanho para que a corrige descendo não mecha onde vc acabou de inserir
  CorrigeDescendo(0);
  return aux;
}

void MaxHeap::Imprimir(){
  for(int i = 0; i< Tamanho; i++){
    cout << Heap[i] << ' ';
  }
}

void MaxHeap::insere(dado d){
  if(Tamanho == Capacidade){
    cerr << "Erro ao inserir" << endl;
    exit(EXIT_FAILURE);
  }
  Heap[Tamanho] = d;
  CorrigeSubindo(Tamanho);
  Tamanho++;
}

int main(){

  int Tam = 13;
  dado Vet[] = {50,2,90,230,43,8,34,66,100,110,3,13};

  MaxHeap* h = new MaxHeap(Vet,Tam);

  h->Imprimir();
  cout << endl;
  for(int i = 0; i< Tam; i++){
    cout << h->RetiraRaiz() << " : ";
    h->Imprimir();
    cout << endl;
  }
  cout << endl;

  for(int i = 0; i< Tam; i++){
    h->insere(Vet[i]);
  }

  h->Imprimir();
  cout << endl;
  for(int i = 0; i< Tam; i++){
    cout << h->RetiraRaiz() << " : ";
    h->Imprimir();
    cout << endl;
  }
  delete h;

  return 0;

}
