#include "gestore.h"
#include <sstream>
#include <algorithm>
#include <utility>

const double MAX_BUDGET=100000.00;


//ORDINAMENTI
bool contatoriB5(pair<string,int> p1,pair<string,int> p2){
    if(p1.second>=p2.second)
        return true;
    return false;
}

bool ordinamentoBudgetCrescente(const progetto* p1,const progetto* p2){
    return p1->get_budget()<p2->get_budget();
}

bool ordinamentoBudgetDecrescente(const progetto* p1,const progetto* p2){
    return p1->get_budget()>p2->get_budget();
}

bool ordinamentoDataCrescente(const progetto* p1,const progetto* p2){
    return p1->get_data()<p2->get_data();
}

bool ordinamentoDataDecrescente(const progetto* p1,const progetto* p2){
    return p1->get_data()>p2->get_data();
}

bool ordinamentoMetodoB14(const progetto* p1,const progetto* p2){
    if(p1->get_durata()==p2->get_durata()){
        if(p1->get_budget()==p2->get_budget()){
            return p1->get_nome()<p2->get_nome();
        }
        else
            return p1->get_budget()<p2->get_budget();
    }
    else
        return p1->get_durata()>p2->get_durata();

    return true;
}
//FINE ORDINAMENTI


//CONTROLLI DATE METODI C4 E C5
bool controlloDataC4(string data1,int durata1,string data2,int durata2){
    string anno1;
    string anno2;
    string mese1;
    string mese2;

    for(int i =0;i<4;i++){
        anno1+=data1[i];
        anno2+=data2[i];
    }
    for(int i = 5;i<7;i++){
        mese1+=data1[i];
        mese2+=data2[i];
    }
    if(anno1==anno2){
        int meseS=stoi(mese1);
        int meseP=stoi(mese2);
        if(meseS+durata1==meseP+durata2)
            return true;
    }
    return false;
}

bool controlloDataC5(string data1,int durata1,string data2,int durata2){
    //FORMATO DATA AAAA/MM/DD
    //             0123 56 89
    string annoInizio_data1;
    string meseInizio_data1;
    string giornoInizio_data1;
    string annoInizio_data2;
    string meseInizio_data2;
    string giornoInizio_data2;

    for(int i=0;i<4;i++){
        annoInizio_data1+=data1[i];
        annoInizio_data2+=data2[i];
    }
    for(int i=5;i<7;i++){
        meseInizio_data1+=data1[i];
        meseInizio_data2+=data2[i];
    }
    for(int i=8;i<10;i++){
        giornoInizio_data1+=data1[i];
        giornoInizio_data2+=data2[i];
    }

    //trasformo in int -> date inizio
    int StartYear_data1=stoi(annoInizio_data1);
    int StartMonth_data1=stoi(meseInizio_data1);
    int StartDay_data1=stoi(giornoInizio_data1);
    int StartYear_data2=stoi(annoInizio_data2);
    int StartMonth_data2=stoi(meseInizio_data2);
    int StartDay_data2=stoi(giornoInizio_data2);

    //trovo le date di fine con le date di inizio e le durate
    int EndYear_data1=StartYear_data1;
    int EndMonth_data1=0;
    int EndDay_data1=StartDay_data1;
    int EndYear_data2=StartYear_data2;
    int EndMonth_data2=0;
    int EndDay_data2=StartDay_data2;

    if(durata1+StartMonth_data1>12){    //devo aumentare l'anno e settare il nuovo mese
        if(durata1>12){
            while(durata1>12){
                EndYear_data1+=1;
                durata1-=12;
            }
            EndMonth_data1=(durata1+StartMonth_data1)-12;
        }
        else{
            EndMonth_data1=(durata1+StartMonth_data1)-12;
            EndYear_data1+=1;
        }
    }
    else{
        EndMonth_data1=StartMonth_data1+durata1;
    }

    if(durata2+StartMonth_data2>12){    //devo aumentare l'anno e settare il nuovo mese
        if(durata2>12){
            while(durata2>12){
                EndYear_data2+=1;
                durata2-=12;
            }
            EndMonth_data2=(durata2+StartMonth_data2)-12;
        }
        else{
            EndMonth_data2=(durata2+StartMonth_data2)-12;
            EndYear_data2+=1;
        }
    }
    else{
        EndMonth_data2=StartMonth_data2+durata2;
    }
    //Ora confronto date di fine progetto e date di inizio progetto di entrambi i progetti

    if(StartYear_data1>EndYear_data2 || StartYear_data2>EndYear_data1)
        return true;
    else{   //gli anni sono uguali->controllo i mesi
        if(StartMonth_data1>EndMonth_data2 || StartMonth_data2>EndMonth_data1)
            return true;
        else{   //i mesi sono uguali->controllo i giorni
            if(StartDay_data1>=EndDay_data2 || StartDay_data2>=EndDay_data1)
                return true;
        }
    }
return false;
}
//FINE CONTROLLI DATE METODI C4 E C5

