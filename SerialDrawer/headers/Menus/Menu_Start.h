#ifndef MENU_START
#define MENU_START

#define NOMINMAX 1
#include "Menu_Template.h"
#include "sub_menu_NewConn.h"
#include "ConnWindow.h"
#include "drag_n_drop.h"
#include <QMenuBar>
#include <QDebug>
#include <QBoxLayout>
#include <QComboBox>
#include <QApplication>
#include <QWidgetAction>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QTimer>
#include <vector>


class AboutPopup;

class Menu_START : public Menu_TEMPLATE
{
private:
QHBoxLayout* TopLayout = nullptr;
QMenuBar* bar_0 = nullptr;
QComboBox* Combo_File = nullptr;
QTextEdit* consoleOUT = nullptr;
QLineEdit* consoleIN = nullptr;
QTimer* basicEventTimer = nullptr;
ConnWindow* connW = nullptr;
QMenuBar* statusBar = nullptr;
//це меню потребує додаткових обробок
QMenu* m_About = nullptr;
QTextEdit* input_buffer;
Drag_n_Drop* drag = nullptr;

std::vector<ConnWindow*> c_windows;

Sub_Menu_NEWCONN* menu_NewConn = nullptr;

void New_CON();
void initializeAboutWidget();
public:
Menu_START(QMainWindow* window);
~Menu_START();
};

#endif