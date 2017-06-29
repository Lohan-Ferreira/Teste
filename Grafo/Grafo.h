/** Implementa��o da classe Grafo */
/*  A classe grafo representa seus dados por meio das classes Vertice e Aresta, ambas incluidas a este documento.
    A estrutura cont�m uma lista encadeada de Vertives sendo que estes cont�m uma lista encadea de arestas.
    Cada aresta possui informa��o sobre a origem e destino da mesma. */

#ifndef GRAFO_H
#define GRAFO_H
#include "Lista.h"
#include <iostream>
#define BLOCO_ITER 100
#include <time.h>
#include <math.h>

using namespace std;

class Grafo
{

    /// Atributos
private:
    bool digrafo;
    int grau;
    int ordem;
    int num_arestas;
    int num_nos;
    int gera_id_v;
    int gera_id_a;
    int num_terminais;
    ListaVertice * Lista_vertice;


    /// M�todos
public:

    Grafo(bool dig)
    {
        Lista_vertice = new ListaVertice();
        digrafo = dig;
        gera_id_v=1;
        num_nos=0;
        num_arestas=0;
        num_terminais=0;
    }
    ~Grafo() {}

float reativo(Grafo* grafo , float alphas[], int tam_alpha, int max_iter_rand, int max_iter, int room){
	int melhorValor = 9999999999999999999, valor_qualquer;
	int temp_sorteio;
	float sorteio, sum_q;
	float soma_alpha[tam_alpha],
		  probabilidades[tam_alpha],
		  enne[tam_alpha],
		  temp_temp[tam_alpha];

	for(int i = 0; i < tam_alpha; i++){
		probabilidades[i] = 1/tam_alpha;
		soma_alpha[i] = 0;
		enne[i] = 0;
	}

    srand(time(NULL));
	for(int i = 0; i < max_iter; i++){
		sorteio = (rand()%1000)/1000;
		temp_sorteio = 0;
		while(true){
			if(sorteio > probabilidades[temp_sorteio]) sorteio -= probabilidades[temp_sorteio];
			else break;
			temp_sorteio++;
		}
		enne[temp_sorteio]++;
//		valor_qualquer = randomizado(Grafo, alphas[temp_sorteio], max_iter_rand);

		if(valor_qualquer < melhorValor) melhorValor = valor_qualquer;

		if(i%BLOCO_ITER == 0){
			sum_q = 0;
			for(int k = 0; k < tam_alpha; k++) temp_temp[k] = pow(melhorValor/(soma_alpha[k]/enne[k]), room);
			for(int k = 0; k < tam_alpha; k++) sum_q += temp_temp[k];
			for(int k = 0; k < tam_alpha; k++) probabilidades[k] = temp_temp[k]/sum_q;

		}
	}

	return melhorValor;
}

    //Retorna o Grau de um N� com um certo id
    int verifGrau(int id)
    {
        if(Lista_vertice->buscaVertice(id)!= NULL)
            return Lista_vertice->buscaVertice(id)->getVertice()->getArestas()->getQuantidade();
        else
        {
            return -1;
        }

    }


    int menorPi(float v[], int n)
    {
        int indice;
        float menor;
        NoListaVertice* tmp = Lista_vertice->Getraiz();

        while(tmp!=NULL)
        {
            if(tmp->getVertice()->getFlag()== 0)
            {
                indice=tmp->getVertice()->getId();
                break;
            }
            tmp=tmp->getProximo();

        }

        menor = v[indice];

        for(int i=0; i<n; i++)
            if(menor>v[i] && Lista_vertice->buscaVertice(i)->getVertice()->getFlag()== 0)
            {
                menor=v[i];
                indice=i;
            }

        return indice;
    }

    //Verifica se o grafo tem regularidade k informada
    bool verificaKregular (int k)
    {
        if(num_nos>0)
        {


            NoListaVertice* tmp=Lista_vertice->Getraiz();
            while(tmp!= NULL)
            {
                if(verifGrau(tmp->getVertice()->getId()!= k))
                    return false;
                tmp=tmp->getProximo();
            }
            return true;
        }
        else return false;
    }

