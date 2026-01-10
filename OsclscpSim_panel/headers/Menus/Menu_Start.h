#ifndef MENU_START
#define MENU_START

#include "Menu_Template.h"
#include "sub_menu_NewConn.h"
#include "Display.h"
#include "Osclscp.h"

#include <QMenuBar>
#include <iostream>
#include <QDebug>
#include <QBoxLayout>
#include <QComboBox>
#include <QApplication>
#include <QWidgetAction>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>

#include <vector>
class AboutPopup;

class Menu_START : public Menu_TEMPLATE
{
private:
QHBoxLayout* TopLayout = nullptr;
// QVBoxLayout* MidSectionLayout = nullptr;
QMenuBar* bar_0 = nullptr;
QComboBox* Combo_File = nullptr;
QTextEdit* consoleOUT = nullptr;
QLineEdit* consoleIN = nullptr;
QTimer* basicEventTimer = nullptr;
AboutPopup* aboutWidget = nullptr;

QWidget* MidSectionWidget = nullptr;

W_Display* m_display = nullptr;

//це меню потребує додаткових обробок
QMenu* m_About = nullptr;

// std::vector<ConnWindow*> c_windows;

Sub_Menu_NEWCONN* menu_NewConn = nullptr;

void New_CON();
void initializeAboutWidget();
public:
Menu_START(QMainWindow* window);
~Menu_START();

friend class AboutPopup;
};

class AboutPopup : public QWidget {
private:
    QTextEdit* textEdit = nullptr;
    Menu_START* menu = nullptr;
public:
    AboutPopup(Menu_START* menu, QWidget* parent);
    ~AboutPopup();

protected:
    // void focusOutEvent(QFocusEvent *e) override {
    //     QWidget::focusOutEvent(e);
    //     close();
    // }

    bool event(QEvent* e) override {
        if (e->type() == QEvent::WindowDeactivate) {
            close();
        }
        return QWidget::event(e);
    }
};
#endif