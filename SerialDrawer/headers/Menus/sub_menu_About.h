#ifndef SUB_MENU_ABOUT
#define SUB_MENU_ABOUT

#include "Menu_Template.h"
#include <QDialog>
#include <QTextEdit>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>

class Sub_Menu_ABOUT : public Menu_TEMPLATE
{
private:
    QDialog* window = nullptr;
    //std::vector<std::string> getComPortList();
    
public:
    Sub_Menu_ABOUT();
    ~Sub_Menu_ABOUT();
};
#endif