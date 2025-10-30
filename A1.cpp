#include <iostream>
using namespace std;

// Estrutura de um n� da �rvore 
// cada n� cont�m: um valor inteiro (valor)
// ponteiro para o filho da esquerda
// ponteiro para o filho da direita
struct No {
    int valor;
    No* esquerda;
    No* direita;
};

// Fun��o: novoNo()
// Cria um novo n� dinamicamente e devolve o ponteiro para ele.
No* novoNo(int valor) {
    No* no = new No;       // aloca mem�ria para um novo n�
    no->valor = valor;     // define o valor armazenado
    no->esquerda = NULL;   // nenhum filho � esquerda por enquanto
    no->direita = NULL;    // nenhum filho � direita por enquanto
    return no;             // retorna o endere�o do novo n�
}

// Fun��o: inserir()
// insere um valor na �rvore de forma ordenada (propriedade da ABB):
// - valores menores v�o para a esquerda
// - valores maiores v�o para a direita
No* inserir(No* raiz, int valor) {
    // Caso base: �rvore vazia -> cria um novo n�
    if (raiz == NULL)
        return novoNo(valor);

    // Se o valor for menor, insere na sub�rvore esquerda
    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);

    // Se for maior, insere na sub�rvore direita
    else if (valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor);

    // Se for igual, n�o faz nada (neste c�digo n�o h� repeti��o)
    return raiz; // retorna a raiz atualizada
}

// Fun��o: listar()
// percorre a �rvore em "ordem sim�trica" (in-order):
// esquerda -> raiz -> direita (valores em ordem crescente)
void listar(No* raiz) {
    if (raiz != NULL) {
        listar(raiz->esquerda);      // 1. visita a esquerda
        cout << raiz->valor << " ";  // 2. exibe o valor do n� atual
        listar(raiz->direita);       // 3. visita a direita
    }
}

// Fun��o: encontrarMinimo()
// acha o menor valor de uma sub�rvore (usado na remo��o).
No* encontrarMinimo(No* raiz) {
    // o menor valor est� sempre no n� mais � esquerda
    while (raiz && raiz->esquerda != NULL)
        raiz = raiz->esquerda;
    return raiz;
}

// Fun��o: remover()
// remove um n� da �rvore, mantendo a propriedade da ABB.
// tr�s casos principais:
// 1. n� folha (sem filhos)
// 2. n� com apenas um filho
// 3. n� com dois filhos
No* remover(No* raiz, int valor) {
    if (raiz == NULL) return raiz; // caso base: �rvore vazia

    // se o valor procurado for menor -> procura na esquerda
    if (valor < raiz->valor)
        raiz->esquerda = remover(raiz->esquerda, valor);

    // se o valor procurado for maior -> procura na direita
    else if (valor > raiz->valor)
        raiz->direita = remover(raiz->direita, valor);

    // se o valor for igual -> achamos o n� a remover
    else {
        // caso 1: n� folha
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            delete raiz;   // libera mem�ria
            return NULL;   // retorna nulo para o pai
        }

        // caso 2: n� com apenas um filho (direita)
        else if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            delete raiz;
            return temp;   // substitui o n� pelo filho
        }

        // caso 2: n� com apenas um filho (esquerda)
        else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            delete raiz;
            return temp;
        }

        // caso 3: n� com dois filhos
        // substitui o valor do n� pelo menor valor da sub�rvore direita
        No* temp = encontrarMinimo(raiz->direita);
        raiz->valor = temp->valor;

        // remove o n� duplicado da sub�rvore direita
        raiz->direita = remover(raiz->direita, temp->valor);
    }
    return raiz; // retorna a raiz atualizada
}

// Fun��o principal (main)
int main() {
    No* raiz = NULL;  // come�a com �rvore vazia
    int opcao, valor;

    // inser��o autom�tica dos valores iniciais
    int numeros[] = {20, 5, 12, 36, 27, 45, 9, 2, 6, 17, 40};
    int tamanho = sizeof(numeros) / sizeof(numeros[0]);
    for (int i = 0; i < tamanho; i++)
        raiz = inserir(raiz, numeros[i]);

    // exibe o menu apenas uma vez
    cout << "\n====== MENU ======\n";
    cout << "1. Inserir elemento\n";
    cout << "2. Listar elementos (em ordem)\n";
    cout << "3. Remover elemento\n";
    cout << "4. Remover na ordem (9, 5, 20)\n";
    cout << "0. Sair\n";
    cout << "==================\n";

    // Loop principal (n�o repete o menu)
    while (true) {
        cout << "\nEscolha uma opcao (0 para sair): ";
        cin >> opcao;

        // Sai do programa
        if (opcao == 0) {
            cout << "Encerrando o programa...\n";
            break;
        }

        // Trata cada op��o do menu
        switch (opcao) {
            case 1:
                cout << "Digite o valor a inserir: ";
                cin >> valor;
                raiz = inserir(raiz, valor);
                cout << "Elemento inserido!\n";
                break;

            case 2:
                cout << "Elementos em ordem: ";
                listar(raiz);
                cout << endl;
                break;

            case 3:
                cout << "Digite o valor a remover: ";
                cin >> valor;
                raiz = remover(raiz, valor);
                cout << "Elemento removido (se existia)!\n";
                break;

            case 4:
                // Remove os n�s na ordem pedida: 9, depois 5, depois 20
                raiz = remover(raiz, 9);
                raiz = remover(raiz, 5);
                raiz = remover(raiz, 20);
                cout << "Removidos: 9, 5 e 20.\n";
                break;

            default:
                cout << "Opcao invalida!\n";
        }
    }

    return 0; 
}