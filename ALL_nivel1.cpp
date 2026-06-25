#include <stack>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

/*
exemplos

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
*/

struct Transicao {
    string estadoAtual;
    char entrada;
    char moverCabecoteDirecao;
    char mudaPara;
    string proximoEstado;
};

vector<Transicao> seta;

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

bool ehEstadoFinal(string estado, vector<string> F){
    for(int i=0; i<F.size(); i++){
        if(estado==F[i]){
            return true;
        }
    }
    return false;
}

void valida(string x, vector<string> F, string estadoInicial) {
    string estado = estadoInicial;
    bool executando = true;

    cout << "\n--- Iniciando Processamento ---\n";
    
    //aqui eu basicamente mudei a forma como se tem a leitura da entrada x, ja que aqui nao podemos apenas caminhar com um for(),
    //pois precisamos que o cabecote ande para a esquerda tambem de acordo com o que foi programado em cada seta
    
    int Cabecote = 0; //cabecote no indice 0 da string x

    //tem que mudar esse for por um while, vendo se chegou no fim, mas nao consegui pensar em algo
    while(executando) {
        bool encontrou = false;

        for (int j = 0; j < seta.size(); j++) {
            if (seta[j].estadoAtual == estado && seta[j].entrada == x[Cabecote]) {
                
                cout << "Lendo: '" << x[Cabecote] << "' | Estado: " << estado << " -> " << seta[j].proximoEstado << endl;
                
                x[Cabecote] = seta[j].mudaPara;
                
                cout << "Andando cabecote para: " << seta[j].moverCabecoteDirecao << endl;
                
                moverCabecote(x, Cabecote, seta[j].moverCabecoteDirecao);//adicionei uma forma de mover o cabecote
                
                estado = seta[j].proximoEstado;
                
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

    if (ehEstadoFinal(estado, F)) {
        cout << "\nVALIDO PARA FIM(cadeia aceita no estado " << estado << ")" << endl;
    } else {
        cout << "\nINVALIDO PARA FIM(nao terminou em estado final)" << endl;
    }
}

int main() {
    string estadoInicial;
    vector<string> F = {};

    cout << "Configuracao do Automato\n";
    
    bool on = true;
    while (on) {
        Transicao t;
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

    entrada = "[" + entrada + "]";

    valida(entrada, F, estadoInicial);

    return 0;
}
