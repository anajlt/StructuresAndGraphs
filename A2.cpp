#include <iostream>
using namespace std;

// Estrutura do nó da árvore
// Cada nó armazena um valor e tem ponteiros para os nós à esquerda (valores menores) e à direita (valores maiores).
struct No {
    int valor;
    No* esquerda;
    No* direita;
};

// Função: novoNo()
// cria dinamicamente um novo nó na memória e inicializa seus ponteiros como NULL.
No* novoNo(int valor) {
    No* no = new No;        // aloca memória para o novo nó
    no->valor = valor;      // armazena o valor passado
    no->esquerda = NULL;    // nenhum filho à esquerda inicialmente
    no->direita = NULL;     // nenhum filho à direita inicialmente
    return no;              // retorna o ponteiro para o novo nó
}

// Função: inserir()
// insere um valor na árvore binária de busca (BST)
// se o valor for menor que o da raiz -> vai para a esquerda
// se for maior -> vai para a direita
// caso a posição esteja vazia, cria um novo nó
No* inserir(No* raiz, int valor) {
    if (raiz == NULL)
        return novoNo(valor);  // caso base: cria um novo nó

    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);  // insere à esquerda
    else if (valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor);    // insere à direita

    // caso o valor já exista, não faz nada (evita duplicatas)
    return raiz;
}

// Função: listar()
// percorre a árvore em ordem crescente (In-Order)
// esquerda -> raiz -> direita (valores em ordem)
void listar(No* raiz) {
    if (raiz != NULL) {
        listar(raiz->esquerda);      // percorre subárvore esquerda
        cout << raiz->valor << " ";  // exibe o valor atual
        listar(raiz->direita);       // percorre subárvore direita
    }
}

// Função: encontrarMaior()
// encontra o maior valor presente na árvore
// o maior valor sempre estará no nó mais à direita
int encontrarMaior(No* raiz) {
    if (raiz == NULL) {
        cout << "A arvore esta vazia!\n";
        return -1; // valor simbólico quando a árvore está vazia
    }

    // Se não há filho à direita, este é o maior valor
    if (raiz->direita == NULL)
        return raiz->valor;

    // Caso contrário, continua descendo à direita
    return encontrarMaior(raiz->direita);
}

// Função principal (main)
int main() {
    No* raiz = NULL;  // ponteiro para a raiz da árvore (inicia vazia)
    int opcao, valor;

    // Exibe o menu apenas UMA VEZ no início
    cout << "\n====== MENU ARVORE BINARIA ======\n";
    cout << "1. Inserir elemento\n";
    cout << "2. Listar elementos (em ordem)\n";
    cout << "3. Encontrar maior valor\n";
    cout << "0. Sair\n";
    cout << "=================================\n";

    // Loop de execução contínua (o menu não se repete)
    while (true) {
        cout << "\nEscolha uma opcao (0 para sair): ";
        cin >> opcao;

        // Se o usuário digitar 0, o programa termina
        if (opcao == 0) {
            cout << "Encerrando o programa...\n";
            break;
        }

        // Escolhe a ação de acordo com a opção digitada
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