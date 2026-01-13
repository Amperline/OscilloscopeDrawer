#include "Osclscp.h"
#include <QTimer>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <vector>
#include <QStackedLayout>

#define OSCLSCP_W 600
#define OSCLSCP_H 480

#define V_LINES_COUNT 9
#define H_LINES_COUNT 7

// #define ONE_DIV OSCLSCP_H /(V_LINES_COUNT + 1)
#define ONE_DIV OSCLSCP_H /(H_LINES_COUNT + 1)

W_Osclscp::W_Osclscp()
{
    QPalette pal_main = this->palette();
    pal_main.setColor(QPalette::Window, Qt::gray);
    this->setAutoFillBackground(true);
    this->setPalette(pal_main);

    this->setLayout(new QVBoxLayout());
    
    this->layout()->addWidget(new QWidget());

    m_screen_Container = std::unique_ptr<QWidget>(this->layout()->itemAt(0)->widget());
    m_screen_Container->setLayout(new QStackedLayout());

    auto stacked_Layout = dynamic_cast<QStackedLayout*>(m_screen_Container->layout());
    // stacked_Layout->setContentsMargins(0, 0, 0, 0);

    //Views setup
    m_main_View = std::unique_ptr<QGraphicsView>(new QGraphicsView());
    m_Overlay_View = std::unique_ptr<QGraphicsView>(new QGraphicsView());

    // m_Overlay_View->setContentsMargins(0, 0, 0, 0);

    // m_screen_Container->layout()->addWidget(m_main_View.get());
    m_screen_Container->layout()->addWidget(m_Overlay_View.get());

    // m_Overlay_View->setStyleSheet("background: transparent");
    // m_Overlay_View->setAttribute(Qt::WA_TransparentForMouseEvents);
    // m_Overlay_View->raise();

    // should be over "Overlay"
    m_main_View->raise();
    m_main_View->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_main_View->setStyleSheet("background: transparent");

    m_Overlay_View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_Overlay_View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //прибирає рамку з скролами.

    m_Overlay_View->setFrameShape(QFrame::NoFrame);
    m_Overlay_View->setStyleSheet("background: transparent");
    m_Overlay_View->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_Overlay_View->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    //4x3
    m_main_View->setFixedSize(OSCLSCP_W, OSCLSCP_H);
    m_Overlay_View->setFixedSize(OSCLSCP_W, OSCLSCP_H);
    m_Overlay_View->setSceneRect(0, 0, OSCLSCP_W, OSCLSCP_H);
    // m_Overlay_Scene->setSceneRect(0, 0, OSCLSCP_W, OSCLSCP_H);

    //scenes setup
    m_main_Scene = std::unique_ptr<QGraphicsScene>(new QGraphicsScene());
    m_Overlay_Scene = std::unique_ptr<QGraphicsScene>(new QGraphicsScene());

    m_Overlay_Scene->addRect(QRectF(0, 0, OSCLSCP_W, OSCLSCP_H), QPen(Qt::NoPen), QBrush(QColor(209, 209, 209, 255)));

    for(short i = 1; i <= V_LINES_COUNT; i++)
    {
        m_Overlay_Scene->addLine(QLine(i * ONE_DIV, 0, i * ONE_DIV, OSCLSCP_H), QPen(Qt::black, 2));
    }

    for(short i = 1; i <= H_LINES_COUNT; i++)
    {
        // QPointF start = QPointF(i * ONE_DIV, 0);
        // QPointF end = QPointF(i * ONE_DIV, OSCLSCP_H);

        // Перетворюємо в координати viewport
        // QPoint startView = m_Overlay_View->mapFromScene(start);
        // QPoint endView = m_Overlay_View->mapFromScene(end);
        m_Overlay_Scene->addLine(QLine(0, i * ONE_DIV, OSCLSCP_W, i * ONE_DIV), QPen(Qt::black, 2));
    }

    //scene sets

    m_main_View->setScene(m_main_Scene.get());
    m_Overlay_View->setScene(m_Overlay_Scene.get());

    // m_main_View->show();
    m_Overlay_View->show();

    //Initalizing logic of Oscilloscope!
    std::vector<double> signal_arr;
    m_osc = new Oscilloscope(OSCLSCP_H, OSCLSCP_W, signal_arr);

    //connections
}

W_Osclscp::~W_Osclscp()
{
    this->destroy(1, 1);
#ifdef DEBUG
    qDebug() << "Osclscp destroyed!" << Qt::endl;
#endif

}