    //Verifica se o grafo � um multigrafo (busca por arestas paralelas)
    bool verifica_multigrafo()
    {
        NoListaVertice * aux_ver = Lista_vertice->Getraiz();
        while(aux_ver != NULL)
        {
            NoListaAresta * aux_ar1 = aux_ver->getVertice()->getArestas()->getraiz();
            while(aux_ar1 != NULL)
            {
                NoListaAresta * aux_ar2 = aux_ar1->getProximo();
                while(aux_ar2 != NULL)
                {
                    if(aux_ar1->getAresta()->getProximo()->getId() == aux_ar2->getAresta()->getProximo()->getId())
                        return true;
                    else
                        aux_ar2 = aux_ar2->getProximo();
                }
                aux_ar1 = aux_ar1->getProximo();
            }
            aux_ver = aux_ver->getProximo();
        }
        return false;
    }

    //Verifica se o grafo � completo
    bool verifCompleto()
    {
        if(verifica_multigrafo()) return false;
        if(digrafo)
            if(num_arestas==num_nos*(num_nos-1))
                return true;
            else return false;
        else if(num_arestas==num_nos*(num_nos-1)/2)
            return true;
        else return false;


    }

    //Aplica o algor�timo de floyd
    void menorCaminhoFloyd(int a , int b)
    {
        float* matriz[gera_id_v];
        for(int i=0; i<gera_id_v; i++)
            matriz[i]=new float[gera_id_v];

        NoListaAresta* aux_ar;
        NoListaVertice* aux_ver;
        aux_ver=Lista_vertice->Getraiz();

        for(int i=1; i<gera_id_v; i++)
            for(int j=1; j<gera_id_v; j++)
            {
                if(i==j)matriz[i][j]=0;
                else matriz[i][j]=9999;
            }
        while(aux_ver!=NULL)
        {
            aux_ar=aux_ver->getVertice()->getArestas()->getraiz();
            while(aux_ar!=NULL)
            {

                matriz[aux_ar->getAresta()->getAnterior()->getId()][aux_ar->getAresta()->getProximo()->getId()] = aux_ar->getAresta()->getPeso();
                aux_ar=aux_ar->getProximo();
            }
            aux_ver=aux_ver->getProximo();
        }
        std::cout<<a;
        for(int i=1; i<gera_id_v; i++)
        {
            for(int j=1; j<gera_id_v; j++)
            {
                for(int k=1; k<gera_id_v; k++)
                {
                    if(matriz[i][j]>matriz[i][k]+matriz[k][j])
                    {
                        matriz[i][j]=matriz[i][k]+matriz[k][j];
                        if(i==a&&j==b)std::cout<<"-->"<<k;
                    }
                }
            }

        }
        std::cout<<"-->"<<b<<std::endl;


        /*IMPRIME TODA A MATRIZ!!
         for(int i=1;i<gera_id_v;i++)
         {
             for(int j=1;j<gera_id_v;j++)
                std::cout<<matriz[i][j]<<"\t";
             std::cout<<std::endl;
         }

        */
    }

    //fun��o auxiliar para swap em um ponteiro

    float** geraFloyd()
    {
        float** matriz = new float*[gera_id_v];
        for(int i=0; i<gera_id_v; i++)
            matriz[i]=new float[gera_id_v];

        NoListaAresta* aux_ar;
        NoListaVertice* aux_ver;
        aux_ver=Lista_vertice->Getraiz();

        for(int i=1; i<gera_id_v; i++)
            for(int j=1; j<gera_id_v; j++)
            {
                if(i==j)matriz[i][j]=0;
                else matriz[i][j]=9999;
            }
        while(aux_ver!=NULL)
        {
            aux_ar=aux_ver->getVertice()->getArestas()->getraiz();
            while(aux_ar!=NULL)
            {

                matriz[aux_ar->getAresta()->getAnterior()->getId()][aux_ar->getAresta()->getProximo()->getId()] = aux_ar->getAresta()->getPeso();
                aux_ar=aux_ar->getProximo();
            }
            aux_ver=aux_ver->getProximo();
        }

        for(int i=1; i<gera_id_v; i++)
        {
            for(int j=1; j<gera_id_v; j++)
            {
                for(int k=1; k<gera_id_v; k++)
                {
                    if(matriz[i][j]>matriz[i][k]+matriz[k][j])
                    {
                        matriz[i][j]=matriz[i][k]+matriz[k][j];
                    }
                }
            }

        }
        /* IMPRIME TODA A MATRIZ!!
          for(int i=1;i<gera_id_v;i++)
          {
              for(int j=1;j<gera_id_v;j++)
                 std::cout<<matriz[i][j]<<"\t";
              std::cout<<std::endl;
          }
         */




        return matriz;

    }


