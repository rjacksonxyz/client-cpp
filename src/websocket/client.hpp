#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <boost/beast/core.hpp>
#include <boost/system/config.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <mutex>

#include "config.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Client : public std::enable_shared_from_this<Client>
{
public:
    Client(const ws::Config &config, net::io_context &ioc);
    void connect();

private:
    std::string apiKey;
    ws::Feed feed;
    ws::Market market;
    std::string url;
    std::string host;
    std::string port;

    tcp::resolver resolver;
    beast::tcp_stream stream;
    websocket::stream<beast::tcp_stream> conn;
    beast::flat_buffer buffer;

    bool shouldBackoff;
    std::mutex m;
    void fail(beast::error_code ec, char const *what)
    {
        std::cerr << what << ": " << ec.message() << "\n";
    }
    void on_resolve(
        beast::error_code ec,
        tcp::resolver::results_type results)
    {
        if (ec)
        {
            std::cerr << "Resolve error: " << ec.message() << std::endl;
            return;
        }

        // Connect to the TCP endpoint
        beast::get_lowest_layer(conn).async_connect(
            results,
            beast::bind_front_handler(&Client::on_connect, shared_from_this()));
    }

    void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
    {
        if (ec)
        {
            std::cerr << "Connect error: " << ec.message() << std::endl;
            return;
        }

        // Set up the websocket handshake
        conn.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));
        // conn.set_option(websocket::stream_base::decorator(
        //     [this](websocket::request_type &req)
        //     {
        //         req.set(http::field::user_agent, "Boost Beast WebSocket Client");
        //         // Add any headers you need, like authentication
        //         if (!apiKey.empty())
        //         {
        //             req.set("Authorization", "Bearer " + apiKey);
        //         }
        //     }));

        // Perform WebSocket handshake
        conn.async_handshake("localhost", "/ws",
                             beast::bind_front_handler(&Client::on_handshake, shared_from_this()));
    }

    void on_handshake(beast::error_code ec)
    {
        if (ec)
        {
            std::cerr << "Handshake error: " << ec.message() << std::endl;
            return;
        }

        std::cout << "WebSocket connection established!" << std::endl;

        // Start reading messages (if you want to receive messages)
        start_reading();
    }

    void start_reading()
    {
        conn.async_read(
            buffer,
            beast::bind_front_handler(&Client::on_read, shared_from_this()));
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred)
    {
        if (ec)
        {
            std::cerr << "Read error: " << ec.message() << std::endl;
            return;
        }

        // Handle the received message
        std::cout << "Received: " << beast::make_printable(buffer.data()) << std::endl;

        // Clear the buffer
        buffer.consume(buffer.size());

        // Queue up another read
        start_reading();
    }
};

Client::Client(const ws::Config &config, net::io_context &ioc)
    : apiKey(config.APIKey),
      feed(config.feed),
      market(config.market),
      resolver(net::make_strand(ioc)),
      stream(net::make_strand(ioc)),
      conn(std::move(stream))
{
    url = "wss://localhost:4444";
    host = "localhost";
    port = "4444";
}

void Client::connect()
{
    std::cout << "Connecting to " << url << std::endl;
    resolver.async_resolve(
        host,
        port,
        beast::bind_front_handler(&Client::on_resolve, shared_from_this()));
}

#endif
