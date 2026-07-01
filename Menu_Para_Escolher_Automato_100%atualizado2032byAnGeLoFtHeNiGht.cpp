#include <stack>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

/*
exemplo Nivel 0:
q0 # R # q0 y
q0 X R X q0 y
q0 Y R Y q0 y
q0 Z R Z q0 y
q0 a R X q1 y
q0 _ R _ q4 y
q1 a R a q1 y
q1 Y R Y q1 y
q1 b R Y q2 y
q2 b R b q2 y
q2 Z R Z q2 y
q2 c R Z q3 y
q3 c L c q3 y
q3 b L b q3 y
q3 a L a q3 y
q3 X L X q3 y
q3 Y L Y q3 y
q3 Z L Z q3 y
q3 _ L _ q3 y
q3 # R # q0 n

inicio q0

fim q4

entrada: #aabbcc
==========================================================================================================
exemplos Nivel 1:

q0 [ R [ q0 y
q0 a R X q1 y
q1 a R a q1 y
q1 Y R Y q1 y
q1 b R Y q2 y
q2 b R b q2 y
q2 Z R Z q2 y
q2 c L Z q3 y
q3 Z L Z q3 y
q3 b L b q3 y
q3 Y L Y q3 y
q3 a L a q3 y
q3 X R X q0 y
q0 Y R Y q_limpeza y
q_limpeza Y R Y q_limpeza y
q_limpeza Z R Z q_limpeza y
q_limpeza ] L ] q_accept n

inicio q0

fim q_accept
==========================================================================================================
exemplos Nivel 2:
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

=====================================================================
aqui eh o formato das entradas, os exemplos são do automato a pilha, basicamente vc esta criando as "setas" do jflap, e com isso cria os estados por consequencia
exemplos Nivel 3:

   3            <- escolhe Nível 3
q0           
a           
q1           
y            
q0          
b
q0
y
q1           
a
q1
y
q1           
b
q0
n            
q0           
q1           
para         
bba          
    
    
*/
//=====================================================================
// Nivel0 Funçoes:
struct TransicaoN0 {
    string estadoAtual;
    char entrada;
    char moverCabecoteDirecaoN0;
    char mudaPara;
    string proximoEstado;
};

vector<TransicaoN0> setaN0;


void moverCabecoteN0(string &x, int &indice, char direcao, char simboloVazio = '_') {
    if (direcao == 'R') {
        indice++;

        if (indice >= x.length()) {
            x.push_back(simboloVazio); 
        }
    } 
    else if (direcao == 'L') {
        if (indice - 1 < 0) {

            cout << "Erro: saiu da fita pela esquerda" << endl;
        } else {
            indice--;
        }
    } 
    else {
        cout << "Direção invalida, use R ou L" << endl;
    }
}

bool ehEstadoFinalN0(string estado, vector<string> F) {
    for (int i = 0; i < F.size(); i++) {
        if (estado == F[i]) {
            return true;
        }
    }
    return false;
}

void validaN0(string x, vector<string> F, string estadoInicial) {
    string estado = estadoInicial;
    bool executando = true;
    int Cabecote = 0; 

    cout << "\n--- Iniciando Processamento (Tipo 0) ---\n";
    
    while (executando) {

        if (ehEstadoFinalN0(estado, F)) {
            cout << "\nFita Final: " << x << endl;
            cout << "VALIDO PARA FIM (cadeia aceita no estado " << estado << ")" << endl;
            return;
        }

        bool encontrou = false;

        for (int j = 0; j < setaN0.size(); j++) {
            if (setaN0[j].estadoAtual == estado && setaN0[j].entrada == x[Cabecote]) {
                
                cout << "Lendo: '" << x[Cabecote] << "' no Estado: " << estado << " -> Vai para: " << setaN0[j].proximoEstado << endl;
                
                x[Cabecote] = setaN0[j].mudaPara;
                
                cout << "Fita atual: " << x << " (Cabeçote na posição " << Cabecote << ")" << endl;
                cout << "Movendo cabeçote para: " << setaN0[j].moverCabecoteDirecaoN0 << endl;
                
                moverCabecoteN0(x, Cabecote, setaN0[j].moverCabecoteDirecaoN0);
                
                estado = setaN0[j].proximoEstado;
                
                cout << "--------------------------" << endl;
                encontrou = true;
                break;
            }
        }

        if (!encontrou) {
            cout << "\nNenhuma transicao encontrada para '" << x[Cabecote] << "' no estado " << estado << endl;
            cout << "Fita Final: " << x << endl;
            cout << "INVALIDO (Máquina travou/rejeitou)" << endl;
            return;
        }
    }
}
//=====================================================================
// Nivel1 Funçoes:
struct TransicaoN1 {
    string estadoAtual;
    char entrada;
    char moverCabecoteDirecao;
    char mudaPara;
    string proximoEstado;
};

