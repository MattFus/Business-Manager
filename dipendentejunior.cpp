#include "dipendentejunior.h"

#include "sstream"

dipendenteJunior::dipendenteJunior()
{

}

dipendenteJunior::dipendenteJunior(string m,string n,string c,double s,list<string> _skill,string _stagista):dipendente(m,n,c,s){
    skills=_skill;
    stagista=_stagista;
}

list<string> dipendenteJunior::get_skills()const{
    return skills;
}

string dipendenteJunior::get_stagista()const{
    return stagista;
}
