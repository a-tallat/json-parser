#pragma once

#include <vector>
#include <variant>
#include <map>
#include <string>
#include <stdexcept>

namespace Json
{

    struct Value
    {
        using Array = std::vector<Value>;
        using Object = std::map<std::string, Value>;
        using Primitive = std::variant<int, double, bool, std::string, std::monostate>;

        std::variant<Primitive, Array, Object> value;
    };

    class Parser
    {
        std::string m_content{};
        size_t m_current{};

        void removewhitespaces();
        char select_char(int curr);
        char advance();
        char current();
        bool is_end();
        void consume(char c, std::string_view msg);

        std::string handle_string();
        Value::Array handle_array();
        Value::Object handle_object();
        Value::Primitive handle_primitive();

    public:
        Parser(std::string_view content);

        std::string get_content()
        {
            return m_content;
        }

        Value parse();
    };

}