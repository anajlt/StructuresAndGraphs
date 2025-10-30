#include <iostream>
#include <string>
#include <algorithm> // para max()
using namespace std;

// Estrutura do n� AVL
struct No {
    string nome;    // chave da �rvore
    char sexo;      // 'M' ou 'F'
    int idade;
    float peso;
    No* esquerda;   // filho esquerdo
    No* direita;    // filho direito
    int altura;     // altura do n�
};

// Fun��o para obter a altura de um n�
int altura(No* n) {
    if (n == NULL)
        return 0;
    return n->altura;
}

// Cria um novo n�
No* criarNo(string nome, char sexo, int idade, float peso) {
    No* novo = new No;
    novo->nome = nome;
    novo->sexo = sexo;
    novo->idade = idade;
    novo->peso = peso;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1; // novo n� � folha inicialmente
    return novo;
}

// Fun��o para rotacionar � direita
No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    // Rota��o
    x->direita = y;
    y->esquerda = T2;

    // Atualiza alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x; // nova raiz
}

// Fun��o para rotacionar � esquerda
No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    // Rota��o
    y->esquerda = x;
    x->direita = T2;

    // Atualiza alturas
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y; // nova raiz
}

// Calcula fator de balanceamento
int fatorBalanceamento(No* n) {
    if (n == NULL)
        return 0;
    return altura(n->esquerda) - altura(n->direita);
}

// Inser��o na �rvore AVL
No* inserir(No* raiz, string nome, char sexo, int idade, float peso) {
    if (raiz == NULL)
        return criarNo(nome, sexo, idade, peso);

    // Inser��o baseada em chave (nome)
    if (nome < raiz->nome)
        raiz->esquerda = inserir(raiz->esquerda, nome, sexo, idade, peso);
    else if (nome > raiz->nome)
        raiz->direita = inserir(raiz->direita, nome, sexo, idade, peso);
    else
        return raiz; // chaves iguais n�o s�o inseridas

    // Atualiza altura do n� atual
    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    // Calcula fator de balanceamento
    int fb = fatorBalanceamento(raiz);

    // Rota��o LL
    if (fb > 1 && nome < raiz->esquerda->nome)
        return rotacaoDireita(raiz);
    // Rota��o RR
    if (fb < -1 && nome > raiz->direita->nome)
        return rotacaoEsquerda(raiz);
    // Rota��o LR
    if (fb > 1 && nome > raiz->esquerda->nome) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }
    // Rota��o RL
    if (fb < -1 && nome < raiz->direita->nome) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz; // retorna raiz balanceada
}

// Encontra o n� com menor valor (para remo��o)
No* minimo(No* raiz) {
    No* atual = raiz;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Remo��o na �rvore AVL
No* remover(No* raiz, string nome) {
    if (raiz == NULL) return raiz;

    if (nome < raiz->nome)
        raiz->esquerda = remover(raiz->esquerda, nome);
    else if (nome > raiz->nome)
        raiz->direita = remover(raiz->direita, nome);
    else {
        // N� encontrado
        if (!raiz->esquerda || !raiz->direita) {
            No* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else
                *raiz = *temp; // copia conte�do
            delete temp;
        } else {
            No* temp = minimo(raiz->direita);
            raiz->nome = temp->nome;
            raiz->sexo = temp->sexo;
            raiz->idade = temp->idade;
            raiz->peso = temp->peso;
            raiz->direita = remover(raiz->direita, temp->nome);
        }
    }

    if (raiz == NULL)
        return raiz;

    // Atualiza altura
    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    // Balanceamento
    int fb = fatorBalanceamento(raiz);

    // Rota��o LL
    if (fb > 1 && fatorBalanceamento(raiz->esquerda) >= 0)
        return rotacaoDireita(raiz);
    // Rota��o LR
    if (fb > 1 && fatorBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }
    // Rota��o RR
    if (fb < -1 && fatorBalanceamento(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);
    // Rota��o RL
    if (fb < -1 && fatorBalanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Consulta de um n� por nome
No* consultar(No* raiz, string nome) {
    if (!raiz) return NULL;
    if (nome == raiz->nome) return raiz;
    if (nome < raiz->nome) return consultar(raiz->esquerda, nome);
    else return consultar(raiz->direita, nome);
}

// Listagem ordenada separando por sexo
void listarPorSexo(No* raiz, char sexo) {
    if (!raiz) return;
    listarPorSexo(raiz->esquerda, sexo);
    if (raiz->sexo == sexo)
        cout << raiz->nome << " | Idade: " << raiz->idade << " | Peso: " << raiz->peso << endl;
    listarPorSexo(raiz->direita, sexo);
}

int main() {
    No* raiz = NULL;
    int opcao;
    string nome;
    char sexo;
    int idade;
    float peso;

    // Menu aparece apenas uma vez
    cout << "===== MENU AVL =====\n";
    cout << "1. Inserir pessoa\n";
    cout << "2. Remover pessoa\n";
    cout << "3. Consultar pessoa\n";
    cout << "4. Listar homens\n";
    cout << "5. Listar mulheres\n";
    cout << "0. Sair\n";
    cout << "===================\n";

    while (true) {
        cout << "\nEscolha uma opcao: ";
        cin >> opcao;
        cin.ignore();

        switch(opcao) {
            case 1:
                cout << "Nome: ";
                getline(cin, nome);
                cout << "Sexo (M/F): ";
                cin >> sexo;
                cin.ignore();
                cout << "Idade: ";
                cin >> idade;
                cin.ignore();
                cout << "Peso: ";
                cin >> peso;
                cin.ignore();
                raiz = inserir(raiz, nome, sexo, idade, peso);
                break;
            case 2:
                cout << "Nome a remover: ";
                getline(cin, nome);
                raiz = remover(raiz, nome);
                break;
            case 3:
                cout << "Nome a consultar: ";
                getline(cin, nome);
                {
                    No* p = consultar(raiz, nome);
                    if (p)
                        cout << p->nome << " | " << p->sexo << " | " << p->idade << " | " << p->peso << endl;
                    else
                        cout << "Pessoa nao encontrada.\n";
                }
                break;
            case 4:
                cout << "Lista de homens:\n";
                listarPorSexo(raiz, 'M');
                break;
            case 5:
                cout << "Lista de mulheres:\n";
                listarPorSexo(raiz, 'F');
                break;
            case 0:
                cout << "Saindo...\n";
                return 0;
            default:
                cout << "Opcao invalida!\n";
        }
    }
}