#include <iostream>
using namespace std;

class noh{
  friend class Pilha;
  private:
    int mValor;
    noh* mNextNoh;   // É um ponteiro do tipo noh* mesmo, pois ele aponta para outro nó (Essa é a lógica da pilha)
  public:
    noh(int valor);   // construtor
    ~noh(){};
};

noh::noh(int valor){
  mValor = valor;
  mNextNoh = NULL;   // Inicializando o ponteiro com NULL
};

class Pilha{
  private:
    noh* mTopo;   // Esse ponteiro é do tipo noh pois aponta para o "mTopo" que é um nó
    int mTamPilha;

  public:
    Pilha();
    ~Pilha();
    void empilha(int valor);
    int desempilha();
    unsigned tamanho();
    void limpaPilha();
    bool vazia();
};

Pilha::Pilha(){   // construtor
  mTopo = NULL;   // Inicializando o ponteiro com NULL
  mTamPilha = 0;
}

Pilha::~Pilha(){    // Desconstrutor
  limpaPilha();
}

void Pilha::limpaPilha(){    // Método de Limpar Pilha
  while(mTamPilha > 0){
    desempilha();
  }
}

unsigned Pilha::tamanho(){    // Método de retornar tamanho da pilha
  return mTamPilha;
}

bool Pilha::vazia(){    // Método vazia
  return (mTamPilha==0);
}

void Pilha::empilha(int valor){    // Método de empilhar
  //cout << "Topo antes de empilhar :" << mTopo << endl;
  noh* novo = new noh(valor);
  novo -> mNextNoh =  mTopo;                     // o operador "->" é a mesma coisa que o "." mas utilizado para quando se acessa PONTEIRO.
  mTopo = novo;
  mTamPilha++;
  //cout << "Topo depois de empilhar: " << mTopo << endl;
  //cout << "Próximo do Topo: " << mTopo -> mNext << endl;
}

int Pilha::desempilha(){    // Método de desempilhar
  int valor = mTopo -> mValor;
  noh* temp = mTopo;
  mTopo = mTopo -> mNextNoh;
  delete temp;
  mTamPilha--;
  return valor;
};

int main(){
  Pilha p1;
  int n;
  cin>>n;

  while(n != -1){
    p1.empilha(n);
    cin>>n;
  }

  cout  << "Tamanho: " << p1.tamanho() << endl;

  cout << "Elementos: ";

  while(p1.tamanho()>0){
    cout << p1.desempilha() << ' ' ;
  }

  cout<<endl;
  return 0;

};