    void fechoDireto(int a)
    {
        std::cout<<"Fecho direto do vertice "<<a<<":";
        float** matriz=geraFloyd();
        for(int i=1; i<gera_id_v; i++)
            if(matriz[a][i]!=9999)
                std::cout<<i<<" ";
        std::cout<<std::endl;

    }
    void fechoIndireto(int a)
    {
        std::cout<<"Fecho indireto do vertice "<<a<<":";
        float** matriz=geraFloyd();
        for(int i=1; i<gera_id_v; i++)
            if(matriz[i][a]!=9999)
                std::cout<<i<<" ";
        std::cout<<std::endl;


    }

    void troca (int* vet, int a, int b)
    {
        int aux = vet[a];
        vet[a] = vet[b];
        vet[b] = aux;

    }



    void trocaArestas(Aresta* vet[], int a, int b)
    {
        Aresta* aux = vet[a];
        vet[a] = vet[b];
        vet[b] = aux;

    }

    //Fun��o para ordena��o dos valores no vetor - (booble)
    void sorting(int *vet, int n)
    {
        int iaux, i,j;

        for(i=0; i<n-1; i++)
        {
            iaux=i;
            for(j=i+1; j<n; j++)
            {
                if(vet[j] < vet[iaux])
                    iaux=j;
            }
            if(iaux != i)
                troca(vet,iaux,i);
        }

    }

    void sortingArestas(Aresta* v[], int n)
    {
        int iaux, i,j;

        for(i=0; i<n-1; i++)
        {
            iaux=i;
            for(j=i+1; j<n; j++)
            {
                if(v[j]->getPeso() < v[iaux]->getPeso())
                    iaux=j;
            }
            if(iaux != i)
                trocaArestas(v,iaux,i);
        }

    }

    //Fun��o que imprime todos os graus dos vertives do grafico em ordem crescente
    int* sequenciaGraus()
    {
        int* graus = new int[gera_id_v];
        for(int i=0; i<gera_id_v; i++)
            graus[i]=verifGrau(i);
        //sorting(graus,gera_id_v);
        for(int i=0; i<gera_id_v; i++)
        {
            if(graus[i]!= -1)
                std::cout<<graus[i];

        }

        return graus;
    }

    bool verificaEuleriano()
    {
        int graus[gera_id_v];
        for(int i=1; i<gera_id_v; i++)
        {
            graus[i]=verifGrau(i);
            if(graus[i]%2!=0)return false;
        }
        return true;
    }


    Aresta* buscaAresta(int a, int b)
    {
        if(Lista_vertice->buscaVertice(a)==NULL) return NULL;
        NoListaAresta* tmp=Lista_vertice->buscaVertice(a)->getVertice()->getArestas()->getraiz();
        while(tmp!=NULL)
        {
            if(tmp->getAresta()->getProximo()->getId()== b) return tmp->getAresta();
            tmp=tmp->getProximo();
        }
        return NULL;
    }

    //Fun��o que verifica se o grafo � bipartido
    bool verificaBipartido()
    {
        NoListaVertice* aux_ver = Lista_vertice->Getraiz();
        while(aux_ver != NULL)
        {
            aux_ver->getVertice()->setVizitado(0);
            aux_ver->getVertice()->setFlag(0);
            aux_ver = aux_ver->getProximo();
            std::cout<<"ruan  ";
        }
        aux_ver = Lista_vertice->Getraiz();
        for(int i = 0; i < Lista_vertice->Getquantidade(); i++)
        {
            if(aux_ver->getVertice()->getVizitado() == 0)
            {
                Vertice* v = aux_ver->getVertice();
                if(!verificaBiProf(v, v->getFlag(), v->getVizitado()))
                    return false;
            }
        }
        return true;
    }

    //Fun��o auxiliar para a fun��o de verifica bipartido
    bool verificaBiProf(Vertice* vertice, bool cor, bool viz)
    {

        if((vertice->getVizitado() == 1) && (vertice->getFlag() != cor))
        {
            return false;
        }
        else
        {
            vertice->setFlag(cor);
            vertice->setVizitado(viz);
        }

        NoListaAresta * aux_ar = vertice->getArestas()->getraiz();
        while(aux_ar != NULL)
        {
            if(vertice->getVizitado() == 0)
                verificaBiProf(aux_ar->getAresta()->getProximo(), !cor, 1);
            aux_ar = aux_ar->getProximo();
        }
        return true;
    }

