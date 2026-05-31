#include "Json.h"

#define NOT_IMPLEMENTED(c) \
    throw std::runtime_error(std::string("parsing for '") + (c) + "' not implemented")

Json::Parser::Parser(std::string_view content)
    : m_content(content) {}

Json::Value Json::Parser::parse()
{
    removewhitespaces();
    char c = current();

    switch (c)
    {
    case '{':
        NOT_IMPLEMENTED(c);
        break;

    case '[':
        NOT_IMPLEMENTED(c);
        break;

    case '"':
        handle_string();
        break;

    default:
        NOT_IMPLEMENTED(c);
        break;
    }
}

Json::Value::Array Json::Parser::handle_array()
{
    advance();
    Value::Array arr{};
    while (current() != ']')
    {
        if (is_end())
        {
            throw std::runtime_error("Expected ] to be present");
        }

        advance();
    }
    advance();

    return arr;
}

std::string Json::Parser::handle_string()
{

    advance();
    size_t start{m_current};
    while (current() != '"')
    {
        if (current() == '\n' || is_end())
        {
            throw std::runtime_error("Expected \" to be present");
        }

        advance();
    }

    size_t end{m_current};
    advance();
    return m_content.substr(start, end - start);
}

void Json::Parser::consume(char c, std::string_view msg)
{
    if (current() != c)
        throw std::runtime_error(msg.data());
    advance();
}

bool Json::Parser::is_end()
{
    return m_current >= m_content.size();
}

char Json::Parser::advance()
{
    return select_char(1);
}

char Json::Parser::current()
{
    return select_char(0);
}

char Json::Parser::select_char(int curr)
{
    if (is_end())
    {
        return '\0';
    }

    char res = m_content[m_current];
    m_content += curr;

    return res;
}

void Json::Parser::removewhitespaces()
{
    while (std::isspace(current()))
    {
        advance();
    }
}