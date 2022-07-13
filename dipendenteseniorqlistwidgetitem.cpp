#include "dipendenteseniorqlistwidgetitem.h"
#include <sstream>

dipendenteSeniorQListWidgetItem::dipendenteSeniorQListWidgetItem(dipendenteSenior* ds)
{
    matricola = QString::fromStdString(ds->get_matricola());
    stringstream out;
    out<<*ds;
    setText(QString::fromStdString(out.str()));
}
