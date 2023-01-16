#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define quantContatos 10

typedef struct contato {
	char nome[20];
	char sobrenome[20];
	long telefone;
	char email[20];
} Contato;

enum opcoes{
	SAIR,
	ADICIONAR,
	REMOVER,
	VER,
	EDITAR,
	SHREK
};

void esperaEnter() {
	puts("Aperte enter pra continuar");
	while( getchar() != '\r' && getchar() != '\n');
}

void limpaContatos(int contatosLength, Contato *contatos) {
    for (int i = 0; i < contatosLength; i++){
        strcpy(contatos[i].nome, "\0");
		strcpy(contatos[i].sobrenome, "\0");
		contatos[i].telefone = 0;
		strcpy(contatos[i].email, "\0");
    }
}

void printaPosicoesLivres(int contatosLength, int *posicoes) {
	printf("Posições disponíveis: \n");
	for (int i = 0; i < contatosLength; i++) {
		if (i % 10 == 0)
			printf("\n");
		if (!posicoes[i])
			printf("%d ", i+1);
	}
}

void printaPosicoesOcupadas(int contatosLength, int *posicoes) {
	printf("Posições para agir: ");
	for (int i = 0; i < contatosLength; i++) {
		if (posicoes[i])
			printf("%d ", i+1);
	}
}

int getPosicao(int *posicoesOcupadas) {
	int posicao;
	puts("\nDiga qual contato voce deseja agir:");
	scanf("%d", &posicao);
	return --posicao;
}
    
int contatoExiste(Contato *contato){
    return contato->nome[0];
}

int *espacosDisponiveis(int contatosLength, Contato *contatos) {
	int *posicoes = malloc(contatosLength * sizeof(contatos[0]));
	if(!posicoes)
		return NULL;
	for (int i = 0; i < contatosLength; i++) {
		if (contatoExiste(&contatos[i]))
			posicoes[i] = i+1;
	}
	return posicoes;
}

void excluiInformacoes(Contato *contato) {
	strcpy(contato->nome, "\0");
    strcpy(contato->sobrenome, "\0");
    contato->telefone = 0;
    strcpy(contato->email, "\0");
}

int taDisponivel(int contatosLength, int posicao, int *posicoesOcupadas) {
	if (posicao >= 0 && posicao < contatosLength)
		return !posicoesOcupadas[posicao];
	else 
		return 0;
}

int removeContato(int contatosLength, Contato *contatos){
	int *posicoesOcupadas = espacosDisponiveis(contatosLength, contatos);
	printaPosicoesOcupadas(contatosLength, posicoesOcupadas);
	int posicao = getPosicao(posicoesOcupadas);
	if(!taDisponivel(contatosLength, posicao, posicoesOcupadas)) {
		excluiInformacoes(&contatos[posicao]);
		return 1;
	}
	else {
		printf("Essa posição está vazia!\n");
		return 0;
	}
}

void printaContatos(int contatosLength, Contato *contatos) {
	printf("\ntamanho %d\n\n", contatosLength);
	for (int i = 0; i < contatosLength; i++) {
		if (contatoExiste(&contatos[i])) {
			printf("%d:", i+1);
            printf(
                "\t%s\n \t%s\n \t%ld\n \t%s\n", 
                contatos[i].nome,
                contatos[i].sobrenome,
                contatos[i].telefone,
                contatos[i].email
            );
			printf("\n");
		}
	}
}


void nome(Contato *contato) {
	printf("Nome: ");
	scanf("%s", contato->nome);
}

void sobrenome(Contato *contato) {
	printf("Sobrenome: ");
	scanf("%s", contato->sobrenome);
}

void telefone(Contato *contato) {
	printf("Telefone: ");
	scanf("%ld", &contato->telefone);
}

void email(Contato *contato) {
	printf("Email: ");
	scanf("%s", contato->email);
}

void perguntaEdicao(Contato *contato) {
	int escolha;
	puts("O que você deseja editar? \n(1) Nome\n(2) Sobrenome\n(3) Telefone\n(4) Email");
	scanf("%d", &escolha);
	switch (escolha){
	case 1:
		nome(contato);
		break;
	case 2:
		sobrenome(contato);
		break;
	case 3:
		telefone(contato);
		break;
	case 4:
		email(contato);
		break;
	}
}

