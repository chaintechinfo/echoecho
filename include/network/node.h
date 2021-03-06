//
// Created by shniu on 18-9-6.
//

#ifndef ECHOECHO_PEER_H
#define ECHOECHO_PEER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include "network/message.h"
#include "network/connection.h"

namespace echoecho {

    class protocol;

    //class connection;
    typedef boost::shared_ptr<connection> connection_ptr;

    using namespace std;
    using boost::asio::io_service;
    using boost::asio::ip::tcp;
    using boost::asio::ip::address;

    typedef boost::shared_ptr<tcp::socket> socket_ptr;

    class node {
    public:
        // node(network &p2p);
        node(boost::shared_ptr<tcp::acceptor> acceptor_ptr, protocol * p, boost::function<std::string()> uuidf);
        ~node();

        void accept();

        // Handle accept
        void handle_accept(const boost::system::error_code& error, connection_ptr conn);

        // new connection
        connection_ptr new_connection();
        void connection_terminated( connection_ptr conn);

        // connect
        void connect_to_remote(tcp::endpoint &ep);
        void connect_to_remote(tcp::endpoint &ep, const map<string, string> &props);

        // Handle completion of a connect operation
        void handle_connect(const boost::system::error_code& e,
                            tcp::endpoint &ep,
                            connection_ptr conn);

        // send msg to all node that connected
        void send_all(message_ptr msg_ptr);

        // gen uuid
        string gen_uuid();
    private:
        /// keep track of connection
        void register_connection( connection_ptr conn );
        void unregister_connection( connection_ptr conn );

        // connection to others
        vector<connection_ptr> m_connections;
        boost::mutex m_connections_mutex;

        // protocol implementation
        protocol * m_protocol;

        // acceptor
        boost::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptor_ptr;

        // uuid gen
        boost::function<std::string()> _uuid_gen;

        unsigned int seen_connections;
    };
}



#endif //ECHOECHO_PEER_H
