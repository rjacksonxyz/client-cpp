#ifndef WS_MODELS_H
#define WS_MODELS_H

#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

namespace models
{
    using json = nlohmann::json;

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

    inline void to_json(json &j, const ControlMessage &cm)
    {
        j = json{
            {"ev", cm.ev},
            {"status", cm.status},
            {"message", cm.message},
            {"action", cm.action},
            {"params", cm.params},
        };
    }

    inline void from_json(json &j, ControlMessage &cm)
    {
        j = json{
            j.at("ev").get_to(cm.ev),
            j.at("status").get_to(cm.status),
            j.at("message").get_to(cm.message),
            j.at("action").get_to(cm.action),
            j.at("params").get_to(cm.params),
        };
    }

    // void to_json(json &j, const ControlMessage &cm);
    // void from_json(json &j, ControlMessage &cm);

}

#endif