//INIZIO GESTORE.CPP=======================================================================================================================================================

Gestore::Gestore(){}
//GESTISCO MEMORIA DINAMICA -> REGOLA DEI 3
Gestore::~Gestore(){
    clear();
}

Gestore::Gestore(const Gestore& orig){
    for(auto element : orig.ElencoJunior){
        ElencoJunior.push_back(element->clone());
    }

    for(auto element : orig.ElencoSenior){
        ElencoSenior.push_back(element->clone());
    }

    for(auto element : orig.ElencoTuttiDipendenti){
        ElencoTuttiDipendenti.push_back(element->clone());
    }

    for(auto element : orig.ElencoProgetti){
        ElencoProgetti.push_back(element->clone());
    }
}

Gestore& Gestore::operator=(const Gestore& orig){
    if(this != &orig){
        clear();
        for(auto element : orig.ElencoJunior){
            ElencoJunior.push_back(element->clone());
        }

        for(auto element : orig.ElencoSenior){
            ElencoSenior.push_back(element->clone());
        }

        for(auto element : orig.ElencoTuttiDipendenti){
            ElencoTuttiDipendenti.push_back(element->clone());
        }

        for(auto element : orig.ElencoProgetti){
            ElencoProgetti.push_back(element->clone());
        }
    }
    return *this;
}

void Gestore::clear(){
    while(!ElencoJunior.empty()){
        delete ElencoJunior.back();
        ElencoJunior.pop_back();
    }

    while(!ElencoSenior.empty()){
        delete ElencoSenior.back();
        ElencoSenior.pop_back();
    }

    while(!ElencoTuttiDipendenti.empty()){
        delete ElencoTuttiDipendenti.back();
        ElencoTuttiDipendenti.pop_back();
    }

    while(!ElencoProgetti.empty()){
        delete ElencoProgetti.back();
        ElencoProgetti.pop_back();
    }
}

//METODI DI CONTROLLO
bool Gestore::get_dipendente(string _matricola){
    for(auto element : ElencoTuttiDipendenti){
        if(element->get_matricola()==_matricola)
            return true;
    }
    return false;
}

bool Gestore::get_dipendenteJunior(string _matricola){
    for(auto element : ElencoJunior){
        if(element->get_matricola()==_matricola)
            return true;
    }
    return false;
}

bool Gestore::get_dipendenteSenior(string _matricola){
    for(auto element :ElencoSenior){
        if(element->get_matricola()==_matricola)
            return true;
    }
    return false;
}

bool Gestore::get_progetto(string _nome){
    for(auto element : ElencoProgetti){
        if(element->get_nome()==_nome)
            return true;
    }
    return false;
}
//FINE METODI DI CONTROLLO

list<dipendenteJunior*> Gestore::get_elencoJunior()const{
    return ElencoJunior;
}

list<dipendenteSenior*> Gestore::get_elencoSenior() const{
    return ElencoSenior;
}

list<string> Gestore::get_skillDipendenteJunior(string matricolaJunior)const{
    list<string> JuniorSkills;
    for(auto junior : ElencoJunior){
        if(junior->get_matricola()==matricolaJunior){
            JuniorSkills=junior->get_skills();
            break;
        }
    }
    return JuniorSkills;
}

/*
***
SEZIONE A
***
*/

//A1: Aggiunta di un dipendente senior.
bool Gestore::aggiungiDipendenteSenior(string matricola, string nome, string cognome, double stipendio, const list<string>& reperibilita, const list<string>& subordinati){
    if(!get_dipendente(matricola)){
        dipendenteSenior* ds=new dipendenteSenior(matricola,nome,cognome,stipendio,reperibilita,subordinati);
        dipendente* d=new dipendente(matricola,nome,cognome,stipendio);
        ElencoSenior.push_back(ds);
        ElencoTuttiDipendenti.push_back(d);
        return true;
    }
    return false;
}

