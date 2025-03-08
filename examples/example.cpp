#include <polygonio.h>
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
    std::cout << "0" << std::endl;
}