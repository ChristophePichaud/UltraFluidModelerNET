#include "pch.h"
#include "UFMCore\PlantUMLTokenizer.h"
#include <regex>
#include <cctype>

namespace PlantUML
{

    std::vector<Token> PlantUMLTokenizer::tokenize(const std::string& input) {
        std::vector<Token> tokens;

        std::regex pattern(R"(\b(class|interface|abstract|enum)\b|[-<|*]+[-]+>|[{}():]|[@+\-#~]|[A-Za-z_]\w*)");
        auto words_begin = std::sregex_iterator(input.begin(), input.end(), pattern);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            std::string match = (*i).str();
            tokens.push_back(classify(match));
        }

        return tokens;
    }

    Token PlantUMLTokenizer::classify(const std::string& value) {
        if (value == "class" || value == "interface" || value == "abstract" || value == "enum")
            return { TokenType::Keyword, value };
        else if (value == "+" || value == "-" || value == "#" || value == "~")
            return { TokenType::Visibility, value };
        else if (value == "-->" || value == "<|--" || value == "*--" || value == "<..")
            return { TokenType::Relation, value };
        else if (value == "{" || value == "}" || value == "(" || value == ")" || value == ":")
            return { TokenType::Symbol, value };
        else if (std::regex_match(value, std::regex("[A-Za-z_][A-Za-z0-9_]*")))
            return { TokenType::Identifier, value };
        else
            return { TokenType::Unknown, value };
    }

}

namespace SmallPlantUML
{

    Tokenizer::Tokenizer(const std::string& text) : input(text), pos(0) {}

    char Tokenizer::peek() const {
        return pos < input.size() ? input[pos] : '\0';
    }

    char Tokenizer::advance() {
        return pos < input.size() ? input[pos++] : '\0';
    }

    void Tokenizer::skipWhitespace() {
        while (std::isspace(peek())) advance();
    }

    Token Tokenizer::parseIdentifier() {
        std::string value;
        while (std::isalnum(peek()) || peek() == '_' || peek() == '`') {
            value += advance();
        }
        if (value == "entity" || value == "@startuml" || value == "@enduml")
            return { TokenType::Keyword, value };
        return { TokenType::Identifier, value };
    }

    Token Tokenizer::parseSymbol() {
        std::string value(1, advance());
        return { TokenType::Symbol, value };
    }

    Token Tokenizer::parseRelationArrow() {
        pos += 2; // skip "--"
        if (peek() == '>') {
            pos++;
            return { TokenType::RelationArrow, "-->" };
        }
        return { TokenType::Symbol, "--" };
    }

    //std::vector<Token> Tokenizer::tokenize() {
    //    std::vector<Token> tokens;
    //    while (pos < input.size()) 
    //    {
    //        skipWhitespace();
    //        if (input.substr(pos, 3) == "-->") {
    //            tokens.push_back(parseRelationArrow());
    //        }
    //        else if (std::isalpha(peek()) || peek() == '@') {
    //            tokens.push_back(parseIdentifier());
    //        }
    //        else if (peek() != '\0') {
    //            tokens.push_back(parseSymbol());
    //        }
    //    }
    //    tokens.push_back({ TokenType::EndOfFile, "" });
    //    return tokens;
    //}

    std::vector<Token> Tokenizer::tokenize() 
    {
        std::vector<Token> tokens;
        while (pos < input.size()) {
            skipWhitespace();

            // Handle @startuml and @enduml specifically
            if (input.substr(pos, 9) == "@startuml") {
                tokens.push_back({ TokenType::Keyword, "@startuml" });
                pos += 9;
                continue;
            }
            else if (input.substr(pos, 8) == "@enduml") {
                tokens.push_back({ TokenType::Keyword, "@enduml" });
                pos += 8;
                continue;
            }

            // Handle relation arrows
            if (input.substr(pos, 3) == "-->") {
                tokens.push_back(parseRelationArrow());
            }
            // Handle identifiers and keywords
            else if (std::isalpha(peek()) || peek() == '@') {
                tokens.push_back(parseIdentifier());
            }
            // Handle symbols
            else if (peek() != '\0') {
                tokens.push_back(parseSymbol());
            }
        }

        tokens.push_back({ TokenType::EndOfFile, "" });
        return tokens;
    }

}