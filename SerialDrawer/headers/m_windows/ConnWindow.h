#ifndef CONN_WINDOW
#define CONN_WINDOW

#include "Menu_Template.h"
#include "ctrl_Module.h"
#include <QMenuBar>
#include <QDebug>
#include <QBoxLayout>
#include <QComboBox>
#include <QApplication>
#include <QWidgetAction>
#include <QTextEdit>
#include <QLineEdit>
#include <qtimer.h>
#include <string>

#include <QChart>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QChartView>
#include <QTimer>
#include <QElapsedTimer>

class ConnWindow : public Menu_TEMPLATE
{
private:
    QHBoxLayout* TopLayout = nullptr;
    QMenuBar* bar_0 = nullptr;
    QComboBox* Combo_File = nullptr;
    QTextEdit* consoleSET = nullptr;
    HControlModule* controlHandler = nullptr;
    QMainWindow* window = nullptr;

    QElapsedTimer graphTimer;
    QChart* chart = nullptr;
    QLineSeries* series = nullptr;
    QDateTimeAxis* axisX = nullptr;
    QValueAxis* axisY = nullptr;
    QChartView* chartView = nullptr;

    std::thread protocol_th;

    QTimer* protocolInteractTimer = nullptr;

    void setupGraph();

public:
    enum STATE
    {
        GOING,
        PAUSE,
        STOPPED
    };
    STATE m_state = STOPPED;
    ConnWindow(std::string portName, QTextEdit* consoleSET);
    void updateData(unsigned int newValue);
    bool isGone();
    void processData(std::string data);
    void clearGraph();
    void send(std::string str);
    ~ConnWindow();
};

#endif