    //Retorna a ordem do grafo
    int ordemGrafo()
    {
        return num_nos;
    }

    //Retorna o grau do grafo
    int grauGrafo()
    {
        return grau;
    }

    //Adiciona um vertive no grafo com peso
    void addVertice(float peso)
    {
        Lista_vertice->addVertice(new Vertice(gera_id_v,peso,0,0));
        gera_id_v++;
        num_nos++;
    }

    //Adiciona um vertice no grafo sem peso
    void addVertice()
    {
        Lista_vertice->addVertice(new Vertice(gera_id_v,0,0,0));
        gera_id_v++;
        num_nos++;
    }



    //Adiciona uma aresta no grafo
    void addAresta(int a , int b, float p)
    {
        Vertice* ant;
        Vertice* prox;
        if(digrafo)
        {
            ant=Lista_vertice->buscaVertice(a)->getVertice();
            prox=Lista_vertice->buscaVertice(b)->getVertice();
            ant->getArestas()->addAresta(new Aresta(0,p,ant,prox));
            if(grau<verifGrau(a)) grau = verifGrau(a);
            num_arestas++;
        }
        else
        {
            //add aresta a-->b
            ant=Lista_vertice->buscaVertice(a)->getVertice();
            prox=Lista_vertice->buscaVertice(b)->getVertice();
            ant->getArestas()->addAresta(new Aresta(0,p,ant,prox));
            if(grau<verifGrau(a)) grau = verifGrau(a);
            num_arestas++;
            //add aresta b-->a
            ant=Lista_vertice->buscaVertice(b)->getVertice();
            prox=Lista_vertice->buscaVertice(a)->getVertice();
            ant->getArestas()->addAresta(new Aresta(0,p,ant,prox));
            if(grau<verifGrau(b)) grau = verifGrau(b);
            num_arestas++;
        }
    }

    //verifica se o grafo � trivial
    bool grafoTrivial ()
    {
        if(num_nos==1) return true;
        else return false;
    }

    //verifica se o grafo � nulo
    bool grafoNulo ()
    {
        if(num_nos==0) return true;
        else return false;
    }

    //imprime a vizinhanca Aberta de um n� com um certo id
    void vizinhancaAberta(int id)
    {
        if(id<=num_nos&&id>0)
        {
            std::cout<<"A vizinhan�a aberta do n�:"<<id<<" Possui os n�s:";
            NoListaAresta* tmp = Lista_vertice->buscaVertice(id)->getVertice()->getArestas()->getraiz();
            int qnt = Lista_vertice->buscaVertice(id)->getVertice()->getArestas()->getQuantidade();
            int v[qnt],i=0,j,k;
            while(tmp!=NULL)
            {
                v[i]=tmp->getAresta()->getProximo()->getId();
                std::cout<<v[i];
                tmp=tmp->getProximo();
                i++;
            }
            std::cout<<std::endl<<"Com as arestas:";
            for(j=0; j<qnt; j++)
            {

                for( k=0; k<qnt; k++)
                {
                    tmp = Lista_vertice->buscaVertice(v[j])->getVertice()->getArestas()->getraiz();
                    while(tmp!=NULL)
                    {
                        if(v[k] == tmp->getAresta()->getProximo()->getId())
                            std::cout<<v[j]<<"-->"<<v[k]<<" ";
                        tmp=tmp->getProximo();
                    }
                }
                std::cout<<std::endl;
            }

        }
    }

