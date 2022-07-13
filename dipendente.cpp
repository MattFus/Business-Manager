#include "dipendente.h"

dipendente::dipendente()
{

}

dipendente::dipendente(string _matricola,string _nome,string _cognome,double _stipendio){
    matricola=_matricola;
    nome=_nome;
    cognome=_cognome;
    stipendio=_stipendio;
}

string dipendente::get_matricola(){
    return matricola;
}
string dipendente::get_nome(){
    return nome;
}
string dipendente::get_cognome(){
    return cognome;
}
double dipendente::get_stipendio(){
    return stipendio;
}

void dipendente::set_nome(string _nome){
    nome=_nome;
}
void dipendente::set_cognome(string _cognome){
    cognome=_cognome;
}
void dipendente::set_stipendio(double _stipendio){
    stipendio=_stipendio;
}
