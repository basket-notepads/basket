#include "qmlbasketscene.h"
#include <QDebug>
#include <QQmlContext>
#include <QQmlEngine>
#include <mutex>
#include "qmlnotehandlegrips.h"
#include "qmlbasket.h"
#include "qmlnote.h"
#include "qmlnotesmodel.h"
#include "qmlutils.h"

using namespace qmlbnp;

std::once_flag qmlRegisterFlag;

QmlBasketScene::QmlBasketScene(QWidget* parent) :
    QObject(parent), m_scrollArea(), m_quickWidget(&m_scrollArea),
    cNoteDrag(new QmlNoteDrag()), cUtils(new Utils()), cBasket(new Basket()), cNoteProperties(new qmlbnp::NoteProperties()),
    cModel(new NotesModel())
{
    //connect(m_quickWidget.quickWindow(), &QQuickWindow::afterSynchronizing, this, &QmlBasketScene::afterSynchronizing);

    //m_quickWidget.setMinimumHeight(300); //DEBUG
    m_quickWidget.setToolTip("TODO: ListView.indexAt + NotesModel.data");
    //to ensure that the tooltip is updated immediately, you must call QToolTip::showText()

    //ui->quickWidget->engine()->rootContext()->setContextProperty("theModel", model.data());

    std::call_once(qmlRegisterFlag, []() {
        //qmlRegisterType<CustomType>("hvoigt.net", 1, 0, "CustomType");
        const char* ORG_DOMAIN = "org.kde.basket";
        qmlRegisterType<NotesModel>(ORG_DOMAIN , 1, 0, "NotesModel");
        qmlRegisterType<NotesFilterModel>(ORG_DOMAIN , 1, 0, "NotesFilterModel");
        qmlRegisterType<NoteHandleGrips>(ORG_DOMAIN, 1, 0, "NoteHandleGrips");
        qmlRegisterType<NoteInserter>(ORG_DOMAIN, 1, 0, "NoteInserter");
        qmlRegisterType<qmlbnp::Note>(ORG_DOMAIN, 1, 0, "Note");
        qmlRegisterType<QmlNoteDrag>(ORG_DOMAIN, 1, 0, "QmlNoteDrag");

        qmlRegisterType<NotesModel>(ORG_DOMAIN , 1, 0, "NotesModelDbg");
    });

    QQmlContext* rootContext = m_quickWidget.engine()->rootContext();
    rootContext->setContextProperty("cNoteDrag", cNoteDrag);
    rootContext->setContextProperty("cUtils", cUtils);
    rootContext->setContextProperty("cBasket", cBasket);
    rootContext->setContextProperty("cNoteProperties", cNoteProperties);
    rootContext->setContextProperty("cModel", cModel);
    m_quickWidget.setSource(QUrl::fromLocalFile(":/basketscene.qml"));

    m_quickWidget.m_parentScrollArea = &m_scrollArea;
    m_scrollArea.setWidget(&m_quickWidget);
}
