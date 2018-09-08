//
// Created by shniu on 18-9-7.
//

#ifndef ECHOECHO_CONNECTION_H
#define ECHOECHO_CONNECTION_H

#include <iostream>
#include <string>
#include <deque>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "network/message.h"

namespace echoecho {
    using namespace std;

    using boost::asio::io_service;
    using boost::asio::ip::tcp;

    class connection : public boost::enable_shared_from_this<connection> {
    public:
        connection(io_service &ios);

        tcp::socket& socket();

        // Setup a call to read the next msg_header
        void async_read();
        void handle_read_header(const boost::system::error_code &error, message_ptr msg_ptr);
        void handle_read_payload(const boost::system::error_code &error, message_ptr msg_ptr);

        // Asynchronously write a data structure to the socket.
        // This just enqueues the data and returns immediately
        void async_write(message_ptr msg_ptr);
        void do_async_write(const boost::system::error_code& e, message_ptr finished_msg);

        void set(const string &k, const string &v) {
            boost::mutex::scoped_lock lk(m_props_mutex);
            m_props[k] = v;
        }

        string get(const string& k) {
            boost::mutex::scoped_lock lk(m_props_mutex);
            if( m_props.find(k) == m_props.end() )
                return "";

            return m_props[k];
        }

    private:
        tcp::socket _socket;

        boost::mutex m_props_mutex;
        map<string, string> m_props;

        // protects outgoing message queue
        boost::mutex queue_mutex;
        // queue of outgoing messages
        deque< message_ptr > m_write_q;
        size_t m_wite_qsize;

    };  // class connection

} // echoecho

#endif //ECHOECHO_CONNECTION_H
