//
// Created by shniu on 18-9-7.
//

#include "network/connection.h"

namespace echoecho {
    connection::connection(io_service &ios) : _socket(ios) {}

    tcp::socket& connection::socket() {
        return _socket;
    }

    void connection::async_read() {
        message_ptr msg_p(new message());

        // first to read header, then the payload body
        boost::asio::async_read(
                _socket,
                boost::asio::buffer(
                        &msg_p->header(),
                        sizeof(msg_p)
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

        if (error) {
            std::cerr << "err " << error.value() << " handle_read_header: "
                      << error.message() << std::endl;
            // todo 异常出错做些关闭操作
            // fin();
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
