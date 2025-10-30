#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

//------------------------------------------------------------------------
//   Classe orientada a objeto para a Árvore AVL
//------------------------------------------------------------------------
class ArvoreAVL {
private:
    // Estrutura interna do nó
    struct NO {
        int info;
        int altura;
        NO* esq;
        NO* dir;
    };

    NO* raiz;

    // ---------- MÉTODOS AUXILIARES PRIVADOS ----------

    void Libera_NO(NO* no) {
        if (no == NULL) return;
        Libera_NO(no->esq);
        Libera_NO(no->dir);
        free(no);
    }

    int Altura_NO(NO* no) {
        if (no == NULL)
            return -1;
        return no->altura;
    }

    int FatorBalance_NO(NO* no) {
        return abs(Altura_NO(no->esq) - Altura_NO(no->dir));
    }

    int Maior(int x, int y) {
        return (x > y) ? x : y;
    }

    void RotacaoEE(NO*& raiz) {
        cout << "Rotacao Esquerda - Esquerda" << endl;
        NO* no = raiz->esq;
        raiz->esq = no->dir;
        no->dir = raiz;
        raiz->altura = Maior(Altura_NO(raiz->esq), Altura_NO(raiz->dir)) + 1;
        no->altura = Maior(Altura_NO(no->esq), raiz->altura) + 1;
        raiz = no;
    }

    void RotacaoDD(NO*& raiz) {
        cout << "Rotacao Direita - Direita" << endl;
        NO* no = raiz->dir;
        raiz->dir = no->esq;
        no->esq = raiz;
        raiz->altura = Maior(Altura_NO(raiz->esq), Altura_NO(raiz->dir)) + 1;
        no->altura = Maior(Altura_NO(no->dir), raiz->altura) + 1;
        raiz = no;
    }

    void RotacaoED(NO*& raiz) {
        cout << "Rotacao Esquerda - Direita" << endl;
        RotacaoDD(raiz->esq);
        RotacaoEE(raiz);
    }

    void RotacaoDE(NO*& raiz) {
        cout << "Rotacao Direita - Esquerda" << endl;
        RotacaoEE(raiz->dir);
        RotacaoDD(raiz);
    }

    NO* ProcuraMenor(NO* atual) {
        NO* no1 = atual;
        NO* no2 = atual->esq;
        while (no2 != NULL) {
            no1 = no2;
            no2 = no2->esq;
        }
        return no1;
    }

    // INSERÇÃO RECURSIVA
    int Insere(NO*& raiz, int valor) {
        int ok;
        if (raiz == NULL) {
            NO* novo = (NO*)malloc(sizeof(NO));
            if (novo == NULL)
                return 0;

            novo->info = valor;
            novo->altura = 0;
            novo->esq = NULL;
            novo->dir = NULL;
            raiz = novo;
            return 1;
        }

        if (valor < raiz->info) {
            if ((ok = Insere(raiz->esq, valor)) == 1) {
                if (FatorBalance_NO(raiz) >= 2) {
                    if (valor < raiz->esq->info)
                        RotacaoEE(raiz);
                    else
                        RotacaoED(raiz);
                }
            }
        } else if (valor > raiz->info) {
            if ((ok = Insere(raiz->dir, valor)) == 1) {
                if (FatorBalance_NO(raiz) >= 2) {
                    if (raiz->dir->info < valor)
                        RotacaoDD(raiz);
                    else
                        RotacaoDE(raiz);
                }
            }
        } else {
            cout << "Valor duplicado!" << endl;
            return 0;
        }

        raiz->altura = Maior(Altura_NO(raiz->esq), Altura_NO(raiz->dir)) + 1;
        return ok;
    }

    // REMOÇÃO RECURSIVA
    int Remove(NO*& raiz, int valor) {
        if (raiz == NULL) {
            cout << "Valor não existe!" << endl;
            return 0;
        }

        int sai;
        if (valor < raiz->info) {
            if ((sai = Remove(raiz->esq, valor)) == 1) {
                if (FatorBalance_NO(raiz) >= 2) {
                    if (Altura_NO(raiz->dir->esq) <= Altura_NO(raiz->dir->dir))
                        RotacaoDD(raiz);
                    else
                        RotacaoDE(raiz);
                }
            }
        } else if (raiz->info < valor) {
            if ((sai = Remove(raiz->dir, valor)) == 1) {
                if (FatorBalance_NO(raiz) >= 2) {
                    if (Altura_NO(raiz->esq->dir) <= Altura_NO(raiz->esq->esq))
                        RotacaoEE(raiz);
                    else
                        RotacaoED(raiz);
                }
            }
        } else {
            // valor encontrado
            if (raiz->esq == NULL || raiz->dir == NULL) {
                NO* oldNode = raiz;
                raiz = (raiz->esq != NULL) ? raiz->esq : raiz->dir;
                free(oldNode);
            } else {
                NO* temp = ProcuraMenor(raiz->dir);
                raiz->info = temp->info;
                Remove(raiz->dir, raiz->info);
                if (FatorBalance_NO(raiz) >= 2) {
                    if (Altura_NO(raiz->esq->dir) <= Altura_NO(raiz->esq->esq))
                        RotacaoEE(raiz);
                    else
                        RotacaoED(raiz);
                }
            }
            if (raiz != NULL)
                raiz->altura = Maior(Altura_NO(raiz->esq), Altura_NO(raiz->dir)) + 1;
            return 1;
        }

        raiz->altura = Maior(Altura_NO(raiz->esq), Altura_NO(raiz->dir)) + 1;
        return sai;
    }

