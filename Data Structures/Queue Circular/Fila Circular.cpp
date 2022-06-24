#include <iostream>
using namespace std;

class FilaCircular{
  private:
    int mInicio;
    int mFim;
    int* mDados;
    int mCapacidade;     // Total
    int mTamanho;   // Ocupadas

  public:
    FilaCircular(int Capacidade = 10);
    ~FilaCircular();
    void Enfileirar(int Valor);
    int Desenfileirar();
    int Desenfileirar(string Placa);
    int Tamanho();
};

FilaCircular::FilaCircular( int Capacidade){   // construtor
  mInicio = -1;   // Inicializando o ponteiro com NULL
  mFim = -1;
  mCapacidade = Capacidade;
  mDados = new int[mCapacidade];
  mTamanho = 0;
}

FilaCircular::~FilaCircular(){    // Desconstrutor (desenfileira tudo da pílha)
  delete[] mDados;
}

int FilaCircular::Tamanho(){    // Método de retornar tamanho da Fila
  return mTamanho;
}

void FilaCircular::Enfileirar(int Valor){    // Método de enfileirar
  if(mTamanho <= mCapacidade){
    mFim++;
    mFim = mFim % mCapacidade;
    mDados[mFim] = Valor;
    if(mTamanho == 0){
      mInicio++;
    }
    mTamanho++;
  }
  else{
    cerr << "ERRO, PILHA CHEIA" << endl;
  }
}

int FilaCircular::Desenfileirar(){    // Método de desemfileirar
  if(mTamanho > 0){
    int valor = mDados[mInicio];
    mTamanho--;
    if(mTamanho > 0){
    mInicio++;
    mInicio = mInicio % mCapacidade;
    }
    else{
      mInicio = -1;
      mFim = -1;
    }
  return valor;
  }
  else{
    cerr << "ERRO, PILHA VAZIA" << endl;
    return -1;
  }
};

int main(){

  FilaCircular F1(12);
  int num;

  for(int i =0; i < 8; i++){
    cin >> num;
    F1.Enfileirar(num);
  }

  cout << "tamanho: " << F1.Tamanho();

  cout << endl <<"5 elementos: ";

  for(int i =0; i < 5; i++){
    cout << F1.Desenfileirar() << ' ';
  }
  cout << endl;

  for(int i =0; i < 8; i++){
    cin >> num;
    F1.Enfileirar(num);
  }

  cout << "tamanho: " << F1.Tamanho() << endl;

  cout << endl << "5 elementos: ";

  for(int i =0; i < 5; i++){
    cout << F1.Desenfileirar() << ' ';
  }
  cout << endl;

  while(F1.Tamanho() != 0){
    cout << F1.Desenfileirar() << ' ';
  }

  cout<<endl;
  return 0;

};

