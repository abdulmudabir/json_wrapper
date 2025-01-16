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
    auto InvalidJSONObject() const
    {
        return ! m_jsonDoc.IsObject();
    }
    friend
    std::ostream& operator<<(std::ostream& os, JSONParser& parser)
    {
        if (parser.InvalidJSONObject())
        {
            std::cerr << "JSON object not instantiated correctly.\n";
            return os << "{}";
        }
        parser.m_jsonDoc.Accept(parser.m_writer);
        return os << parser.m_stringBuffer.GetString();
    }
    template <typename T>
    auto& operator[](const T& key) const
    {
        static const rapidjson::Value value{};
        if (! m_jsonDoc.IsObject())
        {
            return value;
        }
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
        if (value.IsString())
        {
            return os << value.Get<const char*>();
        }
        else if (value.IsNumber())
        {
            return os << value.Get<uint64_t>();
        }
    }
    return os << R"("")";
}

#endif
