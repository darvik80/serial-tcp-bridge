//
// Created by Ivan Kishchenko on 01.01.2021.
//

#include "Bridge.h"

#include <utility>

#include <boost/lexical_cast.hpp>
#include <iostream>

Bridge::Bridge(const BridgeProperties &props)
        : _props(props)
        , _tcpSocket(_service)
        , _serialSocket(_service)
        , _timer(_service)
        , _incTcpBuf(1024)
        , _incSerialBuf(1024) {

}

void Bridge::restartTimer() {
    _outSerial.sputn((char *) "READY", 6);
    boost::asio::async_write(
            _serialSocket,
            _outSerial,
            [](boost::system::error_code err, std::size_t read) {
                if (!err) {
                    std::cout << "Serial notified" << std::endl;
                } else {
                    std::cout << "Serial failed: " << err.message() << std::endl;;
                }
            }
    );

    _timer.expires_from_now(boost::posix_time::seconds{5});
    _timer.async_wait([this](boost::system::error_code err) {
        if (!err) {
            restartTimer();
        }
    });
}

void Bridge::start() {
    boost::asio::ip::tcp::resolver::query resolver_query(_props.host, boost::lexical_cast<std::string>(_props.port));
    boost::asio::ip::tcp::resolver resolver(_service);
    auto iterator = resolver.resolve(resolver_query);
    _tcpEndpoint = *iterator;

    boost::system::error_code err;

    _serialSocket.open(_props.portName, err);
    if (err) {
        std::cout << "error : port_->open() failed...com_port_name="
                  << _props.portName << ", e=" << err.message() << std::endl;
        return;
    }
    _serialSocket.set_option(boost::asio::serial_port_base::baud_rate(_props.baudRate));
    _serialSocket.set_option(boost::asio::serial_port_base::character_size(8));
    _serialSocket.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    _serialSocket.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    _serialSocket.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));

    _tcpSocket.async_connect(_tcpEndpoint, [this](boost::system::error_code err) {
        if (!err) {
            _timer.expires_from_now(boost::posix_time::seconds{0});
            _timer.async_wait([this](boost::system::error_code err) {
                if (!err) {
                    restartTimer();
                }
            });
            startReadSerial(_incSerialBuf, [this](boost::system::error_code err, std::size_t size) {
                onReadSerial(err, size);
            });

//            startRead(_tcpSocket, _incTcpBuf, [this](boost::system::error_code err, std::size_t size) {
//                _outSerial.sputn((char *) _incTcpBuf.data(), size);
//
//                std::string str((char *) _incSerialBuf.data(), size);
//                std::cout << str << std::endl;
//
//                boost::asio::async_write(_serialSocket, _outSerial, [](boost::system::error_code err, std::size_t size) {
//                    if (err) {
//                        std::cout << "error : serial write error: " << err.message().c_str() << std::endl;
//                    }
//                });
//            });
        } else {
            std::cout << "error : connect: " << err.message().c_str() << std::endl;
        }
    });

    _thread = std::make_shared<boost::thread>([this] { _service.run(); });
}

void Bridge::stop() {
    if (_thread) {
        _service.stop();
        _tcpSocket.close();
        _serialSocket.close();
        _thread->join();
        _thread.reset();
    }
}

template<class Reader>
void Bridge::startRead(Reader &reader, std::vector<uint8_t> &buffer, const std::function<void(boost::system::error_code, std::size_t size)> &callback) {
    boost::asio::async_read(
            reader,
            boost::asio::buffer(buffer),
            [buffer, callback](boost::system::error_code err, std::size_t read) {
                callback(err, read);
            }
    );
}

void Bridge::startReadSerial(std::vector<uint8_t>& buffer, const std::function<void(boost::system::error_code, std::size_t size)>& callback) {
    boost::asio::async_read(
            _serialSocket,
            boost::asio::buffer(buffer),
            [this, buffer, callback](boost::system::error_code err, std::size_t read) {
                callback(err, read);
                startReadSerial(_incSerialBuf, callback);
            }
    );
}

void Bridge::onReadSerial(boost::system::error_code err, std::size_t size) {
    if (!err) {
        _outTcp.sputn((char *) _incSerialBuf.data(), size);

        std::string str((char *) _incSerialBuf.data(), size);
        std::cout << str << std::endl;

//        boost::asio::async_write(_tcpSocket, _outTcp, [](boost::system::error_code err, std::size_t size) {
//            if (err) {
//                std::cout << "error : tcp write error: " << err.message().c_str() << std::endl;
//            }
//        });
    } else {
        std::cout << "error : serial read error: " << err.message().c_str() << std::endl;
    }
}
