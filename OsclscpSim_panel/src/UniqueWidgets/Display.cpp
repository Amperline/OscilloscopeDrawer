#include "Display.h"
#include <QTimer>
#include <QMouseEvent>


W_Display::W_Display()
{
    this->setLayout(new QHBoxLayout());


    QPalette pal_main = this->palette();
    pal_main.setColor(QPalette::Window, Qt::blue);
    this->setAutoFillBackground(true);
    this->setPalette(pal_main);
    
    //320х240​​
    this->setFixedSize(320, 240);
    //ініціалізуємо зміні, налаштовуємо
    
}

W_Display::~W_Display()
{
    //затираємо
    // TopLayout = nullptr;
    // bar_0 = nullptr;
    // Combo_File = nullptr;
    // consoleOUT = nullptr;
    // consoleIN = nullptr;
    // basicEventTimer = nullptr;
    // if(aboutWidget != nullptr)
    // {
    //     delete aboutWidget;
    //     aboutWidget = nullptr;
    // }
    // m_About = nullptr;
    m_window = nullptr;


    this->destroy(1, 1);
#ifdef DEBUG
    qDebug() << "Menu_START destroyed!" << Qt::endl;
#endif
}