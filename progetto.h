#ifndef PROGETTO_H
#define PROGETTO_H

#include <string>
#include <iostream>
using namespace std;

class progetto
{
public:
    progetto();
    progetto(string _nome,string _data,int _durata,double _budget,string _responsabile=" ");

    string get_nome()const;
    string get_data()const;
    int get_durata()const;
    double get_budget()const;
    string get_responsabile()const;

    void set_data(string _data);
    void set_durata(int _durata);
    void set_budget(double _budget);
    void set_responsabile(string _responsabile);

    progetto* clone()const{
        return new progetto(*this);
    }

    friend ostream& operator<<(ostream& out,progetto& p){
        return p.stampa(out);
    }
protected:
    ostream& stampa(ostream& out){
        out<<nome<<" |Data: "<<data<<" |Durata: "<<durata<<" |Budget: "<<budget<<" |Responsabile: "<<responsabile;
        return out;
    }
private:
    string nome;
    string data;
    int durata;
    double budget;
    string responsabile;
};

#endif // PROGETTO_H
