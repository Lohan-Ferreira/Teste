#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Grafo.h"

using namespace std;

int main(){

    /** Variáveis */
    Grafo * grafo = new Grafo(true);
    string temp;
    float arestemp[3];


    /** Tratamento de arquivo e construção do grafo*/
    ifstream file;
    file.open("grafo.txt");


    getline(file, temp);
    for(int i = 1; i <= atoi(temp.c_str()); i++)
        grafo->addVertice();

    //leitura de arquivo e contrução do grafo
    while(true)
    {
        file>>arestemp[0]>>arestemp[1]>>arestemp[2];
        if(file.eof()) break;

        cout<<arestemp[0]<<arestemp[1]<<arestemp[2]<<endl; //salvar os 3 valores do arquivo no vetor como float
        grafo->addAresta(arestemp[0], arestemp[1], arestemp[2]);
    }
    file.close();


    /** Testes */
    cout<<endl;
    grafo->sequenciaGraus();
    cout<<endl;
    //if(grafo->verificaBipartido()) cout<<"Eh bi";
    grafo->menorCaminhoFloyd(4,2);
    grafo->fechoDireto(3);
    grafo->fechoIndireto(3);
    cout<<"Eh euleriano? "<<grafo->verificaEuleriano();


    return 0;
}