#include <iostream>
#include <string>

using namespace std;

// Estrutura do n� da �rvore
struct No {
    string chave;    // valor do n�
    No* esquerda;    // ponteiro para filho esquerdo
    No* direita;    // ponteiro para filho direito
};

// Cria um novo n�
No* criarNo(string chave) {
    No* novo = new No;
    novo->chave = chave;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Inser��o simples em BST
No* inserir(No* raiz, string chave) {
    if (!raiz) return criarNo(chave);

    if (chave < raiz->chave)
        raiz->esquerda = inserir(raiz->esquerda, chave);
    else if (chave > raiz->chave)
        raiz->direita = inserir(raiz->direita, chave);
    // chaves iguais n�o s�o inseridas (para simplificar)
    return raiz;
}

// Fun��o que verifica se a �rvore � cheia
int ehCheia(No* raiz) {
    if (raiz == NULL)
        return 1; // �rvore vazia � cheia

    // Se n� folha
    if (raiz->esquerda == NULL && raiz->direita == NULL)
        return 1;

    // Se n� tem os dois filhos
    if (raiz->esquerda != NULL && raiz->direita != NULL)
        return ehCheia(raiz->esquerda) && ehCheia(raiz->direita);

    // N� com apenas um filho ? n�o cheia
    return 0;
}

// Percorre e imprime a �rvore em ordem
void imprimirEmOrdem(No* raiz) {
    if (!raiz) return;
    imprimirEmOrdem(raiz->esquerda);
    cout << raiz->chave << " ";
    imprimirEmOrdem(raiz->direita);
}

int main() {
    No* raiz = NULL;
    int opcao;
    string chave;

    // Menu aparece apenas uma vez
    cout << "\n=== MENU ARVORE ===\n";
    cout << "1. Inserir chave\n";
    cout << "2. Imprimir arvore em ordem\n";
    cout << "3. Verificar se a arvore e cheia\n";
    cout << "0. Sair\n";
    cout << "==================\n";

    while (true) {
        cout << "\nEscolha uma opcao (0 para sair): ";
        cin >> opcao;
        cin.ignore(); // limpa buffer

        switch(opcao) {
            case 1:
                cout << "Digite a chave: ";
                getline(cin, chave);
                raiz = inserir(raiz, chave);
                break;
            case 2:
                cout << "Arvore em ordem: ";
                imprimirEmOrdem(raiz);
                cout << endl;
                break;
            case 3:
                if (ehCheia(raiz))
                    cout << "A arvore e cheia!" << endl;
                else
                    cout << "A arvore nao e cheia!" << endl;
                break;
            case 0:
                cout << "Saindo...\n";
                return 0;
            default:
                cout << "Opcao invalida!\n";
        }
    }
}