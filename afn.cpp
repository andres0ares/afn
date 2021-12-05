#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define num_estados 10
#define num_transicoes 10


class ElementClass {
    public:
        int amountData;
        string* data = new string [num_estados];
};

class TransicaoClass {
    public:
        string from, to, symbol;
};



//Variavei globais
int error = 1; 
int qtd_transicoes = 0;
const char *els[4]= {"alfabeto=", "estados=", "inicial=", "finais="};
ElementClass* elements = new ElementClass [4];
TransicaoClass* transicoes = new TransicaoClass [num_transicoes];
string cadeia;



void getDescricao(void) {

    string linhaTexto, line;
    ifstream MyReadFile("descricao.txt");
    size_t found, found2;

    for(int j = 0; j < 4; j++){

        // for lê as quatro primeiras linhas e procura pelas strings "alfabeto=", "estados=", "inicial=", "finais="
        getline(MyReadFile, linhaTexto);
        found = linhaTexto.find(els[j]);
        elements[j].amountData = 0;
        
        line = linhaTexto.substr(linhaTexto.find("=") +1);

        //caso nao encontre as strings ou não exista dados, retorna erro.
        if((found == string::npos )|| (j != 3 && line.length() == 0)){
            cout << "\n error: dados insuficientes -> " << els[j]; 
            error = 0;
            j = 4;
        }
        
        if (error != 0){
        
            //lê os dados após o "=" e a ",".
            int works = 1;
            while(works){
    
                found2 = line.find(",");
                if(found2 != string::npos) {

                    elements[j].data[elements[j].amountData] = line.substr(0, found2);
                    line = line.substr(found2 + 1);
                    elements[j].amountData++;

                }else{

                    elements[j].data[elements[j].amountData] = line;
                    elements[j].amountData++;
                    works = 0;

                } 
            }

        }

    }

    if(error != 0){
        //procura pelas transiçoes 
        getline(MyReadFile, linhaTexto);
        if(linhaTexto.find("transicoes") != string::npos){

            //le todas as linhas e armazena as transicoes
            while (getline(MyReadFile, linhaTexto)){

                transicoes[qtd_transicoes].from = linhaTexto.substr(0, linhaTexto.find(","));
                linhaTexto = linhaTexto.substr(linhaTexto.find(",") +1);
                transicoes[qtd_transicoes].to = linhaTexto.substr(0, linhaTexto.find(","));
                transicoes[qtd_transicoes].symbol = linhaTexto.substr(linhaTexto.find(",") +1);
                qtd_transicoes++;
            }

        }else{
            cout << "error: transicoes not found";
            error = 0;
        }
    }
    

    MyReadFile.close();
}


// verifica se ha um simbolo que nao faz parte do alfabeto
int fazParteAlfabeto(void) {
    for(int i = 0; i < cadeia.length(); i++){
        string simbolo(1, cadeia[i]);
        int count = 0;
        for(int j = 0; j < elements[0].amountData; j++){
            if(simbolo == elements[0].data[j]){
                count++;
            }
        }
        if(count == 0){
            return 0;
        }
    }

    return 1;
}


int main(void) {


    cout << "\n\n ===== SIMULACAO AUTOMATO FINITO NAO-DETERMINISTICO =====";

    // Lê dados do arquivo descricao.txt | encerra programa se contem erro no arquivo.
    getDescricao();
    if(error == 0) {
        return -1;
    }

    // *********************** exibe dados da descricao.txt  ***************************

    cout << "\n\n ---- DADOS LIDOS (descricao.txt) ----\n\n";

    for(int j = 0; j < 4; j++){
        cout << "\n " << els[j];
        for(int i = 0; i < elements[j].amountData; i++){
            cout << "\n -> " << elements[j].data[i]; 
        }
    }

    for(int i = 0; i < qtd_transicoes; i++) {
        cout << "\n transicao " << i+1;
        cout << "\n de: " << transicoes[i].from;
        cout << ", para: " << transicoes[i].to;
        cout << ", simbolo: " << transicoes[i].symbol;
    }

    cout << "\n\n Para proseguir digite a cadeia, e precione enter: ";
    cin >> cadeia;

    cout << "\n\n ===== INICIO DA SIMULACAO =====";
    cout << "\n\n Cadeia inserida -> " << cadeia;    
    cout << "\n\n";


    // verifica se a cadeia contem um simbolo que nao faz parte do alfabeto

    if(fazParteAlfabeto() == 0){
        cout << "\n error: cadeia possui simbolo que nao faz parte do alfabeto. \n";
        return -1;
    }


    // *********************** simulacao ***************************

    // elements[0] = alfabeto
    // elements[1] = estados
    // elements[2] = estado inicial
    // elements[3] = estados finais


    
    string* estado = new string [elements[1].amountData]; 
    string* newEstado = new string [elements[1].amountData];
    int qtd_estado = 1; 
    int qtd_newEstado = 0;

    estado[0] = elements[1].data[0];
    

    for(int i = 0; i < cadeia.length(); i++){


        cout << "\n\n ------- Caractere " << cadeia[i];
        cout << "-------";

        string simbolo(1, cadeia[i]);
        int count = 0;

        //verifica se ha possibilidade de transicao
        for(int j = 0; j < qtd_transicoes; j++) {


            for(int l=0; l < qtd_estado; l++){
                
                //se ha, armazena o novo estado no array newEstado
                if(estado[l] == transicoes[j].from && (simbolo == transicoes[j].symbol)){
                    cout << "\n de " << estado[l];
                    cout << ", para " << transicoes[j].to;

                    //evita duplicidade de estados
                    int exist = 1;
                    for(int k = 0; k < qtd_newEstado; k++){
                        if(newEstado[k] == transicoes[j].to)
                            exist = 0
                        ;
                    }
                    if(exist != 0){
                        newEstado[qtd_newEstado] = transicoes[j].to;
                        qtd_newEstado++;
                    }

                }
            
            }        

        }

        //limpa array
        for(int j = 0; j < qtd_estado; j++){
            estado[j] = "";
        }

        //atualiza o array estado e limpa o array newEstado
        for(int j = 0; j < qtd_newEstado; j++){
            estado[j] = newEstado[j];
            newEstado[j] = "";
        }

        //atualiza a quantidade
        qtd_estado = qtd_newEstado;
        qtd_newEstado = 0;
        
    }

    //verifica de possui um estado final no array estado
    int aceita = 0;
    for(int i = 0; i < qtd_estado; i++){
        for(int j = 0; j < elements[3].amountData; j++){
            if(estado[i] == elements[3].data[j]){
                if(aceita == 0)
                    cout << "\n\n ===========  CADEIA ACEITA ===============\n"
                ;
                cout << "\n Aceita no estado: " << estado[i];
                aceita++;
            }
                
        }
    }

    if(aceita == 0)
        cout << "\n\n ===========  CADEIA REJEITADA ===============\n"
    ;

    cout << "\n";


    return -1;

    // ******************* fim simulacao ***************************
    
}