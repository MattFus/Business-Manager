#ifndef DIPENDENTE_H
#define DIPENDENTE_H

#include <iostream>
#include <string>
#include <list>
using namespace std;

class dipendente
{
public:
    dipendente();
    dipendente(string _matricola,string _nome,string _cognome,double _stipendio);
    virtual ~dipendente(){}

    string get_matricola();
    string get_nome();
    string get_cognome();
    double get_stipendio();

    void set_nome(string _nome);
    void set_cognome(string _cognome);
    void set_stipendio(double _stipendio);

    virtual dipendente* clone()const{
        return new dipendente(*this);
    }

    friend ostream& operator<<(ostream& out,dipendente& d){
        return d.stampa(out);
    }
protected:
    virtual ostream& stampa(ostream& out)const{
        out<<nome<< " "<<cognome<< " - " << "Matricola: "<<matricola<< " - " << "Stipendio: "<<stipendio;
        return out;
    }
private:
    string matricola;
    string nome;
    string cognome;
    double stipendio;
};

#endif // DIPENDENTE_H
