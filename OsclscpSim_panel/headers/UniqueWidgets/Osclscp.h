#ifndef W_OSCLSCP
#define W_OSCLSCP

#include <QWidget>
#include <QStackedWidget>
#include <vector>
#include <initializer_list>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "Oscilloscope.h"

#include <memory>

//320х240​​
class W_Osclscp : public QWidget
{
private:
enum HS
{
    HIDE,
    SHOW
};

std::unique_ptr<QWidget> m_screen_Container;
std::unique_ptr<QGraphicsView> m_main_View;
std::unique_ptr<QGraphicsView> m_Overlay_View;

std::unique_ptr<QGraphicsScene> m_main_Scene;
std::unique_ptr<QGraphicsScene> m_Overlay_Scene;





void m_Hide_Show(HS state);

Oscilloscope* m_osc;

public:
W_Osclscp();
~W_Osclscp();
};

#endif