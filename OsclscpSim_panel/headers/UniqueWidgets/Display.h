#ifndef W_DISPLAY
#define W_DISPLAY   

#include <QWidget>
#include <QStackedWidget>
#include <vector>
#include <initializer_list>
#include <QMainWindow>
#include <QHBoxLayout>

//320х240​​
class W_Display : public QWidget
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
W_Display();
~W_Display();

};

#endif