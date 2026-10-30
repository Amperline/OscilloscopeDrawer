#include "ConnWindow.h"
#include <QDateTime>
#include <qdatetime.h>
#include <qdebug.h>
#include <stdexcept>

ConnWindow::ConnWindow(std::string portName, QTextEdit* consoleSET)
:Menu_TEMPLATE(nullptr, {})
{
    this->consoleSET = consoleSET;
    window = new QMainWindow();
    window->setCentralWidget(this);
    window->showMaximized();
    window->setMinimumSize(600, 400);
    //window->setFixedSize(600,400);
    // QApplication::setStyle("Fusion");  // важливо, щоб палітра працювала

    QPalette pal_main = this->palette();
    pal_main.setColor(QPalette::Window, Qt::Key_Yellow);
    this->setAutoFillBackground(true);
    this->setPalette(pal_main);

    protocolInteractTimer = new QTimer(this);
    protocolInteractTimer->start(5);//ms

    setupGraph();
    this->layout()->addWidget(chartView);

    controlHandler = new HControlModule(portName);

    protocol_th = std::thread([=]()
    {
        controlHandler->start_Protocol_execution();
    });
    // protocol_th->detach();

    //processing data from controle module
    connect(protocolInteractTimer, &QTimer::timeout, [&](){
        //buffer 100
        std::string recieved_data = "";
        if(controlHandler != nullptr)
            recieved_data = controlHandler->getData();
        if(!recieved_data.empty())
        {
            processData(recieved_data);
            qDebug() << "(about to parce)Something recieved!";
        }
    });

    try {
        // consoleOUT = dynamic_cast<QTextEdit*>(this->layout()->itemAt(1)->widget());
        // consoleIN = dynamic_cast<QLineEdit*>(this->layout()->itemAt(2)->widget());
    } catch (const std::bad_cast& e) {
        // qDebug() << "Menu_START ERROR!" << Qt::endl;
        // std::cerr << "Dynamic cast to reference failed: " << e.what() << std::endl;
    }

    window->show();
}

ConnWindow::~ConnWindow()
{   
    if(window != nullptr)
    {
        window->takeCentralWidget();
        window->setCentralWidget(nullptr);
        delete window;
        window = nullptr;
    }
    if(controlHandler != nullptr)
    {
        controlHandler->stop_Protocol_execution();
    }
    if (protocol_th.joinable()) {
        protocol_th.join();
    }
    delete controlHandler;
    this->destroy(1, 1);
    qDebug("ConnWindow destroyed!");
}

void ConnWindow::setupGraph() {
    series = new QLineSeries();//математика (дані)
    chart = new QChart();//дизайн (координатна сітка)

    chart->addSeries(series);
    chart->setTitle("ADC Graph");
    chart->legend()->hide();

    // Налаштування осі X (Час)
    axisX = new QDateTimeAxis();
    axisX->setFormat("mm.ss");
    axisX->setTitleText("Час");
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(0), QDateTime::fromMSecsSinceEpoch(30000));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Налаштування осі Y (АЦП)
    axisY = new QValueAxis();
    axisY->setRange(0, 5000);
    axisY->setTitleText("Voltage(mV)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Створення віджета і додавання його в Layout вашого вікна
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRubberBand(QChartView::RectangleRubberBand);
    // Припустимо, у вас у формі є QVBoxLayout* mainLayout
    // ui->verticalLayout->addWidget(chartView);
}

void ConnWindow::clearGraph() {
    if(series != nullptr)
        series->clear();
    if (axisX != nullptr) {
        axisX->setRange(QDateTime::fromMSecsSinceEpoch(0), QDateTime::fromMSecsSinceEpoch(30000));
    }
    graphTimer.restart();
}

// Функція, яка викликається при отриманні нових даних (наприклад, з Serial Port)
void ConnWindow::updateData(unsigned int newValue) {
    if (series == nullptr || axisX == nullptr) {
        throw std::logic_error("(update data) empty series or axis");
    }

    qint64 elapsed = graphTimer.elapsed();
    series->append(elapsed, newValue);

    if (elapsed > axisX->max().toMSecsSinceEpoch()) {
        axisX->setMax(QDateTime::fromMSecsSinceEpoch(elapsed));
    }
}

bool ConnWindow::isGone()
{
    if(window != nullptr && window->isHidden())
    {
        return true;
    }
    return false;
}

void ConnWindow::send(std::string str)
{
    if(controlHandler != nullptr)
    {
        controlHandler->ext_send(str);
        qDebug() << "Sending:" << str;
    }
}

//data from slave control module
//safe parcing function
void ConnWindow::processData(std::string data)
{
    Q_ASSERT(consoleSET != nullptr); // ← одразу побачите
    qDebug() << "consoleSET ptr:" << (void*)consoleSET;
    //R_ - recieved and should be written to console
    //E_ - also from MC
    unsigned int value;
    if(sscanf(data.c_str(), "DATA:%u", &value) == 1)
    {
        try{
        updateData(value);
        }
        catch(std::logic_error &e)
        {
            qDebug() << e.what();
        }
    }
    else if(strncmp(data.c_str(), "MSG:", 4) == 0)
    {
        consoleSET->setText("R_" + QString::fromStdString(data).mid(4));
    }
    else if(strncmp(data.c_str(), "ERR:", 4) == 0)
    {
        consoleSET->setText("E_" + QString::fromStdString(data).mid(4));
    }
    else if(strncmp(data.c_str(), "RESET:", 6) == 0)
    {
        clearGraph();
    }
    else
    {
        consoleSET->setText("E_Wrong Data!");
        qDebug() << data;
    }

}