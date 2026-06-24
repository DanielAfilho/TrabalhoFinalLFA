//EXPLICACAO INSANA DE CODIGO

//esse codigo é da hierarquia 3, eu basicamente peguei meu trabalho da hierarquia 2 que era o da pilha
//e coloquei em comentario as partes que era da pilha, assim vira um automato finito(hierarquia 3)

#include <stack>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

/*
aqui eh o formato das entradas, os exemplos são do automato a pilha, basicamente vc esta criando as "setas" do jflap, e com isso cria os estados por consequencia

exempls
    {"nomeDoEstado", 'o que é lido na entrada', 'o topo da pilha', 'o que vai ser colocado na pilha' <-(se nao tiver nada ele apenas faz o pop na pilha), "nomeDoProximoEstado"}

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

//um exemplo de entrada do automato finito (desse codigo)
//{"nomeDoStage", 'o que é lido na entrada', "nomeDoProximoStage"}

//voce basicamente tira a parte da pilha (:


//aqui eh a etrutura da seta
struct Transicao {
    string estadoAtual;
    char entrada;
    //char topo;        isso sai pq nao temos pilha no automato finito
    //string empilha;       idem
    string proximoEstado;
};

vector<Transicao> seta;

//Isso aqui seria uma funcao para mostrar a pilha que eu deixei comentada pra vcs verem oq eu "tirei"

/*void exibirPilha(stack<char> s) {
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
}*/

//aqui fazemos a verificacao se é estagio final
bool ehEstadoFinal(string estado, vector<string> F){
    for(int i=0; i<F.size(); i++){
        if(estado==F[i]){
            return true;
        }
    }
    return false; //a resposta eh um boleano
}

//aqui eh o coracao do codigo, pois verificamos se a entrada funciona de acordo com os estados e setas criadas

//ele funciona basicamente passando por todo o vetor de setas, procurando uma na qual consegue se encaixar

//se ele encontrar é pq tinha algum caminho a ser seguido

void valida(string x, /char Z0,/ vector<string> F, string estadoInicial) {
    //stack<char> pilha;            so tirei o que seria parte da pilha
    //pilha.push(Z0);
    string estado = estadoInicial;
    //o estado inicial é estabelecido nas entradas do programa, e a variavel estado vai ser aquela que possui o estado atual
    //ou seja, quando essa variavel for trocada, quer dizer que mudamos para outro estado (outra bolinha no jflap)
    //mas ela pode se manter a mesma, pois no jflap tbm temos os loops que recaem sobre o mesmo estado

    cout << "\n--- Iniciando Processamento ---\n";

    for (int i = 0; i < x.length(); i++) {
        char c = x[i]; //aqui pegamos o caracter inicial da entrada, que no caso é x, uma string
        bool encontrou = false;

        //basicamente tirei as condicoes do if que serviam para pilha
        //e essa parte verifica para cada seta, no vetor de seta, quais batem com os dados de entrada atual e de estado atual
        for (int j = 0; j < seta.size(); j++) {                         
            if (seta[j].estadoAtual == estado && seta[j].entrada == c /&& !pilha.empty() && seta[j].topo == pilha.top()/) {
                
                cout << "Lendo: '" << c << "' | Estado: " << estado << " -> " << seta[j].proximoEstado << endl;

                //essa parte comentada basicamente era a verificacao da pilha, e mudanca dela a cada iteracao

                //se 'empilha' for vazio "" da pop
                /*if (seta[j].empilha == "") {
                    cout << "POP (" << pilha.top() << ")" << endl;
                    pilha.pop();
                }*/
                //se 'empilha' for "n" nao mexe na pilha
                /*else if(seta[j].empilha == "n"){
                    cout << "nao mexe na pilha" << endl;
                }*/
                //se 'empilha' for algo que nao "" ou "n"
                /*else{
                    cout << "POP (" << pilha.top() << ")" << endl;
                    pilha.pop();
                    cout << "PUSH (" << seta[j].empilha << ")" << endl;
                    for (int k = seta[j].empilha.size() - 1; k >= 0; k--) {
                        pilha.push(seta[j].empilha[k]);
                    }
                }*/

                estado = seta[j].proximoEstado;//aqui fazemos a mudanca do estado, para qual seria o proximo a partir da seta escolhida
                //exibirPilha(pilha);
                cout << "--------------------------" << endl;
                encontrou = true;
                break; 
            }
        }

        if (!encontrou) {//aqui verifica se nao encontrou
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
    
    //aqui verificava se a pilha tava vazia
    
    /*if (pilha.empty()) {
        cout << "\nVALIDO PARA PILHA(pilha vazia " << endl;
    } else {
        cout << "\nINVALIDO PARA PILHA(pilha nao vazia)" << endl;
    }*/
}

int main() {
    string estadoInicial;
    vector<string> F = {};//vetor de finais, apenas guarda os estados que seriam finais
    //char Z0 = 'Z'; //isso aqui era para pilha

    cout << "Configuracao do Automato\n";
    //cout << "Para remover o topo (pop), deixe Empilha vazio ou seja so de enter\n";
    //cout << "Para nao mexer na pilha, digite 'n' em Empilha\n";
    
    bool on = true;
    
    //aqui a criacao de regras, ou seja, das setas
    
    while (on) {
        Transicao t; //cria uma variavel do tipo da struct e guarda no vetor de setas lá do comeco
        cout << "\n--- Nova Regra (seta) ---" << endl;
        cout << "Estado Atual: "; 
        cin >> t.estadoAtual;
        cout << "Entrada: ";      
        cin >> t.entrada;
        //cout << "Topo: "; 
        //cin >> t.topo;
        //cout << "Empilha: ";      
        //cin.ignore();
        //getline(cin, t.empilha); //permite entrada vazia para POP
        
        cout << "Proximo Estado: "; 
        cin >> t.proximoEstado;

        seta.push_back(t);//aqui eh onde guarda no vetor de setas a seta criada

        //auto explicativo 
        cout << "Adicionar outra? [y/n]: ";
        char op; cin >> op;
        if (op == 'n') on = false;
    }
    
    //aqui voce decide o inicio
    cout << "Digite qual estado vai ser o inicio\n";
    cin >> estadoInicial;
    
    string final;
    
    cout << "Digite quais vao ser os estados finais\n Quando acabar de digita-los apenas entre: para\n";
    
    //aqui vc decide os finais
    while(cin >> final && final != "para"){
        F.push_back(final);
    }
    
    string entrada;
    cout << "\nDigite a string para testar: ";
    cin >> entrada;

    valida(entrada, /Z0,/ F, estadoInicial);

    return 0;
}