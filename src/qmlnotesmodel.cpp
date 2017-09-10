#include "qmlnotesmodel.h"
#include "notedrag.h"
#include <QDebug>

using namespace qmlbnp;

NotesModel::NotesModel(QObject *parent) :
    QAbstractListModel(parent)
{
    int x= 10;
    int y = 10;
    for (const char* s : {"1 The Phantom Menace", "2 Attack of the Clones", "3 Revenge of the Siths",
         "4 A New Hope", "5 The Empire Strikes Back", "6 Return of the Jedi", "7 The Force Awakens",
         "11 aa", "12 bb", "13 cc", "14 dd", "15 ee", "16 ff",
         "17 gg", "18 hh", "19 ii", "20 gg", "21 kk", "22 ll", "23 mm", "24 nn", "25 oo", "26 pp"}) {
        notes.append(new Note(QString(s), x, y, /*&notesParent*/NULL));
        x += 3;
        y += 20;
    }

}


int NotesModel::rowCount(const QModelIndex &) const
{
    return notes.count();
}

QVariant NotesModel::data(const QModelIndex &index, int role) const
{
    QVariant result;

    int row = index.row();

    if(row < 0 || row >= notes.count()) {
        return result;
    }

    switch(role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        // Qt automatically converts it to the QVariant
        //return notes.value(row);
        //result = QVariant::fromValue<QSharedPointer<Note>>(notes[row]);
        result.setValue(notes[row]);
        break;
    case Qt::ToolTipRole:
        result.setValue(QString("Edit this text"));
        break;
    }

    return result;
}

Qt::ItemFlags NotesModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

bool NotesModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    qDebug("NotesModel::setData @ index %d", index.row());
    if (index.isValid() && role == Qt::EditRole) {
        Note* n = value.value<qmlbnp::Note*>();
        Q_ASSERT(n != NULL);
        notes.replace(index.row(), n);
        dataChanged(index, index);
        return true;
    }
    return false;
}

bool NotesModel::insertRows(int position, int rows, const QModelIndex& index)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; row++) {
        notes.insert(position, new Note(this));
    }

    endInsertRows();
    return true;
}

bool NotesModel::removeRows(int position, int rows, const QModelIndex& index)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; row++) {
        notes.removeAt(position);
    }

    endRemoveRows();
    return true;
}

QStringList NotesModel::mimeTypes() const
{
    return {NoteDrag::NOTE_MIME_STRING};
}

void NotesModel::addNote(int nx, int ny, QString name)
{
    qWarning("addNote is obsolete");
    if (name.length() == 0)
        name = "NEW";
    beginInsertRows(QModelIndex(), notes.count(), notes.count());
    notes.append(new Note(name, nx, ny, NULL));
    endInsertRows();

    connectNoteToFilterModel(notes.last());


//    QVector<int> roles = { Qt::DisplayRole };
//    int COLUMN = 0;
//    QModelIndex last = NotesModel::createIndex(notes.count()-1, COLUMN);
    //    dataChanged(last, last, roles);
}

void NotesModel::insertNote(int index, QString name, int x, int y)
{
    if (insertRow(index)) {
        QModelIndex newIndex = createIndex(index, 0);
        auto note = new Note(name, x, y, this);
        setData(newIndex, QVariant::fromValue(note));
    }
}

void NotesModel::deleteNote(int index)
{
    removeRow(index);
}

void NotesModel::setFilterModel(NotesFilterModel *model)
{
    filterModel = model;

    //Initial notes were not connected
    for (Note* n : notes) {
        connectNoteToFilterModel(n);
    }
}

void NotesModel::connectNoteToFilterModel(Note *n)
{
    //Q_ASSERT(!filterModel.isNull());
    if (filterModel.isNull()) {
        qDebug("filterModel is null, new note will not be connected to it");
        return;
    }

    //Name changed -> OnAnyChanged -> automatically refilter
    connect(n, &Note::OnAnyChanged, filterModel.data(), &NotesFilterModel::invalidateFilter);
    //TODO: replace OnAnyChanged with OnNameChanged
}

/*QString Note::getTestStr()
{
    return QString("%1, %2").arg(x).arg(y);
}

//Note &Note::Note::operator=(const Note & other)
//{
//    this->name = other.name;
//    return *this;
//}

Note::~Note()
{
    qDebug("Note destructor");
    //name.clear();
}*/

NotesFilterModel::NotesFilterModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    model = new NotesModel(this);
    model->setFilterModel(this);
    this->setSourceModel(model);
}

bool NotesFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    Note* n = qvariant_cast<Note*>(sourceModel()->data(index));
    return n->name.contains(filterRegExp());
}

