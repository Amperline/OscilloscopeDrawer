#ifndef SUB_MENU_NEWCONN
#define SUB_MENU_NEWCONN

#include "Menu_Template.h"
#include <QDialog>
#include <QTextEdit>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <string>
#include <vector>


class Sub_Menu_NEWCONN : public Menu_TEMPLATE
{
private:
QDialog* window = nullptr;
QTextEdit* consoleOUT = nullptr;
std::string strToReturn;

std::vector<std::string> getComPortList();

public:
Sub_Menu_NEWCONN(QTextEdit* consoleOUT);
std::string getOption();
~Sub_Menu_NEWCONN();

};
#endif