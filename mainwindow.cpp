#include "mainwindow.h"
#include "QList"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AlertAttenzione(QWidget* widget){
    QMessageBox::critical(widget, "Attenzione","Assicurati di aver inserito tutti i campi obbligatori.");
}

//METODI DI AGGIORNAMENTO LISTE===============================================================================================================================================
void MainWindow::aggiornaOnlySeniorList(){
    ui->OnlySeniorListWidget->clear();
    ui->ListaWidgetSenior_Opzioni->clear();
    auto LISTdipendentiSenior=gestore.get_elencoSenior();
    for(auto element: LISTdipendentiSenior){
        ui->OnlySeniorListWidget->addItem(new dipendenteSeniorQListWidgetItem(element));
        ui->ListaWidgetSenior_Opzioni->addItem(new dipendenteSeniorQListWidgetItem(element));
    }
}
void MainWindow::aggiornaOnlyJuniorList(){
    ui->OnlyJuniorListWidget->clear();
    ui->ListaWidgetJunior_Opzioni->clear();
    auto LISTdipendentiJunior=gestore.get_elencoJunior();
    for(auto element: LISTdipendentiJunior){
        ui->OnlyJuniorListWidget->addItem(new dipendenteJuniorQListWidgetItem(element));
        ui->ListaWidgetJunior_Opzioni->addItem(new dipendenteJuniorQListWidgetItem(element));
    }
}
void MainWindow::aggiornaListeDipendenti(){
    ui->listWidget_Dipendenti->clear();
    auto tuttiDipendenti=gestore.getDipendenti();
    for(auto element : tuttiDipendenti){
        ui->listWidget_Dipendenti->addItem(new dipendenteQListWidgetItem(element));
    }
}
void MainWindow::aggiornaListeProgetti(){
    ui->listWidget_Progetti->clear();
    ui->OnlyProjectsListWidget->clear();
    ui->ListaWidgetProgetti_Opzioni->clear();
    auto tuttiProgetti=gestore.getProgetti();
    for(auto element: tuttiProgetti){
        ui->listWidget_Progetti->addItem(new progettoQListWidgetItem(element));
        ui->OnlyProjectsListWidget->addItem(new progettoQListWidgetItem(element));
        ui->ListaWidgetProgetti_Opzioni->addItem(new progettoQListWidgetItem(element));
    }
}

void MainWindow::deleteAll(QListWidget* widget) {
    for(int i = 0; i < widget->count(); i++) {
        delete widget->item(i);
    }
    widget->clear();
}
//FINE METODI DI AGGIORNAMENTO LISTE===========================================================================================================================================

//HOME-PAGE BUTTONS=====================================================================================================================================================
void MainWindow::on_HOME_btn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->HomePage);
}


void MainWindow::on_Opzioni_btn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->OpzioniPage);
}


