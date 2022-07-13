#include "dipendentejuniorqlistwidgetitem.h"

#include <sstream>
using namespace std;

dipendenteJuniorQListWidgetItem::dipendenteJuniorQListWidgetItem(dipendenteJunior* dj)
{
    matricola = QString::fromStdString(dj->get_matricola());
    stringstream out;
    out<<*dj;
    setText(QString::fromStdString(out.str()));
}
