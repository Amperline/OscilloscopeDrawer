#include "ConnWindow.h"

ConnWindow::ConnWindow(std::string portName)
:Menu_TEMPLATE(nullptr, {})
{
    window = new QMainWindow();
    window->setCentralWidget(this);
    window->showMaximized();

    // QApplication::setStyle("Fusion");  // важливо, щоб палітра працювала
    resize(600, 400);

    QPalette pal_main = this->palette();
    pal_main.setColor(QPalette::Window, Qt::Key_Yellow);
    this->setAutoFillBackground(true);
    this->setPalette(pal_main);

    try {
        // consoleOUT = dynamic_cast<QTextEdit*>(this->layout()->itemAt(1)->widget());
        // consoleIN = dynamic_cast<QLineEdit*>(this->layout()->itemAt(2)->widget());
    } catch (const std::bad_cast& e) {
        // qDebug() << "Menu_START ERROR!" << Qt::endl;
        // std::cerr << "Dynamic cast to reference failed: " << e.what() << std::endl;
    }

    window->show();
}

ConnWindow::~ConnWindow()
{
    if(window != nullptr)
    {
        window->takeCentralWidget();
        window->setCentralWidget(nullptr);
        delete window;
        window = nullptr;
    }

    TopLayout = nullptr;
    bar_0 = nullptr;
    Combo_File = nullptr;
    consoleOUT = nullptr;
    consoleIN = nullptr;

    this->destroy(1, 1);
}

bool ConnWindow::isGone()
{
    if(window != nullptr && window->isHidden())
    {
        return true;
    }
    return false;
}