void MainWindow::on_CaricaDaFile_btn_clicked()
{
    //reset delle liste
    gestore.clear();
    deleteAll(ui->listWidget_Dipendenti);
    deleteAll(ui->listWidget_Progetti);
    deleteAll(ui->OnlyJuniorListWidget);
    deleteAll(ui->OnlyProjectsListWidget);
    deleteAll(ui->OnlySeniorListWidget);
    deleteAll(ui->ListaWidgetJunior_Opzioni);
    deleteAll(ui->ListaWidgetProgetti_Opzioni);
    deleteAll(ui->ListaWidgetSenior_Opzioni);
    //prendo da file e aggiungo agli elenchi
    QString filename=QFileDialog::getOpenFileName(this,"Apri File",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),"Text File (*txt)");
    if(filename.isNull()){
        //QMessageBox::critical(this,"Attenzione!","Non è stato possibile aprire il file.");
        return;
    }
    QFile inputfile(filename);
    if(inputfile.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->statusbar->showMessage("File Caricato.",3000);
        QTextStream in(&inputfile);
        while(!in.atEnd()){
            QString line=in.readLine();
            QStringList items=line.split(";");
            /*
            for(auto it=items.begin();it!=items.end();++it){
                item.push_back((it)->toStdString());
            }
            for(auto element : item){
                cout<<element<<endl;
            }
            */
            QString tipo=items.at(0);
            string type=tipo.toStdString();
                //DIPENDENTE JUNIOR
            if(type=="DJ"){
                QString matricola=items.at(1);
                QString nome=items.at(2);
                QString cognome=items.at(3);
                QString _stipendio=items.at(4);
                double stipendio=_stipendio.toDouble();

                QString skilles=items.at(5);
                QStringList skill=skilles.split(",");

                QString stagista=items.at(6);
                list<string> skills;
                for(auto element:skill){
                    skills.push_back(element.toStdString());
                }
                bool res=gestore.aggiungiDipendenteJunior(matricola.toStdString(),nome.toStdString(),cognome.toStdString(),stipendio,skills,stagista.toStdString());
                if(!res)
                   QMessageBox::critical(this,"Attenzione","Esiste già un dipendente con quella matricola!");
            }
                //DIPENDENTE SENIOR
            if(type=="DS"){
                QString matricola=items.at(1);
                QString nome=items.at(2);
                QString cognome=items.at(3);
                QString _stipendio=items.at(4);
                double stipendio=_stipendio.toDouble();
                QStringList _reper=items.at(5).split(",");
                QStringList _subs;
                if(!items.at(6).isEmpty())
                    _subs=items.at(6).split(",");
                list<string> reperibilita;
                list<string> subordinati;

                //CHANGE FROM QLIST TO STD::LIST
                for(auto element: _reper){
                    reperibilita.push_back(element.toStdString());
                }
                for(auto element:_subs){
                       subordinati.push_back(element.toStdString());
                }
                bool res=gestore.aggiungiDipendenteSenior(matricola.toStdString(),nome.toStdString(),cognome.toStdString(),stipendio,reperibilita,subordinati);
                if(!res)
                   QMessageBox::critical(this,"Attenzione","Esiste già un dipendente con quella matricola!");
            }
                //PROGETTO
            if(type=="P"){
                QString nome=items.at(1);
                QString data=items.at(2);
                QString _durata=items.at(3);
                int durata=_durata.toInt();
                QString _budget=items.at(4);
                double budget=_budget.toDouble();
                QString responsabile=items.at(5);

                bool res=gestore.aggiungiProgetto(nome.toStdString(),data.toStdString(),durata,budget,responsabile.toStdString());
                if(!res)
                   QMessageBox::critical(this,"Attenzione","Esiste già un progetto con quel nome!");
            }
        }

    }

    //aggiorno tutte le liste
    aggiornaOnlySeniorList();
    aggiornaOnlyJuniorList();
    aggiornaListeDipendenti();
    aggiornaListeProgetti();


}


void MainWindow::on_AggiungiProgetto_btn_clicked()
{
    ui->InputNome_Progetto->clear();
    ui->InputData_Progetto->clear();
    ui->InputDurata_Progetto->setValue(0);
    ui->InputBudget_Progetto->setValue(0.00);
    ui->InputResponsabile_Progetto->clear();
    ui->stackedWidget->setCurrentWidget(ui->PageProgetti);
}


void MainWindow::on_AggiungiDipendente_btn_clicked()
{
    int index=ui->DipendenteTypeComboBox->currentIndex();
    switch (index){
    case 0:
        //pulisco
        ui->InputMatricola_Senior->clear();
        ui->InputNome_Senior->clear();
        ui->InputCognome_Senior->clear();
        ui->InputStipendio_Senior->setValue(0.0);
        ui->InputReperibilita_Senior->clear();
        ui->InputSubordinati_Senior->clear();
        ui->stackedWidget->setCurrentWidget(ui->PageDipendenteSenior);
        break;
    case 1:
        //pulisco
        ui->InputMatricola_Junior->clear();
        ui->InputNome_Junior->clear();
        ui->InputCognome_Junior->clear();
        ui->InputStipendio_Junior->setValue(0.0);
        ui->InputSkills_Junior->clear();
        ui->InputStagista_Junior->clear();
        ui->stackedWidget->setCurrentWidget(ui->PageDipendenteJunior);
        break;
    }
}

