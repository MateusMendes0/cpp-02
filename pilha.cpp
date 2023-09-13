/* Classe pilha encadeada
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: "<< umDado.nome << " Tipo: " << umDado.tipo << " Valor: " << umDado.valor << endl;

}

class Noh {
    friend class Pilha;
    private:
        Dado mDado; // poderia ser outro tipo de variável
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

class Pilha {
    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no mPtTopo da pilha.
        // Escreve uma mensagem de erro se não for possível desempilhar.
        Dado Desempilhar(); // retorna o mPtTopo da Pilha.
        // Insere um valor na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no mPtTopo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
    private:
        Noh* mPtTopo;
};

Pilha::Pilha() {
}

Pilha::~Pilha() {
    LimparTudo();
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
//    // completar com o código, caso não esteja vazia
        Noh *aux = mPtTopo;
        Dado dado = aux->mDado;
        mPtTopo = aux->mProx;
        delete aux;

        return dado;

}

void Pilha::Empilhar(const Dado& d) {
    Noh *novo =  new Noh(d);
    novo->mProx = mPtTopo;
    mPtTopo = novo;
   
}

void Pilha::LimparTudo() {

    while (!Vazia()) {
        Noh* aux = mPtTopo;
        mPtTopo = aux->mProx;
        delete aux;
    }
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");

    imprimir_dado(mPtTopo->mDado);
}

bool Pilha::Vazia() {
    if(mPtTopo->mProx == NULL){
        return true;
    }
    return false;
}


int main() {
    Pilha pilha;
    Dado info;
    char comando;
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.valor;
                    pilha.Empilhar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(pilha.Desempilhar());
                    break;
                case 'l': // limpar tudo
                    pilha.LimparTudo();
                    break;
                case 'e': // espiar                
                    pilha.Topo();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    while (not pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}