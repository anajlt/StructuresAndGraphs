#include <iostream>
#include <string>

using namespace std;

// Estrutura do n� da �rvore
struct No {
    string chave;    // valor da pessoa
    int contador;    // n�mero de ocorr�ncias
    No* esquerda;    // filho � esquerda
    No* direita;    // filho � direita
};

// Cria um novo n�
No* criarNo(string chave) {
    No* novo = new No;
    novo->chave = chave;
    novo->contador = 1;  // inicia com 1 ocorr�ncia
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Inser��o na BST considerando repeti��es
No* inserir(No* raiz, string chave) {
    if (raiz == NULL) {
        return criarNo(chave);
    }

    if (chave == raiz->chave) {
        raiz->contador++; // incrementa contador se chave j� existe
        cout << "Chave repetida. Contador agora: " << raiz->contador << endl;
    } else if (chave < raiz->chave) {
        raiz->esquerda = inserir(raiz->esquerda, chave);
    } else {
        raiz->direita = inserir(raiz->direita, chave);
    }
    return raiz;
}

// Encontra o menor n� (necess�rio na remo��o)
No* minimo(No* raiz) {
    while (raiz && raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

// Remo��o considerando contador
No* remover(No* raiz, string chave) {
    if (raiz == NULL) return NULL;

    if (chave < raiz->chave) {
        raiz->esquerda = remover(raiz->esquerda, chave);
    } else if (chave > raiz->chave) {
        raiz->direita = remover(raiz->direita, chave);
    } else {
        // Encontrou o n�
        if (raiz->contador > 1) {
            raiz->contador--; // apenas decrementa contador
            cout << "Decrementando contador. Novo contador: " << raiz->contador << endl;
            return raiz;
        }

        // Remo��o do n� quando contador == 1
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            delete raiz;
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            delete raiz;
            return temp;
        }

        // N� com dois filhos
        No* temp = minimo(raiz->direita);
        raiz->chave = temp->chave;
        raiz->contador = temp->contador;
        raiz->direita = remover(raiz->direita, temp->chave);
    }
    return raiz;
}

// Impress�o em ordem
void imprimirEmOrdem(No* raiz) {
    if (!raiz) return;
    imprimirEmOrdem(raiz->esquerda);
    cout << raiz->chave << " (ocorrencias: " << raiz->contador << ")" << endl;
    imprimirEmOrdem(raiz->direita);
}

int main() {
    No* raiz = NULL;
    int opcao;
    string chave;

    // Menu aparece apenas uma vez
    cout << "\n=== MENU ARVORE ===\n";
    cout << "1. Inserir chave\n";
    cout << "2. Remover chave\n";
    cout << "3. Imprimir arvore\n";
    cout << "0. Sair\n";
    cout << "==================\n";

    while (true) {
        cout << "\nEscolha uma opcao (0 para sair): ";
        cin >> opcao;
        cin.ignore();

        switch(opcao) {
            case 1:
                cout << "Digite a chave: ";
                getline(cin, chave);
                raiz = inserir(raiz, chave);
                break;
            case 2:
                cout << "Digite a chave a remover: ";
                getline(cin, chave);
                raiz = remover(raiz, chave);
                break;
            case 3:
                cout << "Arvore em ordem:\n";
                imprimirEmOrdem(raiz);
                break;
            case 0:
                cout << "Saindo...\n";
                return 0;
            default:
                cout << "Opcao invalida!\n";
        }
    }
}