//AGGIUNGI DIPENDENTE-PAGE BUTTONS=====================================================================================================================================================
void MainWindow::on_AddDipendenteSenior_btn_clicked()
{
    QString matricola=ui->InputMatricola_Senior->text();
    QString nome=ui->InputNome_Senior->text();
    QString cognome=ui->InputCognome_Senior->text();
    double stipendio=ui->InputStipendio_Senior->value();
    QString _reperibilita=ui->InputReperibilita_Senior->text();
    QString _subordinati=ui->InputSubordinati_Senior->text();

    if(matricola.isEmpty() || nome.isEmpty() || cognome.isEmpty() || _reperibilita.isEmpty()){
        AlertAttenzione(ui->stackedWidget);
        return;
    }
    else{
        //reperibilità e subordinati
        QStringList listReper=_reperibilita.split(",");
        list<string> reperibilita;
        for(auto element: listReper){
            reperibilita.push_back(element.toStdString());
        }

        QStringList listSubs=_subordinati.split(",");
        list<string> subordinati;
        for(auto element : listSubs){
            subordinati.push_back(element.toStdString());
        }

        bool res=gestore.aggiungiDipendenteSenior(matricola.toStdString(),nome.toStdString(),cognome.toStdString(),stipendio,reperibilita,subordinati);
        if(!res){
            QMessageBox::critical(this,"Attenzione","Esiste già un dipendente con quella matricola!");
        }
        else{
            statusBar()->showMessage("Dipendente Senior aggiunto con successo!",3000);
            aggiornaListeDipendenti();
            aggiornaOnlySeniorList();

        }

        ui->InputMatricola_Senior->clear();
        ui->InputNome_Senior->clear();
        ui->InputCognome_Senior->clear();
        ui->InputStipendio_Senior->setValue(0.0);
        ui->InputReperibilita_Senior->clear();
        ui->InputSubordinati_Senior->clear();
    }
}


void MainWindow::on_AddDipendenteJunior_btn_clicked()
{
    QString matricola=ui->InputMatricola_Junior->text();
    QString nome=ui->InputNome_Junior->text();
    QString cognome=ui->InputCognome_Junior->text();
    double stipendio=ui->InputStipendio_Junior->value();
    QString _skills=ui->InputSkills_Junior->text();
    QString stagista=ui->InputStagista_Junior->text();

    if(matricola.isEmpty() || nome.isEmpty() || cognome.isEmpty() || _skills.isEmpty()){
        AlertAttenzione(ui->stackedWidget);
        return;
    }
    else{
        //reperibilità e subordinati

        QStringList listSkill=_skills.split(",");
        list<string> skill;
        for(auto element: listSkill){
            skill.push_back(element.toStdString());
        }

        bool res=gestore.aggiungiDipendenteJunior(matricola.toStdString(),nome.toStdString(),cognome.toStdString(),stipendio,skill,stagista.toStdString());
        if(!res){
            QMessageBox::critical(this,"Attenzione","Esiste già un dipendente con quella matricola!");
        }
        else{
            statusBar()->showMessage("Dipendente Junior aggiunto con successo!",3000);
            aggiornaListeDipendenti();
            aggiornaOnlyJuniorList();

        }

        ui->InputMatricola_Junior->clear();
        ui->InputNome_Junior->clear();
        ui->InputCognome_Junior->clear();
        ui->InputStipendio_Junior->setValue(0.0);
        ui->InputSkills_Junior->clear();
        ui->InputStagista_Junior->clear();
    }
}

//AGGIUNGI PROGETTO-PAGE BUTTON=====================================================================================================================================================
void MainWindow::on_AddProject_btn_clicked()
{
    QString nome=ui->InputNome_Progetto->text();
    QString data=ui->InputData_Progetto->text();
    int durata=ui->InputDurata_Progetto->value();
    double budget=ui->InputBudget_Progetto->value();
    QString responsabile=ui->InputResponsabile_Progetto->text();

    if(nome.isEmpty() || data.isEmpty() || responsabile.isEmpty() || durata==0 || budget==0.00){
        AlertAttenzione(ui->stackedWidget);
    }
    else{
        bool res=gestore.aggiungiProgetto(nome.toStdString(),data.toStdString(),durata,budget,responsabile.toStdString());
        if(!res){
            QMessageBox::critical(this,"Attenzione!","Esiste già un progetto con quel nome!.");
            return;
        }
        else{
            statusBar()->showMessage("Progetto aggiunto con successo!",3000);
            aggiornaListeProgetti();
        }
        ui->InputNome_Progetto->clear();
        ui->InputData_Progetto->clear();
        ui->InputDurata_Progetto->clear();
        ui->InputBudget_Progetto->clear();
        ui->InputResponsabile_Progetto->clear();
    }
}

