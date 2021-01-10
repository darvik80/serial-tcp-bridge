//
// Created by Ivan Kishchenko on 01.01.2021.
//

#ifndef ROVER_BRIDGE_H
#define ROVER_BRIDGE_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "BridgeProperties.h"

class Bridge {
private:
    BridgeProperties _props;
    boost::asio::io_service _service;
    boost::asio::ip::tcp::endpoint _tcpEndpoint;
    boost::asio::ip::tcp::socket _tcpSocket;
    std::vector<uint8_t> _incTcpBuf;
    boost::asio::streambuf _outTcp;


    boost::asio::serial_port  _serialSocket;
    std::vector<uint8_t> _incSerialBuf;
    boost::asio::streambuf _outSerial;

    std::shared_ptr<boost::thread> _thread;

    boost::asio::deadline_timer _timer;
private:

    template<class Reader>
    void startRead(Reader& reader, std::vector<uint8_t>& buffer, const std::function<void(boost::system::error_code, std::size_t size)>& callback);

    void restartTimer();

    void startReadSerial(std::vector<uint8_t>& buffer, const std::function<void(boost::system::error_code, std::size_t)>& callback);
    void onReadSerial(boost::system::error_code err, std::size_t size);
public:
    explicit Bridge(const BridgeProperties& props);

    void start();
    void stop();
};


#endif //ROVER_BRIDGE_H
