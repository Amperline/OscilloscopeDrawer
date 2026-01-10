#include "Menu_Start.h"
#include <QTimer>
#include <QMouseEvent>

Menu_START::Menu_START(QMainWindow* window)
:Menu_TEMPLATE(window, {new QMenuBar(), new QWidget()})
{
    //ініціалізуємо зміні, налаштовуємо

    aboutWidget = new AboutPopup(this, nullptr);

    basicEventTimer = new QTimer(this);
    basicEventTimer->start(3000);

    // m_window->setFixedSize(450, 300);
    m_window->setCentralWidget(this);
    QApplication::setStyle("Fusion");  // важливо, щоб палітра працювала
    // resize(600, 400);

    QPalette pal_main = this->palette();
    pal_main.setColor(QPalette::Window, Qt::red);
    this->setAutoFillBackground(true);
    this->setPalette(pal_main);

    //доступ до об'єктів голового лей ауту,
    //але щоб нічого не зламати dynamic_cast
    try {
        bar_0 = dynamic_cast<QMenuBar*>(this->layout()->itemAt(0)->widget());
        MidSectionWidget = this->layout()->itemAt(1)->widget();
        // consoleOUT = dynamic_cast<QTextEdit*>(this->layout()->itemAt(1)->widget());
        // consoleIN = dynamic_cast<QLineEdit*>(this->layout()->itemAt(2)->widget());
    } catch (const std::bad_cast& e) {
        qDebug() << "Menu_START ERROR!" << Qt::endl;
    }

    MidSectionWidget->setLayout(new QHBoxLayout());
    MidSectionWidget->layout()->addWidget(new W_Display());
    MidSectionWidget->layout()->addWidget(new W_Osclscp());

//QSlider, QDial, QCheckBox / QRadioButton

    // TopLayout = new QHBoxLayout();
    // bar_0->setLayout(TopLayout);
    //додаємо основні можливості
    QMenu* m_File = bar_0->addMenu("File");
    QMenu* m_Settings = bar_0->addMenu("Settings");
    m_About = bar_0->addMenu("About");

    QAction* m_action_NEWCONN = m_File->addAction("New connection");
    m_File->addAction("COOL");

    // consoleOUT->setReadOnly(true);

    //трохи кольору
    QPalette pal_0 = bar_0->palette();
    pal_0.setColor(QPalette::WindowText, Qt::white);
    pal_0.setColor(QPalette::Window, Qt::gray);
    bar_0->setAutoFillBackground(true);
    bar_0->setPalette(pal_0);
    bar_0->setFixedHeight(25);

    //пішли конекти
    // connect(m_action_NEWCONN, &QAction::triggered, [=](){
    //     menu_NewConn = new Sub_Menu_NEWCONN(consoleOUT);
    //     if(menu_NewConn->getOption().empty()) goto LEAVE;
    //     this->c_windows.push_back(new ConnWindow(menu_NewConn->getOption()));
    //     LEAVE:
    //     delete menu_NewConn;
    //     menu_NewConn = nullptr;
    // });

    // connect(consoleOUT, &QTextEdit::textChanged, [=]() {
    //     QString text = consoleOUT->toPlainText();
    //     if (text.endsWith("\n")) {
    //         QString command = text.section("\n", -2, -2); // останній рядок
    //         qDebug() << "Order: " << command;
    //         consoleOUT->append("Done: " + command);
    //     }
    // });

    // connect(consoleIN, &QLineEdit::returnPressed, [=]() {
    //     QString text = consoleIN->text();
    //     consoleOUT->append(text);
    //     consoleIN->clear();
    // });

    connect(m_About, &QMenu::aboutToShow, [=](){
        QPoint globalPos = bar_0->mapToGlobal(bar_0->actionGeometry(m_About->menuAction()).bottomLeft());
        aboutWidget->move(globalPos);
        aboutWidget->show();
        aboutWidget->setFocus();
    });

    connect(m_About, &QMenu::aboutToHide, [=](){
        aboutWidget->hide();
    });
    // connect(dynamic_cast<QWidget*>(m_About), &QWidget::focusOutEvent, [](){});

    //загальний обробник
    // connect(basicEventTimer, &QTimer::timeout, [&](){
    //     for(size_t i = 0; i < c_windows.size();)
    //     {
    //         if(c_windows.at(i) != nullptr && c_windows.at(i)->isGone())
    //         {
    //             delete c_windows.at(i);
    //             c_windows.at(i) = nullptr;
    //             c_windows.erase(c_windows.begin() + i);
    //         }
    //         else
    //             i++;
    //     }
    // });
}

Menu_START::~Menu_START()
{
    //затираємо
    TopLayout = nullptr;
    bar_0 = nullptr;
    Combo_File = nullptr;
    consoleOUT = nullptr;
    consoleIN = nullptr;
    basicEventTimer = nullptr;
    if(aboutWidget != nullptr)
    {
        delete aboutWidget;
        aboutWidget = nullptr;
    }
    m_About = nullptr;


    this->destroy(1, 1);
#ifdef DEBUG
    qDebug() << "Menu_START destroyed!" << Qt::endl;
#endif
}

void Menu_START::New_CON()
{
    qDebug() << "New_CON triggered!";
}

AboutPopup::AboutPopup(Menu_START* menu, QWidget* parent = nullptr)
:QWidget(parent)
{
    this->menu = menu;

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);

    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    textEdit->setText(
        "Програма: TVA Panel\n"
        "Версія: 1.0\n"
        "Автор: Артем\n\n"
        "Можна копіювати текст (Ctrl+C)"
    );

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(textEdit);

    setFocusPolicy(Qt::StrongFocus);
}

AboutPopup::~AboutPopup()
{
    this->menu = nullptr;
}


// bool AboutPopup::eventFilter(QObject* obj, QEvent* event) {
//     if (event->type() == QEvent::MouseButtonPress) {
//         QMouseEvent* me = static_cast<QMouseEvent*>(event);
//         if(me->button() == Qt::LeftButton) {
//             QAction* action = menu->m_About->actions().first();
//             if(action) action->trigger();
//             return true; // подія оброблена, AboutPopup не реагує
//         }
//     }
//     return QObject::eventFilter(obj, event);
// }