#pragma once
#include "websocket/models/models.h"
#include "websocket/client.hpp"

namespace polygonio
{
    namespace models = ::models;

    class Client
    {
    public:
        Client(const std::string &api_key);
        void connect();

    private:
        std::string api_key_;
    };
}