#ifndef WS_MODELS_H
#define WS_MODELS_H

#include <string>
#include <iostream>

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
}

#endif