#include "sub_menu_NewConn.h"
#include <QLayout>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>
#include <QLabel>

Sub_Menu_NEWCONN::Sub_Menu_NEWCONN(QTextEdit* consoleOUT)
:Menu_TEMPLATE(nullptr, {new QLabel(), new QComboBox(), new QPushButton()})
{
    //ініціалізуємо зміні, налаштовуємо
    this->consoleOUT = consoleOUT;
    window = new QDialog();

    window->setLayout(new QHBoxLayout());
    window->layout()->addWidget(this);
    window->setFixedSize(300, 150);

    QPalette pal_main = this->palette();
    pal_main.setColor(QPalette::Window, Qt::darkGreen);
    this->setAutoFillBackground(true);
    this->setPalette(pal_main);

    QTimer comboUpdate(this);
    std::vector<std::string> portList;

    //доступ до об'єктів голового лей ауту,
    //але щоб нічого не зламати dynamic_cast
    QLabel* label = nullptr;
    QComboBox* combo = nullptr;
    QPushButton* Butt_CONNECT = nullptr;
    try {
        label = dynamic_cast<QLabel*>(this->layout()->itemAt(0)->widget());
        combo = dynamic_cast<QComboBox*>(this->layout()->itemAt(1)->widget());
        Butt_CONNECT = dynamic_cast<QPushButton*>(this->layout()->itemAt(2)->widget());
    } catch (const std::bad_cast& e) {
        qDebug() << "sub_menu_NewConn ERROR!" << Qt::endl;
    }
    Butt_CONNECT->setText("Connect");
    label->setText("COM PORTS:");
    
    //throw QTimer::timeout кожн 0.5 сек.
    comboUpdate.start(500);

    //пішли конекти(основна логіка вікна)
    connect(&comboUpdate, &QTimer::timeout, [=, &portList](){
        std::vector<std::string> tempList = getComPortList();

        if(tempList.empty() || tempList.at(0) == "ERROR")
        {
            if(combo->count() != 0)
                combo->clear();
            combo->addItem("Not Found");
        }

        if(portList != tempList)
        {
            if(combo == nullptr)
                qDebug() << "Error: Combo is nullptr!!!";
            if(combo->count() != 0)
                combo->clear();
            portList = tempList;
            for(int i = 0; i < portList.size(); i++)
            {
                combo->addItem(portList.at(i).c_str());
            }
#ifdef DEBUG
            combo->addItem("D_Audit");
#endif
        }
    });
    
    connect(Butt_CONNECT, &QPushButton::pressed, [=](){
        this->strToReturn = combo->currentText().toStdString();
        if(this->strToReturn == "Not Found" || this->strToReturn.empty())
        {
            this->consoleOUT->append("Error: nothing to connect!");
            this->strToReturn.clear();
            return;
        }
        window->close();
    });

    //затираємо перед exec
    //бо більше не використається
    combo = nullptr;
    Butt_CONNECT = nullptr;
    label = nullptr;
    window->exec();
}


Sub_Menu_NEWCONN::~Sub_Menu_NEWCONN()
{
    //просто чистимо
    if(window != nullptr)
    {
        window->layout()->removeWidget(this);
        this->setParent(nullptr);
        delete window;
        window = nullptr;
    }
    consoleOUT = nullptr;
    this->destroy(1, 1);
}

std::string Sub_Menu_NEWCONN::getOption()
{
    //це ми передамо до вікна(класу) з'єднання, який буде мати вбудованний протокол керування.
    return strToReturn;
}

std::vector<std::string> Sub_Menu_NEWCONN::getComPortList()
{
    std::vector<std::string> portList;
    // SetupDiGetClassDevs – функція, яка повертає список пристроїв певного класу.

    // GUID_DEVCLASS_PORTS – спеціальний ідентифікатор класу COM/LPT портів.

    // DIGCF_PRESENT – означає, що цікавлять лише підключені (присутні) пристрої.

    // Результат – HDEVINFO, який є "handle" на список інформації про пристрої.
    HDEVINFO deviceInfo = SetupDiGetClassDevs(
        (const GUID*)&GUID_DEVCLASS_PORTS,
        0, 0, DIGCF_PRESENT);

    if (deviceInfo == INVALID_HANDLE_VALUE)
    {
        portList.push_back("ERROR");
        return portList;
    }

    // SP_DEVINFO_DATA – структура, що описує один пристрій у списку.

    // cbSize треба виставити вручну (WinAPI так перевіряє правильність).

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    // SetupDiOpenDevRegKey – відкриває гілку реєстру, де зберігається інформація про пристрій.
    for (DWORD i = 0; SetupDiEnumDeviceInfo(deviceInfo, i, &deviceInfoData); i++) {
        HKEY hDeviceRegistryKey = SetupDiOpenDevRegKey(
            deviceInfo, &deviceInfoData,
            DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);

        if (hDeviceRegistryKey == INVALID_HANDLE_VALUE) continue;

        char portName[256];
        DWORD size = sizeof(portName);
        DWORD type = 0;

        if (RegQueryValueExA(hDeviceRegistryKey, "PortName", 0, &type, (LPBYTE)portName, &size) == ERROR_SUCCESS) {
            portList.push_back(portName);
        }
        RegCloseKey(hDeviceRegistryKey);
    }
    SetupDiDestroyDeviceInfoList(deviceInfo);
    return portList;
}