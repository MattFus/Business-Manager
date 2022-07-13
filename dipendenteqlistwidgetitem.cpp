#include "dipendenteqlistwidgetitem.h"

#include <sstream>
using namespace std;

dipendenteQListWidgetItem::dipendenteQListWidgetItem(dipendente* d)
{
    matricola = QString::fromStdString(d->get_matricola());
    stringstream out;
    out<<*d;
    setText(QString::fromStdString(out.str()));
}
