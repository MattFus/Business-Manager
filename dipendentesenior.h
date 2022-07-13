#ifndef DIPENDENTESENIOR_H
#define DIPENDENTESENIOR_H

#include "dipendente.h"

class dipendenteSenior: public dipendente
{
public:
    dipendenteSenior();
    dipendenteSenior(string m,string n,string c,double s,list<string> r,list<string> sub={});

    list<string> get_reperibilita() const;
    list<string> get_subordinati() const;

    dipendenteSenior* clone()const{
        return new dipendenteSenior(*this);
    }

    friend ostream& operator<<(ostream& out,dipendenteSenior& dj){
        return dj.stampa(out);
    }
protected:
    ostream& stampa(ostream& out){
        dipendente::stampa(out);
        out<<endl<<" - Giorni reperibile: ";
        for(auto element: reperibilita){
            out<<element<<"-";
        }

        out<<endl<<" - Subordinati: ";
        if(subordinati.empty()){
            out<<"Nessun subordinato";
        }

        else{
            for(auto element: subordinati){
                out<<element<<"-";
            }
        }
        return out;
    }

private:
    list<string> reperibilita;
    list<string> subordinati;
};

#endif // DIPENDENTESENIOR_H
