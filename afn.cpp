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

int main(void) {

    

    cout << "===== SIMULACAO AUTOMATO FINITO NAO-DETERMINISTICO =====";
    getDescricao();

    if(error == 0) {
        return 0;
    }

    cout << "\n\n---- DADOS LIDOS ----\n\n";

    for(int j = 0; j < 4; j++){
        cout << "\n" << els[j];
        for(int i = 0; i < elements[j].amountData; i++){
            cout << "\n-> " << elements[j].data[i]; 
        }
    }

    cout << "\n\n---- TRANSICOES ----\n\n";

    for(int i = 0; i < qtd_transicoes; i++) {
        cout << "\ntransicao " << i+1;
        cout << "\nde: " << transicoes[i].from;
        cout << ", para: " << transicoes[i].to;
        cout << ", simbolo: " << transicoes[i].symbol;
    }

    cout << "\n\nPara proseguir digite a cadeia, e precione enter: ";
    cin >> cadeia;

    cout << "\n\n===== INICIO DA SIMULACAO =====";
    cout << "\n\nCadeia inserida -> " << cadeia;

    
    
    cout << "\n\n";

    // *********************** simulacao ***************************

    // elements[0] = alfabeto
    // elements[1] = estados
    // elements[2] = estado inicial
    // elements[3] = estados finais


    // fazParteAlfabeto();
    
    string* estado = new string [elements[1].amountData];
    string* newEstado = new string [elements[1].amountData];
    int qtd_estado = 1; 
    int qtd_newEstado = 0;

    estado[0] = elements[1].data[0];
    

    for(int i = 0; i < cadeia.length(); i++){

        cout << "\nCaracter lido " << cadeia[i];

        string simbolo(1, cadeia[i]);
        int count = 0;
        for(int j = 0; j < qtd_transicoes; j++) {


            for(int l=0; l < qtd_estado; l++){
                
                if(estado[l] == transicoes[j].from && (simbolo == transicoes[j].symbol)){
                    cout << "\nindo para " << transicoes[j].to;

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

        cout << "\n estados: ";
        for(int j = 0; j < qtd_estado; j++){
            cout << " " << estado[j];
            estado[j] = "";
        }

        cout << "\n new estados: ";
        for(int j = 0; j < qtd_newEstado; j++){
            cout << " " << newEstado[j];
            estado[j] = newEstado[j];
            newEstado[j] = "";
        }

        qtd_estado = qtd_newEstado;
        qtd_newEstado = 0;

        cout << "\n estados: ";
        for(int j = 0; j < qtd_estado; j++){
            cout << " " << estado[j];
        }
        
    }

    return 0;

    // ******************* fim simulacao ***************************
    
}