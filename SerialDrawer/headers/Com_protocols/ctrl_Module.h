//UART controle module
//responsible only for communication protocol
#ifndef CONTROL_MODULE
#define CONTROL_MODULE

#include <boost/asio.hpp>
#include <boost/exception/all.hpp>
#include <deque>
#include <QTextEdit>
#include <mutex>
#include <thread>
#include <vector>

#define S_R_BUFFER_SIZE 100

using namespace boost;

class HControlModule
{
    enum REQUEST_WEIGHT
    {
        STRONG,
        WEAK
    };
private:
asio::io_context* io = nullptr;
asio::serial_port* serial = nullptr;
std::atomic<bool> is_running = true;

char r_buffer[S_R_BUFFER_SIZE];
std::string row_data = "";

std::deque<std::string> data_list;
std::deque<std::string> internal_commands;

bool buffer_unprocessed = false;

std::mutex read_mutex;
std::mutex internal_recieve;
std::mutex port_mutex;

std::thread read_th;

public:
void clearBuff();
~HControlModule();

HControlModule(std::string portName);
bool moduleHandler();
bool writeMainConsole(QTextEdit* consoleOUT, char* str);

bool write(char* msg);
bool read();

//gives one time once it recieved
std::string getData();

void start_Protocol_execution();
void stop_Protocol_execution();

void push_Command(std::string cmd);

void ext_send(std::string data)
{
    internal_recieve.lock();
    internal_commands.push_back(data);
    internal_recieve.unlock();
};

};
#endif