#include "qmlnote.h"

using namespace qmlbnp;

Note::Note(QObject *parent) : QObject(parent), x(-1), y(-1)
{

}

Note::~Note()
{
    qDebug(QString("Note destructor('%1')").arg(name).toLatin1());
    //name.clear();
}
