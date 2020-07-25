#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#define MAX 9999
#define TF 10000

/*
	Metodos de Pesquisa e Ordenacao
	
	Dev C++, Windows 10
	
	Aluno: Ana Paula Rodrigues Bellon

*/
class VETOR{
	public:
		long tl;
		long vetor[TF];
		bool ordenado;
	public:
		cria();
		void exibe();
		bool ordenaBolha();
		bool ordenaSelecao();
		bool ordenaInsercaoDireta();
		bool ordenaInsercaoBinaria();
		long BuscaExaustiva(long elem);
		long BuscaSequencial(long elem);
		long BuscaBinaria(long elem, long tam);
		long BuscaRecursiva(long elem, long inicio, long fim);
		void tempo();
};
VETOR::cria(){
	long i;
	srand(time(NULL));
	tl=TF;
	for(i=0;i<tl;i++){
		vetor[i]=rand()%MAX;
	}
	printf("\nO vetor foi criado!\n");
	ordenado=false;
}
void VETOR::exibe(){
	long i;
	printf("\n      ----  VETOR:  ----\n");
	for(i=0;i<tl;i++)
		printf("\n       Vetor[%2d]= %3d",i,vetor[i]);
	if(ordenado)
		printf("\n\n     Vetor Ordenado!\n");
	else
		printf("\n\n     Vetor Desordenado!\n");
	printf("\n      ------------------");
}
bool VETOR::ordenaBolha(){
	long i, j, aux;
	for(i=tl-1;i>0;i--){
		for(j=0;j<i;j++){
			if(vetor[j]>vetor[j+1]){
				aux=vetor[j];
				vetor[j]=vetor[j+1];
				vetor[j+1]=aux;
			}
		}
	}
	ordenado=true;
}
bool VETOR::ordenaSelecao(){
	long i,j,menor,posmenor,pergunta=0;
	for(i=0;i<tl;i++){
		menor=vetor[i];
		posmenor=i;
		for(j=i+1;j<tl;j++){
			if(vetor[j]<menor){
				pergunta++;
				menor=vetor[j];
				posmenor=j;
			}
		}
		vetor[posmenor]=vetor[i];
		vetor[i]=menor;	
	}
	ordenado=true;
	printf("\nOcorreram %d perguntas no Ordena Selecao\n",pergunta);
}
bool VETOR::ordenaInsercaoDireta(){
	long aux, i, j, posicao, troca=0;
	if(vetor[0]>vetor[1]){
		aux=vetor[0];
		vetor[0]=vetor[1];
		vetor[1]=aux;
		troca++;
	}
	for(i=2;i<tl;i++){
		aux=vetor[i];
		posicao=BuscaSequencial(vetor[i]);
		for(j=i;j>posicao;j--){
			vetor[j]=vetor[j-1];
			vetor[posicao]=aux;
		}
		troca++;
	}
	ordenado=true;
	printf("\nOcorreram %d remanejamentos no Ordena Insercao Direta\n",troca);
}
bool VETOR::ordenaInsercaoBinaria(){
	long aux, i, j, posicao, troca=0;
	if(vetor[0]>vetor[1]){
		aux=vetor[0];
		vetor[0]=vetor[1];
		vetor[1]=aux;
		troca++;
	}
	for(i=2;i<tl;i++){
		aux=vetor[i];
		posicao=BuscaBinaria(vetor[i],i-1);
		for(j=i;j>posicao;j--){
			vetor[j]=vetor[j-1];
			vetor[posicao]=aux;
		}
		troca++;
	}
	ordenado=true;
	printf("\nOcorreram %d remanejamentos no Ordena Insercao Binaria\n",troca);
}
long VETOR::BuscaExaustiva(long elem){
	long i=0, posicao=-1;
	while((elem!=vetor[i])&&(i<tl))
		i++;
	if((i<tl)&&(vetor[i]==elem))
		posicao=i;
	return posicao;
}
long VETOR::BuscaSequencial(long elem){
	int i=0, posicao=-1;
	while((elem>vetor[i])&&(i<tl))
		i++;
	if((i<tl)&&(elem<=vetor[i]))
		posicao=i;
	return posicao;
}
long VETOR::BuscaBinaria(long elem, long tam){
	long inicio=0,meio,fim;
	fim=tam;
	meio=(inicio+fim)/2;
	while((elem!=vetor[meio])&&(inicio<fim)){
		if(elem>vetor[meio])
			inicio=meio+1;
		else
			fim=meio;
		meio=(inicio+fim)/2;
	}
	if(elem>vetor[meio])
		return (meio+1);
	else
		return meio;
}
long VETOR::BuscaRecursiva(long elem, long inicio, long fim){
	long meio;
	if(inicio>fim)
		return -1;
	else{
		meio=(inicio+fim)/2;
		if(elem==vetor[meio])
			return meio;
		else if(elem<vetor[meio])
			BuscaRecursiva(elem,inicio,meio-1);
		else
			BuscaRecursiva(elem,meio+1,fim);
	}
}
void VETOR::tempo(){
	clock_t inicio, fim;
    double timebolha=0,timeselecao=0,timedireta=0,timebinaria=0; // double tem capacidade maior que o float
    // tempo OrdenaBolha
    cria();
    inicio=clock();
	ordenaBolha();
	fim=clock();
	timebolha=(double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);
	// tempo OrdenaSelecao
	cria();
	inicio=clock();
	ordenaSelecao();
	fim=clock();
	timeselecao=(double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);
	// tempo OrdenaInsercaoDireta
	cria();
	inicio=clock();
	ordenaInsercaoDireta();
	fim=clock();
	timedireta=(double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);
	// tempo OrdenaInsercaoBinaria
	cria();
	inicio=clock();
	ordenaInsercaoBinaria();
	fim=clock();
	timebinaria=(double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);
	printf("\nTempo de processamento dos metodos de ordenacao em um vetor de %d posicoes:\n",TF);
	printf("\n               |      Metodo        |  Tempo de Processamento  |");
	printf("\n               | Bolha              |    %4.5lf   segundos    |",timebolha);
	printf("\n               | Selecao            |    %4.5lf   segundos    |",timeselecao);
	printf("\n               | Direta             |    %4.5lf   segundos    |",timedireta);
	printf("\n               | Binaria            |    %4.5lf   segundos    |\n",timebinaria);
}
int main(){
	VETOR a=VETOR();
	long opcao=0,posicao,elem,i=0,j=TF;
	while(opcao!=12){
		printf("\n\n--------------------------------//--------------------------------");
		printf("\n        Programacao 2 - Metodos de Pesquisa e Classificacao\n");
		printf("\n 1 - Cria um vetor de %d elementos",TF);
		printf("\n 2 - Exibe o vetor");
		printf("\n 3 - Ordena pelo metodo Bolha");
		printf("\n 4 - Ordena pelo metodo Selecao");
		printf("\n 5 - Ordena pelo metodo Insercao Direta");
		printf("\n 6 - Ordena pelo metodo Insercao Binaria");
		printf("\n 7 - Busca Exaustiva de um elemento");
		printf("\n 8 - Busca Sequencial (apenas em vetor ja Ordenado)");
		printf("\n 9 - Busca Binaria (apenas em vetor ja Ordenado)");
		printf("\n 10 - Busca Recursiva Binaria (apenas em vetor ja Ordenado)");
		printf("\n 11 - Tempo de processamento dos metodos de ordenacao");
		printf("\n 12 - EXIT");
		printf("\n--------------------------------//--------------------------------");
		printf("\nEntre com a opcao desejada: ");
		scanf("%d",&opcao);
		system("cls");
		switch(opcao){
			case 1: system("cls");
					a.cria();
					break;
			case 2: system("cls");
					a.exibe();
					break;
			case 3: printf("\nAguarde...\n");
					a.ordenaBolha();
					printf("\nO vetor foi ordenado!");
					break;
			case 4: printf("\nAguarde...\n");
					a.ordenaSelecao();
					printf("\nO vetor foi ordenado!");
					break;
			case 5: printf("\nAguarde...\n");
					a.ordenaInsercaoDireta();
					printf("\nO vetor foi ordenado!");
					break;
			case 6: printf("\nAguarde...\n");
					a.ordenaInsercaoBinaria();
					printf("\nO vetor foi ordenado!");
					break;
			case 7: printf("\nEntre com o elemento a ser buscado: ");
					scanf("%d",&elem);
					posicao=a.BuscaExaustiva(elem);
					if(posicao!=-1)
						printf("\nO elemento %d esta na posicao %d do vetor",elem,posicao);
					else
						printf("\nO elemento %d nao foi encontrado",elem);
					break;
			case 8: if(a.ordenado){
						printf("\nEntre com o elemento a ser buscado: ");
						scanf("%d",&elem);
						posicao=a.BuscaSequencial(elem);
						if(posicao!=-1)
							printf("\nO elemento %d esta na posicao %d do vetor",elem,posicao);
						else
							printf("\nO elemento %d nao foi encontrado",elem);
					}
					else
						printf("\nO vetor nao esta ordenado!");
					break;
			case 9: if(a.ordenado){
						printf("\nEntre com o elemento a ser buscado: ");
						scanf("%d",&elem);
						posicao=a.BuscaBinaria(elem,TF);
						if(a.vetor[posicao]==elem)
							printf("\nO elemento %d esta na posicao %d do vetor",elem,posicao);
						else
							printf("\nO elemento %d nao foi encontrado, mas o local ideal para o inserir seria na posicao %d ",elem,posicao);
					}
					else
						printf("\nO vetor nao esta ordenado!");
					break;
			case 10:if(a.ordenado){
						printf("\nEntre com o elemento a ser buscado: ");
						scanf("%d",&elem);
						posicao=a.BuscaRecursiva(elem,i,j);
						if(posicao!=-1)
							printf("\nO elemento %d esta na posicao %d do vetor",elem,posicao);
						else
							printf("\nO elemento %d nao foi encontrado",elem);
					}
					else
						printf("\nO vetor nao esta ordenado!");
					break;
			case 11:printf("\nAguarde...\n");
					a.tempo();
					break;
					
		}
	}
	system("pause");
	return 0;
}