vector<TransicaoN1> setaN1;
//aqui eu criei uma verificacao de saida da fita original, ja que na hierarquia de nivel 1 nao podemos sair do tamanho da fita original
// e pensando bem, acho q a verificacao fica melhor com < e > ja que eu acho q toda entrada aqui possui eles

void moverCabecote(string x, int &indice, char direcao){
    if(direcao == 'R'){
        if(indice + 1 >= x.length()){
            cout << "Erro saiu da fita pela direita" << endl;
        }
        else{
            indice++;
        }
    }
    else if(direcao == 'L'){
        if(indice - 1 < 0){
            cout << "Erro saiu da fita pela esquerda" << endl;
        }
        else{
            indice--;
        }
    }
    else{
        cout << "Nao foi preenchido corretamente com R ou L a direcao" << endl;
    }
}

bool ehEstadoFinalN1(string estado, vector<string> F){
    for(int i=0; i<F.size(); i++){
        if(estado==F[i]){
            return true;
        }
    }
    return false;
}

void validaN1(string x, vector<string> F, string estadoInicial) {
    string estado = estadoInicial;
    bool executando = true;

    cout << "\n--- Iniciando Processamento ---\n";
    
    //aqui eu basicamente mudei a forma como se tem a leitura da entrada x, ja que aqui nao podemos apenas caminhar com um for(),
    //pois precisamos que o cabecote ande para a esquerda tambem de acordo com o que foi programado em cada seta
    
    int Cabecote = 0; //cabecote no indice 0 da string x

    //tem que mudar esse for por um while, vendo se chegou no fim, mas nao consegui pensar em algo
    while(executando) {
        bool encontrou = false;

        for (int j = 0; j < setaN1.size(); j++) {
            if (setaN1[j].estadoAtual == estado && setaN1[j].entrada == x[Cabecote]) {
                
                cout << "Lendo: '" << x[Cabecote] << "' | Estado: " << estado << " -> " << setaN1[j].proximoEstado << endl;
                
                x[Cabecote] = setaN1[j].mudaPara;
                
                cout << "Andando cabecote para: " << setaN1[j].moverCabecoteDirecao << endl;
                
                moverCabecote(x, Cabecote, setaN1[j].moverCabecoteDirecao);//adicionei uma forma de mover o cabecote
                
                estado = setaN1[j].proximoEstado;
                
                cout << "--------------------------" << endl;
                encontrou = true;
                break;
            }
        }

        if (!encontrou) {
            cout << "\nNenhuma transicao encontrada para '" << x[Cabecote] << "' no estado " << estado << endl;
            cout << "INVALIDO" << endl;
            return;
        }
    }

    if (ehEstadoFinalN1(estado, F)) {
        cout << "\nVALIDO PARA FIM(cadeia aceita no estado " << estado << ")" << endl;
    } else {
        cout << "\nINVALIDO PARA FIM(nao terminou em estado final)" << endl;
    }
}


//=====================================================================
// Nivel2 Funçoes:
struct TransicaoN2 {
    string estadoAtual;
    char entrada;
    char topo;        
    string empilha;   
    string proximoEstado;
};

vector<TransicaoN2> setaN2;

