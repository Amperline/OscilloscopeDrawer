#include "ctrl_Module.h"
#include "QDebug"
#include <QString>
#include <cstddef>
#include <cstring>
#include <qlogging.h>

 
HControlModule::HControlModule(std::string portName)
{
    io = new asio::io_context();
    serial = new asio::serial_port(*this->io);

    try
    {
        serial->open(portName);
        serial->set_option(asio::serial_port_base::baud_rate(9600));
    }
    catch(boost::system::system_error& e)
    {
        qDebug() << e.what();
    }

    //serial->write_some(asio::buffer(s_buffer, strlen(s_buffer) + 1));
    //serial->read_some(asio::buffer(r_buffer, 128));
}
 
HControlModule::~HControlModule()
{
    qDebug() << "ctrl module delete";
    if(is_running != false)
        is_running = false;

    if(io != nullptr) delete io;
    if(serial != nullptr) delete serial;
}

bool HControlModule::moduleHandler()
{
    return true;
}

void HControlModule::clearBuff()
{
    memset(r_buffer, '0', S_R_BUFFER_SIZE);
}

bool HControlModule::writeMainConsole(QTextEdit* consoleOUT, char* str)
{
    if(str == nullptr) return false;
    consoleOUT->append(QString::fromUtf8(str));
    return true;
}

bool HControlModule::write(char* msg)
{
    if(msg == nullptr)
        return false;

    std::vector<char> final_msg(msg, msg + strlen(msg));//without \0
    final_msg.insert(final_msg.end(), 5, '\0');//for unique protocol

    
    port_mutex.lock();
    if(serial == nullptr || !serial->is_open())
    {
        port_mutex.unlock();
        return false;
    }
    if(serial->write_some(asio::buffer(final_msg)) != 0)
    {
        port_mutex.unlock();
        return true;
    }
    
    return false;
}

bool HControlModule::read()
{
    clearBuff();
    size_t bytes_read = 0;
    boost::system::error_code ec;

    std::unique_lock<std::mutex> lock(port_mutex);
    if (serial == nullptr || !serial->is_open()) return false;

    COMSTAT status;
    DWORD errors;
    if (ClearCommError(serial->native_handle(), &errors, &status)) {
        if (status.cbInQue == 0)
        {
            lock.unlock();
            return false;  
        }
    }

    bytes_read = serial->read_some(asio::buffer(r_buffer, S_R_BUFFER_SIZE), ec);
    lock.unlock();

    if (ec || bytes_read == 0) return false;

    row_data.append(r_buffer, bytes_read); 
    qDebug() << "(ctr module) Received chunk size:" << bytes_read;
    qDebug() << "(ctr module) FULL row:" << row_data;

    const std::string delimiter(5, '\0');


    while(true)
    {
        size_t pos = row_data.find(delimiter);
    
        if (pos == std::string::npos) {
            break; // Більше повних пакетів немає, виходимо з циклу
        }
        std::string data_to_process = row_data.substr(0, pos);
        row_data.erase(0, pos + 5);

        read_mutex.lock();
        data_list.push_back(data_to_process);
        buffer_unprocessed = true;
        read_mutex.unlock();
    }

    return true;
}

std::string HControlModule::getData()
{
    std::string str_to_return = std::string("");

    read_mutex.lock();
    
    if(buffer_unprocessed == true)
    {
        str_to_return = data_list[0];
        data_list.pop_front();
    }

    buffer_unprocessed = false;
    if(!data_list.empty())
        buffer_unprocessed = true;

    read_mutex.unlock();
    
    return str_to_return;
}


void HControlModule::stop_Protocol_execution()
{
    is_running = false;

    if (serial != nullptr && serial->is_open())
    {
        serial->cancel();
        serial->close();
    }

    if(read_th.joinable())
    {
        read_th.join();
    }
}


void HControlModule::start_Protocol_execution()
{
    is_running = true;
    read_th =std::thread([&]()
    {
        while(is_running == true)
        {
            read();
        }
    });
while(is_running == true){
    internal_recieve.lock();
    if(!internal_commands.empty())
    {
        if(!internal_commands[0].empty())
        {
            char to_send[S_R_BUFFER_SIZE];
            strcpy(to_send, internal_commands.at(0).c_str());
            write(to_send);
        }
        internal_commands.pop_front();
    }
    internal_recieve.unlock();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
}

void HControlModule::push_Command(std::string cmd)
{
    internal_recieve.lock();
    internal_commands.push_back(cmd);
    internal_recieve.unlock();
}