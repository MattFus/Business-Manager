#ifndef DIPENDENTEJUNIORQLISTWIDGETITEM_H
#define DIPENDENTEJUNIORQLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QObject>
#include "dipendentejunior.h"

class dipendenteJuniorQListWidgetItem : public QListWidgetItem
{
public:
    dipendenteJuniorQListWidgetItem(dipendenteJunior* dj);
    string get_matricola()const{return matricola.toStdString();}
private:
    QString matricola;
};

#endif // DIPENDENTEJUNIORQLISTWIDGETITEM_H
