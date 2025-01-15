#include "JSONParser.hpp"

int main()
{
    JSONParser json_parser{R"({"hello" : "world", "stars" : 10})"};
    std::cout << json_parser << '\n';
    std::cout << json_parser["world"] << '\n';
}
