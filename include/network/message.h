//
// Created by shniu on 18-9-3.
//

#ifndef ECHOECHO_MESSAGE_H
#define ECHOECHO_MESSAGE_H

#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/asio/buffer.hpp>


namespace echoecho {
    using namespace std;

    class Message;
    typedef boost::shared_ptr<Message> message_ptr;
    class Connection;
    class Router;
    typedef boost::shared_ptr<Connection> connection_ptr;
    typedef boost::weak_ptr<Connection> connection_ptr_weak;

    struct message_header {
        char guid[36];
        char type;
        char ttl;
        char hops;
        boost::uint32_t length;
    };

    class Message {
    public:
        Message() : m_payload(0) {}
        Message(const message_header &header) : m_payload(0) {
            m_header = header;
        }
        virtual ~Message(){
            if (m_payload) {
                free(m_payload);
            }
        }

        virtual const boost::uint32_t total_length() const {
            return sizeof(m_header) + length();
        }

        virtual const string str() const {
            ostringstream os;
            os << "[Msg type:" << (int)type()
               << " ttl:" << (int)ttl()
               << " hops:" << (int)hops()
               << " length:" << (int)length()
               << " guid:" << guid() << "]";
        }

        virtual message_header& header() { return m_header; }
        virtual const boost::uint32_t length() const { return ntohl(m_header.length); }
        virtual const char type() const { return m_header.type; }
        virtual const short ttl() const { return m_header.ttl; }
        virtual const short hops() const { return m_header.hops; }
        virtual const string& guid() const {
            if (m_guid.empty()) {
                m_guid = string(m_header.guid, 36);
            }
            return m_guid;
        }

        // payload
        virtual const char* payload() const { return m_payload; }
        virtual char* payload() { return m_payload; }
        virtual string payload_str() const {
            string s(m_payload, length());
            return s;
        }

        virtual size_t malloc_payload() {
            if (length() == 0) return 0;
            free(m_payload);
            m_payload = (char *)malloc( length() );
            return length();
        }

        virtual const boost::asio::mutable_buffer payload_buffer() const {
            return boost::asio::buffer(m_payload, length());
        }

        virtual vector<boost::asio::const_buffer> to_buffers() const {
            vector<boost::asio::const_buffer> buffers;
            buffers.push_back(boost::asio::const_buffer(
                    (char *)m_header, sizeof(m_header)
            ));

            if (length()) {
                buffers.push_back(
                        boost::asio::const_buffer(m_payload, length())
                );
            }

            return buffers;
        }

    protected:
        message_header m_header;
        string m_guid;
        char* m_payload;
    };

    class GeneralMessage : public Message {
    public:
        GeneralMessage(const char msgtype, const string& body, string& uuid) {
            message_header h;
            memcpy(&h.guid, uuid.data(), 36);
            h.type = msgtype;
            h.ttl = 1;
            h.hops = 0;
            h.length = ntohl( body.length() );
            m_header = h;
            malloc_payload();
            memcpy(m_payload, body.data(), length());
        }
    };

} // echoecho

#endif //ECHOECHO_MESSAGE_H
