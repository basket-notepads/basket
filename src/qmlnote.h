#ifndef NOTE_H
#define NOTE_H

#include <QObject>

namespace qmlbnp
{

class Note : public QObject
{
    Q_OBJECT
public:
    explicit Note(QObject *parent = 0);
    Note(QString AName, int nx, int ny, QObject* parent) : QObject(parent), name(AName), x(nx), y(ny) {}
    ~Note();

    QString name;
    Q_PROPERTY(QString Name MEMBER name NOTIFY OnAnyChanged USER true)
    Q_PROPERTY(int X MEMBER x NOTIFY OnAnyChanged)
    Q_PROPERTY(int Y MEMBER y NOTIFY OnAnyChanged)
    //Q_PROPERTY(int TAG_ARROW_WIDTH READ m_tagArrowWidth CONSTANT)
    //static const int m_tagArrowWidth  =5;
    enum Sizes {
        TAG_ARROW_WIDTH = 5
    };
    Q_ENUMS(Sizes)

private:
    int x, y;

signals:
    void OnAnyChanged(); //Expression depends on non-NOTIFYable properties: Note::Y

public slots:
};

}
Q_DECLARE_METATYPE(qmlbnp::Note*)

#endif // NOTE_H
