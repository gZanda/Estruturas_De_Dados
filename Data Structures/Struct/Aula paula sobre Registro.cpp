#include <iostream>
using namespace std;
//declaração da struct

struct carro {
	int ano;
	string marca, cor;
};

void imprime (carro vetor[], int tamanho) {
	int i;
	cout<<"Dados de todos os carros"<<endl;
	for (i=0;i<tamanho;i++) {
		cout<<vetor[i].cor<<" "<<vetor[i].ano<<" "<<vetor[i].marca<<endl;
	}

	cout<<"Caracteres de string "<<endl;
	for (i=0;i<tamanho;i++) {
		for (int j=0; j<int (vetor[i].marca.length()); j++) {
			cout<<vetor[i].marca[j]<<" ";
		}
		cout<<endl;
	}

}

//buscar o carro mais velho e retornar o registro

carro buscarCarroVelho (carro vetor[], int tamanho ) {
	int i, posicao, velho=2022;
	for (i=0; i<tamanho; i++) {
		if (vetor[i].ano < velho ) {
			velho=vetor[i].ano;
			posicao = i;
		}
	}
	return vetor[posicao];

}

//buscar o carro mais velho e retornar a posicao
int buscarCarroVelhoPosicao (carro vetor[], int tamanho ) {
	int i, posicao, velho=2022;
	for (i=0; i<tamanho; i++) {
		if (vetor[i].ano < velho ) {
			velho=vetor[i].ano;
			posicao = i;
		}
	}
	return posicao;

}


//alterar o ano do mais velho para 2022
void alterar (carro vetor[], int tamanho, int novoAno) {
	int posicao = buscarCarroVelhoPosicao(vetor, tamanho);
	vetor[posicao].ano=novoAno;
}


int main () {
	int tamanho=3;
	carro vetor [tamanho];
	int i;
	for (i=0;i<tamanho;i++) {
		//acessar os elementos
		cin>>vetor[i].cor; //nomeVariavel[posicao].campo
		cin>>vetor[i].ano;
		cin>>vetor[i].marca;
	}
	//imprime(vetor,tamanho);

	//buscar o carro mais velho
	//carro velho;
	//velho=buscarCarroVelho(vetor,tamanho);
	//cout<<"Carro velho "<<velho.marca<<endl;

	//cout<<"Posicao do mais velho "<<buscarCarroVelhoPosicao (vetor,  tamanho);

	alterar (vetor, tamanho, 2020);
	imprime(vetor,tamanho);

}
