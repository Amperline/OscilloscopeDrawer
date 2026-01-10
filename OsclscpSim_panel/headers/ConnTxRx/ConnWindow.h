#ifndef CONN_WINDOW
#define CONN_WINDOW

#include "Menu_Template.h"
#include <QMenuBar>
#include <iostream>
#include <QDebug>
#include <QBoxLayout>
#include <QComboBox>
#include <QApplication>
#include <QWidgetAction>
#include <QTextEdit>
#include <QLineEdit>
#include <string>

class ConnWindow : public Menu_TEMPLATE
{
private:
QHBoxLayout* TopLayout = nullptr;
QMenuBar* bar_0 = nullptr;
QComboBox* Combo_File = nullptr;
QTextEdit* consoleOUT = nullptr;
QLineEdit* consoleIN = nullptr;
QMainWindow* window = nullptr;

public:
ConnWindow(std::string portName);
bool isGone();
~ConnWindow();
};

#endif