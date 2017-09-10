#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QColor>
#include <QPointer>
#include "qmlnote.h"

namespace qmlbnp
{

class NotesFilterModel;

/*class Note : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Note)
private:
    QString getTestStr();

    int x, y;

signals:
    void OnAnyChanged(); //Expression depends on non-NOTIFYable properties: Note::Y

public:
    QString name;
//    std::string name;
    Q_PROPERTY(QString Name MEMBER name NOTIFY OnAnyChanged USER true)
    Q_PROPERTY(int X MEMBER x NOTIFY OnAnyChanged)
    Q_PROPERTY(int Y MEMBER y NOTIFY OnAnyChanged)
//    Q_PROPERTY(QString TestStr READ getTestStr NOTIFY OnXChanged)

    Note() : x(-1), y(-1) { }
    Note(QString AName, int nx, int ny, QObject* parent) : QObject(parent), name(AName), x(nx), y(ny) {}
//    Note() : QObject() { name = ""; }
//    Note(const Note& other) : QObject(), name(other.name) {}
//    Note& operator=(const Note& other);
    ~Note();
};*/




//shared with QML
//NoteDimensions?
class NoteProperties : public QObject
{
    Q_OBJECT
public:
    //setBigNotes
    static const int NOTE_MARGIN      =2;
    static const int INSERTION_HEIGHT =5;
    static const int EXPANDER_WIDTH   =9;
    static const int EXPANDER_HEIGHT  =9;
    static const int GROUP_WIDTH      =2*NOTE_MARGIN + EXPANDER_WIDTH;
    static const int HANDLE_WIDTH     =GROUP_WIDTH;
    static const int RESIZER_WIDTH    =GROUP_WIDTH;
    static const int TAG_ARROW_WIDTH  =5;
    static const int EMBLEM_SIZE      =16;
    static const int MIN_HEIGHT       =2*NOTE_MARGIN + EMBLEM_SIZE;

    Q_PROPERTY(int noteMargin MEMBER NOTE_MARGIN CONSTANT)
    Q_PROPERTY(int handleWidth MEMBER HANDLE_WIDTH CONSTANT)
    Q_PROPERTY(int tagArrowWidth MEMBER TAG_ARROW_WIDTH CONSTANT)
    //Q_PROPERTY(int PROP_MIN_HEIGHT MEMBER MIN_HEIGHT CONSTANT)
};

//QAbstractListModel vs. QStandardItemModel?
class NotesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit NotesModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex& index = QModelIndex()) override;

    QStringList mimeTypes() const override;

    //insert, remove, get
    Q_INVOKABLE void addNote(int nx, int ny, QString name = QString());
    Q_INVOKABLE void insertNote(int index, QString name, int x, int y);
    Q_INVOKABLE void deleteNote(int index);
    Q_INVOKABLE qmlbnp::Note* get(int index) { return notes[index]; }

    void setFilterModel(NotesFilterModel* model);

signals:

public slots:

private:
    void connectNoteToFilterModel(Note* n);

    QList<Note*> notes;
    //Note is QObject - has to be pointer
// !!    QObject notesParent;
    QPointer<NotesFilterModel> filterModel;

};


class NotesFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit NotesFilterModel(QObject *parent = 0);

    //NotesModel facade
    Q_INVOKABLE void addNote(int nx, int ny) { model->addNote(nx, ny); }
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
private:
    NotesModel* model;

public slots:
    void invalidateFilter() { QSortFilterProxyModel::invalidateFilter(); }
};

}
/*Q_DECLARE_METATYPE(qmlbnp::Note*)*/


#endif // NOTESMODEL_H
