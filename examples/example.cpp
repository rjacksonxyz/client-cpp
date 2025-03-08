#include <polygonio.hpp>
#include <iostream>

int main()
{
    polygonio::Client client("POLYGON_API_KEY");
    polygonio::models::ControlMessage cm{
        polygonio::models::EventType("auth"),
        "OK",
        "it's a me, Mario!",
        polygonio::models::ActionToString(polygonio::models::Action::Auth),
        "(x, y, z)"};
    nlohmann::json j = cm;
    std::cout << j << std::endl;
}