    //imprime a vizinhanca Fechada de um n� com um certo id
    void vizinhancaFechada(int id)
    {
        if(id<=num_nos&&id>0)
        {
            std::cout<<"A vizinhan�a fechada do n�:"<<id<<" Possui os n�s:";
            NoListaAresta* tmp = Lista_vertice->buscaVertice(id)->getVertice()->getArestas()->getraiz();
            int qnt = Lista_vertice->buscaVertice(id)->getVertice()->getArestas()->getQuantidade() + 1;
            int v[qnt],i=1,j,k;
            v[0]= id;
            std::cout<<v[0];
            while(tmp!=NULL)
            {
                v[i]=tmp->getAresta()->getProximo()->getId();
                std::cout<<v[i];
                tmp=tmp->getProximo();
                i++;
            }
            std::cout<<std::endl<<"Com as arestas:";
            for(j=0; j<qnt; j++)
            {

                for( k=0; k<qnt; k++)
                {
                    tmp = Lista_vertice->buscaVertice(v[j])->getVertice()->getArestas()->getraiz();
                    while(tmp!=NULL)
                    {
                        if(v[k] == tmp->getAresta()->getProximo()->getId())
                            std::cout<<v[j]<<"-->"<<v[k]<<" ";
                        tmp=tmp->getProximo();
                    }
                }
                std::cout<<std::endl;
            }

        }
    }

    ListaVertice* getListaVertice()
    {
        return Lista_vertice;
    }

    //encontra o grafo complementar
    Grafo* grafoComplementar(Grafo *grafo)
    {
        Grafo *gComp = new Grafo(digrafo);
        bool tinha[gera_id_v-1];
        NoListaVertice *tmpNo = Lista_vertice->Getraiz();
        NoListaAresta *tmpAr;

        while(tmpNo != NULL)
        {
            gComp->addVertice();
            tmpNo = tmpNo->getProximo();
        }

        tmpNo = Lista_vertice->Getraiz();
        while(tmpNo != NULL)
        {
            for(int i = 0; i < gera_id_v-1; i++) tinha[i] = false;
            tmpAr = tmpNo->getVertice()->getArestas()->getraiz();

            //Irforma arestas a serem criadas
            while(tmpAr != NULL)
            {
                tinha[(tmpAr->getAresta()->getProximo()->getId())-1] = true;
                tmpAr = tmpAr->getProximo();
            }

            //cria arestas
            for(int i = 1; i <= gera_id_v-1; i++)
            {
                if(tinha[i-1] == false &&                                         //n�o tinha a aresta
                        gComp->getListaVertice()->buscaVertice(i) != NULL &&           //existe vertice com o id
                        gComp->buscaAresta(tmpNo->getVertice()->getId(), i) == NULL && //impede criar 2 vezes quando n�o digrafo
                        tmpNo->getVertice()->getId() != i)                             //impede selfloop
                {
                    gComp->addAresta(tmpNo->getVertice()->getId(), i, 1);

                    //aresta que n�o tinham no original
                    cout <<endl;
                    cout <<tmpNo->getVertice()->getId() << " " << i;
                }
            }
            tmpNo = tmpNo->getProximo();


        }
        cout<< endl;
        gComp->sequenciaGraus();

        return gComp;
    }

    //limpa os valores das flags nos objetos Vertices
    void limpaVert()
    {
        NoListaVertice* aux_ver = Lista_vertice->Getraiz();
        while(aux_ver != NULL)
        {
            aux_ver->getVertice()->setFlag(0);
            aux_ver = aux_ver->getProximo();
        }
    }

    ListaVertice* getLV()
    {
        return Lista_vertice;
    }
    int getGera()
    {
        return gera_id_v;
    }
    void setGera(int gera)
    {
        gera_id_v=gera;
    }

    Grafo* subgrafoInd(int v[],int n)
    {
        Grafo *sub = new Grafo(false);
        for(int i=0; i<n; i++)
        {
            if(Lista_vertice->buscaVertice(v[i])!= NULL)
            {

                sub->addVertice();
                int aux = v[i];
                sub->getLV()->Getraiz()->getVertice()->setId(aux);
                if(sub->getGera()<=aux) sub->setGera(aux+1);

            }

        }

        /*NoListaVertice* tmp= sub->getLV()->Getraiz();
        while(tmp!=NULL)
        {
            std::cout<<tmp->getVertice()->getId();
            tmp=tmp->getProximo();
        }*/

        for(int i=0; i<n-1; i++)
            for(int j=1; j<n; j++)
                if(buscaAresta(v[i],v[j])!= NULL)
                {

                    sub->addAresta(v[i],v[j],buscaAresta(v[i],v[j])->getPeso());

                }

        /* NoListaVertice* tmp=sub->getLV()->Getraiz();
         NoListaAresta*  tmp2;
         while(tmp!=NULL)
         {
             tmp2=tmp->getVertice()->getArestas()->getraiz();
             while(tmp2!=NULL)
             {
                 std::cout<<tmp2->getAresta()->getAnterior()->getId()<<tmp2->getAresta()->getProximo()->getId()<<std::endl;
                 tmp2=tmp2->getProximo();
             }
             tmp=tmp->getProximo();
         }*/

        return sub;


    }


