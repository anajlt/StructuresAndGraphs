#include <iostream>
using namespace std;

// Estrutura do n� da �rvore
// Cada n� armazena um valor e tem ponteiros para os n�s � esquerda (valores menores) e � direita (valores maiores).
struct No {
    int valor;
    No* esquerda;
    No* direita;
};

// Fun��o: novoNo()
// cria dinamicamente um novo n� na mem�ria e inicializa seus ponteiros como NULL.
No* novoNo(int valor) {
    No* no = new No;        // aloca mem�ria para o novo n�
    no->valor = valor;      // armazena o valor passado
    no->esquerda = NULL;    // nenhum filho � esquerda inicialmente
    no->direita = NULL;     // nenhum filho � direita inicialmente
    return no;              // retorna o ponteiro para o novo n�
}

// Fun��o: inserir()
// insere um valor na �rvore bin�ria de busca (BST)
// se o valor for menor que o da raiz -> vai para a esquerda
// se for maior -> vai para a direita
// caso a posi��o esteja vazia, cria um novo n�
No* inserir(No* raiz, int valor) {
    if (raiz == NULL)
        return novoNo(valor);  // caso base: cria um novo n�

    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);  // insere � esquerda
    else if (valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor);    // insere � direita

    // caso o valor j� exista, n�o faz nada (evita duplicatas)
    return raiz;
}

// Fun��o: listar()
// percorre a �rvore em ordem crescente (In-Order)
// esquerda -> raiz -> direita (valores em ordem)
void listar(No* raiz) {
    if (raiz != NULL) {
        listar(raiz->esquerda);      // percorre sub�rvore esquerda
        cout << raiz->valor << " ";  // exibe o valor atual
        listar(raiz->direita);       // percorre sub�rvore direita
    }
}

// Fun��o: encontrarMaior()
// encontra o maior valor presente na �rvore
// o maior valor sempre estar� no n� mais � direita
int encontrarMaior(No* raiz) {
    if (raiz == NULL) {
        cout << "A arvore esta vazia!\n";
        return -1; // valor simb�lico quando a �rvore est� vazia
    }

    // Se n�o h� filho � direita, este � o maior valor
    if (raiz->direita == NULL)
        return raiz->valor;

    // Caso contr�rio, continua descendo � direita
    return encontrarMaior(raiz->direita);
}

// Fun��o principal (main)
int main() {
    No* raiz = NULL;  // ponteiro para a raiz da �rvore (inicia vazia)
    int opcao, valor;

    // Exibe o menu apenas UMA VEZ no in�cio
    cout << "\n====== MENU ARVORE BINARIA ======\n";
    cout << "1. Inserir elemento\n";
    cout << "2. Listar elementos (em ordem)\n";
    cout << "3. Encontrar maior valor\n";
    cout << "0. Sair\n";
    cout << "=================================\n";

    // Loop de execu��o cont�nua (o menu n�o se repete)
    while (true) {
        cout << "\nEscolha uma opcao (0 para sair): ";
        cin >> opcao;

        // Se o usu�rio digitar 0, o programa termina
        if (opcao == 0) {
            cout << "Encerrando o programa...\n";
            break;
        }

        // Escolhe a a��o de acordo com a op��o digitada
        switch (opcao) {
            case 1:
                cout << "Digite o valor a inserir: ";
                cin >> valor;
                raiz = inserir(raiz, valor);
                cout << "Elemento inserido com sucesso!\n";
                break;

            case 2:
                cout << "Elementos em ordem crescente: ";
                listar(raiz);
                cout << endl;
                break;

            case 3:
                valor = encontrarMaior(raiz);
                if (raiz != NULL)
                    cout << "Maior valor da arvore: " << valor << endl;
                break;

            default:
                cout << "Opcao invalida! Tente novamente.\n";
        }
    }

    return 0; 
}