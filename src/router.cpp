//
// Created by shniu on 18-9-5.
//

#include <utility>

#include "network/router.h"

namespace echoecho {
    Router::Router(boost::shared_ptr<tcp::acceptor> accp, Protocol *p, boost::function<string()> uuidf)
            : _acceptor( accp ) {

    }

    connection_ptr Router::new_connection() {
        // TODO
        // return connection_ptr( new Connection(_acceptor->get_io_service(), this) );
        return nullptr;
    }

    void Router::connect_to_remote(tcp::endpoint &endpoint) {
        cout << "router::connect_to_remote("
             << endpoint.address().to_string() << ":"
             << endpoint.port() << ")"
             << endl;
        connection_ptr new_conn = new_connection();

        new_conn->socket();
    }
}
/*
// uuid gen function
std::string lame_uuid_gen() {
    boost::uuids::random_generator gen;
    boost::uuids::uuid uuid = gen();
    // #include <boost/lexical_cast.h>
    // boost::lexical_cast<std::string>(uuid);
    return boost::uuids::to_string(uuid);
}

void iorun( boost::asio::io_service * ios ) {
    ios->run();
    std::cout << "io ended" << std::endl;
}

// temp
void temp(int argc, char** argv) {
    // arg count
    auto port = static_cast<short>(atoi(argv[1]));
    std::cout << "Listening on port " << port << std::endl;

    boost::asio::io_service ios;

    boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor(
            new boost::asio::ip::tcp::acceptor(
                    ios,
                    boost::asio::ip::tcp::endpoint(
                            boost::asio::ip::tcp::v4(),
                            static_cast<unsigned short>(port)
                    )
            )
    );

    echoecho::Router router(acceptor, nullptr, boost::bind(&lame_uuid_gen));

    boost::thread t(boost::bind(&iorun, &ios));
}*/