    bool existeCaminho(int a, int b)
    {

        NoListaVertice* ant = Lista_vertice->buscaVertice(a);
        NoListaAresta* aux;
        if(ant!=NULL)
        {

            if(buscaAresta(a,b)!=NULL)
            {
                return true;
            }
            else
            {
                ant->getVertice()->setFlag(1);
                aux=ant->getVertice()->getArestas()->getraiz();
                while(aux!=NULL)
                {
                    //std::cout<<aux->getAresta()->getProximo()->getId()<<"\t";
                    if(aux->getAresta()->getProximo()->getFlag()==0)
                    {
                        if(existeCaminho(aux->getAresta()->getProximo()->getId(),b)) return true;
                    }
                    else aux=aux->getProximo();
                }
            }
        }
        return false;
    }

    Grafo* AGM()
    {
        Aresta* arestas[num_arestas];
        NoListaVertice* aux_ver = Lista_vertice->Getraiz();
        NoListaAresta* aux_ar;
        int i=0,contador=0;
        while(aux_ver!=NULL)
        {
            aux_ar=aux_ver->getVertice()->getArestas()->getraiz();
            while(aux_ar!=NULL)
            {
                arestas[i]=aux_ar->getAresta();
                i++;
                aux_ar=aux_ar->getProximo();
            }
            aux_ver=aux_ver->getProximo();
        }
        sortingArestas(arestas,num_arestas);



        Grafo* agm = new Grafo(false);
        for(int j=0; j<num_nos; j++)
            agm->addVertice();
        std::cout<<"Imprimindo arestas da AGM:";
        for(int j=0; j<num_arestas&&contador<num_nos-1; j++)
        {
            agm->limpaVert();
            if(!agm->existeCaminho(arestas[j]->getAnterior()->getId(),arestas[j]->getProximo()->getId()))
            {
                std::cout<<arestas[j]->getAnterior()->getId()<<"-->"<<arestas[j]->getProximo()->getId()<<"\t";
                agm->addAresta(arestas[j]->getAnterior()->getId(),arestas[j]->getProximo()->getId(),arestas[j]->getPeso());
                contador++;
            }

        }


        return agm;

    }
    void verPontes ()
    {
        NoListaVertice* aux_ver = Lista_vertice->Getraiz();
        while(aux_ver != NULL)
        {
            NoListaAresta *aux_Pro,*aux_ar = aux_ver->getVertice()->getArestas()->getraiz();
            while(aux_ar != NULL)
            {
                aux_Pro = aux_ar->getProximo();
                Vertice *aux_ver2 = aux_ar->getAresta()->getProximo();
                Aresta ar = *aux_ar->getAresta();
                aux_ver->getVertice()->getArestas()->deletaAresta(aux_ar->getAresta());
                if (!existeCaminho(aux_ver->getVertice()->getId(),aux_ver2->getId()))
                {
                    std::cout<<"E ponte a aresta entre os nos"<<aux_ver->getVertice()->getId()<<"e"<<aux_ver2->getId()<<endl;
                }
                aux_ver->getVertice()->getArestas()->addAresta(&ar);
                aux_ar = aux_Pro;
            }
            aux_ver = aux_ver->getProximo();
        }
    }


   /* bool ehSolucao(int id_Atual, int id_Anterior, int numTerm)
    {

        NoListaVertice* atual = Lista_vertice->buscaVertice(id_Atual);
        NoListaAresta* aux;

        if(atual->getVertice()->getSteiner()) numTerm--;
        if(numTerm == 0) return true;
        atual->getVertice()->setFlag(1);
        aux = atual->getVertice()->getArestas()->getraiz();
        while(aux != NULL){
            if(aux->getAresta()->getProximo()->getFlag()==0)
            {
                if(ehSolucao(aux->getAresta()->getProximo()->getId(), id_Atual, numTerm)) return true;
            }
                aux = aux->getProximo();
        }
        return false;
    }*/


