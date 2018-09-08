//
// Created by shniu on 18-9-8.
//

#ifndef ECHOECHO_MESSAGE_H
#define ECHOECHO_MESSAGE_H

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>

namespace echoecho {

    // All messages start with this header
    struct message_header {
        // msg guid
        char    guid[36];
        // msg type
        char    type;
        // time to live, The number of times the message
        // will be forwarded by servers before it is
        // removed from the network
        char    ttl;
        // The number of times the message has been forwarded.
        char    hops;
        // payload data length
        boost::uint32_t length;
    };

    class message {
    public:
        message() : _payload(0) {}

        message(const message_header &header)
                : _payload(0) {
            _header = header;
        }

        virtual ~message() {
            if (_payload) {
                free(_payload);
            }
        }

        virtual const string str() const {
            std::ostringstream os;
            os  << "[Msg type:" << (int)type()
                << " ttl:" << (int)ttl()
                << " hops:" << (int)hops()
                << " length:" << (int)length()
                << " guid:" << guid() << "]";
            return os.str();
        }

        virtual message_header& header() { return _header; }
        virtual const char type() const { return _header.type; }
        virtual const short ttl() const { return _header.ttl; }
        virtual const short hops() const { return _header.hops; }
        virtual const std::string& guid() const {
            if( _msg_guid.empty() ) {
                _msg_guid = std::string(_header.guid, 36);
            }
            return _msg_guid;
        }

        virtual const boost::uint32_t total_length() const {
            return sizeof(message_header) + payload_length();
        }

        virtual const boost::uint32_t payload_length() const {
            return ntohl(_header.length);
        }

        /// payload
        virtual char * payload() { return _payload; }

        virtual size_t malloc_payload() {
            if (payload_length() == 0) {
                return 0;
            }

            free(_payload);
            _payload = (char *)malloc(payload_length());
            return payload_length();
        }

        // to_buffer
        virtual std::vector<boost::asio::const_buffer> to_buffer() const {
            std::vector<boost::asio::const_buffer> buffers;

            buffers.push_back(
                    boost::asio::buffer((char *)&_header, sizeof(message_header))
            );

            if (payload_length()) {
                buffers.push_back(
                        boost::asio::buffer(_payload, payload_length())
                );
            }

            return buffers;
        }

    private:
        // message header
        message_header _header;
        // msg guid
        mutable std::string _msg_guid;
        // payload data, message body
        char * _payload;
    };

    // smart pointer
    typedef boost::shared_ptr<message> message_ptr;
}

#endif //ECHOECHO_MESSAGE_H