//A2: Aggiunta di un dipendente junior.
bool Gestore::aggiungiDipendenteJunior(string matricola,string nome,string cognome,double stipendio,const list<string>& skill,const string stagista){
    if(!get_dipendente(matricola)){
        dipendenteJunior* ds=new dipendenteJunior(matricola,nome,cognome,stipendio,skill,stagista);
        dipendente* d=new dipendente(matricola,nome,cognome,stipendio);
        ElencoJunior.push_back(ds);
        ElencoTuttiDipendenti.push_back(d);
        return true;
    }
    return false;
}

//A3: Aggiunta di un progetto.
bool Gestore::aggiungiProgetto(string nome, string data, int durata, double budget, string responsabile){
    if(!get_progetto(nome)){
        progetto* p=new progetto(nome,data,durata,budget,responsabile);
        ElencoProgetti.push_back(p);
        return true;
    }
    return false;
}

//A4: Visualizzare tutti i dipendenti.
list<dipendente*> Gestore::getDipendenti()const{
    return ElencoTuttiDipendenti;
}

//A5: Visualizzare tutti i progetti.
list<progetto*> Gestore::getProgetti()const{
    return ElencoProgetti;
}


/*
***
SEZIONE B
***
*/

//B1: Visualizzare tutti i progetti di cui un dipendente senior è responsabile.
list<progetto*> Gestore::b1(string matricola) const{
    list<progetto*> ListaProgetti_Senior;
    for(auto element : ElencoProgetti){
        if(element->get_responsabile()==matricola){
            ListaProgetti_Senior.push_back(element);
        }
    }
    return ListaProgetti_Senior;
}

//B2: Visualizzare tutti i progetti di cui un dipendente junior è partecipante.
list<progetto*> Gestore::b2(string matricola) const{
    list<progetto*> ListaProgetti_Junior;
    for(auto senior : ElencoSenior){
        list<string> Subordinati = senior->get_subordinati();
        for(auto sub : Subordinati){
            if(sub==matricola){
                for(auto progetto : ElencoProgetti){
                    if(progetto->get_responsabile()==senior->get_matricola()){
                       ListaProgetti_Junior.push_back(progetto);
                    }
                }
            }
        }
    }
    return ListaProgetti_Junior;
}

//B3: Visualizzare tutte le skill (senza duplicati) dei dipendenti partecipanti a un progetto.
list<string> Gestore::b3(string nomeProgetto) const{
    list<string> ListaSkill;
    //trovo la matricola del senior da ElencoProgetti->prendo i subs->prendo le skill->unique()
    for(auto progetto : ElencoProgetti){
        if(progetto->get_nome() == nomeProgetto){
            for(auto senior : ElencoSenior){
                if(senior->get_matricola() == progetto->get_responsabile()){
                    list<string> subordinati = senior->get_subordinati();
                    for(auto sub : subordinati){
                        list<string> junior_skill = get_skillDipendenteJunior(sub);
                        for(auto skill : junior_skill){
                            if(find(ListaSkill.begin(),ListaSkill.end(),skill) == ListaSkill.end())
                                ListaSkill.push_back(skill);
                        }
                    }
                }
            }
        }
    }
    return ListaSkill;
}

//B4: Visualizzare le skill comuni in tutti i dipendenti.
list<string> Gestore::b4()const{
    list<string> allSkills;
    list<string> ListaSkill;
    list<string> JuniorSkills;
    for(auto junior : ElencoJunior){
        JuniorSkills = junior->get_skills();
        for(auto skill : JuniorSkills){
            if(find(allSkills.begin(),allSkills.end(),skill)==allSkills.end()){
                allSkills.push_back(skill);
            }
        }
    }

    for(auto skill : allSkills){
        bool presente=true;
        for(auto junior : ElencoJunior){
            JuniorSkills = junior->get_skills();
            if(find(JuniorSkills.begin(),JuniorSkills.end(),skill)==JuniorSkills.end())
                presente=false;
        }
        if(presente)
            ListaSkill.push_back(skill);
    }
    return ListaSkill;
}

