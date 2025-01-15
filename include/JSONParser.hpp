#ifndef __JSON_PARSER_HPP__
#define __JSON_PARSER_HPP__

#include <string_view>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

class JSONParser
{
public:
    JSONParser()
    {
        m_writer.Reset(m_stringBuffer);
    }
    JSONParser(std::string_view sv)
    {
        m_writer.Reset(m_stringBuffer);

        m_jsonDoc.Parse(sv.data());
    }
    friend
    std::ostream& operator<<(std::ostream& os, JSONParser& parser)
    {
        parser.m_jsonDoc.Accept(parser.m_writer);
        const auto* buff = parser.m_stringBuffer.GetString();
        if (! std::memcmp(buff, "null", sizeof("null")))
        {
            return os << "{}";
        }
        return os << buff;
    }
    template <typename T>
    auto& operator[](const T& key) const
    {
        return m_jsonDoc.FindMember(key)->value;
    }
private:
    rapidjson::Document m_jsonDoc{};
    rapidjson::StringBuffer m_stringBuffer{};
    rapidjson::Writer<rapidjson::StringBuffer> m_writer;
};

inline
std::ostream& operator<<(std::ostream& os, const rapidjson::Value& value)
{
    if (! value.IsNull())
    {
        return os << value.Get<const char*>();
    }
    return os << "\"\"";
}

#endif
