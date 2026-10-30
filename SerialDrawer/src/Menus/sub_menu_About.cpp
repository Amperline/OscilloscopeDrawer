#include "sub_menu_About.h"
#include <QLayout>
#include <QTimer>
#include <QLabel>

Sub_Menu_ABOUT::Sub_Menu_ABOUT()
:Menu_TEMPLATE(nullptr, {new QLabel()})
{
    //ініціалізуємо зміні, налаштовуємо
    window = new QDialog();

    window->setLayout(new QHBoxLayout());
    window->layout()->addWidget(this);
    window->setFixedSize(300, 400);

    QPalette pal_main = this->palette();
    pal_main.setColor(QPalette::Window, Qt::gray);
    this->setAutoFillBackground(true);
    this->setPalette(pal_main);

    //QTimer comboUpdate(this);

    //доступ до об'єктів голового лей ауту,
    //але щоб нічого не зламати dynamic_cast
    QLabel* label = nullptr;
    try {
        label = dynamic_cast<QLabel*>(this->layout()->itemAt(0)->widget());
    } catch (const std::bad_cast& e) {
        qDebug() << "sub_menu_NewConn ERROR!" << Qt::endl;
    }
    label->setText(
        "Програма: Serial_Panel\n"
        "Версія: 1.0 BETA\n"
        "Автор: Artem Viktorenko\n\n"
        "commands: \n"
        "START -n x -d y \n(x - number of measurements)\n(y - duration)\n"
        "START (to resume)\n"
        "STOP\n"
        "PAUSE\n"
        
        "Всі кредити до РС.\n"
        "Слава Україні!\n"
    );

    label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    //затираємо перед exec
    //бо більше не використається
    label = nullptr;
    
    window->exec();
}


Sub_Menu_ABOUT::~Sub_Menu_ABOUT()
{
    //просто чистимо
    if(window != nullptr)
    {
        window->layout()->removeWidget(this);
        this->setParent(nullptr);
        delete window;
        window = nullptr;
    }
    this->destroy(1, 1);
}