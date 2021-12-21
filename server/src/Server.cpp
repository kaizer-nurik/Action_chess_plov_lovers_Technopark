#include "Server.h"

#include <boost/bind.hpp>
#include <iostream>

#include "RoomHandlers.h"
#include "GameHandler.h"

Server::Server(const std::string address, const std::string port, std::size_t threadNum)
        : m_threadNum(threadNum),
          m_signals(m_ioContext),
          m_acceptor(m_ioContext),
          m_client(),
          m_mainMenu() {
    
    m_signals.add(SIGINT);
    m_signals.add(SIGTERM);
    m_signals.async_wait(boost::bind(&Server::onStop, this));

    m_router.addMethod("CreateRoom", Router::Steps{ new CreateRoomRequest(), new CreateRoomHandler(), new CreateRoomResponse() });
    m_router.addMethod("EnterRoom",  Router::Steps{ new EnterRoomRequest(),  new EnterRoomHandler(),  new EnterRoomResponse()  });
    //m_router.addMethod("LeaveRoom",  Router::Steps{ new LeaveRoomRequest(),  new LeaveRoomHandler(),  new LeaveRoomResponse()  });
    //m_router.addMethod("GetRooms",   Router::Steps{ new GetRoomsRequest(),  new GetRoomsHandler(),  new GetRoomsResponse()   });
    m_router.addMethod("StartGame",  Router::Steps{ new StartGameRequest(),  new StartGameHandler(),  new StartGameResponse()  });
    m_router.addMethod("GameAction", Router::Steps{ new GameRequest(),       new GameHandler(),       new GameResponse()       });

    boost::asio::ip::tcp::resolver resolver(m_ioContext);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
    m_acceptor.open(endpoint.protocol());
    m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor.bind(endpoint);
    m_acceptor.listen();

    startAccept();
    std::cout << "Started accept" << std::endl; 
}

void Server::run() {
    std::vector<boost::shared_ptr<std::thread>> threads;
    for (std::size_t i = 0; i < m_threadNum; ++i) {
        boost::shared_ptr<std::thread> thread(new std::thread(boost::bind(&boost::asio::io_context::run, &m_ioContext)));
        threads.push_back(thread);
    }

    for (std::size_t i = 0; i < threads.size(); ++i) {
        threads[i]->join();
    }
}

void Server::startAccept() {
    m_client.reset(new ClientHandler(m_ioContext, m_mainMenu, m_router));
    m_acceptor.async_accept(m_client->getSocket(), boost::bind(&Server::onAccept, this, boost::asio::placeholders::error));
}

void Server::onAccept(const boost::system::error_code& err) {
    if (!err) {
        boost::asio::ip::tcp::socket& socket = m_client->getSocket();
        std::cout << "Started handling: " << socket.remote_endpoint().address().to_string() + 
                                                  ":" + std::to_string(socket.remote_endpoint().port()) << std::endl;
        m_client->start();
    }

    startAccept();
}

void Server::onStop() {
    std::cout << "Stoped connection" << std::endl; 
    m_ioContext.stop();
}
