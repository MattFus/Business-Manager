#ifndef DIPENDENTEQLISTWIDGETITEM_H
#define DIPENDENTEQLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QObject>
#include "dipendente.h"

class dipendenteQListWidgetItem: public QListWidgetItem
{
public:
    dipendenteQListWidgetItem(dipendente* d);
    string get_matricola()const{return matricola.toStdString();}
private:
    QString matricola;
};

#endif // DIPENDENTEQLISTWIDGETITEM_H