//B5: Visualizzare le 5 skill più diffuse tra i dipendenti
vector<string> Gestore::b5() const{
    //prendo tutte le skill, le salvo, le conto, le prime 5 si salvano, dopo controllo i cont(1..5) se uno è minore scambio con la nuova skill;
    list<pair<string,int>> pairList;
    list<string> AllSkills;
    vector<string> ListaSkill;

    for(auto junior : ElencoJunior){
        list<string> junior_skill = junior->get_skills();
        for(auto skill : junior_skill){
            AllSkills.push_back(skill);
        }
    }

    for(auto skill : AllSkills){
        int cont = 0;
        for(auto element : AllSkills){
            if(element == skill)
                cont++;
        }
        bool trovato = false;
        for(auto element : pairList){
            if(element.first == skill)
                trovato = true;
        }
        if(!trovato)
            pairList.push_back(make_pair(skill,cont));
    }
    pairList.sort(contatoriB5);
    pairList.unique();
    pairList.resize(5);
    for(auto element : pairList){
        ListaSkill.push_back(element.first+","+to_string(element.second));
    }
    return ListaSkill;
}

//B6: Visualizzare i progetti i cui dipendenti non hanno skill in comune.
list<progetto*> Gestore::b6() const{
    //prendo tutti i progetti e per ogni progetto cerco il responsabile->lista subordinati-> ogni subordinato le skill->controllo
    list<progetto*> ListaProgetti;

    for(auto progetto : ElencoProgetti){
        bool inComune=false;
        for(auto senior : ElencoSenior){
            if(senior->get_matricola() == progetto->get_responsabile()){
                list<string> subordinati = senior->get_subordinati();
                for(auto sub1 : subordinati){
                    list<string> skillSub_corrente=get_skillDipendenteJunior(sub1);
                    for(auto sub2: subordinati){
                        if(sub2!=sub1){
                            list<string> skillSub_confronto=get_skillDipendenteJunior(sub2);
                            for(auto skill : skillSub_corrente){
                                if(find(skillSub_confronto.begin(),skillSub_confronto.end(),skill)!=skillSub_confronto.end())
                                    inComune=true;
                            }
                        }
                    }
                }
            }
        }
        if(!inComune){
            bool presente=false;
            for(auto element : ListaProgetti){
                if(element->get_nome()==progetto->get_nome())
                    presente = true;
            }
            if(!presente)
                ListaProgetti.push_back(progetto);
        }
    }

    return ListaProgetti;
}

//B7: Visualizzare il progetto con il budget più basso tra tutti i progetti di un responsabile.
list<string> Gestore::b7(string matricola) const{
    //prendo tutti i progetti di "Matricola" e trovo il min per budget //-> potrei usare min_element();
    list<string> ListaProgetti;
    list<progetto*> ProgettiSenior = b1(matricola);
    double min_budget=MAX_BUDGET;
    for(auto progetto : ProgettiSenior){
        if(progetto->get_budget()<min_budget){
            min_budget=progetto->get_budget();
            ListaProgetti.clear();
            ListaProgetti.push_back(progetto->get_nome());
        }
        else if(progetto->get_budget()==min_budget){
            ListaProgetti.push_back(progetto->get_nome());
        }
    }
    return ListaProgetti;
}

//B8: Visualizzare il progetto con il budget più alto tra tutti i progetti di un responsabile.
list<string> Gestore::b8(string matricola) const{
    //b7 ma trovo il max per budget //-> potrei usare max_element();
    list<string> ListaProgetti;
    list<progetto*> ProgettiSenior = b1(matricola);
    double max_budget=0;
    for(auto progetto : ProgettiSenior){
        if(progetto->get_budget()>max_budget){
            max_budget=progetto->get_budget();
            ListaProgetti.clear();
            ListaProgetti.push_back(progetto->get_nome());
        }
        else if(progetto->get_budget()==max_budget){
            ListaProgetti.push_back(progetto->get_nome());
        }
    }
    return ListaProgetti;
}

