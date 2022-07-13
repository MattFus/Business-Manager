#ifndef CLASSEPROGETTO_H
#define CLASSEPROGETTO_H

#include "Dipendente.h"

class Progetto{
public:
    Progetto();
    Progetto(string _nome,string _data,int _durata,double _budget,string _responsabile);

    void stampa();
private:
    //string nome, string data, int durata, double budget, string responsabile
    string nome;
    string data;
    int durata;
    double budget;
    string responsabile;
};

Progetto::Progetto(){
    nome=" ";
    data=" ";
    durata=0;
    budget=0;
}

Progetto::Progetto(string _nome,string _data,int _durata,double _budget,string _responsabile){
    nome=_nome;
    data=_data;
    durata=_durata;
    budget=_budget;
    responsabile=_responsabile;
}

void Progetto::stampa(){
    cout<<"Progetto: "<<nome;
    cout<<" |Data: "<<data<<" |Durata: "<<durata<<" |Budget: "<<budget;
    cout<<" || Responsabile: "<<responsabile;
}
#endif
