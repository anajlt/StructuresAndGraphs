#include <iostream>
using namespace std;

#define vertex int

// Função auxiliar para alocar matriz de inteiros dinamicamente
int **Aloca_MatrizInt(int l, int c, int **m) {
    m = new int*[l];
    for(int i = 0; i < l; i++) {
        m[i] = new int[c];
        for(int j = 0; j < c; j++)
            m[i][j] = 0; // inicializa com 0
    }
    return m;
}

class Graph {
private:
    int V; // número de vértices
    int A; // número de arestas

public:
    int **adj;  // matriz de adjacência
    int **dist; // matriz de distâncias (opcional para algoritmos como Floyd-Warshall)
    int *grau;  // vetor de grau dos vértices

    // Construtor
    Graph(int vertices = 0) {
        V = vertices;
        A = 0;
        adj = Aloca_MatrizInt(V, V, adj);
        dist = Aloca_MatrizInt(V, V, dist);
        grau = new int[V];
        for(int i = 0; i < V; i++)
            grau[i] = 0;
    }

    // Destrutor
    ~Graph() {
        for(int i = 0; i < V; i++) {
            delete[] adj[i];
            delete[] dist[i];
        }
        delete[] adj;
        delete[] dist;
        delete[] grau;
    }

    // Adiciona aresta entre u e v
    void addEdge(vertex u, vertex v) {
        if(u >= 0 && u < V && v >= 0 && v < V) {
            adj[u][v] = 1;
            adj[v][u] = 1; // grafo não direcionado
            A++;
        } else {
            cout << "Vertices invalidos!" << endl;
        }
    }

    // Imprime a matriz de adjacência
    void printGraph() {
        cout << "\nMatriz de adjacencia:" << endl;
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Calcula o grau de todos os vértices
    void calculaGrau() {
        cout << "\nGrau dos vertices:" << endl;
        for(int i = 0; i < V; i++) {
            grau[i] = 0;
            for(int j = 0; j < V; j++)
                grau[i] += adj[i][j];
            cout << "Vertice " << i << ": " << grau[i] << endl;
        }
    }

    // Menu principal do grafo (aparece uma vez)
    void menu() {
        int opcao;

        // imprime o menu apenas uma vez
        cout << "\nEscolha uma opcao:" << endl;
        cout << "1 - Adicionar aresta" << endl;
        cout << "2 - Imprimir matriz de adjacencia" << endl;
        cout << "3 - Calcular grau dos vertices" << endl;
        cout << "0 - Sair" << endl;

        do {
            cout << "\nDigite a opcao desejada: ";
            cin >> opcao;

            switch(opcao) {
                case 1: {
                    int u, v;
                    cout << "Digite os vertices u e v: ";
                    cin >> u >> v;
                    addEdge(u, v);
                    break;
                }
                case 2:
                    printGraph();
                    break;
                case 3:
                    calculaGrau();
                    break;
                case 0:
                    cout << "Saindo do programa..." << endl;
                    break;
                default:
                    cout << "Opcao invalida!" << endl;
            }
        } while(opcao != 0);
    }
};

// Programa principal
int main() {
    int n;
    cout << "Digite o numero de vertices do grafo: ";
    cin >> n;

    Graph g(n); // cria o grafo com n vértices
    g.menu();   // chama o menu do grafo

    return 0;
}