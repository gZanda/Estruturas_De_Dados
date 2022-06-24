#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

typedef int dado;

class MaxHeap{
  private:
    dado* Heap;   // Ponteiro que é direcionado ao vetor que reserva os valores de cada nó
    int Capacidade;   // Quantidade máxima de dados
    int Tamanho;    // Quantidade de "espaços" ocupados no vetor
    inline int Pai(int i);
    inline int Esquerdo(int i);
    inline int Direito(int i);
    void Arruma();    // heapify (constroi o heap e arruma com corrige descendo da metade pra cima)   // auxiliar
    void CorrigeDescendo(int i);  // auxiliar
    void CorrigeSubindo(int i);   // auxiliar

  public:
    MaxHeap(int cap);   // construtor que apenas cria o heap ( USADO SOMENTE NO INSET )
    MaxHeap(dado vet[], int tam);   // construtor com tamanho ( USADO QUANDO SE TEM O VETOR COMPLETO, USA O ARRUMA() )
    ~MaxHeap();
    void Imprimir();    // Imprimir o vetor do heap ( ESSA É APENAS DIDÁTICA )
    dado EspiaRaiz();   // ?
    dado RetiraRaiz();  // ?
    void Inserir(dado d);   // Método insert (Usado para inserir um valor ao heap - depois é aplicado "CorrigeSubindo")
};

MaxHeap::MaxHeap(int cap){    // construtor do caso de INSERT
  Capacidade = cap;
  Heap = new dado[cap];   // O ponteiro HEAP é apontado para o Vetor criado com a cpacidade fornecida
  Tamanho = 0;
}

MaxHeap::MaxHeap(dado vet[], int tam){    // construtor que já recebe o vetor com os dados preenchidos - usado no caso de heapify
  Capacidade = tam;
  Heap = new dado[Capacidade];    // O ponteiro é apontado ao vetor criado

  memcpy(Heap, vet, tam*sizeof(dado));    // copia o "vet" de dados para o vetor "HEAP"; Heap = Destino ; Vet = Endereço de memória; Tamanho em bytes

  /*
  for(int i = 0; i<tam; i++){   // for de copia  "memcpy" faz a cópia mais eficientemente
    Heap[i] = vet[i];
  }
  */

  Tamanho = tam;
  Arruma();
}

MaxHeap::~MaxHeap(){
  delete[] Heap;     // Deleta o vetor de dados que foi alocado dinamicamente ( tanto em caso de INSERT como em HEAPIFY )
}

void MaxHeap::Arruma(){    // método chamado pelo construtor do caso de HEAPIFY
  for(int i = (Tamanho/2-1); i >= 0; i--){    // COMEÇA na METADE, ou seja, RAIZ = 0
    CorrigeDescendo(i);
  }
}

int MaxHeap::Pai(int i){  // método que retorna o index pai (PARA VETOR QUE COMEÇA EM 0)
  return (i-1)/2;

}

int MaxHeap::Esquerdo(int i){   // método que retorna o index do  filho esquerdo (PARA VETOR QUE COMEÇA EM 0)
  return 2*i+1;
}

int MaxHeap::Direito(int i){    // método que retorna o index do filho direito (PARA VETOR QUE COMEÇA EM 0)
  return 2*i+2;
}

void MaxHeap::CorrigeDescendo(int i){   // método CorrigeDescendo ( É CHAMADA DENTRO DO MÉTODO "Arruma()" - HEAPIFY)
  int esq = Esquerdo(i);    // FILHO ESQUERDO
  int dir = Direito(i);   // FILHO DIREITO
  int maior = i;    // esse "i" é o nó da METADE do heap ( nó pai desses esquerdo e direito a cima )

  if(( esq < Tamanho ) and ( Heap[esq] > Heap[maior] )){    // verifica o tamanho primeiro, depois verifica em relação ao pai
    maior = esq;
  }

  if(( dir < Tamanho ) and ( Heap[dir] > Heap[maior] ) ){   // verifica o tamanho primeiro pra não acessar memória indevida, depois verifica o pai
    maior = dir;
  }

  if (maior != i){    // Aqui troca o pai pelo filho com MAIOR valor ( encontrado através da verificação )
    swap(Heap[i], Heap[maior]);   // usa swap para trocar sem ter q usar variável auxiliar (vem da cstlib);
    CorrigeDescendo(maior);   // Chama a corrige descendo novamente com o nó que acabou de descer, no caso com o pai  (SWAP TROCA APENAS O VALOR, POR ISSO É O "maior" que entra como parâmetro)
  }
}

void MaxHeap::CorrigeSubindo(int i){    // método corrige subindo (usado em INSERT)
  int p = Pai(i);   // Encontra o pai dessa última folha que foi inserida ( pois i = tamanho )
  if(Heap[i] > Heap[p]){
    swap(Heap[i],Heap[p]);
    CorrigeSubindo(p);     // Chama corrige subindo com o valor que acabou de subir
  }
}

dado MaxHeap::EspiaRaiz(){
  return Heap[0];
}

dado MaxHeap::RetiraRaiz(){    // RAIZ == INDEX 0 do vetor
  if( Tamanho == 0 ){
    cerr << "Erro ao retirar raiz" << endl;
    exit( EXIT_FAILURE);
  }
  dado aux = Heap[0];
  swap(Heap[0], Heap[Tamanho-1]);   // Troca  A RAIZ com o valor da última posição do vertor
  Tamanho--;    // Reduz o Tamanho para que a corrige descendo não mexa nesse que vc acabou de "remover" mas ele continua lá ( só não é acessável )
  CorrigeDescendo(0);  // Chama a corrige descendo para organizar a do index 0 ( que contém o valor que tava lá no último index)
  return aux;
}

void MaxHeap::Imprimir(){    // Imprimi o vetor
  for(int i = 0; i< Tamanho; i++){
    cout << Heap[i] << ' ';
  }
  cout << endl;
}

void MaxHeap::Inserir(dado d){     // Insere um valor na última posição ( se ela não for igual ao tamanho )
  if(Tamanho == Capacidade){    // Se o vetor estiver cheio
    cerr << "Erro ao inserir" << endl;
    exit(EXIT_FAILURE);
  }
  Heap[Tamanho] = d;    // Insere o valor na última posição ( afinal, só está ocupado até tamanho -1 )
  CorrigeSubindo(Tamanho);    // Chama corrige subindo passando o index do tamanho
  Tamanho++;
}

int main(){

  int Tam = 13;
  dado Vet[] = {50,2,90,230,43,8,34,66,100,110,3,13};

  MaxHeap* h = new MaxHeap(Vet,Tam);    // aqui já pe chamado ARRUMA();

  h->Imprimir();    // Imprime como ficou dps de arrumado

  for(int i = 0; i< Tam; i++){
    cout << h->RetiraRaiz() << " : ";   // Retira a raiz e aplica corrige descendo para organizar
    h->Imprimir();    // Imprimir como ficou sem a raiz
  }
  cout << endl;

  for(int i = 0; i< Tam; i++){
    h->Inserir(Vet[i]);     // Insere o dado aramazenado em Vet[i], aqui já aplica corrige subindo
  }

  h->Imprimir();  // Imprime como ficou após todas as inserções

  for(int i = 0; i< Tam; i++){
    cout << h->RetiraRaiz() << " : ";
    h->Imprimir();
  }

  delete h;

  // Basicamente: o primiro bloco recebe um vetor já pronto, aplica ARRUMA() e vai retirando as raízes até acabar;
  // Em seguida : o segundo bloco vai inserindo novamente esses valores "retirados" (do index 1 até o index do tamanho novamente );

  return 0;

}
