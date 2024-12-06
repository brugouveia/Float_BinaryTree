#include <iostream>
#include <string>
using namespace std;

// Estrutura de nó da árvore binária
struct Node {
    string estato;      // Nome do estado
    Node* left = NULL;  // Transição para um próximo estado
    Node* right = NULL; // Alternativa de transição
    bool isFinal;       // Indica se é um estado final

    Node(string estato, bool finalState = false) {
        this->estato = estato;
        isFinal = finalState;
    }
};

// Verificar se um caractere é um número
bool isNumero(char c) {
    return c >= '0' && c <= '9';
}

bool isFloatLiteral(Node* node, string& input, int index) {
    if (node == NULL) return false;
    if (index == input.size()) {
        return node->isFinal; // Chegou no final da string
    }

    char current = input[index];
    
    // cout << "\nstate " << node->estato << endl;
    // cout << "curr  " << current << endl;
    // if(node->right != NULL) cout << "right " << node->right->estato << endl;
    // if(node->left != NULL) cout << "left  " << node->left->estato << endl;

    // Verificamos o estado atual e seguimos as transições correspondentes
    if (node->estato == "Inicio") {
        if (current == '+' || current == '-' || isNumero(current)) 
            return isFloatLiteral(node->left, input, index + 1) || isFloatLiteral(node->right, input, index + 1);
        if (current == '.') return isFloatLiteral(node->left, input, index + 1);
    }
    else if (node->estato == "Inteiro") {
        if (isNumero(current)) return isFloatLiteral(node->right, input, index + 1);
        if (current == '.') return isFloatLiteral(node->left, input, index + 1);
    }
    else if (node->estato == "Ponto") {
        if (isNumero(current)) return isFloatLiteral(node->right, input, index + 1);
    }
    else if (node->estato == "Fracionado") {
        if (isNumero(current)) return isFloatLiteral(node->right, input, index + 1);
        return isFloatLiteral(node->left, input, index + 1);
    }

    return false;
}

// Construção da árvore binária
Node* construirArvoreEstado() {
    Node* inicio = new Node("Inicio");
    Node* inteiro = new Node("Inteiro");
    Node* ponto = new Node("Ponto", true);
    Node* fracionado = new Node("Fracionado", true);

    // Definindo as transições da árvore
    inicio->right = inteiro;
    inicio->left = ponto;

    inteiro->right = inteiro;
    inteiro->left = ponto;

    ponto->right = fracionado;

    fracionado->right = fracionado;

    return inicio;
}

int main() {
    Node* arvoreEstado = construirArvoreEstado();

    string tests[] = {
        "0.123", "-.5", "123.", ".123",
        "+123.45e-6", "1e10", "e3"
    };
    
    for (string input : tests) {
        if (isFloatLiteral(arvoreEstado, input, 0)) {
            cout << input << " válido\n";
        } else {
            cout << input << " inválido\n";
        }
    }
}