    // RELATÓRIOS
    void Relatorio_Insercao(NO* raiz) {
        cout << "| " << setw(2) << raiz->info << "  |\t " << setw(2)
             << Altura_NO(raiz) << "    |" << endl;
        cout << "----------------" << endl;
    }

    void Relatorio_Balance(NO* raiz) {
        cout << "| " << setw(2) << raiz->info << "  |\t " << setw(2)
             << Altura_NO(raiz) << "    |" << setw(3)
             << FatorBalance_NO(raiz) << "  |" << endl;
        cout << "----------------------" << endl;
    }

    // IMPRESSÕES RECURSIVAS
    void PreOrdem(NO* raiz) {
        if (raiz != NULL) {
            Relatorio_Insercao(raiz);
            PreOrdem(raiz->esq);
            PreOrdem(raiz->dir);
        }
    }

    void EmOrdem(NO* raiz) {
        if (raiz != NULL) {
            EmOrdem(raiz->esq);
            Relatorio_Balance(raiz);
            EmOrdem(raiz->dir);
        }
    }

    void PosOrdem(NO* raiz) {
        if (raiz != NULL) {
            PosOrdem(raiz->esq);
            PosOrdem(raiz->dir);
            cout << raiz->info << " ";
        }
    }

    int TotalNO(NO* raiz) {
        if (raiz == NULL)
            return 0;
        return TotalNO(raiz->esq) + TotalNO(raiz->dir) + 1;
    }

public:
    // ---------- CONSTRUTOR / DESTRUTOR ----------
    ArvoreAVL() { raiz = NULL; }

    ~ArvoreAVL() {
        Libera_NO(raiz);
        raiz = NULL;
    }

    // ---------- MÉTODOS PÚBLICOS ----------
    bool Vazia() { return raiz == NULL; }

    void Inserir(int valor) { Insere(raiz, valor); }

    void Remover(int valor) { Remove(raiz, valor); }

    bool Consultar(int valor) {
        NO* atual = raiz;
        while (atual != NULL) {
            if (valor == atual->info)
                return true;
            if (valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        return false;
    }

    int Altura() { return Altura_NO(raiz); }

    int TotalNos() { return TotalNO(raiz); }

    void MostrarPreOrdem() {
        cout << "----------------" << endl;
        cout << "|INSERCAO - AVL|" << endl;
        cout << "----------------" << endl;
        cout << "|  NO | ALTURA |" << endl;
        cout << "----------------" << endl;
        PreOrdem(raiz);
    }

    void MostrarEmOrdem() {
        cout << "----------------------" << endl;
        cout << "|Relatorio Arvore AVL|" << endl;
        cout << "----------------------" << endl;
        cout << "|  NO | ALTURA | FB  |" << endl;
        cout << "----------------------" << endl;
        EmOrdem(raiz);
    }

    void MostrarPosOrdem() {
        cout << "\nPos-Ordem: ";
        PosOrdem(raiz);
        cout << endl;
    }
};

//------------------------------------------------------------------------
//   FUNÇÃO MAIN COM MENU INTERATIVO
//------------------------------------------------------------------------
int main() {
    ArvoreAVL arv;
    int opcao, valor;

    do {
        cout << "\n========== MENU ARVORE AVL ==========";
        cout << "\n1 - Inserir no";
        cout << "\n2 - Remover no";
        cout << "\n3 - Consultar valor";
        cout << "\n4 - Mostrar Em-Ordem";
        cout << "\n5 - Mostrar Pre-Ordem";
        cout << "\n6 - Mostrar Pos-Ordem";
        cout << "\n7 - Total de nos";
        cout << "\n8 - Altura da arvore";
        cout << "\n0 - Sair";
        cout << "\n=====================================";
        cout << "\nOpcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Valor a inserir: ";
                cin >> valor;
                arv.Inserir(valor);
                break;
            case 2:
                cout << "Valor a remover: ";
                cin >> valor;
                arv.Remover(valor);
                break;
            case 3:
                cout << "Valor a consultar: ";
                cin >> valor;
                cout << (arv.Consultar(valor) ? "Valor encontrado!" : "Valor nao encontrado!") << endl;
                break;
            case 4:
                arv.MostrarEmOrdem();
                break;
            case 5:
                arv.MostrarPreOrdem();
                break;
            case 6:
                arv.MostrarPosOrdem();
                break;
            case 7:
                cout << "Total de nos: " << arv.TotalNos() << endl;
                break;
            case 8:
                cout << "Altura da arvore: " << arv.Altura() << endl;
                break;
            case 0:
                cout << "Encerrando o programa..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }

    } while (opcao != 0);

    return 0;
}