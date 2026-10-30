#include "Menu_Start.h"
#include <QTimer>
#include <QMouseEvent>
#include <qdebug.h>
#include <qmainwindow.h>
#include <qobject.h>
#include <qtextedit.h>
#include <winsock2.h>
#include "ConnWindow.h"
#include "sub_menu_About.h"

Menu_START::Menu_START(QMainWindow* window)
:Menu_TEMPLATE(window, {new QMenuBar(), new QMenuBar(), new QTextEdit(), new QLineEdit(), new Drag_n_Drop()})
{
    //ініціалізуємо зміні
    basicEventTimer = new QTimer(this);
    basicEventTimer->start(3000);

    //design
    m_window->setFixedSize(450, 300);
    m_window->setCentralWidget(this);
    QApplication::setStyle("Fusion");  // важливо, щоб палітра працювала
    resize(600, 400);

    QPalette pal_main = this->palette();
    pal_main.setColor(QPalette::Window, Qt::darkBlue);
    this->setAutoFillBackground(true);
    this->setPalette(pal_main);

    //доступ до об'єктів голового лей ауту,
    //але щоб нічого не зламати dynamic_cast
    try {
        bar_0 = dynamic_cast<QMenuBar*>(this->layout()->itemAt(0)->widget());
        statusBar = dynamic_cast<QMenuBar*>(this->layout()->itemAt(1)->widget());
        consoleOUT = dynamic_cast<QTextEdit*>(this->layout()->itemAt(2)->widget());
        consoleIN = dynamic_cast<QLineEdit*>(this->layout()->itemAt(3)->widget());
        drag = dynamic_cast<Drag_n_Drop*>(this->layout()->itemAt(4)->widget());
    } catch (const std::bad_cast& e) {
        qDebug() << "Menu_START ERROR!" << e.what() << Qt::endl;
    }

    // TopLayout = new QHBoxLayout();
    // bar_0->setLayout(TopLayout);
    //додаємо основні можливості
    QMenu* m_File = bar_0->addMenu("File");
    QAction* m_About = bar_0->addAction("About");

    QAction* m_action_NEWCONN = m_File->addAction("New connection");
    m_File->addAction("COOL");

    consoleOUT->setReadOnly(true);

    //трохи кольору
    QPalette pal_0 = bar_0->palette();
    pal_0.setColor(QPalette::WindowText, Qt::white);
    pal_0.setColor(QPalette::Window, Qt::gray);
    bar_0->setAutoFillBackground(true);
    bar_0->setPalette(pal_0);
    bar_0->setFixedHeight(25);

    //buttons-commands:
    QAction* m_action_STOP =  statusBar->addAction("STOP");
    QAction* m_action_PAUSE =  statusBar->addAction("PAUSE");

    input_buffer = new QTextEdit();
    //пішли конекти
    connect(m_action_NEWCONN, &QAction::triggered, [=](){
        Sub_Menu_NEWCONN menu_NewConn(consoleOUT);
        if(!menu_NewConn.getOption().empty())
        {
            std::string port_name;
            asio::io_context io;
            asio::serial_port serial(io);
            bool failed_to_connect = false;
            try{serial.open(port_name = menu_NewConn.getOption());}
            catch(boost::system::system_error& e){failed_to_connect =true;}
            if(!failed_to_connect)
            {
                serial.close();
                try{
                    connW = new ConnWindow(port_name, input_buffer);            
                }
                catch(boost::system::system_error& e)
                {
                    qDebug() << e.what();
                }
            }
            else
            {
                serial.close();
                consoleOUT->setTextColor(Qt::red);
                consoleOUT->append("ERROR: failed to connect serial!");
            }
        }
        //delete menu_NewConn;
        //menu_NewConn = nullptr;
    });

    connect(m_action_PAUSE, &QAction::triggered, [=]()
    {
        QString text("PAUSE");
        if(connW != nullptr)
        {
            consoleOUT->setTextColor(Qt::green);
            consoleOUT->append("(ORDER): " + text);
            connW->send(text.toStdString());
        }
        else
        {
            consoleOUT->setTextColor(Qt::red);
            consoleOUT->append("ERROR: nothing connected!");
        }
    });

    connect(m_action_STOP, &QAction::triggered, [=]()
    {
        QString text("STOP");
        if(connW != nullptr)
        {
            consoleOUT->setTextColor(Qt::green);
            consoleOUT->append("(ORDER): " + text);
            connW->send(text.toStdString());
        }
        else
        {
            consoleOUT->setTextColor(Qt::red);
            consoleOUT->append("ERROR: nothing connected!");
        }
    });

    connect(input_buffer, &QTextEdit::textChanged, [=]() {
        QString indentificator = input_buffer->toPlainText().left(2);
        QString text = input_buffer->toPlainText().mid(2);
        //C_ - command
        //R_ - recieved
        //E_ - error
        consoleOUT->setTextColor(Qt::green);
        if(indentificator == "C_")
        {
            consoleOUT->setTextColor(Qt::green);
            consoleOUT->append("(ORDER): " + text);
        }
        else if(indentificator == "R_")
        {
            consoleOUT->setTextColor(Qt::blue);
            consoleOUT->append("(MC): " + text);
        }
        else if(indentificator == "E_")
        {
            consoleOUT->setTextColor(Qt::red);
            consoleOUT->append("(MC): " + text);
        }
    });

    connect(consoleIN, &QLineEdit::returnPressed, [=]() {
        QString text = "C_" + consoleIN->text();
        if(!text.isEmpty())
        {
            if(connW != nullptr)
            {
                consoleOUT->setTextColor(Qt::green);
                input_buffer->setText(text);
                connW->send(text.mid(2).toStdString());
            }
            else
            {
                consoleOUT->setTextColor(Qt::red);
                consoleOUT->append("ERROR: nothing connected!");
            }
        }
        else
        {
            consoleOUT->setTextColor(Qt::red);
            consoleOUT->append("ERROR: nothing to send!");
        }
        consoleIN->clear();
    });

    connect(m_About, &QAction::triggered, [=](){
        Sub_Menu_ABOUT sub_about_m;
    });

    //загальний обробник
    connect(basicEventTimer, &QTimer::timeout, [&](){
        for(size_t i = 0; i < c_windows.size();)
        {
            if(c_windows.at(i) != nullptr && c_windows.at(i)->isGone())
            {
                delete c_windows.at(i);
                c_windows.at(i) = nullptr;
                c_windows.erase(c_windows.begin() + i);
            }
            else
                i++;
        }
    });

    consoleOUT->append("HI! IT IS OUT! Good Luck!");
}

Menu_START::~Menu_START()
{
    //затираємо
    // TopLayout = nullptr;
    // bar_0 = nullptr;
    // Combo_File = nullptr;
    // consoleOUT = nullptr;
    // consoleIN = nullptr;
    // basicEventTimer = nullptr;
    // m_About = nullptr;
    if(input_buffer != nullptr)
        delete input_buffer;
    this->destroy(1, 1);
#ifdef DEBUG
    qDebug() << "Menu_START destroyed!" << Qt::endl;
#endif
}

void Menu_START::New_CON()
{
    qDebug() << "New_CON triggered!";
}
