//
// Created by shniu on 18-9-6.
//

#include <utility>

#include "network/node.h"

namespace echoecho {

    node::node(boost::shared_ptr<tcp::acceptor> acceptor_ptr, boost::function<std::string()> uuidf)
            : _acceptor_ptr(std::move(acceptor_ptr)),
              _uuid_gen(std::move(uuidf)),
              seen_connections(0) {
        cout << "Testing uuid generator... " << flush;
        string uuid = _uuid_gen();
        if (uuid.length() != 36) {
            cout << "ERROR length must be 36." << endl;
            throw;
        }

        cout << "OK" << endl;

        // Start an accept operation for a new connection.
        connection_ptr new_conn = new_connection();
        _acceptor_ptr->async_accept(new_conn->socket(), boost::bind(
                &node::handle_accept, this, boost::asio::placeholders::error, new_conn));
    }

    node::~node() {
        cout << "Close the node" << endl;
    }

    connection_ptr node::new_connection() {
        return connection_ptr( new connection(_acceptor_ptr->get_io_service()) );
    }

    void node::connect_to_remote(tcp::endpoint &ep) {
        map<string, string> props;
        connect_to_remote( ep, props );
    }

    void node::connect_to_remote(tcp::endpoint &ep, const map<string, string> &props) {
        cout << "router::connect_to_remote("
             << ep.address().to_string() <<":"
             << ep.port() << ")"
             << endl;
        connection_ptr new_conn = new_connection();
        auto iter = props.begin();
        auto end = props.end();
        for (; iter != end; ++iter) {
            new_conn->set(iter->first, iter->second);
        }

        // Start an asynchronous connect operation
        new_conn->socket().async_connect(ep, boost::bind(
                &node::handle_connect,
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

        // Successfully established connection
        // todo m_protocol->new_outgoing_connection( conn );
        register_connection(conn);

        // start read loop for this connection
        conn->async_read();
    }

    /*void node::accept() {
        socket_ptr socket(new tcp::socket(_ios));
        _acceptor.async_accept(
                *socket,
                boost::bind(
                        &node::handle_accept,
                        this,
                        boost::asio::placeholders::error
                )
        );
    }*/

    void node::handle_accept(const boost::system::error_code &error, connection_ptr conn) {
        std::cout << "Accept a message from remote"
                  << std::endl;
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

    /*void node::start_listening() {
        accept();
        cout << "Start the node server async accept" << endl;
        _ios.run();
        // _p2p.awake();
    }*/

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

