#pragma once
#include <string>
#include <vector>

namespace PlantUML
{
    enum class TokenType {
        Keyword, Identifier, Symbol, Visibility, Type, Relation, Unknown
    };

    struct Token {
        TokenType type;
        std::string value;
    };

    class PlantUMLTokenizer {
    public:
        std::vector<Token> tokenize(const std::string& input);

    private:
        Token classify(const std::string& value);
    };
}

namespace SmallPlantUML
{

    enum class TokenType {
        Keyword,
        Identifier,
        Type,
        Symbol,
        RelationArrow,
        EndOfFile
    };

    struct Token {
        TokenType type;
        std::string value;
    };

    class Tokenizer {
    public:
        explicit Tokenizer(const std::string& text);
        std::vector<Token> tokenize();

    private:
        std::string input;
        size_t pos;

        char peek() const;
        char advance();
        void skipWhitespace();

        Token parseIdentifier();
        Token parseSymbol();
        Token parseRelationArrow();
    };
}