//OPZIONI INFO BUTTON=====================================================================================================================================================
void MainWindow::on_GetInfoAbout_btn_clicked()
{
    int index=ui->OptionsComboBox->currentIndex();
    switch (index){
    case 0:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutti i progetti legati ad un dipendente senior. (Tip: inserisci matricola)");
        break;
    case 1:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutti i progetti legati ad un dipendente junior. (Tip: inserisci matricola)");
        break;
    case 2:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutte le skill (senza duplicati) di un dipendente junior partecipante ad un progetto. (Tip: inserisci nome del progetto)");
        break;
    case 3:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutte le skill presenti in tutti i dipendenti.");
        break;
    case 4:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra le 5 skill più diffuse tra i dipendenti.");
        break;
    case 5:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra i progetti i cui dipendenti non hanno skill in comune.");
        break;
    case 6:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra il progetto con il budget più basso tra tutti i progetti di un responsabile");
        break;
    case 7:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra il progetto con il budget più basso tra tutti i progetti di un responsabile");
        break;
    case 8:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra la media dei budget di tutti i progetti di un responsabile (Tip: inserisci matricola");
        break;
    case 9:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutti i progetti ordinati per budget crescente");
        break;
    case 10:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutti i progetti ordinati per budget decrescente");
        break;
    case 11:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutti i progetti ordinati per data di inizio crescente");
        break;
    case 12:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutti i progetti ordinati per data di inizo decrescente");
        break;
    case 13:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutti i progetti ordinati per durata decrescente, prezzo crescente o per ordine alfabetico");
        break;
    case 14:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutte le skill con il guadagno più alto.");
        break;
    case 15:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutti i dipendenti senior indispensabili.");
        break;
    case 16:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutti i dipendente junior influenzati da un dipendente Senior. (tip: inserisci matricola)");
        break;
    case 17:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra i progetti simili ad un determinato progetto. (tip: inserisci nomeProgetto)");
        break;
    case 18:
        QMessageBox::information(this,"Informazioni","Questa opzione mostra tutte le coppie di dipendenti Senior ottimali.");
        break;
    }
}

//OPZIONI RICERCA BUTTON=====================================================================================================================================================
void MainWindow::on_SearchOpzioni_btn_clicked()
{
    int index=ui->OptionsComboBox->currentIndex();
    QString ricerca=ui->InputCampoRicerca_Opzioni->text();
    switch (index){
    case 0: //B1
        if(ricerca.isEmpty()){
            AlertAttenzione(this);
            return;
        }
        else{
            ui->OptionsListWidget->clear();
            auto Progetti_Senior=gestore.b1(ricerca.toStdString());
            for(auto element: Progetti_Senior){
                ui->OptionsListWidget->addItem(new progettoQListWidgetItem(element));
            }
            QString count=QString::number(ui->OptionsListWidget->count());
            statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
        }
        break;
    case 1: //B2
        if(ricerca.isEmpty()){
            AlertAttenzione(this);
            return;
        }
        else{
            ui->OptionsListWidget->clear();
            auto Progetti_junior=gestore.b2(ricerca.toStdString());
            for(auto element: Progetti_junior){
                ui->OptionsListWidget->addItem(new progettoQListWidgetItem(element));
            }
            QString count=QString::number(ui->OptionsListWidget->count());
            statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
        }
        break;
    case 2: //B3
        if(ricerca.isEmpty()){
            AlertAttenzione(this);
            return;
        }
        else{
            ui->OptionsListWidget->clear();
            auto ListaSkill=gestore.b3(ricerca.toStdString());
            for(auto element: ListaSkill){
                ui->OptionsListWidget->addItem(QString::fromStdString(element));
            }
            QString count=QString::number(ui->OptionsListWidget->count());
            statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
        }
        break;
    case 3:{ //B4
        ui->OptionsListWidget->clear();
        auto ListaSkill=gestore.b4();
        for(auto element : ListaSkill){
            ui->OptionsListWidget->addItem(QString::fromStdString(element));
        }
        QString count=QString::number(ui->OptionsListWidget->count());
        statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
    }
        break;
    case 4:{ //B5
        ui->OptionsListWidget->clear();
        auto ListaSkill=gestore.b5();
        for(auto element : ListaSkill){
            ui->OptionsListWidget->addItem(QString::fromStdString(element));
        }
        QString count=QString::number(ui->OptionsListWidget->count());
        statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
    }
        break;
    case 5:{ //B6
        ui->OptionsListWidget->clear();
        auto ListaProgetti=gestore.b6();
        for(auto element : ListaProgetti){
            ui->OptionsListWidget->addItem(new progettoQListWidgetItem(element));
        }
        QString count=QString::number(ui->OptionsListWidget->count());
        statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
    }
        break;
    case 6: //B7
        if(ricerca.isEmpty()){
            AlertAttenzione(this);
            return;
        }
        else{
            ui->OptionsListWidget->clear();
            auto ListaProgetti=gestore.b7(ricerca.toStdString());
            for(auto element : ListaProgetti){
                ui->OptionsListWidget->addItem(QString::fromStdString(element));
            }
            QString count=QString::number(ui->OptionsListWidget->count());
            statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
        }
        break;
    case 7: //B8
        if(ricerca.isEmpty()){
            AlertAttenzione(this);
            return;
        }
        else{
            ui->OptionsListWidget->clear();
            auto ListaProgetti=gestore.b8(ricerca.toStdString());
            for(auto element : ListaProgetti){
                ui->OptionsListWidget->addItem(QString::fromStdString(element));
            }
            QString count=QString::number(ui->OptionsListWidget->count());
            statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
        }
        break;
    case 8: //B9
        if(ricerca.isEmpty()){
            AlertAttenzione(this);
            return;
        }
        else{
            ui->OptionsListWidget->clear();
            double budget=gestore.b9(ricerca.toStdString());
            if(budget <=0){
                QMessageBox::information(this,"Informazione","Nessun progetto per questa matricola.");
                return;
            }
            else{
                ui->OptionsListWidget->addItem(QString::number(budget));
            }
            QString count=QString::number(ui->OptionsListWidget->count());
            statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
        }
        break;
    case 9:{ //B10
        ui->OptionsListWidget->clear();
        auto ListaProgetti=gestore.b10();
        for(auto element : ListaProgetti){
            ui->OptionsListWidget->addItem(new progettoQListWidgetItem(element));
        }
        QString count=QString::number(ui->OptionsListWidget->count());
        statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
    }
        break;
    case 10:{ //B11
        ui->OptionsListWidget->clear();
        auto ListaProgetti=gestore.b11();
        for(auto element : ListaProgetti){
            ui->OptionsListWidget->addItem(new progettoQListWidgetItem(element));
        }
        QString count=QString::number(ui->OptionsListWidget->count());
        statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
    }
        break;
    case 11:{ //B12
        ui->OptionsListWidget->clear();
        auto ListaProgetti=gestore.b12();
        for(auto element : ListaProgetti){
            ui->OptionsListWidget->addItem(new progettoQListWidgetItem(element));
        }
        QString count=QString::number(ui->OptionsListWidget->count());
        statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
    }
        break;
    case 12:{ //B13
        ui->OptionsListWidget->clear();
        auto ListaProgetti=gestore.b13();
        for(auto element : ListaProgetti){
            ui->OptionsListWidget->addItem(new progettoQListWidgetItem(element));
        }
        QString count=QString::number(ui->OptionsListWidget->count());
        statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
    }
        break;
    case 13:{ //B14
        ui->OptionsListWidget->clear();
        auto ListaProgetti=gestore.b14();
        for(auto element : ListaProgetti){
            ui->OptionsListWidget->addItem(new progettoQListWidgetItem(element));
        }
        QString count=QString::number(ui->OptionsListWidget->count());
        statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
    }
        break;
    case 14:{ //C1
        ui->OptionsListWidget->clear();
        auto ListaSkill=gestore.c1();
        for(auto element : ListaSkill){
            ui->OptionsListWidget->addItem(QString::fromStdString(element));
        }
        QString count=QString::number(ui->OptionsListWidget->count());
        statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
    }
        break;
    case 15:{ //C2
        ui->OptionsListWidget->clear();
        auto ListaSenior=gestore.c2();
        for(auto element : ListaSenior){
            ui->OptionsListWidget->addItem(new dipendenteSeniorQListWidgetItem(element));
        }
        QString count=QString::number(ui->OptionsListWidget->count());
        statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
    }
        break;
    case 16: //C3
        if(ricerca.isEmpty()){
            AlertAttenzione(this);
            return;
        }
        else{
            ui->OptionsListWidget->clear();
            auto ListaJunior=gestore.c3(ricerca.toStdString());
            for(auto element : ListaJunior){
                ui->OptionsListWidget->addItem(new dipendenteJuniorQListWidgetItem(element));
            }
            QString count=QString::number(ui->OptionsListWidget->count());
            statusBar()->showMessage("Ricerca completata, elemnti trovati: "+count,5000);
        }
        break;
    case 17: //C4
        if(ricerca.isEmpty()){
            AlertAttenzione(this);
            return;
        }
        else{
            ui->OptionsListWidget->clear();
            auto ListaProgetti=gestore.c4(ricerca.toStdString());
            for(auto element : ListaProgetti){
                ui->OptionsListWidget->addItem(new progettoQListWidgetItem(element));
            }
            QString count=QString::number(ui->OptionsListWidget->count());
            statusBar()->showMessage("Ricerca completata, elementi trovati: "+count,5000);
        }
        break;
    case 18:{ //C5
        ui->OptionsListWidget->clear();
        auto ListaCoppie=gestore.c5();
        for(auto element : ListaCoppie){
            ui->OptionsListWidget->addItem(QString::fromStdString(element));
        }
    }
        break;
    default:{ //NON DOVREBBE ACCADERE
        ui->OptionsListWidget->clear();
        QMessageBox::critical(this,"Attenzione","Attenzione, nessun metodo selezionato!");
    }
        break;
    }
}
//FINE OPZIONI RICERCA-BUTTON================================================================================================================================================

void MainWindow::on_Clean_btn_clicked()
{
    deleteAll(ui->listWidget_Dipendenti);
    deleteAll(ui->listWidget_Progetti);
    deleteAll(ui->OnlyJuniorListWidget);
    deleteAll(ui->OnlyProjectsListWidget);
    deleteAll(ui->OnlySeniorListWidget);
    deleteAll(ui->OptionsListWidget);
    deleteAll(ui->ListaWidgetJunior_Opzioni);
    deleteAll(ui->ListaWidgetProgetti_Opzioni);
    deleteAll(ui->ListaWidgetSenior_Opzioni);
    gestore.clear();

    statusBar()->showMessage("Liste svuotate!",3000);
}

//MENU-BAR BUTTONS===========================================================================================================================================================
void MainWindow::on_actionFile_txt_triggered()
{
    //reset delle liste
    gestore.clear();
    deleteAll(ui->listWidget_Dipendenti);
    deleteAll(ui->listWidget_Progetti);
    deleteAll(ui->OnlyJuniorListWidget);
    deleteAll(ui->OnlyProjectsListWidget);
    deleteAll(ui->OnlySeniorListWidget);
    deleteAll(ui->ListaWidgetJunior_Opzioni);
    deleteAll(ui->ListaWidgetProgetti_Opzioni);
    deleteAll(ui->ListaWidgetSenior_Opzioni);
    //prendo da file e aggiungo agli elenchi
    QString filename=QFileDialog::getOpenFileName(this,"Apri File",QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),"Text File (*txt)");
    if(filename.isNull()){
        //QMessageBox::critical(this,"Attenzione!","Non è stato possibile aprire il file.");
        return;
    }
    QFile inputfile(filename);
    if(inputfile.open(QIODevice::ReadOnly | QIODevice::Text)){
        ui->statusbar->showMessage("File Caricato.",3000);
        QTextStream in(&inputfile);
        while(!in.atEnd()){
            QString line=in.readLine();
            QStringList items=line.split(";");
            /*
            for(auto it=items.begin();it!=items.end();++it){
                item.push_back((it)->toStdString());
            }
            for(auto element : item){
                cout<<element<<endl;
            }
            */
            QString tipo=items.at(0);
            string type=tipo.toStdString();
                //DIPENDENTE JUNIOR
            if(type=="DJ"){
                QString matricola=items.at(1);
                QString nome=items.at(2);
                QString cognome=items.at(3);
                QString _stipendio=items.at(4);
                double stipendio=_stipendio.toDouble();

                QString skilles=items.at(5);
                QStringList skill=skilles.split(",");

                QString stagista=items.at(6);
                list<string> skills;
                for(auto element:skill){
                    skills.push_back(element.toStdString());
                }
                bool res=gestore.aggiungiDipendenteJunior(matricola.toStdString(),nome.toStdString(),cognome.toStdString(),stipendio,skills,stagista.toStdString());
                if(!res)
                   QMessageBox::critical(this,"Attenzione","Esiste già un dipendente con quella matricola!");
            }
                //DIPENDENTE SENIOR
            if(type=="DS"){
                QString matricola=items.at(1);
                QString nome=items.at(2);
                QString cognome=items.at(3);
                QString _stipendio=items.at(4);
                double stipendio=_stipendio.toDouble();
                QStringList _reper=items.at(5).split(",");
                QStringList _subs;
                if(!items.at(6).isEmpty())
                    _subs=items.at(6).split(",");
                list<string> reperibilita;
                list<string> subordinati;

                //CHANGE FROM QLIST TO STD::LIST
                for(auto element: _reper){
                    reperibilita.push_back(element.toStdString());
                }
                for(auto element:_subs){
                       subordinati.push_back(element.toStdString());
                }
                bool res=gestore.aggiungiDipendenteSenior(matricola.toStdString(),nome.toStdString(),cognome.toStdString(),stipendio,reperibilita,subordinati);
                if(!res)
                  QMessageBox::critical(this,"Attenzione","Esiste già un dipendente con quella matricola!");
            }
                //PROGETTO
            if(type=="P"){
                QString nome=items.at(1);
                QString data=items.at(2);
                QString _durata=items.at(3);
                int durata=_durata.toInt();
                QString _budget=items.at(4);
                double budget=_budget.toDouble();
                QString responsabile=items.at(5);

                bool res=gestore.aggiungiProgetto(nome.toStdString(),data.toStdString(),durata,budget,responsabile.toStdString());
                if(!res)
                   QMessageBox::critical(this,"Attenzione","Esiste già un progetto con quel nome!");
            }
        }

    }

    //aggiorno tutte le liste
    aggiornaOnlySeniorList();
    aggiornaOnlyJuniorList();
    aggiornaListeDipendenti();
    aggiornaListeProgetti();

}


void MainWindow::on_actionNew_triggered()
{
    if(ui->listWidget_Dipendenti->count()!=0){
        QMessageBox::StandardButton response;
        response=QMessageBox::question(this,"Informazioni","Vuoi davvero aprire un nuovo foglio?. \n Tutti i dati verranno persi.");
        if(response == QMessageBox::Yes){
            gestore.clear();
            aggiornaListeDipendenti();
            aggiornaListeProgetti();
            aggiornaOnlyJuniorList();
            aggiornaOnlySeniorList();
            ui->OptionsListWidget->clear();
        }
        statusBar()->showMessage("Nuovo foglio caricato.",5000);
        return;
    }
    gestore.clear();
    aggiornaListeDipendenti();
    aggiornaListeProgetti();
    aggiornaOnlyJuniorList();
    aggiornaOnlySeniorList();
    statusBar()->showMessage("Nuovo foglio caricato.",5000);
}

void MainWindow::on_actionChiudi_triggered()
{
    QApplication::quit();
}
