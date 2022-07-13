#include "progettoqlistwidgetitem.h"

#include <sstream>
using namespace std;

progettoQListWidgetItem::progettoQListWidgetItem(progetto* p)
{
    nome = QString::fromStdString(p->get_nome());
    stringstream out;
    out<<*p;
    setText(QString::fromStdString(out.str()));
}
