#include <iostream>
using namespace std;

struct criancas {
    string Nome, Presente;
    int BoasAcoes, Travessuras;
};

int main(){
    int N,i;
    cin>>N;
    criancas VetorCriancas[N];
    bool TeveCriancaComPresente=false;
    for(i=0;i<N;i++){
        cin>>VetorCriancas[i].Nome;
        cin>>VetorCriancas[i].Presente;
        cin>>VetorCriancas[i].BoasAcoes;
        cin>>VetorCriancas[i].Travessuras;
    }

    i=0;
    for(i=0;i<N;i++){
        if(VetorCriancas[i].BoasAcoes>=VetorCriancas[i].Travessuras){
            cout<<VetorCriancas[i].Presente<<endl;
            TeveCriancaComPresente=true;
        }
    }
    if(TeveCriancaComPresente==false){
        cout<<"nada"<<endl;
    }
    return 0;
}
