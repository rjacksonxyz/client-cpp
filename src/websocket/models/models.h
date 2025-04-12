#ifndef WS_MODELS_H
#define WS_MODELS_H

#include <string>
#include <iostream>
#include <vector>

namespace models
{
    // set of recognized actions used in control messages
    enum class Action
    {
        Auth,
        Subscribe,
        Unsubscribe
    };

    inline std::string ActionToString(Action action)
    {
        switch (action)
        {
        case Action::Auth:
            return "auth";
        case Action::Subscribe:
            return "subscribe";
        case Action::Unsubscribe:
            return "unsubscribe";
        default:
            return "";
        }
    }

    inline Action StringToAction(const std::string &str)
    {
        if (str == "auth")
            return Action::Auth;
        if (str == "subscribe")
            return Action::Subscribe;
        if (str == "unsubscribe")
            return Action::Unsubscribe;
        throw std::invalid_argument("Invalid action string");
    }

    typedef std::string EventType;

    struct ControlMessage
    {
        EventType ev;
        std::string status;
        std::string message;
        std::string action;
        std::string params;
    };

    // EquityAgg is an aggregate for either stock tickers or option contracts.
    struct EquityAgg
    {
        // The event type
        EventType ev;

        // json:"sym" - The ticker symbol for the given stock
        std::string Symbol;

        // json:"v" - The tick volume
        double Volume;

        // json:"av" - Today's accumulated volume
        double AccumulatedVolume;

        // json:"op" - Today's official opening price
        double OfficialOpenPrice;

        // json:"vw" - The tick's volume weighted average price
        double VWAP;

        // json:"o" - The opening tick price for this aggregate window
        double Open;

        // json:"c" - The closing tick price for this aggregate window
        double Close;

        // json:"h" - The highest tick price for this aggregate window
        double High;

        // json:"l" - The lowest tick price for this aggregate window
        double Low;

        // json:"a" - Today's volume weighted average price
        double AggregateVWAP;

        // json:"z" - The average trade size for this aggregate window
        double AverageSize;

        // json:"s" - Start timestamp in Unix Milliseconds
        int64_t StartTimestamp;

        // json:"e" - End timestamp in Unix Milliseconds
        int64_t EndTimestamp;

        // json:"otc" - Whether this aggregate is for an OTC ticker
        bool OTC;
    };

    // CurrencyAgg is an aggregate for either forex currency pairs or crypto pairs
    struct CurrencyAgg
    {
        // The event type
        EventType ev;

        // json:"pair" - The currency pair
        std::string Pair;

        // json:"o" - The open price for this aggregate window
        double Open;

        // json:"c" - The close price for this aggregate window
        double Close;

        // json:"h" - The high price for this aggregate window
        double High;

        // json:"l" - The low price for this aggregate window
        double Low;

        // json:"v" - The volume of trades during this aggregate window
        double Volume;

        // json:"vw" - The volume weighted average price
        double VWAP;

        // json:"s" - Start time in Unix Milliseconds
        int64_t StartTimestamp;

        // json:"e" - End time in Unix Milliseconds
        int64_t EndTimestamp;

        // json:"z" - The average trade size for this aggregate window
        int32_t AVGTradeSize;
    };

    // EquityTrade is trade data for either stock tickers or option contracts
    struct EquityTrade
    {
        // The event type
        EventType ev;

        // json:"sym" - The ticker symbol
        std::string Symbol;

        // json:"x" - The exchange ID
        int32_t Exchange;

        // json:"i" - The trade ID
        std::string ID;

        // json:"z" - The tape (1 = NYSE, 2 = AMEX, 3 = Nasdaq)
        int32_t Tape;

        // json:"p" - The price
        double Price;

        // json:"s" - The trade size
        int64_t Size;

        // json:"c" - The trade conditions
        std::vector<int32_t> Conditions;

        // json:"t" - Timestamp in Unix MS
        int64_t Timestamp;

        // json:"q" - The sequence number
        int64_t SequenceNumber;

        // json:"trfi" - Trade Reporting Facility ID
        int64_t TradeReportingFacilityID;

        // json:"trft" - TRF Timestamp
        int64_t TradeReportingFacilityTimestamp;
    };

    // CryptoTrade is a trade for a crypto pair
    struct CryptoTrade
    {
        // The event type
        EventType ev;

        // json:"pair" - The crypto pair
        std::string Pair;

        // json:"x" - The crypto exchange ID
        int32_t Exchange;

        // json:"i" - The ID of the trade
        std::string ID;

        // json:"p" - The price
        double Price;

        // json:"s" - The size
        double Size;

        // json:"c" - The conditions
        std::vector<int32_t> Conditions;

        // json:"t" - Timestamp in Unix MS
        int64_t Timestamp;

        // json:"r" - Polygon received timestamp
        int64_t ReceivedTimestamp;
    };

    // EquityQuote is a quote for either stock tickers or option contracts
    struct EquityQuote
    {
        // The event type
        EventType ev;

