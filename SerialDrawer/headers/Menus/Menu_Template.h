#ifndef MENU_TEMPLATE
#define MENU_TEMPLATE

#include <QWidget>
#include <QStackedWidget>
#include <initializer_list>
#include <QMainWindow>

class Menu_TEMPLATE : public QWidget
{
protected:
QMainWindow* m_window = nullptr;

enum HS
{
    HIDE,
    SHOW
};
void m_Hide_Show(HS state);

public:
Menu_TEMPLATE(QMainWindow* window, std::initializer_list<QWidget*> widgets);
~Menu_TEMPLATE();

};

#endif