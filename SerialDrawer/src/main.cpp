#include <winsock2.h>
#include <windows.h>
#include <tlhelp32.h>

#include <QApplication>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>

#include "Menu_Start.h"

// enum APP_STATE
// {
//     IN_MAIN_MENU,
//     IN_CONNECTION
// };

int main(int argc, char *argv[])
{
#ifndef DEBUG
    HWND CWindow = GetConsoleWindow();
    if(CWindow != NULL)
        ShowWindow(CWindow, SW_HIDE);
#endif
    // APP_STATE state = IN_MAIN_MENU;
    QApplication app(argc, argv);
    QMainWindow window;
    window.setWindowIconText("Lab7");
    
    Menu_START menu_Start(&window);
    
    // std::thread thread_QT([&](){
    //     window.show();
    //     return app.exec();
    // });

    window.show();
    return app.exec();
}