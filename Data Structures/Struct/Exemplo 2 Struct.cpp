#include <iostream>
using namespace std;

struct Compadres{
    string Nome,Alimento1,Alimento2;
    int Quantidade1,Quantidade2;
};

struct Alimentos{
    string Nome;
    int Quantidade;
};

void InserirAlimento(Alimentos VetorAlimento[], int &tam, string NomeAlimento, int Quantidade){
    int posicao= -1;
    int i=0;

    while((i<tam) and (VetorAlimento[i].Nome!=NomeAlimento)){
        i++;
    }
    if(i<tam){
        VetorAlimento[i].Quantidade += Quantidade;
    }
    else{
        VetorAlimento[i].Nome=NomeAlimento;
        VetorAlimento[i].Quantidade=Quantidade;
        tam++;
    }
}

int main(){
    int N;
    cin>>N;

    Compadres VetorCompadres[N];
    for(int i=0;i<N;i++){
        cin>>VetorCompadres[i].Nome;
        cin>>VetorCompadres[i].Alimento1;
        cin>>VetorCompadres[i].Quantidade1;
        cin>>VetorCompadres[i].Alimento2;
        cin>>VetorCompadres[i].Quantidade2;
    }

    Alimentos VetorAlimentos[2*N];
    int QuantiadeAlimentos=0;
    for(int i=0;i<N;i++){
        InserirAlimento(VetorAlimentos,QuantiadeAlimentos,VetorCompadres[i].Alimento1,VetorCompadres[i].Quantidade1);
        InserirAlimento(VetorAlimentos,QuantiadeAlimentos,VetorCompadres[i].Alimento2,VetorCompadres[i].Quantidade2);
    }

    for(int i=0;i<QuantiadeAlimentos;i++){
        cout<<VetorAlimentos[i].Nome<<" "<<VetorAlimentos[i].Quantidade<<endl;
    }

    return 0;
}
