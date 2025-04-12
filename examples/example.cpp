#include <websocket/client.hpp>
#include <websocket/config.hpp>
#include <iostream>

int main()
{
    net::io_context ioc;
    ws::Config config;
    config.APIKey = "POLYGON_API_KEY";
    config.feed = ws::Feed::RealTime;
    config.market = ws::Market::Stocks;
    std::make_shared<Client>(config, ioc)->connect();
    ioc.run();

    std::cout << "0" << std::endl;
}