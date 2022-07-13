#include "progetto.h"

progetto::progetto()
{

}

progetto::progetto(string _nome,string _data,int _durata,double _budget,string _responsabile){
    nome=_nome;
    data=_data;
    durata=_durata;
    budget=_budget;
    responsabile=_responsabile;
}

string progetto::get_nome()const{
    return nome;
}
string progetto::get_data()const{
    return data;
}
int progetto::get_durata()const{
    return durata;
}
double progetto::get_budget()const{
    return budget;
}
string progetto::get_responsabile()const{
    return responsabile;
}

void progetto::set_data(string _data){
    data=_data;
}
void progetto::set_durata(int _durata){
    durata=_durata;
}
void progetto::set_budget(double _budget){
    budget=_budget;
}
void progetto::set_responsabile(string _responsabile){
    responsabile=_responsabile;
}