//B9: Visualizzare la media dei budget di tutti i progetti di un responsabile.
double Gestore::b9(string matricola) const{
    //sommo i budget di tutti i progetti di "Matricola" e divido per il numero di progetti di cui "Matricola" è responsabile
    list<progetto*> ProgettiSenior=b1(matricola);
    double somma_budget=0;
    double media=0;
    for(auto progetto : ProgettiSenior){
        somma_budget+=progetto->get_budget();
    }
    if(somma_budget==0){
        return media;
    }
    else
        media=somma_budget/ProgettiSenior.size();
    return media;
}

//B10: Visualizzare tutti i progetti ordinati per budget crescente.
list<progetto*> Gestore::b10() const{
    list<progetto*> ListaProgetti=ElencoProgetti;
    ListaProgetti.sort(ordinamentoBudgetCrescente);
    return ListaProgetti;
}

//B11: Visualizzare tutti i progetti ordinati per budget decrescente
list<progetto*> Gestore::b11() const{
    list<progetto*> ListaProgetti=ElencoProgetti;
    ListaProgetti.sort(ordinamentoBudgetDecrescente);
    return ListaProgetti;
}

//B12: Visualizzare tutti i progetti ordinati per data di inizio crescente.
list<progetto*> Gestore::b12() const{
    list<progetto*> ListaProgetti=ElencoProgetti;
    ListaProgetti.sort(ordinamentoDataCrescente);
    return ListaProgetti;
}

//B13: Visualizzare tutti i progetti ordinati per data di inizio decrescente.
list<progetto*> Gestore::b13() const{
    list<progetto*> ListaProgetti=ElencoProgetti;
    ListaProgetti.sort(ordinamentoDataDecrescente);
    return ListaProgetti;
}

//B14: Visualizzare tutti i progetti ordinati per durata decrescente, a parità di durata, ordinati per budget crescente e, a parità di durata, ordinati in ordine alfabetico del nome.
list<progetto*> Gestore::b14() const{
    list<progetto*> ListaProgetti=ElencoProgetti;
    ListaProgetti.sort(ordinamentoMetodoB14);
    return ListaProgetti;
}

/*
***
SEZIONE C
***
*/

//C1: Il guadagno di una skill è definito come la somma dei budget di tutti i progetti in cui c’è almeno un dipendente con quella skill partecipante al progetto. Visualizzare tutte le skill con il guadagno più alto.
list<string> Gestore::c1() const{
    //per ogni skill controllo in quali progetti è presente, se è presente aggiungo il budget del progetto alla somma del budget della skill, se è maggiore->clear() su ListaSkill e poi aggiungo, se è uguale aggiungo.
    list<string> ListaSkill;
    list<string> allSkills;
    double Tot_budget=0;
    for(auto junior : ElencoJunior){
        list<string> junior_skill = junior->get_skills();
        for(auto skill : junior_skill){
            allSkills.push_back(skill);
        }
    }
    allSkills.sort();   //ordinamento alfabetico
    allSkills.unique(); // rimuovo duplicati

    for(auto skill : allSkills){
        double skill_budget=0;
        for(auto progetto : ElencoProgetti){
            bool presente=false;
            string matricola_senior=progetto->get_responsabile();
            for(auto senior : ElencoSenior){
                if(senior->get_matricola() == matricola_senior){
                    list<string> subordinati = senior->get_subordinati();
                    for(auto sub : subordinati){
                        list<string> junior_skills = get_skillDipendenteJunior(sub);
                        if(find(junior_skills.begin(),junior_skills.end(),skill) != junior_skills.end())
                            presente = true;
                    }
                }
            }
            if(presente){
                skill_budget+=progetto->get_budget();
            }
        }

        //cout<<"SKILL : "<<skill<<" - BUDGET: "<<skill_budget<<endl;
        if(skill_budget > Tot_budget){
            Tot_budget = skill_budget;
            ListaSkill.clear();
            ListaSkill.push_back(skill);
        }
        else if(skill_budget == Tot_budget)
            ListaSkill.push_back(skill);
    }

    ListaSkill.sort();
    return ListaSkill;
}

