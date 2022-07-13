#ifndef DIPENDENTESENIORQLISTWIDGETITEM_H
#define DIPENDENTESENIORQLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QObject>
#include "dipendentesenior.h"

class dipendenteSeniorQListWidgetItem : public QListWidgetItem
{
public:
    dipendenteSeniorQListWidgetItem(dipendenteSenior* ds);
    string get_matricola()const{return matricola.toStdString();}
private:
    QString matricola;
};

#endif // DIPENDENTESENIORQLISTWIDGETITEM_H
