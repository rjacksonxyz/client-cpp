#ifndef WS_CONFIG_H
#define WS_CONFIG_H

#include <string>
#include <functional>
#include <optional>
#include <cstdint>

namespace ws
{

    // Forward declaration of Logger interface
    class Logger;

    // Feed is the data feed (e.g. Delayed, RealTime) which represents the server host
    enum class Feed
    {
        Delayed,
        RealTime,
        Nasdaq,
        PolyFeed,
        PolyFeedPlus,
        StarterFeed,
        LaunchpadFeed,
        BusinessFeed,
        EdgxBusinessFeed,
        IEXBusiness,
        DelayedBusinessFeed,
        DelayedEdgxBusinessFeed,
        DelayedNasdaqLastSaleBusinessFeed,
        DelayedNasdaqBasicFeed,
        DelayedFullMarketBusinessFeed,
        FullMarketBusinessFeed,
        NasdaqLastSaleBusinessFeed,
        NasdaqBasicBusinessFeed
    };

    // Market is the type of market (e.g. Stocks, Crypto) used to connect to the server
    enum class Market
    {
        Stocks,
        Options,
        Forex,
        Crypto,
        Indices,
        Futures
    };

    // Topic is the data type used to subscribe and retrieve data from the server
    enum class Topic : uint8_t
    {
        // Stocks range
        stocksMin = 10,
        StocksSecAggs = 11,
        StocksMinAggs = 12,
        StocksTrades = 13,
        StocksQuotes = 14,
        StocksImbalances = 15,
        StocksLULD = 16,
        StocksLaunchpadMinAggs = 17,
        StocksLaunchpadValue = 18,
        stocksMax = 19,

        // Options range
        optionsMin = 30,
        OptionsSecAggs = 31,
        OptionsMinAggs = 32,
        OptionsTrades = 33,
        OptionsQuotes = 34,
        OptionsLaunchpadMinAggs = 35,
        OptionsLaunchpadValue = 36,
        optionsMax = 37,

        // Forex range
        forexMin = 50,
        ForexSecAggs = 51,
        ForexMinAggs = 52,
        ForexQuotes = 53,
        ForexLaunchpadMinAggs = 54,
        ForexLaunchpadValue = 55,
        forexMax = 56,

        // Crypto range
        cryptoMin = 70,
        CryptoSecAggs = 71,
        CryptoMinAggs = 72,
        CryptoTrades = 73,
        CryptoQuotes = 74,
        CryptoL2Book = 75,
        CryptoLaunchpadMinAggs = 76,
        CryptoLaunchpadValue = 77,
        cryptoMax = 78,

        // Index range
        IndexSecAggs = 90,
        IndexMinAggs = 91,
        IndexValue = 92,

        BusinessFairMarketValue = 100,

        // Futures range
        futuresMin = 110,
        FutureSecAggs = 111,
        FutureMinAggs = 112,
        FutureTrades = 113,
        FutureQuotes = 114,
        futuresMax = 115
    };

    // Config is a set of WebSocket client options
    struct Config
    {
        // APIKey is the API key used to authenticate against the server
        std::string APIKey;

        // Feed is the data feed (e.g. Delayed, RealTime) which represents the server host
        Feed feed;

        // Market is the type of market (e.g. Stocks, Crypto) used to connect to the server
        Market market;

        // MaxRetries is the maximum number of retry attempts that will occur
        std::optional<uint64_t> MaxRetries;

        // RawData is a flag indicating whether data should be returned as a raw JSON or raw bytes
        bool RawData = false;

        // BypassRawDataRouting is a flag that interacts with the RawData flag
        bool BypassRawDataRouting = false;

        // ReconnectCallback is triggered on automatic reconnects by the websocket client
        std::function<void(const std::exception *)> ReconnectCallback;

        // Log is an optional logger
        Logger *Log = nullptr;

        // Validates the configuration
        bool validate() const;
    };

    // Logger is a basic logger interface used for logging within the client
    class Logger
    {
    public:
        virtual ~Logger() = default;
        virtual void Debugf(const char *template_, ...) = 0;
        virtual void Infof(const char *template_, ...) = 0;
        virtual void Errorf(const char *template_, ...) = 0;
    };

    // Feed string conversion functions
    std::string FeedToString(Feed feed);
    Feed StringToFeed(const std::string &str);

    // Market string conversion functions
    std::string MarketToString(Market market);
    Market StringToMarket(const std::string &str);

    // Topic prefix function
    std::string TopicPrefix(Topic topic);

    // Market support check
    bool MarketSupportsTopic(Market market, Topic topic);

} // namespace ws

#endif // WS_CONFIG_H