//C2: Visualizzare i dipendenti senior indispensabili. Un dipendente senior D1 è considerato indispensabile se esiste un altro dipendente senior D2 tale che le skill dei subordinati di D1 sono un soprainsieme proprio delle skill dei subordinati di D2.
list<dipendenteSenior*> Gestore::c2() const{
    list<dipendenteSenior*> ListaSenior;
    list<string> matricoleJunior;

    //per ogni senior->prendo le skill dei subs->trovo senior_2,prendo le skill dei subs_2->controllo
    for (auto senior : ElencoSenior){
        list<string> skillSenior;
        matricoleJunior=senior->get_subordinati();
        for(auto matricola : matricoleJunior){
            list<string> skill_junior=get_skillDipendenteJunior(matricola);
            for(auto skill : skill_junior){
                skillSenior.push_back(skill);
            }
        }
        for(auto senior2 : ElencoSenior){
            list<string> skillSenior_2;
            matricoleJunior=senior2->get_subordinati();
            for(auto matricola : matricoleJunior){
                list<string> skill_junior=get_skillDipendenteJunior(matricola);
                for(auto skill : skill_junior){
                    skillSenior_2.push_back(skill);
                }
            }
            if(skillSenior.size()>skillSenior_2.size()){
                if(includes(skillSenior.begin(),skillSenior.end(),skillSenior_2.begin(),skillSenior_2.end())){  //se tutte le skill di skillSenior_2 sono in skillSenior -> è un soprainsieme
                    bool presente = false;
                    for(auto element : ListaSenior){
                        if(element->get_matricola()==senior->get_matricola())
                            presente = true;
                    }
                    if(!presente)
                        ListaSenior.push_back(senior);
                }
            }
        }
    }
    return ListaSenior;
}

/*C3: Visualizzare tutti i dipendenti junior influenzati da un dipendente senior. Un dipendente junior D1 influenza un altro dipendente junior D2 se
- D2 è uno stagista di D1, oppure
- D1 influenza un dipendente junior D e D influenza DJ
Un dipendente senior DS influenza un dipendente junior DJ se DJ è un subordinato di DS oppure se esiste un dipendente D che è subordinato di DS e D influenza DJ.
*/
list<dipendenteJunior*> Gestore::c3(string matricola) const{
    list<dipendenteJunior*> ListaJunior;

    for(auto senior : ElencoSenior){                        //trovo i subs del DipendenteSenior
        if(senior->get_matricola()==matricola){
            list<string> matricoleJunior=senior->get_subordinati();
            for(auto matricola : matricoleJunior){
                for(auto junior : ElencoJunior){
                    if(junior->get_matricola()==matricola){
                        if(find(matricoleJunior.begin(),matricoleJunior.end(),junior->get_stagista())==matricoleJunior.end()) //controllo se lo stagista di junior non è già presente-> aggiungo.
                            matricoleJunior.push_back(junior->get_stagista());  //aggiungo il suo stagista se serve.
                        bool presente=false;
                        for(auto element : ListaJunior){
                            if(element->get_matricola()==junior->get_matricola())   //se il junior è già nella lista ListaJunior non lo aggiungo.
                                presente=true;
                        }
                        if(!presente)
                            ListaJunior.push_back(junior);
                    }
                }
            }
        }
    }
    return ListaJunior;
}

