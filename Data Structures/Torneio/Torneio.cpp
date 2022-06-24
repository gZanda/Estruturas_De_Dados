#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef int dado;
const int INVALIDO = -1;

class Torneio{
  private:
    dado* Heap;
    int Capacidade;
    int Tamanho;
    int InicioDados; // Prineiro nó folha
    inline int Pai(int i);
    inline int Esquerdo(int i);
    inline int Direito(int i);
    void Arruma();    // heapify (constroi o heap e arruma com corrige descendo da metade pra cima)   // auxiliar
    void CopiaMaior(int i);  // auxiliar
    void CopiaSubindo(int i);   // auxiliar

  public:
    Torneio(int nFolhas);   // construtor que apenas cria o heap
    Torneio(dado vet[], int tam);   // construtor com tamanho
    ~Torneio();
    void Imprimir();    // Imprimir o vetor do heap "ESSA É APENAS DIDÁTICA"
    dado RetiraRaiz();
    void Inserir(dado d);
};

Torneio::Torneio(int nFolhas){
  Capacidade = 1;
  while( Capacidade < nFolhas){
    Capacidade *= 2;
  }
  cout << endl <<"Capacidade aqui: " << Capacidade << endl;
  Capacidade = Capacidade -1 + nFolhas;

  Heap = new dado[Capacidade];
  InicioDados = Capacidade - nFolhas;

  cout << "InicioDados: " << InicioDados << endl;
  cout << "capacidade: " << Capacidade << endl;

  for( int i = 0; i < Capacidade; i++){
    Heap[i] = INVALIDO;
  }
}

Torneio::Torneio(dado vet[], int tam){
  Capacidade = 1;
  while(Capacidade < tam ){
    Capacidade *= 2;
  }
  cout << endl <<"Capacidade aqui: " << Capacidade << endl;
  Capacidade = Capacidade -1 + tam;

  Heap = new dado[Capacidade];
  InicioDados = Capacidade - tam;

  cout << "InicioDados: " << InicioDados << endl;
  cout << "capacidade: " << Capacidade << endl;


  memcpy(&Heap[InicioDados],vet, tam*sizeof(dado));

  Tamanho = tam;
  Arruma();

  /*
  for(int i = 0; i<tam; i++){   // for de copia  "memcpy" faz a cópia mais eficientemente
    Heap[i] = vet[i];
  }
  */
}

Torneio::~Torneio(){
  delete[] Heap;
}

void Torneio::Arruma(){
  // Aplica recebe maior na primeira metade dos elementos
  cout << "arruma" << InicioDados -1 << endl;
  for(int i = InicioDados -1; i >= 0; i--){
    CopiaMaior(i);
  }
}

int Torneio::Pai(int i){  // método que retorna o pai
  return (i-1)/2;

}

int Torneio::Esquerdo(int i){   // método que retorna esquerdo
  return 2*i+1;
}

int Torneio::Direito(int i){    // método que retorna o direito
  return 2*i+2;
}

void Torneio::CopiaMaior(int i){   // método CorrigeDescendo
  int esq = Esquerdo(i);
  int dir = Direito(i);
  int maior = INVALIDO;
  cout << " i: "<< i << " e: " << esq << " d: " << dir << endl;
  if(esq < Capacidade){
    if(( dir < Capacidade ) and ( Heap[dir] > Heap[esq])){    // verifica o tamanho primeiro pra não acessar memória indevida
      maior = dir;
    }
    else{
      maior = esq;
    }
    Heap[i] = Heap[maior];
  }
  else{
    Heap[i] = INVALIDO;
  }

}

void Torneio::CopiaSubindo(int i){    // método corrige subindo
  int p = Pai(i);
  if(Heap[i] > Heap[p]){
    Heap[p] = Heap[i];
    CopiaSubindo(p);
  }
}

/*
dado Torneio::EspiaRaiz(){
  return Heap[0];
}
*/

/*
dado Torneio::RetiraRaiz(){
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
*/

void Torneio::Imprimir(){
  for(int i = 0; i< Capacidade; i++){
    cout << Heap[i] << ' ';
  }
  cout << endl;
}

void Torneio::Inserir(dado d){
  if(Tamanho == Capacidade){
    cerr << "Erro ao inserir" << endl;
    exit(EXIT_FAILURE);
  }
  Heap[Tamanho + InicioDados] = d;
  CopiaSubindo(Tamanho + InicioDados);
  Tamanho++;
}

int main(){

  int tam = 9;
  dado vet1[] = {50,2,90,20,230,43,8,34,66};

  Torneio *h = new Torneio(vet1,tam);
  h->Imprimir();
  delete h;

  tam = 13;
  dado vet2[] = {50,2,90,20,230,43,8,34,66,100,110,3,13};

  h = new Torneio(vet2,tam);
  h->Imprimir();
  delete h;

  tam = 9;    // recurso de inserção
  h = new Torneio(9);
  for(int i=0; i < tam; i++){
    h->Inserir(vet1[i]);
    h->Imprimir();
  }
  delete h;

  return 0;

}
