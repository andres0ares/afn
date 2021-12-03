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

        getline(MyReadFile, linhaTexto);
        found = linhaTexto.find(els[j]);
        elements[j].amountData = 0;
        
        line = linhaTexto.substr(linhaTexto.find("=") +1);

        if((found == string::npos )|| (j != 3 && line.length() == 0)){
            cout << "\n error: dados insuficientes -> " << els[j]; 
            error = 0;
            j = 4;
        }
        
        if (error != 0){
        
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
        getline(MyReadFile, linhaTexto);
        if(linhaTexto.find("transicoes") != string::npos){

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

    if(error !=0){

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

    }
    
    cout << "\n\n";
    
}