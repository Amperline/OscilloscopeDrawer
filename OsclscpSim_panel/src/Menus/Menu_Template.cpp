#include "Menu_Template.h"
#include <QVBoxLayout>

Menu_TEMPLATE::Menu_TEMPLATE(QMainWindow* window, std::initializer_list<QWidget*> widgets)
: QWidget()
{
    //дефолтний лей аут для віджета, який слугує головним в кожному вікні.
    this->setLayout(new QVBoxLayout(this));
    m_window = window;
    auto it = widgets.begin();
    //додаємо всі підвіджети до головного лей ауту.
    for(size_t i = 0; i < widgets.size(); i++)
    {
        this->layout()->addWidget(*(it + i ));
    }
}

Menu_TEMPLATE::~Menu_TEMPLATE()
{
    //просто чистимо
    m_window = nullptr;
    this->destroy(1, 1);
#ifdef DEBUG
    qDebug() << "Menu destroyed!" << Qt::endl;
#endif
}


//поки не застосовував
void Menu_TEMPLATE::m_Hide_Show(HS state)
{
    switch(state)
    {
    case HIDE:
        hide();
        // for(int i = 0; i < this->count(); i++)
        // {
            
        // }
        break;
    case SHOW:
        show();
        break;
    }
}