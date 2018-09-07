//
// Created by shniu on 18-9-7.
//

#ifndef ECHOECHO_CONNECTION_H
#define ECHOECHO_CONNECTION_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>

namespace echoecho {
    using namespace std;

    using boost::asio::io_service;
    using boost::asio::ip::tcp;

    class connection {
    public:
        connection(io_service &ios);

        tcp::socket& socket();

        // Setup a call to read the next msg_header
        void async_read();

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

    };  // class connection

} // echoecho

#endif //ECHOECHO_CONNECTION_H
