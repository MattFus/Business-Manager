#include "dipendentesenior.h"

dipendenteSenior::dipendenteSenior()
{

}

dipendenteSenior::dipendenteSenior(string m,string n,string c,double s,list<string> r,list<string> sub):dipendente(m,n,c,s){
    subordinati=sub;
    reperibilita=r;
}


list<string> dipendenteSenior:: get_reperibilita() const{
    return reperibilita;
}
list<string> dipendenteSenior:: get_subordinati() const{
    return subordinati;
}