        // json:"sym" - The ticker symbol
        std::string Symbol;

        // json:"bx" - The bid exchange ID
        int32_t BidExchangeID;

        // json:"bp" - The bid price
        double BidPrice;

        // json:"bs" - The bid size
        int32_t BidSize;

        // json:"ax" - The ask exchange ID
        int32_t AskExchangeID;

        // json:"ap" - The ask price
        double AskPrice;

        // json:"as" - The ask size
        int32_t AskSize;

        // json:"c" - The condition
        int32_t Condition;

        // json:"i" - The indicators
        std::vector<int32_t> Indicators;

        // json:"t" - Timestamp in Unix MS
        int64_t Timestamp;

        // json:"z" - The tape
        int32_t Tape;

        // json:"q" - The sequence number
        int64_t SequenceNumber;
    };

    // ForexQuote is a quote for a forex currency pair
    struct ForexQuote
    {
        // The event type
        EventType ev;

        // json:"p" - The current pair
        std::string Pair;

        // json:"x" - The exchange ID
        int32_t ExchangeID;

        // json:"a" - The ask price
        double AskPrice;

        // json:"b" - The bid price
        double BidPrice;

        // json:"t" - Timestamp in Unix MS
        int64_t Timestamp;
    };

    // CryptoQuote is a quote for a crypto pair
    struct CryptoQuote
    {
        // The event type
        EventType ev;

        // json:"pair" - The crypto pair
        std::string Pair;

        // json:"bp" - The bid price
        double BidPrice;

        // json:"bs" - The bid size
        double BidSize;

        // json:"ap" - The ask price
        double AskPrice;

        // json:"as" - The ask size
        double AskSize;

        // json:"t" - Timestamp in Unix MS
        int64_t Timestamp;

        // json:"x" - The crypto exchange ID
        int32_t ExchangeID;

        // json:"r" - Polygon received timestamp
        int64_t ReceivedTimestamp;
    };

    // Imbalance is an imbalance event for a given stock ticker symbol
    struct Imbalance
    {
        // The event type
        EventType ev;

        // json:"T" - The ticker symbol
        std::string Symbol;

        // json:"t" - Timestamp in Unix MS
        int64_t Timestamp;

        // json:"at" - The auction time
        int32_t AuctionTime;

        // json:"a" - The auction type
        std::string AuctionType;

        // json:"i" - The symbol sequence
        int32_t SymbolSequence;

        // json:"x" - The exchange ID
        int32_t ExchangeID;

        // json:"o" - The imbalance quantity
        int32_t ImbalanceQuantity;

        // json:"p" - The paired quantity
        int32_t PairedQuantity;

        // json:"b" - The book clearing price
        double BookClearingPrice;
    };

    // LimitUpLimitDown is a LULD event for a given stock ticker symbol
    struct LimitUpLimitDown
    {
        // The event type
        EventType ev;

        // json:"T" - The ticker symbol
        std::string Symbol;

        // json:"h" - The high price
        double HighPrice;

        // json:"l" - The low price
        double LowPrice;

        // json:"i" - The Indicators
        std::vector<int32_t> Indicators;

        // json:"z" - The tape
        int32_t Tape;

        // json:"t" - Timestamp in Unix MS
        int64_t Timestamp;

        // json:"q" - The sequence number
        int64_t SequenceNumber;
    };

    // Level2Book is level 2 book data for a given crypto pair
    struct Level2Book
    {
        // The event type
        EventType ev;

        // json:"pair" - The crypto pair
        std::string Pair;

        // json:"b" - Bid prices array
        std::vector<std::vector<double>> BidPrices;

        // json:"a" - Ask prices array
        std::vector<std::vector<double>> AskPrices;

        // json:"t" - Timestamp in Unix MS
        int64_t Timestamp;

        // json:"x" - The crypto exchange ID
        int32_t ExchangeID;

        // json:"r" - Polygon received timestamp
        int64_t ReceivedTimestamp;
    };

    // IndexValue is value data for indices
    struct IndexValue
    {
        // The event type
        EventType ev;

        // json:"val" - The value
        double Value;

        // json:"T" - The ticker symbol
        std::string Ticker;

        // json:"t" - Timestamp in Unix MS
        int64_t Timestamp;
    };

    // LaunchpadValue represents a launchpad value event
    struct LaunchpadValue
    {
        // The event type
        EventType ev;

        // json:"val" - The value
        double Value;

        // json:"sym" - The ticker symbol
        std::string Ticker;

        // json:"t" - Timestamp in nanoseconds
        int64_t Timestamp;
    };

    // FairMarketValue represents a fair market value event
    struct FairMarketValue
    {
        // The event type
        EventType ev;

        // json:"fmv" - The value
        double FMV;

        // json:"sym" - The ticker symbol
        std::string Ticker;

        // json:"t" - Timestamp in nanoseconds
        int64_t Timestamp;
    };
}

#endif