//C4: Visualizzare i progetti simili a un progetto specificato dall’utente. Un progetto è simile a un altro progetto se il numero di skill che hanno in comune è almeno il doppio rispetto al numero di skill che non hanno in comune e se finiscono nello stesso mese.
list<progetto*> Gestore::c4(string nomeProgetto) const{
    list<progetto*> ListaProgetti;
    //prendo tutte le skill dei dipendenti che partecipano al progetto "nomeProgetto"  e la data->prendo le skill degli altri progetti e la data->controllo.
    for(auto progetto : ElencoProgetti){
        if(progetto->get_nome() == nomeProgetto){
            list<string> skill_progetto;
            string data_progetto = progetto->get_data();
            for(auto senior : ElencoSenior){
                if(senior->get_matricola() == progetto->get_responsabile()){
                    list<string> subordinati = senior->get_subordinati();
                    for(auto sub : subordinati){
                        list<string> lista_skill = get_skillDipendenteJunior(sub);
                        for(auto skill : lista_skill){
                            if(find(skill_progetto.begin(),skill_progetto.end(),skill) == skill_progetto.end())
                                skill_progetto.push_back(skill);
                        }
                    }
                }
            }
            for(auto progettoConfronto : ElencoProgetti){
                if(progettoConfronto->get_nome() != nomeProgetto){
                    int skill_comuni = 0;
                    int skill_non_comuni = 0;
                    list<string> skill_progettoConfronto;
                    string data_progettoConfronto = progettoConfronto->get_data();
                    for(auto senior : ElencoSenior){
                        if(senior->get_matricola() == progettoConfronto->get_responsabile()){
                            list<string> subordinati = senior->get_subordinati();
                            for(auto sub : subordinati){
                                list<string> lista_skill = get_skillDipendenteJunior(sub);
                                for(auto skill : lista_skill){
                                    if(find(skill_progettoConfronto.begin(),skill_progettoConfronto.end(),skill) == skill_progettoConfronto.end())
                                        skill_progettoConfronto.push_back(skill);
                                }
                            }
                        }
                    }
                    //confronto-> conto le skill in comune, trovo le skill non in comune, se il controllo va a buon fine aggiungo
                    for(auto skill : skill_progetto){
                        if(find(skill_progettoConfronto.begin(),skill_progettoConfronto.end(),skill) != skill_progettoConfronto.end())
                            skill_comuni+=1;
                    }
                    skill_non_comuni = skill_progetto.size() - skill_comuni;    //le skill non in comune sono tutte le skill della lista meno quelle in comune.
                    if(skill_comuni >=(skill_non_comuni*2) && controlloDataC4(data_progetto,progetto->get_durata(),data_progettoConfronto,progettoConfronto->get_durata()))
                        ListaProgetti.push_back(progettoConfronto);
                }
            }
        }
    }
    return ListaProgetti;
}

//C5: Una coppia di dipendenti senior D1,D2 è considerata ottimale se la combinazione dei loro giorni di reperibilità copre l’intera settimana (ad esempio, D1 è reperibile da lunedì a venerdì e D2 è reperibile da mercoledì a domenica) e se tutti i loro progetti non hanno intersezioni di date (ad esempio i progetti di D1 iniziano tutti il 1 gennaio 2021 e durano 11 mesi e i progetti di D2 iniziano tutti il 1 dicembre 2021). Visualizzare tutte le coppie (senza duplicati) di dipendenti senior ottimali.
list<string> Gestore::c5() const{
        //PRENDO SENIOR E SENIOR 2, PRENDO I LORO PROGETTI E CONFRONTO LE DATE, PRENDO I LORO GIORNI E CONTROLLO SE FORMANO UNA SETTIMANA->SE SI AGGIUNGO LA COPPIA
    list<string> ElencoCoppie;
    for(auto senior : ElencoSenior){
        list<string> giorni_rep = senior->get_reperibilita();
        for(auto senior2 : ElencoSenior){
            bool date_ideali=true;
            for(auto progetto : ElencoProgetti){
                if(progetto->get_responsabile()==senior->get_matricola()){
                    for(auto progetto2 : ElencoProgetti){
                        if(progetto2->get_responsabile()==senior2->get_matricola()){       //ho preso progetto di senior e progetto di senior2->controllo le date.
                            if(!controlloDataC5(progetto->get_data(),progetto->get_durata(),progetto2->get_data(),progetto2->get_durata()))
                                date_ideali=false;
                        }
                    }
                }
            }
            list<string> Settimana;
            if(senior2->get_matricola()!=senior->get_matricola()){
                list<string> giorni_rep2 = senior2->get_reperibilita();
                for(auto element : giorni_rep){
                    if(find(Settimana.begin(),Settimana.end(),element)==Settimana.end())    //controllo doppioni
                        Settimana.push_back(element);
                }
                for(auto element : giorni_rep2){
                    if(find(Settimana.begin(),Settimana.end(),element)==Settimana.end())    //controllo doppioni
                        Settimana.push_back(element);
                }
            }
            if(Settimana.size()==7 && date_ideali){   //settimana? 7: yes perchè {lun-mar-mer-gio-ven-sab-dom}=7.
                //Controllo doppioni-> doppione: Se esiste già matr1,matr2 or matr2,matr1 non aggiungo
                bool presente=false;
                for(auto element : ElencoCoppie){
                    if(element==senior->get_matricola()+","+senior2->get_matricola() || element==senior2->get_matricola()+","+senior->get_matricola()){
                        presente = true;
                    }
                }
                if(!presente)
                    ElencoCoppie.push_back(senior->get_matricola()+","+senior2->get_matricola());
            }
        }

    }
    return ElencoCoppie;
}
