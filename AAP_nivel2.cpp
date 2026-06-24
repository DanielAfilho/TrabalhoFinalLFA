#include <stack>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

/*
exemplos
    {"q0", 'a', 'Z', "AZ", "q0"}, q0 a Z A q0 y
    {"q0", 'a', 'A', "AA", "q0"}, q0 a A A q0 y
    {"q0", 'b', 'A', "", "q1"}, q0 b A "" q1 y
    {"q1", 'b', 'A', "", "q1"} q1 b A "" q1 n
    
    {"q0", 'a', 'Z', "AZ", "q0"}, q0 a Z A q0 y
    {"q0", 'a', 'A', "AA", "q0"}, q0 a A A q0 y
    {"q0", 'b', 'A', "CCA", "q1"}, q0 b A "" q1 y
    {"q1", 'b', 'C', "CCC", "q1"} q1 b A "" q1 n
    {"q1", 'c', 'C', "", "q1"} q1 b A "" q1 n
    {"q1", 'c', 'C', "", "q1"} q1 b A "" q1 n
    
    {"q0", 'a', 'Z', "AZ", "q0"}, q0 a Z A q0 y
    {"q0", 'a', 'A', "AA", "q0"}, q0 a A A q0 y
    {"q0", 'c', 'Z', "n", "q1"}, q0 b A "" q1 y
    {"q0", 'c', 'A', "n", "q1"}, q0 b A "" q1 y
    {"q1", 'b', 'A', "", "q1"} q1 b A "" q1 n
*/

struct Transicao {
    string estadoAtual;
    char entrada;
    char topo;        
    string empilha;   
    string proximoEstado;
};

vector<Transicao> seta;

void exibirPilha(stack<char> s) {
    if (s.empty()) {
        cout << "[ Pilha Vazia ]" << endl;
        return;
    }
    stack<char> temp;
    while(!s.empty()){
        temp.push(s.top());
        s.pop();
    }
    cout << "Pilha: ";
    while(!temp.empty()){
        cout << "[" << temp.top() << "] ";
        temp.pop();
    }
    cout << endl;
}

bool ehEstadoFinal(string estado, vector<string> F){
    for(int i=0; i<F.size(); i++){
        if(estado==F[i]){
            return true;
        }
    }
    return false;
}

void valida(string x, char Z0, vector<string> F, string estadoInicial) {
    stack<char> pilha;
    pilha.push(Z0);
    string estado = estadoInicial;

    cout << "\n--- Iniciando Processamento ---\n";

    for (int i = 0; i < x.length(); i++) {
        char c = x[i];
        bool encontrou = false;

        for (int j = 0; j < seta.size(); j++) {
            if (seta[j].estadoAtual == estado && seta[j].entrada == c && !pilha.empty() && seta[j].topo == pilha.top()) {
                
                cout << "Lendo: '" << c << "' | Estado: " << estado << " -> " << seta[j].proximoEstado << endl;

                //se 'empilha' for vazio "" da pop
                if (seta[j].empilha == "") {
                    cout << "POP (" << pilha.top() << ")" << endl;
                    pilha.pop();
                }
                //se 'empilha' for "n" nao mexe na pilha
                else if(seta[j].empilha == "n"){
                    cout << "nao mexe na pilha" << endl;
                }
                //se 'empilha' for algo que nao "" ou "n"
                else{
                    cout << "POP (" << pilha.top() << ")" << endl;
                    pilha.pop();
                    cout << "PUSH (" << seta[j].empilha << ")" << endl;
                    for (int k = seta[j].empilha.size() - 1; k >= 0; k--) {
                        pilha.push(seta[j].empilha[k]);
                    }
                }

                estado = seta[j].proximoEstado;
                exibirPilha(pilha);
                cout << "--------------------------" << endl;
                encontrou = true;
                break; 
            }
        }

        if (!encontrou) {
            cout << "\nNenhuma transicao encontrada para '" << c << "' no estado " << estado << endl;
            cout << "INVALIDO" << endl;
            return;
        }
    }

    //verifica o estado final e pilha
    if (ehEstadoFinal(estado, F)) {
        cout << "\nVALIDO PARA FIM(cadeia aceita no estado " << estado << ")" << endl;
    } else {
        cout << "\nINVALIDO PARA FIM(nao terminou em estado final)" << endl;
    }
    if (pilha.empty()) {
        cout << "\nVALIDO PARA PILHA(pilha vazia " << endl;
    } else {
        cout << "\nINVALIDO PARA PILHA(pilha nao vazia)" << endl;
    }
}

int main() {
    string estadoInicial;
    vector<string> F = {};
    char Z0 = 'Z';

    cout << "Configuracao do Automato\n";
    cout << "Para remover o topo (pop), deixe Empilha vazio ou seja so de enter\n";
    cout << "Para nao mexer na pilha, digite 'n' em Empilha\n";
    
    bool on = true;
    while (on) {
        Transicao t;
        cout << "\n--- Nova Regra (seta) ---" << endl;
        cout << "Estado Atual: "; 
        cin >> t.estadoAtual;
        cout << "Entrada: ";      
        cin >> t.entrada;
        cout << "Topo: "; 
        cin >> t.topo;
        cout << "Empilha: ";      
        cin.ignore();
        getline(cin, t.empilha); //permite entrada vazia para POP
        
        cout << "Proximo Estado: "; 
        cin >> t.proximoEstado;

        seta.push_back(t);

        cout << "Adicionar outra? [y/n]: ";
        char op; cin >> op;
        if (op == 'n') on = false;
    }
    
    cout << "Digite qual estado vai ser o inicio\n";
    cin >> estadoInicial;
    
    string final;
    
    cout << "Digite quais vao ser os estados finais\n Quando acabar de digita-los apenas entre: para\n";
    
    while(cin >> final && final != "para"){
        F.push_back(final);
    }
    
    string entrada;
    cout << "\nDigite a string para testar: ";
    cin >> entrada;

    valida(entrada, Z0, F, estadoInicial);

    return 0;
}