void exibirPilhaN2(stack<char> s) {
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

bool ehEstadoFinalN2(string estado, vector<string> F){
    for(int i=0; i<F.size(); i++){
        if(estado==F[i]){
            return true;
        }
    }
    return false;
}

void validaN2(string x, char Z0, vector<string> F, string estadoInicial) {
    stack<char> pilha;
    pilha.push(Z0);
    string estado = estadoInicial;

    cout << "\n--- Iniciando Processamento ---\n";

    for (int i = 0; i < x.length(); i++) {
        char c = x[i];
        bool encontrou = false;

        for (int j = 0; j < setaN2.size(); j++) {
            if (setaN2[j].estadoAtual == estado && setaN2[j].entrada == c && !pilha.empty() && setaN2[j].topo == pilha.top()) {
                
                cout << "Lendo: '" << c << "' | Estado: " << estado << " -> " << setaN2[j].proximoEstado << endl;

                //se 'empilha' for vazio "" da pop
                if (setaN2[j].empilha == "") {
                    cout << "POP (" << pilha.top() << ")" << endl;
                    pilha.pop();
                }
                //se 'empilha' for "n" nao mexe na pilha
                else if(setaN2[j].empilha == "n"){
                    cout << "nao mexe na pilha" << endl;
                }
                //se 'empilha' for algo que nao "" ou "n"
                else{
                    cout << "POP (" << pilha.top() << ")" << endl;
                    pilha.pop();
                    cout << "PUSH (" << setaN2[j].empilha << ")" << endl;
                    for (int k = setaN2[j].empilha.size() - 1; k >= 0; k--) {
                        pilha.push(setaN2[j].empilha[k]);
                    }
                }

                estado = setaN2[j].proximoEstado;
                exibirPilhaN2(pilha);
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
    if (ehEstadoFinalN2(estado, F)) {
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

//=====================================================================
//Funçoes Nivel 3:
struct TransicaoN3 {
    string estadoAtual;
    char entrada;
    //char topo;        isso sai pq nao temos pilha no automato finito
    //string empilha;       idem
    string proximoEstado;
};

vector<TransicaoN3> setaN3;

bool ehEstadoFinalN3(string estado, vector<string> F){
    for(int i=0; i<F.size(); i++){
        if(estado==F[i]){
            return true;
        }
    }
    return false; //a resposta eh um boleano
}
void validaN3(string x, char Z0, vector<string> F, string estadoInicial) {

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
        for (int j = 0; j < setaN3.size(); j++) {                         
            if (setaN3[j].estadoAtual == estado && setaN3[j].entrada == c) {
                
                cout << "Lendo: '" << c << "' | Estado: " << estado << " -> " << setaN3[j].proximoEstado << endl;
                estado = setaN3[j].proximoEstado;//aqui fazemos a mudanca do estado, para qual seria o proximo a partir da seta escolhida
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
    if (ehEstadoFinalN3(estado, F)) {
        cout << "\nVALIDO PARA FIM(cadeia aceita no estado " << estado << ")" << endl;
    } else {
        cout << "\nINVALIDO PARA FIM(nao terminou em estado final)" << endl;
    }
    
}

//=====================================================================
void Nivel0(){
    string estadoInicial;
    vector<string> F = {};

    cout << "Configuracao do Automato Tipo 0 (Maquina de Turing)\n";
    
    bool on = true;
    while (on) {
        TransicaoN0 t;
        cout << "\n--- Nova Regra (seta) ---" << endl;
        cout << "Estado Atual: "; 
        cin >> t.estadoAtual;
        cout << "Entrada (use '_' para o símbolo vazio/branco): ";      
        cin >> t.entrada;
        cout << "Direção que o cabeçote se move (R/L): ";      
        cin >> t.moverCabecoteDirecaoN0;
        cout << "Muda para: ";      
        cin >> t.mudaPara;
        cout << "Proximo Estado: "; 
        cin >> t.proximoEstado;

        setaN0.push_back(t);

        cout << "Adicionar outra? [y/n]: ";
        char op; cin >> op;
        if (op == 'n') on = false;
    }
    
    cout << "\nDigite qual estado vai ser o inicio: ";
    cin >> estadoInicial;
    
    string final;
    cout << "Digite os estados finais (digite 'para' para encerrar):\n";
    while (cin >> final && final != "para") {
        F.push_back(final);
    }
    
    string entrada;
    cout << "\nDigite a string para testar (ex: [aabbcc]): ";
    cin >> entrada;

    validaN0(entrada, F, estadoInicial);
}
//=====================================================================
void Nivel1(){
     string estadoInicial;
    vector<string> F = {};

    cout << "Configuracao do Automato\n";
    
    bool on = true;
    while (on) {
        TransicaoN1 t;
        cout << "\n--- Nova Regra (seta) ---" << endl;
        cout << "Estado Atual: "; 
        cin >> t.estadoAtual;
        cout << "Entrada: ";      
        cin >> t.entrada;
        cout << "Direção que o cabeçote se move: ";      
        cin >> t.moverCabecoteDirecao;
        cout << "Muda para: ";      
        cin >> t.mudaPara;
        cout << "Proximo Estado: "; 
        cin >> t.proximoEstado;

        setaN1.push_back(t);

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

    entrada = "[" + entrada + "]";

    validaN1(entrada, F, estadoInicial);
}
//=====================================================================
void Nivel2(){
     string estadoInicial;
    vector<string> F = {};
    char Z0 = 'Z';

    cout << "Configuracao do Automato\n";
    cout << "Para remover o topo (pop), deixe Empilha vazio ou seja so de enter\n";
    cout << "Para nao mexer na pilha, digite 'n' em Empilha\n";
    
    bool on = true;
    while (on) {
        TransicaoN2 t;
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

        setaN2.push_back(t);

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

    validaN2(entrada, Z0, F, estadoInicial);
}
//=====================================================================
void Nivel3(){
     string estadoInicial;
    vector<string> F = {};//vetor de finais, apenas guarda os estados que seriam finais
 

    cout << "Configuracao do Automato\n";

    
    bool on = true;
    
    //aqui a criacao de regras, ou seja, das setas
    
    while (on) {
        TransicaoN3 t; //cria uma variavel do tipo da struct e guarda no vetor de setas lá do comeco
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

        setaN3.push_back(t);//aqui eh onde guarda no vetor de setas a seta criada

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

    validaN3(entrada, 'Z',F, estadoInicial);
}


int main(){
    
    int Respsta = 0;
    cout << "Qual hierarquia será utilizada?\nR:";
    cin >> Respsta;
    switch(Respsta){
        case 0:
        Nivel0();
        break;
        case 1:
        Nivel1();
        break;
        case 2:
        Nivel2();
        break;
        case 3:
        Nivel3();
        break;
    }
    return 0;
}