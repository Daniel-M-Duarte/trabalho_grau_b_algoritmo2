#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Variavel global com o  numero de contatos
#define NUM_CONTATOS 3
//Atributos da variavel tipo contato
typedef struct{
    char nome[25];
    char data_nasc[8];
    char email[50];
    char telefone[20];
}Contato;
//Ponteiro para cada contato
typedef struct{
  Contato *elemento;
  int qtdContato;
}ListaContato;

ListaContato *criarList ();
void insereContato (ListaContato *liPtr);
void listarContato (ListaContato *liPtr);
void removeContato (ListaContato *liPtr);
void pesquisaContato (ListaContato *liPtr);
void contato_final_lista(ListaContato *liPtr, Contato novoCont);
void liberaLista (ListaContato *liPtr);
char* lerStringSeguramente(char* string, int tamanho);

int main(void){
  //Declarando ponteiro
  ListaContato *listContato;
  listContato = criarList();
  Contato novoCont;
  void(*vet_ptr_funcao[])(ListaContato *liPtr) = {insereContato, listarContato,
  removeContato, pesquisaContato};
  int opcao;
  do{
  printf("\nBem vindo..."
  "\nDigite a opcao desejada "
  "\n1- Inserir"
  "\n2- Listar"
  "\n3- Remover"
  "\n4- Pesquisar"
  "\n0- Sair\n");
  scanf("%d", &opcao);
  fflush(stdin);
  if(opcao>=1 && opcao <=4){
  (*vet_ptr_funcao[opcao-1])(listContato);
  }else if (opcao !=0){
  printf("\nOpcao invalida\nDigite novamente...\n");
  }
  }
  while (opcao != 0);
  liberaLista(listContato);
}

//Cria lista e retorna endereço da lista criada...
ListaContato* criarList(){

    ListaContato *liPtr;
    //aloca "ListaContatos"...
    liPtr = malloc(sizeof(ListaContato));
    //Aloca (vetor) "elementos"...
    liPtr->elemento = malloc(NUM_CONTATOS * sizeof(Contato));

    if((liPtr != NULL)){
        liPtr->qtdContato = 0;
        printf("Alocando memoria para %d contatos\n", NUM_CONTATOS);
    }
    return liPtr;
}
//Funcção insere contato
void insereContato (ListaContato *liPtr){
  Contato novoCont;
  if (liPtr == NULL){
    printf("\nErro ao tentar inserir novo elemento na lista!\n");
    //return 0;
  }  else if (liPtr->qtdContato == NUM_CONTATOS){
    printf("\nLista cheia\nErro ao tentar acrescentar\n");
  }
  else{
    contato_final_lista (liPtr, novoCont);
    liPtr->qtdContato++;
    }
  }


//Funcao libera Lista
void liberaLista(ListaContato* liPtr){
    puts("Lista encerrada...");
    free(liPtr);
}
//Função inserir Contato
void contato_final_lista(ListaContato *liPtr, Contato novoCont){
  printf("Entre com os dados do contato:\n");
  printf("Nome: ");
  lerStringSeguramente(novoCont.nome, 25);
  printf("Data de nascimento: ");
  lerStringSeguramente(novoCont.data_nasc, 8);
  printf("E-mail: ");
  lerStringSeguramente(novoCont.email, 50);
  printf("Telefone (com ddd): ");
  lerStringSeguramente(novoCont.telefone, 20);
  liPtr->elemento[liPtr->qtdContato] = novoCont;
  printf("Inserindo registro no final da lista...\n");

}


//Função de lerStringSeguramente
char* lerStringSeguramente(char* string, int tamanho){
    if(fgets(string, tamanho, stdin) != NULL){
		/* Remove a nova linha (\n), caso ela tenha sido lida pelo fgets */
		int indiceUltimoCaractere = strlen(string) - 1;
		if(string[indiceUltimoCaractere] == '\n') {
			string[indiceUltimoCaractere] = '\0';
		}
		return string;
	}
	return NULL;
}

//Função de listar contato

void listarContato (ListaContato *liPtr){
  Contato novoCont;
  int i;
  if (liPtr->qtdContato > 0){
    printf("Numero de elementos da lista: %d\n", liPtr->qtdContato);
    for (i=0; i< liPtr->qtdContato; i++){
      printf("\nDados do contato %d:\n", i + 1);
      printf("-->> Nome: %s \n-->> Data de nascimento %s\n-->> Email: %s"
          "\n-->> telefone: %s \n",
          liPtr->elemento[i].nome,
          liPtr->elemento[i].data_nasc,
          liPtr->elemento[i].email,
          liPtr->elemento[i].telefone
        );
    }
  puts("");
}else{
  printf("Lista inexistente...");
}

}

void removeContato(ListaContato* liPtr){
    if(liPtr == NULL){
        printf("\nErroo");
    }else if(liPtr->qtdContato == 0){
        printf("\nLista vazia, nao ha contatos armazenados...");
    }else{
        liPtr->qtdContato--;
      printf("\nRemovido com sucesso..");
    }
}


void pesquisaContato (ListaContato *liPtr){
  char pesquisaNome[25];
  if(liPtr->qtdContato > 0 && liPtr->qtdContato <= NUM_CONTATOS ){
  printf("\nDigite 'NOME' do contato para iniciar a sua pesquisa: ");
  gets(pesquisaNome);
  for (int i = 0; i < liPtr->qtdContato; i++){
    if(strcmp(pesquisaNome,liPtr->elemento[i].nome)==0){
      printf("\nContato encontrado com sucesso no ID [%d]...\nDados da pesquisa:\n", i);
      printf("\tNome: %s \n\tData de nascimento %s\n\tEmail: %s"
          "\n\tTelefone: %s \n\t",
          liPtr->elemento[i].nome,
          liPtr->elemento[i].data_nasc,
          liPtr->elemento[i].email,
          liPtr->elemento[i].telefone
        );
    }else{
      printf("\nNenhum contato encontrado no ID [%d]..", i);
    }
  }
  }else
  printf("\nAgenda com 0 elementos, erro na pesquisa..");
  }
