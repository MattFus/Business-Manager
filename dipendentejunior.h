#ifndef DIPENDENTEJUNIOR_H
#define DIPENDENTEJUNIOR_H

#include "dipendente.h"

class dipendenteJunior: public dipendente
{
public:
    dipendenteJunior();
    dipendenteJunior(string m,string n,string c,double s,list<string> _skill,string _stagista=" ");

    list<string> get_skills()const;
    string get_stagista()const;

    dipendenteJunior* clone()const{
        return new dipendenteJunior(*this);
    }

    friend ostream& operator<<(ostream& out,dipendenteJunior& dj){
        return dj.stampa(out);
    }
protected:
    ostream& stampa(ostream& out){
        dipendente::stampa(out);
        out<<endl<<" - Skill: ";
        for(auto element: skills){
            out<<element<<"-";
        }

        out<<endl<<" - Stagista: ";
        if(!stagista.empty()){
            out<<stagista;
        }
        else
            out<<"nessuno stagista";

        return out;
    }

private:
    list<string> skills;
    string stagista;
};


#endif // DIPENDENTEJUNIOR_H
