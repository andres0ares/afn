#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define num_estados 10


class Elemento {
    public:
        int amountData;
        string* data = new string [num_estados];
};



//Variavei globais
const char *els[4]= {"alfabeto=", "estados=", "inicial=", "finais="};
Elemento* elementos = new Elemento [4];
int error = 1; 


void getDados(void) {
    string linhaTexto, alfabeto;
    ifstream MyReadFile("descricao.txt");


    for(int j = 0; j < 4; j++){

        getline(MyReadFile, linhaTexto);
        elementos[j].amountData = 0;
        size_t found = linhaTexto.find(els[j]);
        size_t found2;
        string line = linhaTexto.substr(linhaTexto.find("=") +1);

        if((j != 3 && line.length() == 0)){
            error = 0;
            j = 4;
        }
        
        if (found != string::npos && error != 0){
        
            int works = 1;
            while(works){
                
                found2 = line.find(",");
                if(found2 != string::npos) {

                    elementos[j].data[elementos[j].amountData] = line.substr(0, found2);
                    line = line.substr(found2 + 1);
                    elementos[j].amountData++;

                }else{

                    elementos[j].data[elementos[j].amountData] = line;
                    elementos[j].amountData++;
                    works = 0;

                } 
            }

        }else{
            cout << "\n error: dados insuficientes"; 
            error = 0;
            j = 4;
        }
    }

    MyReadFile.close();
}

int main(void) {

    

    printf("===== SIMULACAO AUTOMATO FINITO NAO-DETERMINISTICO =====\n\nDados: \n");
    getDados();

    if(error !=0){
        for(int j = 0; j < 4; j++){
        cout << "\n" << els[j];
        for(int i = 0; i < elementos[j].amountData; i++){
            cout << "\n--> " << elementos[j].data[i]; 
        }
    }
    }
    
    cout << "\n";
    
}