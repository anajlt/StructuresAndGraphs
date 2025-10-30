#include <iostream>
#include <fstream> // Para ler o arquivo .txt
using namespace std;

#define vertex int // Define 'vertex' como apelido para 'int'

// Classe que representa um grafo
class Graph {
private:
    int V;      // número de vértices
    int A;      // número de arestas

public:
    int **adj;  // matriz de adjacência
    int *grau;  // vetor com o grau de cada vértice

    // Construtor
    Graph(int vertices) {
        V = vertices;
        A = 0;

        // Aloca memória para a matriz de adjacência
        adj = new int*[V];
        for (int i = 0; i < V; i++) {
            adj[i] = new int[V];
            for (int j = 0; j < V; j++)
                adj[i][j] = 0; // inicializa todas as posições com 0
        }

        // Aloca memória para o vetor de graus
        grau = new int[V];
        for (int i = 0; i < V; i++)
            grau[i] = 0;
    }

    // Destrutor (libera memória)
    ~Graph() {
        for (int i = 0; i < V; i++)
            delete[] adj[i]; // libera cada linha da matriz
        delete[] adj;        // libera o ponteiro da matriz
        delete[] grau;       // libera o vetor de graus
    }

    // Insere uma aresta (v1 - v2)
    void inserirAresta(int v1, int v2) {
        if (adj[v1][v2] == 0) { // se ainda não existe a aresta
            adj[v1][v2] = 1;
            adj[v2][v1] = 1; // grafo não direcionado
            A++;
            grau[v1]++;
            grau[v2]++;
        }
    }

    // Remove uma aresta (v1 - v2)
    void removerAresta(int v1, int v2) {
        if (adj[v1][v2] == 1) { // se a aresta existe
            adj[v1][v2] = 0;
            adj[v2][v1] = 0; // grafo não direcionado
            A--;
            grau[v1]--;
            grau[v2]--;
        }
    }

    // Mostra a matriz de adjacência
    void mostrarMatriz() {
        cout << "\nMatriz de Adjacencia:\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++)
                cout << adj[i][j] << " ";
            cout << endl;
        }
    }

    // Mostra o grau de cada vértice
    void mostrarGrau() {
        cout << "\nGrau dos vertices:\n";
        for (int i = 0; i < V; i++)
            cout << "Vertice " << i << ": " << grau[i] << endl;
    }

    // Lê o grafo de um arquivo .txt
    void lerArquivo(string nomeArquivo) {
        ifstream arq(nomeArquivo.c_str()); // converte string para const char*

        if (!arq) { // se não conseguir abrir
            cout << "Erro ao abrir o arquivo!\n";
            return;
        }

        int v1, v2;
        // Lê cada linha (pares de vértices)
        while (arq >> v1 >> v2) {
            inserirAresta(v1, v2);
        }

        arq.close();
        cout << "Grafo carregado com sucesso!\n";
    }

    // Algoritmo de Floyd-Warshall
    void floydWarshall() {
        // Cria a matriz de distâncias
        int **dist = new int*[V];
        for (int i = 0; i < V; i++) {
            dist[i] = new int[V];
            for (int j = 0; j < V; j++) {
                if (i == j)
                    dist[i][j] = 0;         // cistância para ele mesmo
                else if (adj[i][j] != 0)
                    dist[i][j] = 1;         // peso da aresta (grafo não ponderado)
                else
                    dist[i][j] = 1000000;   // representa infinito
            }
        }

        // Atualiza a matriz com as menores distâncias
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        // Mostra a matriz de distâncias mínimas
        cout << "\nMatriz de caminhos minimos (Floyd-Warshall):\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == 1000000)
                    cout << "INF ";
                else
                    cout << dist[i][j] << " ";
            }
            cout << endl;
        }

        // Libera memória
        for (int i = 0; i < V; i++)
            delete[] dist[i];
        delete[] dist;
    }
};

// Função do MENU principal
int Menu_Grafo(Graph &g) {
    int opcao, v1, v2;

    // Mostra o menu apenas uma vez
    cout << "\n===== MENU DO GRAFO =====\n";
    cout << "1. Inserir aresta\n";
    cout << "2. Remover aresta\n";
    cout << "3. Mostrar matriz de adjacencia\n";
    cout << "4. Mostrar grau dos vertices\n";
    cout << "5. Floyd-Warshall (caminho minimo)\n";
    cout << "6. Sair\n";

    // Loop principal para executar as operações
    do {
        cout << "\nDigite a opcao desejada: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "Digite v1 e v2: ";
            cin >> v1 >> v2;
            g.inserirAresta(v1, v2);
            break;
        case 2:
            cout << "Digite v1 e v2: ";
            cin >> v1 >> v2;
            g.removerAresta(v1, v2);
            break;
        case 3:
            g.mostrarMatriz();
            break;
        case 4:
            g.mostrarGrau();
            break;
        case 5:
            g.floydWarshall();
            break;
        case 6:
            cout << "Encerrando o programa...\n";
            break;
        default:
            cout << "Opcao invalida!\n";
        }
    } while (opcao != 6); // mantém o loop até o usuário escolher sair

    return 0;
}

// Função principal (main)
int main() {
    int vertices;
    cout << "Digite o numero de vertices do grafo: ";
    cin >> vertices;

    Graph g(vertices); // cria o grafo com o número de vértices informado

    string nomeArquivo;
    cout << "Digite o nome do arquivo .txt: ";
    cin >> nomeArquivo;

    g.lerArquivo(nomeArquivo); // lê as arestas do arquivo

    Menu_Grafo(g); // exibe o menu uma vez e permite operações repetidas

    return 0;
}