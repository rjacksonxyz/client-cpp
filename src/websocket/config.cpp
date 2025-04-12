#include "config.hpp"
#include <stdexcept>

namespace ws
{

    bool Config::validate() const
    {
        if (APIKey.empty())
        {
            throw std::runtime_error("API key is required");
        }
        return true;
    }

    std::string FeedToString(Feed feed)
    {
        switch (feed)
        {
        case Feed::Delayed:
            return "wss://delayed.polygon.io";
        case Feed::RealTime:
            return "wss://socket.polygon.io";
        case Feed::Nasdaq:
            return "wss://nasdaqfeed.polygon.io";
        case Feed::PolyFeed:
            return "wss://polyfeed.polygon.io";
        case Feed::PolyFeedPlus:
            return "wss://polyfeedplus.polygon.io";
        case Feed::StarterFeed:
            return "wss://starterfeed.polygon.io";
        case Feed::LaunchpadFeed:
            return "wss://launchpad.polygon.io";
        case Feed::BusinessFeed:
            return "wss://business.polygon.io";
        case Feed::EdgxBusinessFeed:
            return "wss://edgx-business.polygon.io";
        case Feed::IEXBusiness:
            return "wss://iex-business.polygon.io";
        case Feed::DelayedBusinessFeed:
            return "wss://delayed-business.polygon.io";
        case Feed::DelayedEdgxBusinessFeed:
            return "wss://delayed-edgx-business.polygon.io";
        case Feed::DelayedNasdaqLastSaleBusinessFeed:
            return "wss://delayed-nasdaq-last-sale-business.polygon.io";
        case Feed::DelayedNasdaqBasicFeed:
            return "wss://delayed-nasdaq-basic-business.polygon.io";
        case Feed::DelayedFullMarketBusinessFeed:
            return "wss://delayed-fullmarket-business.polygon.io";
        case Feed::FullMarketBusinessFeed:
            return "wss://fullmarket-business.polygon.io";
        case Feed::NasdaqLastSaleBusinessFeed:
            return "wss://nasdaq-last-sale-business.polygon.io";
        case Feed::NasdaqBasicBusinessFeed:
            return "wss://nasdaq-basic-business.polygon.io";
        default:
            return "";
        }
    }

    std::string MarketToString(Market market)
    {
        switch (market)
        {
        case Market::Stocks:
            return "stocks";
        case Market::Options:
            return "options";
        case Market::Forex:
            return "forex";
        case Market::Crypto:
            return "crypto";
        case Market::Indices:
            return "indices";
        case Market::Futures:
            return "futures";
        default:
            return "";
        }
    }

    std::string TopicPrefix(Topic topic)
    {
        switch (topic)
        {
        case Topic::StocksSecAggs:
            return "A";
        case Topic::StocksMinAggs:
            return "AM";
        case Topic::StocksTrades:
            return "T";
        case Topic::StocksQuotes:
            return "Q";
        case Topic::StocksImbalances:
            return "NOI";
        case Topic::StocksLULD:
            return "LULD";
        case Topic::StocksLaunchpadMinAggs:
            return "AM";
        case Topic::StocksLaunchpadValue:
            return "LV";
        case Topic::OptionsSecAggs:
            return "A";
        case Topic::OptionsMinAggs:
            return "AM";
        case Topic::OptionsTrades:
            return "T";
        case Topic::OptionsQuotes:
            return "Q";
        case Topic::OptionsLaunchpadMinAggs:
            return "AM";
        case Topic::OptionsLaunchpadValue:
            return "LV";
        case Topic::ForexSecAggs:
            return "CAS";
        case Topic::ForexMinAggs:
            return "CA";
        case Topic::ForexQuotes:
            return "C";
        case Topic::ForexLaunchpadMinAggs:
            return "AM";
        case Topic::ForexLaunchpadValue:
            return "LV";
        case Topic::CryptoSecAggs:
            return "XAS";
        case Topic::CryptoMinAggs:
            return "XA";
        case Topic::CryptoTrades:
            return "XT";
        case Topic::CryptoQuotes:
            return "XQ";
        case Topic::CryptoL2Book:
            return "XL2";
        case Topic::CryptoLaunchpadMinAggs:
            return "AM";
        case Topic::CryptoLaunchpadValue:
            return "LV";
        case Topic::IndexSecAggs:
            return "A";
        case Topic::IndexMinAggs:
            return "AM";
        case Topic::IndexValue:
            return "V";
        case Topic::BusinessFairMarketValue:
            return "FMV";
        case Topic::FutureSecAggs:
            return "A";
        case Topic::FutureMinAggs:
            return "AM";
        case Topic::FutureTrades:
            return "T";
        case Topic::FutureQuotes:
            return "Q";
        default:
            return "";
        }
    }

    bool MarketSupportsTopic(Market market, Topic topic)
    {
        // FMV is supported for Stocks, Options, Forex, and Crypto but is not within the range
        bool isBusinessFairMarketValue = (topic == Topic::BusinessFairMarketValue);

        switch (market)
        {
        case Market::Stocks:
            return isBusinessFairMarketValue ||
                   (static_cast<int>(topic) > static_cast<int>(Topic::stocksMin) &&
                    static_cast<int>(topic) < static_cast<int>(Topic::stocksMax));
        case Market::Options:
            return isBusinessFairMarketValue ||
                   (static_cast<int>(topic) > static_cast<int>(Topic::optionsMin) &&
                    static_cast<int>(topic) < static_cast<int>(Topic::optionsMax));
        case Market::Forex:
            return isBusinessFairMarketValue ||
                   (static_cast<int>(topic) > static_cast<int>(Topic::forexMin) &&
                    static_cast<int>(topic) < static_cast<int>(Topic::forexMax));
        case Market::Crypto:
            return isBusinessFairMarketValue ||
                   (static_cast<int>(topic) > static_cast<int>(Topic::cryptoMin) &&
                    static_cast<int>(topic) < static_cast<int>(Topic::cryptoMax));
        default:
            return true; // assume user knows what they're doing if they use some unknown market
        }
    }

} // namespace ws
