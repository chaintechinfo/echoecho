//
// Created by shniu on 18-9-6.
//

#include <utility>

#include "network/node.h"
#include "network/protocol.h"

namespace echoecho {

    node::node(boost::shared_ptr<tcp::acceptor> acceptor_ptr, protocol * p, boost::function<std::string()> uuidf)
            : _acceptor_ptr(std::move(acceptor_ptr)),
              m_protocol(p),
              _uuid_gen(std::move(uuidf)),
              seen_connections(0) {
        cout << "Testing uuid generator... " << flush;
        string uuid = _uuid_gen();
        if (uuid.length() != 36) {
            cout << "ERROR length must be 36." << endl;
            throw;
        }

        cout << "OK" << endl;

        p->set_node( this );

        // Start an accept operation for a new connection.
        connection_ptr new_conn = new_connection();
        _acceptor_ptr->async_accept(new_conn->socket(), boost::bind(
                &node::handle_accept, this, boost::asio::placeholders::error, new_conn));
    }

    node::~node() {
        cout << "Close the node" << endl;
    }

    connection_ptr node::new_connection() {
        return connection_ptr( new connection( _acceptor_ptr->get_io_service(), this ) );
    }

    void node::connect_to_remote(tcp::endpoint &ep) {
        map<string, string> props;
        connect_to_remote( ep, props );
    }

    void node::connect_to_remote(tcp::endpoint &ep, const map<string, string> &props) {
        cout << "router::connect_to_remote("
             << ep.address().to_string() <<":" << ep.port() << ")"
             << endl;

        connection_ptr new_conn = new_connection();
        auto iter = props.begin();
        auto end = props.end();
        for (; iter != end; ++iter) {
            new_conn->set(iter->first, iter->second);
        }

        // Start an asynchronous connect operation.
        // call handle_connect when connect succeed
        new_conn->socket().async_connect(ep, boost::bind(
                &node::handle_connect,   // callback, support by boost.asio and os
                this,
                boost::asio::placeholders::error,
                ep,
                new_conn
        ));
    }

    void node::handle_connect(const boost::system::error_code &e, tcp::endpoint &ep, connection_ptr conn) {
        if (e) {
            cerr << "Failed to connect out to remote server: "
                 << e.message() << std::endl;
            return;
        }

        cout << "Connect succeed." << endl;

        // Successfully established connection
        m_protocol->new_outgoing_connection( conn );
        register_connection(conn);

        // start read loop for this connection
        conn->async_read();
    }

    void node::handle_accept(const boost::system::error_code &error, connection_ptr conn) {

        if (error) {
            cerr << error.message() << endl;
            return;
        }

        // protocol hook
        if (m_protocol->new_incoming_connection(conn)) {
            std::cout << "Accept a message from remote"
                      << std::endl;

            // register conn
            register_connection( conn );
            conn->async_read();
        } else {
            std::cout << "Reject a connection from the client"
                      << std::endl;
        }

        // Start an accept operation for a new connection.
        connection_ptr new_conn = new_connection();
        _acceptor_ptr->async_accept(
                new_conn->socket(),
                boost::bind(
                        &node::handle_accept,
                        this,
                        boost::asio::placeholders::error,
                        new_conn
                )
        );
    }

    /// private
    void node::register_connection(connection_ptr conn) {
        boost::mutex::scoped_lock lk(m_connections_mutex);
        auto iter = m_connections.begin();
        for (; iter != m_connections.end(); ++iter) {
            if (*iter == conn) {
                // already registered
                cout << "ERROR connection already registered!" << endl;
                assert(false);
                return;
            }
        }
        m_connections.push_back(conn);
    }

    void node::send_all(message_ptr msg_ptr) {
        boost::mutex::scoped_lock lk(m_connections_mutex);
        auto iter = m_connections.begin();
        for (; iter != m_connections.end(); ++iter) {
            //*iter->async_write();
            iter->get()->async_write( msg_ptr );
        }
    }

    string node::gen_uuid() {
        return _uuid_gen();
    }

    void node::connection_terminated(connection_ptr conn) {
        unregister_connection( conn );
        m_protocol->connection_terminated( conn );
    }

    void node::unregister_connection(connection_ptr conn) {
        boost::mutex::scoped_lock lk(m_connections_mutex);
        auto itr = m_connections.begin();
        for (; itr != m_connections.end(); ++itr) {
            if (*itr == conn) {
                m_connections.erase( itr );
                // break;
            }
        }
    }

    /*void node::send_all(const std::string &message) {
        std::cout << "Send the message to all that connected, the message is: "
                  << message
                  << std::endl;
        //tcp::endpoint endpoint(address::from_string(""), 1111);

        auto iter = _peers.begin();
        auto end = _peers.end();
        for (; iter != end; ++iter) {
            vector<string> domain;
            boost::split(domain, *iter, boost::is_any_of(":"));
            std::cout << domain.size() << " "
                      << domain[0] << " "
                      << domain[1]
                      << std::endl;
            // tcp::endpoint ep(address::from_string(domain[0]), boost::lexical_cast<unsigned short>(domain[1]));
            tcp::endpoint ep(address::from_string("192.168.1.118"), 1112);
            //socket_ptr sock_ptr(new tcp::socket(_ios));
            //(*sock_ptr).connect(endpoint);
            tcp::socket sock(_ios);
            sock.connect(ep);
            // write
            size_t write_length = boost::asio::write(sock, boost::asio::buffer(message));
            std::cout << "Write succeed, data length is " << write_length << std::endl;
        }

    }*/

}

