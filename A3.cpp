#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Estrutura do n� da �rvore
// Cada n� armazena: nome (chave para ordena��o na �rvore);
// sexo: 'M' ou 'F';
// idade e peso: dados adicionais.;
// esquerda/direita: ponteiros para os n�s filhos
struct No {
    string nome;
    char sexo;
    int idade;
    float peso;
    No* esquerda;
    No* direita;
};

// Fun��o: novoNo()
// cria um novo n� na mem�ria, preenchendo seus campos
No* novoNo(string nome, char sexo, int idade, float peso) {
    No* no = new No;
    no->nome = nome;
    no->sexo = sexo;
    no->idade = idade;
    no->peso = peso;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

// Fun��o: inserir()
// insere uma pessoa na �rvore bin�ria de busca (BST)
// a chave � o nome, usada para decidir a posi��o de inser��o
No* inserir(No* raiz, string nome, char sexo, int idade, float peso) {
    if (raiz == NULL)
        return novoNo(nome, sexo, idade, peso);

    // Ordena��o alfab�tica (lexicogr�fica) pelo nome
    if (nome < raiz->nome)
        raiz->esquerda = inserir(raiz->esquerda, nome, sexo, idade, peso);
    else if (nome > raiz->nome)
        raiz->direita = inserir(raiz->direita, nome, sexo, idade, peso);

    // Se o nome for igual, ignora (n�o insere duplicado)
    return raiz;
}

// Fun��o: separarPorSexo()
// percorre a �rvore em ordem (esquerda -> raiz -> direita)
// adiciona cada n� � lista correspondente ao sexo
void separarPorSexo(No* raiz, vector<No*>& homens, vector<No*>& mulheres) {
    if (raiz != NULL) {
        separarPorSexo(raiz->esquerda, homens, mulheres); // visita esquerda

        // Classifica o n� conforme o sexo informado
        if (raiz->sexo == 'M' || raiz->sexo == 'm')
            homens.push_back(raiz);
        else if (raiz->sexo == 'F' || raiz->sexo == 'f')
            mulheres.push_back(raiz);

        separarPorSexo(raiz->direita, homens, mulheres); // visita direita
    }
}

// Fun��o: exibirLista()
// percorre o vetor e exibe os dados de cada pessoa
void exibirLista(const std::vector<No*>& lista) {
    for (size_t i = 0; i < lista.size(); i++) {
        No* no = lista[i];
        cout << "Nome: " << no->nome
             << ", Sexo: " << no->sexo
             << ", Idade: " << no->idade
             << ", Peso: " << no->peso << endl;
    }
}

// Fun��o principal (main)
int main() {
    No* raiz = NULL; // ponteiro para a raiz da �rvore
    int opcao;
    string nome;
    char sexo;
    int idade;
    float peso;

    // Vetores para armazenar as listas separadas por sexo
    vector<No*> homens;
    vector<No*> mulheres;

    // Mostra o menu APENAS UMA VEZ
    cout << "\n====== MENU ARVORE DE PESSOAS ======\n";
    cout << "1. Inserir pessoa na arvore\n";
    cout << "2. Gerar listas separadas por sexo\n";
    cout << "3. Exibir lista de homens\n";
    cout << "4. Exibir lista de mulheres\n";
    cout << "0. Sair\n";
    cout << "====================================\n";

    // O menu n�o se repete, mas o programa segue em loop
    while (true) {
        cout << "\nEscolha uma opcao (0 para sair): ";
        cin >> opcao;
        cin.ignore(); // limpa o buffer de entrada

        if (opcao == 0) {
            cout << "Encerrando o programa...\n";
            break; // sai do loop principal
        }

        switch (opcao) {
            case 1:
                // Inserir pessoa na �rvore
                cout << "Digite o nome: ";
                getline(cin, nome);
                cout << "Digite o sexo (M/F): ";
                cin >> sexo;
                cout << "Digite a idade: ";
                cin >> idade;
                cout << "Digite o peso: ";
                cin >> peso;
                cin.ignore(); // limpa o buffer
                raiz = inserir(raiz, nome, sexo, idade, peso);
                cout << "Pessoa inserida com sucesso!\n";
                break;

            case 2:
                // Gera listas de homens e mulheres
                homens.clear();
                mulheres.clear();
                separarPorSexo(raiz, homens, mulheres);
                cout << "Listas geradas com sucesso!\n";
                break;

            case 3:
                // Exibir lista de homens
                if (homens.empty())
                    cout << "Lista de homens vazia ou ainda nao gerada.\n";
                else {
                    cout << "\n--- Lista de homens ---\n";
                    exibirLista(homens);
                }
                break;

            case 4:
                // Exibir lista de mulheres
                if (mulheres.empty())
                    cout << "Lista de mulheres vazia ou ainda nao gerada.\n";
                else {
                    cout << "\n--- Lista de mulheres ---\n";
                    exibirLista(mulheres);
                }
                break;

            default:
                cout << "Opcao invalida! Digite novamente.\n";
        }
    }

    return 0;
}