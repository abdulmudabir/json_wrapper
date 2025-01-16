#include "JSONParser.hpp"

int main()
{
    JSONParser json_parser{R"({"hello" : "world", "stars" : 10, "12" : 23})"};
    std::cout << json_parser << '\n';
    std::cout << json_parser["world"] << '\n';
    std::cout << json_parser["12"] << '\n';
}
