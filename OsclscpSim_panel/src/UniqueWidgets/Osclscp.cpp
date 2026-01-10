#include "Osclscp.h"
#include <QTimer>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <vector>
#include <QStackedLayout>

#define OSCLSCP_W 400
#define OSCLSCP_H 300

#define V_LINES_COUNT 9 
#define H_LINES_COUNT 7

#define ONE_DIV OSCLSCP_H /(V_LINES_COUNT + 1)

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

    //Views setup
    m_main_View = std::unique_ptr<QGraphicsView>(new QGraphicsView());
    m_Overlay_View = std::unique_ptr<QGraphicsView>(new QGraphicsView());

    m_screen_Container->layout()->addWidget(m_main_View.get());
    m_screen_Container->layout()->addWidget(m_Overlay_View.get());

    // m_Overlay_View->setStyleSheet("background: transparent");
    // m_Overlay_View->setAttribute(Qt::WA_TransparentForMouseEvents);
    // m_Overlay_View->raise();

    // should be over "Overlay"
    m_main_View->raise();
    m_main_View->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_main_View->setStyleSheet("background: transparent");

    //400x300
    m_main_View->setFixedSize(OSCLSCP_W, OSCLSCP_H);
    m_Overlay_View->setFixedSize(OSCLSCP_W, OSCLSCP_H);

    //scenes setup
    m_main_Scene = std::unique_ptr<QGraphicsScene>(new QGraphicsScene());
    m_Overlay_Scene = std::unique_ptr<QGraphicsScene>(new QGraphicsScene());

    m_Overlay_Scene->addRect(QRectF(0, 0, OSCLSCP_W, OSCLSCP_H), QPen(Qt::white));

    for(short i = 1; i <= V_LINES_COUNT; i++)
    {
        m_Overlay_Scene->addLine(QLine(i * ONE_DIV, 0, i * ONE_DIV, OSCLSCP_H), QPen(Qt::black, 2));
    }

    for(short i = 1; i <= H_LINES_COUNT; i++)
    {
        m_Overlay_Scene->addLine(QLine(0, i * ONE_DIV, OSCLSCP_W, i * ONE_DIV), QPen(Qt::black, 2));
    }

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