    verificaSteiner(int marcadores[], int terminais[],int num_terminais)
    {
        for(int i=0;i<num_terminais-1;i++)
        {
                cout<<"HA"<<marcadores[terminais[i]]<<" "<<marcadores[terminais[i+1]]<<"HE"<<endl;
            if(marcadores[terminais[i]]!= marcadores[terminais[i+1]])
            {

                return false;
            }
        }
        return true;
    }

    bool removeAresta(int a, int b)
    {



        Lista_vertice->buscaVertice(a)->getVertice()->getArestas()->deletaAresta(buscaAresta(a,b));
        Lista_vertice->buscaVertice(b)->getVertice()->getArestas()->deletaAresta(buscaAresta(b,a));
        return true;
    }

    void setSteiner(int id)
    {
        Lista_vertice->buscaVertice(id)->getVertice()->setSteiner();
        num_terminais++;

    }

    Grafo* gulosoSteiner()
    {
        Grafo* solucao = new Grafo(false);
        for(int i=1; i<=num_nos; i++)
            solucao->addVertice();
        Aresta* candidatos[num_arestas];
        int cont_arestas=0;
        int marcadores[gera_id_v] = {0};
        int terminais[num_terminais];
        int c = 0,marcaAnt,marcaProx;

        //ListaAresta* vcandidatos = new ListaAresta();
        NoListaVertice* tmp = Lista_vertice->Getraiz();
        NoListaAresta* tmp2;
        while(tmp!=NULL)
        {
            if(tmp->getVertice()->getSteiner())
            {
                terminais[c]=tmp->getVertice()->getId();
                marcadores[terminais[c]]=c+1;
                c++;
                tmp2=tmp->getVertice()->getArestas()->getraiz();
                while(tmp2!=NULL)
                {
                    //vcandidatos->addAresta(tmp2->getAresta());
                    if(tmp2->getAresta()!=NULL)
                    {
                    candidatos[cont_arestas]=tmp2->getAresta();
                    cont_arestas++;
                    }
                    tmp2=tmp2->getProximo();

                }

            }
            tmp=tmp->getProximo();
        }

        /*int id_terminal = solVertices->Getraiz()->getVertice()->getId();
        cout<<"AQUI";*/


        cout<<num_terminais;
        while(!verificaSteiner(marcadores,terminais,num_terminais)&&cont_arestas>=0)
        {
            cout<<"HAb";
            sortingArestas(candidatos,cont_arestas);
            marcaAnt=marcadores[candidatos[0]->getAnterior()->getId()];
            marcaProx=marcadores[candidatos[0]->getProximo()->getId()];

            if(marcaAnt>marcaProx)
                {
                    solucao->addAresta(candidatos[0]->getAnterior()->getId(),candidatos[0]->getProximo()->getId(),candidatos[0]->getPeso());
                    if(marcaProx==0)marcadores[candidatos[0]->getProximo()->getId()]= marcaAnt;
                    else
                    {
                        for(int i=1;i<gera_id_v;i++)
                            if(marcadores[i]==marcaProx)marcadores[i]=marcaAnt;
                    }

                cout<<candidatos[0]->getAnterior()->getId()<<"---->"<<candidatos[0]->getProximo()->getId();

                tmp2=candidatos[0]->getProximo()->getArestas()->getraiz();


                    while(tmp2!=NULL)
                    {
                        if(tmp2->getAresta()!=NULL)
                        {
                            candidatos[cont_arestas]=tmp2->getAresta();


                            cont_arestas++;
                        }
                    tmp2=tmp2->getProximo();
                    }
                }


            cout<<"\t"<<cont_arestas<<" ";
            candidatos[0]=candidatos[cont_arestas-1];
            cont_arestas--;
        }



        tmp=solucao->getLV()->Getraiz();
         while(tmp!=NULL)
         {
             tmp2=tmp->getVertice()->getArestas()->getraiz();
             while(tmp2!=NULL)
             {
                 std::cout<<tmp2->getAresta()->getAnterior()->getId()<<"-->"<<tmp2->getAresta()->getProximo()->getId()<<std::endl;
                 tmp2=tmp2->getProximo();
             }
             tmp=tmp->getProximo();
         }





        bool grau1 = false;
        int* v = solucao->sequenciaGraus();
        cout<<endl;
        int no1;
        for(int i=0; i<gera_id_v; i++)
        {
            if(v[i]==1 && !Lista_vertice->buscaVertice(i)->getVertice()->getSteiner())
            {
                cout<<"ESSE AQUI:"<<i<<endl;
            grau1 = true;
            no1=i;
            break;
            }
        }
        while(grau1)
        {
            grau1=false;
            int no2 = solucao->getListaVertice()->buscaVertice(no1)->getVertice()->getArestas()->getraiz()->getAresta()->getProximo()->getId();

            solucao->removeAresta(no1,no2);
            cout<<"removido:"<<no1<<"-->"<<no2<<endl;
            //solucao->removeAresta(no2,no1);
            v = solucao->sequenciaGraus();
            cout<<endl;
            for(int i=0; i<gera_id_v; i++)
            {

                if(v[i]==1&&!Lista_vertice->buscaVertice(i)->getVertice()->getSteiner())
                {
                    cout<<"ESSE AQUI:"<<i<<endl;
                    grau1 = true;
                    no1=i;
                    break;
                }
            }

        }

        float soma=0.0;
        tmp=solucao->getLV()->Getraiz();
         while(tmp!=NULL)
         {
             tmp2=tmp->getVertice()->getArestas()->getraiz();
             while(tmp2!=NULL)
             {
                 std::cout<<tmp2->getAresta()->getAnterior()->getId()<<"-->"<<tmp2->getAresta()->getProximo()->getId()<<std::endl;
                 soma+=tmp2->getAresta()->getPeso();
                 tmp2=tmp2->getProximo();
             }
             tmp=tmp->getProximo();
         }



        cout<<soma/2;
        return solucao;


    }



