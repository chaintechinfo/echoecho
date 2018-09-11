//
// Created by shniu on 18-9-7.
//

#include "network/node.h"
#include "network/connection.h"

namespace echoecho {
    connection::connection(io_service &ios, node * n)
            : _socket(ios),
              m_shutting_down(false),
              m_node(n) {
        max_write_qsize = 20 * 1024;
        cout << "New connection ..." << endl;
    }

    connection::~connection() {
        cout << "The connection shutting down" << endl;
    }

    void connection::close() {
        socket().close();
    }

    void connection::fin() {
        if (m_shutting_down) {
            return;
        }

        m_shutting_down = true;
        cout << "FIN connection " << str() << endl;
        m_node->connection_terminated(shared_from_this());
        close();
    }

    string connection::str() const {
        ostringstream os;
        os   << "[Connection: '" << m_name << "' ";

        if (_socket.is_open()) {
            try {
                os << _socket.remote_endpoint().address().to_string()
                   << ":"
                   << _socket.remote_endpoint().port();
            } catch (...) {

            }
        }

        os << "]";
        return os.str();
    }

    tcp::socket& connection::socket() {
        return _socket;
    }

    void connection::async_read() {

        if (m_shutting_down)
            return;

        message_ptr msg_p(new message());

        // first to read header, then the payload body
        boost::asio::async_read(
                _socket,
                boost::asio::buffer(
                        (char *)&msg_p->header(),
                        sizeof(message_header)
                ),
                boost::bind(
                        &connection::handle_read_header,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        msg_p
                )
        );
    }

    void connection::handle_read_header(const boost::system::error_code &error, message_ptr msg_ptr) {

        if (m_shutting_down) {
            return;
        }

        if (error) {
            std::cerr << "err " << error.value() << " handle_read_header: "
                      << error.message() << std::endl;
            // 异常出错做些关闭操作
            fin();
            return;
        }

        cout << "Received message payload length: " << msg_ptr->payload_length() << endl;

        // payload size can limit
        assert(msg_ptr->payload_length() <= 16384);

        msg_ptr->malloc_payload();
        if (msg_ptr->payload_length() == 0) {
            handle_read_payload( error, msg_ptr);
            return;
        }

        // read payload data from stream
        boost::asio::async_read(
                _socket,
                boost::asio::buffer(msg_ptr->payload(), msg_ptr->payload_length()),
                boost::bind(
                        &connection::handle_read_payload,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        msg_ptr
                )
        );
    }

    void connection::handle_read_payload(const boost::system::error_code &error, message_ptr msg_ptr) {

        if (error) {
            std::cerr << "err " << error.value() << " handle_read_payload: "
                      << error.message() << std::endl;
            // todo 异常出错做些关闭操作
            // fin();
            return;
        }

        cout << "connection::received_msg: " << msg_ptr->str() << endl;
        // todo 处理收到的message

        // Continue loop async_read
        async_read();
    }

    void connection::async_write(message_ptr msg_ptr) {
        {
            boost::mutex::scoped_lock lk(queue_mutex);
            m_write_q.push_back(msg_ptr);
            m_wite_qsize += msg_ptr->total_length();
        }

        /// make sure our sending loop is running
        boost::system::error_code e;
        do_async_write( e, message_ptr() );
    }

    void connection::do_async_write(const boost::system::error_code &e, message_ptr finished_msg) {

        if (e) {
            /// todo
            cerr << "Error in do_async_write, terminating connection: "
                 << e.value() << ", " << e.message() << endl;
            return;
        }

        message_ptr msg_p;
        {
            boost::mutex::scoped_lock lk(queue_mutex);

            /// todo
            /*if (finished_msg.empty()) {
                return;
            }*/

            if (m_write_q.empty()) {
                /// todo
                return;
            }

            msg_p = m_write_q.front();
            m_write_q.pop_front();
            m_wite_qsize -= msg_p->total_length();
        }

        cout << "Async write: " << msg_p->str() << endl;

        boost::asio::async_write(
                socket(),
                boost::asio::buffer(msg_p->to_buffer()),
                boost::bind(
                        &connection::do_async_write,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        msg_p
                )
        );
    }
}
