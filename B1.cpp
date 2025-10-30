#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Estrutura do nó da árvore binária
struct No {
    string nome;    // chave da árvore
    char sexo;      // 'M' ou 'F'
    int idade;
    float peso;
    No* esquerda;   // filho esquerdo
    No* direita;   // filho direito
};

// Cria um novo nó
No* criarNo(string nome, char sexo, int idade, float peso) {
    No* novo = new No;
    novo->nome = nome;
    novo->sexo = sexo;
    novo->idade = idade;
    novo->peso = peso;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

// Inserção simples na BST (baseada na chave nome)
No* inserir(No* raiz, string nome, char sexo, int idade, float peso) {
    if (raiz == NULL)
        return criarNo(nome, sexo, idade, peso);

    if (nome < raiz->nome)
        raiz->esquerda = inserir(raiz->esquerda, nome, sexo, idade, peso);
    else if (nome > raiz->nome)
        raiz->direita = inserir(raiz->direita, nome, sexo, idade, peso);
    // nomes iguais não são inseridos
    return raiz;
}

// Percorre a árvore em ordem e separa por sexo
void separarPorSexo(No* raiz, vector<No*>& homens, vector<No*>& mulheres) {
    if (!raiz) return;

    // Percorre a subárvore esquerda
    separarPorSexo(raiz->esquerda, homens, mulheres);

    // Adiciona nó à lista correspondente
    if (raiz->sexo == 'M')
        homens.push_back(raiz);
    else if (raiz->sexo == 'F')
        mulheres.push_back(raiz);

    // Percorre a subárvore direita
    separarPorSexo(raiz->direita, homens, mulheres);
}

// Imprime uma lista de nós
void imprimirLista(const vector<No*>& lista) {
    for (size_t i = 0; i < lista.size(); ++i) {
    	No* p = lista[i]; // pega o ponteiro do vetor
        cout << p->nome << " | Sexo: " << p->sexo << " | Idade: " << p->idade
             << " | Peso: " << p->peso << endl;
	}
}

int main() {
    No* raiz = NULL;

    // Inserindo alguns dados de exemplo
    raiz = inserir(raiz, "Ana", 'F', 25, 55.0);
    raiz = inserir(raiz, "Bruno", 'M', 30, 70.5);
    raiz = inserir(raiz, "Carlos", 'M', 22, 68.0);
    raiz = inserir(raiz, "Daniela", 'F', 28, 60.0);
    raiz = inserir(raiz, "Eduardo", 'M', 35, 80.0);

    // Vetores para armazenar listas separadas por sexo
    vector<No*> homens;
    vector<No*> mulheres;

    // Separando a árvore em duas listas ordenadas
    separarPorSexo(raiz, homens, mulheres);

    // Imprimindo resultados
    cout << "Lista de homens:\n";
    imprimirLista(homens);

    cout << "\nLista de mulheres:\n";
    imprimirLista(mulheres);

    return 0;
}