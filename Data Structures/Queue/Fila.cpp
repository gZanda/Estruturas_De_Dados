#include <iostream>
using namespace std;

class noh{
  friend class Fila;
  private:
    string mPlaca;
    noh *mNext;
  public:
    noh(string Placa);   // construtor
    ~noh(){};
};

noh::noh(string Placa){
  mPlaca = Placa;
  mNext = NULL;   // Inicializando o ponteiro com NULL
};

class Fila{
  private:
    noh* mInicio;
    noh* mFim;     // Esse ponteiro é do tipo noh pois aponta para o "mTopo" que é um nó
    int mTamanho;

  public:
    Fila();
    ~Fila();
    void Enfileirar(string Placa);
    string Desenfileirar();
    int Desenfileirar(string Placa);
    int BuscarCarro(string Placa);
    int Tamanho();
    string getInicio();
};

Fila::Fila(){   // construtor
  mInicio = NULL;   // Inicializando o ponteiro com NULL
  mFim = NULL;
  mTamanho = 0;
}

Fila::~Fila(){    // Desconstrutor (desenfileira tudo da pílha)
  while(mTamanho > 0){
    Desenfileirar();
  }
}

int Fila::Tamanho(){    // Método de retornar tamanho da Fila
  return mTamanho;
}

string Fila::getInicio(){
  return mInicio->mPlaca;
}

void Fila::Enfileirar(string Placa){    // Método de enfileirar
  noh* novo = new noh(Placa);
  if(mTamanho == 0){
    mInicio = novo;
  }
  else{
    mFim -> mNext  = novo;
  }
  mFim = novo;
  mTamanho++;
}

string Fila::Desenfileirar(){    // Método de desemfileirar
  string Placa = mInicio -> mPlaca;
  noh* temp = mInicio;
  mInicio = temp -> mNext;
  delete temp;
  mTamanho--;
  if(mTamanho == 0){
    mFim = NULL;
  }
  return Placa;
};

int Fila::Desenfileirar(string Placa){    // Método de desemfileirar um carro específico
  string PlacaEspecifica = Placa;
  int nChecados = Tamanho();
  bool Encontrado = false;
  int Cont = 0;
  while( nChecados != 0 && Encontrado != true){
    Enfileirar(Desenfileirar());
    ++Cont;
    --nChecados;
    if( getInicio() == PlacaEspecifica ){
      Encontrado = true;
      cout<<"\nachei \n";
      cout << "\nInicio da fila: " << getInicio();
    }
  }
  if( getInicio() == PlacaEspecifica){
    cout << "\nta igual";
    Desenfileirar();
    ++Cont;
  }
  return Cont;
};

int main(){

  char Op = 'A';
  Fila F1;
  string Placa;
  int CarrosMovidos = 0;
  while(Op != 'S'){
    cin>>Op;
    switch(Op){

      case 'E':
        cout<<"caso b \n";
        cin >> Placa;
        F1.Enfileirar(Placa);
        break;

      case 'D':
        cout << "caso c \n";
        cin >> Placa;
        CarrosMovidos = F1.Desenfileirar(Placa);
        break;

      case 'S':
        cout<<"fim \n";
        break;

      case 'A':   // EXIBIR COMO A FILA ESTÁ
        while(F1.Tamanho() > 0){
          cout << F1.Desenfileirar() << ' ';
        }
        cout << "\ncarros movidos para desenfileirar: " << CarrosMovidos;
        break;

      default:
        cout<<"Invalido \n";
    }
  }
   // Aqui printar os carros


  cout<<endl;
  return 0;

};