int editaContato(int contatosLength, Contato *contatos) {
	int *posicoesOcupadas = espacosDisponiveis(contatosLength, contatos);
	printaContatos(contatosLength, contatos);
	printaPosicoesOcupadas(contatosLength, posicoesOcupadas);
	int posicao = getPosicao(posicoesOcupadas);
	if(!taDisponivel(contatosLength, posicao, posicoesOcupadas)) {
		perguntaEdicao(&contatos[posicao]);
		return 1;
	}
	else {
		printf("Essa posição está vazia!\n");
		return 0;
	}
}

void perguntaInformacoes(Contato *contato) {
	nome(contato);
	sobrenome(contato);
	telefone(contato);
	email(contato);
}

int adicionaContato(int contatosLength, Contato *contatos){
	int *posicoesOcupadas = espacosDisponiveis(contatosLength, contatos);
	printaPosicoesLivres(contatosLength, posicoesOcupadas);
	int posicao = getPosicao(posicoesOcupadas);
	if(taDisponivel(contatosLength, posicao, posicoesOcupadas)){
		perguntaInformacoes(&contatos[posicao]);
		return 1;
	} 
	else {
		printf("Essa posição está ocupada!\n");
		return 0;
	}
}

void inicializaContatos(int contatosLength, Contato *contatos) {
	Contato *primeiro = &contatos[0];
	Contato *meio = &contatos[contatosLength/2-1];
	Contato *ultimo = &contatos[contatosLength-1];
	strcpy(primeiro->nome, "Everson");
	strcpy(primeiro->sobrenome, "Um");
	primeiro->telefone = 123456789;
	strcpy(primeiro->email, "email.com");

	strcpy(meio->nome, "Everson");
	strcpy(meio->sobrenome, "Dois");
	meio->telefone = 987654321;
	strcpy(meio->email, "roger.com");
	
	strcpy(ultimo->nome, "Everson");
	strcpy(ultimo->sobrenome, "Pi");
	ultimo->telefone = 314159265;
	strcpy(ultimo->email, "zanella.com");
}

void shrek(int contatosLength, Contato *contatos) {
	for (int i = 0; i < contatosLength; i++){
		strcpy(contatos[i].nome, "ogros tem camadas\n");
		strcpy(contatos[i].sobrenome, "SHREK LANCHES");
		contatos[i].telefone = 3532919486;
		strcpy(contatos[i].email, "\n\thttps://www.youtube.com/watch?v=gagePw3QA3U");
	}
}

int perguntaAcoes() {
	int opcao;
	puts("O que você deseja realizar?");
	printf("\
1: Adicionar contato\n\
2: Remover contato\n\
3: Ver contatos\n\
4: Editar contato\n\
5: Shrek\n\n\
0: Sair\n");
	scanf("%d", &opcao);
	return opcao;
}

void perguntasInterface(int contatosLength, Contato *contatos) {
	int opcao = -1;
	while(opcao != SAIR){
		opcao = perguntaAcoes();
		switch (opcao){
		case ADICIONAR:
			if(adicionaContato(contatosLength, contatos))
				puts("\nContato adicionado! ");
			break;
		case REMOVER:
			if(removeContato(contatosLength, contatos))
				puts("\nContato excluido! ");
			break;
		case EDITAR:
			if(editaContato(contatosLength, contatos))
				puts("\nContato editado! ");
			break;
		case VER:
			printaContatos(contatosLength, contatos);
			break;
		case SHREK:
			shrek(contatosLength, contatos);
			puts("\nVoce foi SHREKADO ");
			break;
		case SAIR:
			puts("\nPrograma finalizado.\n");
			break;
		default:
			puts("\nEssa opcao nao existe!!");
			break;
		}
	esperaEnter();
	}
}

int main(void) {
	Contato *contatos;
	long contatosLength;
	puts("Diga quantos contatos terá sua lista telefonica");
	scanf("%ld", &contatosLength);
	contatos = malloc(contatosLength * sizeof(*contatos));
    limpaContatos(contatosLength, contatos);
	inicializaContatos(contatosLength, contatos);
	perguntasInterface(contatosLength, contatos);
	free(contatos);
}