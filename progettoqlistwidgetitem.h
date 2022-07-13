#ifndef PROGETTOQLISTWIDGETITEM_H
#define PROGETTOQLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QObject>
#include "progetto.h"

class progettoQListWidgetItem: public QListWidgetItem
{
public:
    progettoQListWidgetItem(progetto* p);
    string get_nome()const{return nome.toStdString();}
private:
    QString nome;
};

#endif // PROGETTOQLISTWIDGETITEM_H