    /*  void addVertice(float peso, int id)
            {
                Lista_vertice->addVertice(new Vertice(id,peso,0,0));
                num_nos++;
            }
         */

    /*
        void caminhoMinimo(int a, int b, bool dijskra)
        {

            //limpaVert();

            if(dijskra)
            {
                std::cout<<"Procurando o menor caminho pelo metodo de Dijkstra"<<std::endl;
                // 0 = S' && 1 = S //
                ListaVertice *lista=new ListaVertice();
                lista->addVertice(new Vertice(a,0,0,0));
                float pi[num_nos+1];
                for(int i=0;i<num_nos+1;i++)
                    pi[i]=999999999999;
                int seletor,seletor_ant;
                Vertice* va = Lista_vertice->buscaVertice(a)->getVertice();
                va->setFlag(1);
                NoListaAresta *tmp=va->getArestas()->getraiz();
                while(tmp!=NULL)
                {
                    pi[tmp->getAresta()->getProximo()->getId()]=tmp->getAresta()->getPeso();
                    tmp=tmp->getProximo();
                }
                seletor_ant=a;
                seletor = menorPi(pi,num_nos+1);
                lista->addVertice(new Vertice(seletor,0,0,0));
                va=Lista_vertice->buscaVertice(seletor)->getVertice();
                va->setFlag(1);

                while(va!=Lista_vertice->buscaVertice(b)->getVertice())
                {
                NoListaAresta *tmp=va->getArestas()->getraiz();
                    while(tmp!=NULL)
                {
                    if(pi[seletor]+tmp->getAresta()->getPeso()< pi[tmp->getAresta()->getProximo()->getId()])
                    pi[tmp->getAresta()->getProximo()->getId()]=pi[seletor]+tmp->getAresta()->getPeso();
                    tmp=tmp->getProximo();
                }
                seletor_ant=seletor;
                seletor = menorPi(pi,num_nos+1);

                if(buscaAresta(seletor_ant,seletor)!=NULL)
                {
                lista->addVertice(new Vertice(seletor,0,0,0));
                va=Lista_vertice->buscaVertice(seletor)->getVertice();
                va->setFlag(1);
                }
                else
                {
                    lista->deletaVertice(seletor_ant);
                    lista->addVertice(new Vertice(seletor,0,0,0));
                    va=Lista_vertice->buscaVertice(seletor)->getVertice();
                    va->setFlag(1);
                }
                }
                NoListaVertice* imprime = lista->Getraiz();
                while(imprime!=NULL)
                {
                std::cout<<imprime->getVertice()->getId()<<"-->";
                imprime=imprime->getProximo();
                }

            }
        }


    */





};

#endif // GRAFO_H
