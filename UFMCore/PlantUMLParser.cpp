#include "pch.h"
#include "UFMCore\PlantUMLTokenizer.h"
#include "UFMCore\PlantUMLParser.h"

namespace PlantUML
{

    PlantUMLParser::PlantUMLParser(const std::vector<Token>& tokens)
        : tokens(tokens), pos(0) {
    }

    void PlantUMLParser::parse() {
        while (pos < tokens.size()) {
            if (matchKeyword("class") || matchKeyword("interface") || matchKeyword("enum")) {
                parseEntity();
            }
            else if (peek().type == TokenType::Identifier && lookAheadRelation()) {
                parseRelation();
            }
            else {
                ++pos;
            }
        }
    }

    const std::vector<Entity>& PlantUMLParser::getEntities() const {
        return entities;
    }

    const std::vector<Relation>& PlantUMLParser::getRelations() const {
        return relations;
    }

    const Token& PlantUMLParser::peek() {
        return tokens[pos];
    }

    bool PlantUMLParser::matchKeyword(const std::string& word) {
        return pos < tokens.size() && tokens[pos].type == TokenType::Keyword && tokens[pos].value == word;
    }

    bool PlantUMLParser::lookAheadRelation() {
        return pos + 2 < tokens.size() && tokens[pos + 1].type == TokenType::Relation;
    }

    void PlantUMLParser::parseEntity() {
        EntityType entityType;
        if (matchKeyword("class")) entityType = EntityType::Class;
        else if (matchKeyword("interface")) entityType = EntityType::Interface;
        else entityType = EntityType::Enum;

        ++pos; // Skip keyword
        std::string name = tokens[pos++].value;
        Entity entity;
        entity.type = entityType;
        entity.name = name;

        if (tokens[pos].value == "{") {
            ++pos;
            while (tokens[pos].value != "}") {
                if (entity.type == EntityType::Enum && tokens[pos].type == TokenType::Identifier) {
                    entity.enumValues.push_back(tokens[pos++].value);
                }
                else if (tokens[pos].type == TokenType::Visibility) {
                    char vis = tokens[pos++].value[0];
                    std::string memberName = tokens[pos++].value;

                    if (tokens[pos].value == ":") {
                        ++pos;
                        std::string type = tokens[pos++].value;
                        entity.attributes.push_back({ vis, memberName, type });
                    }
                    else if (tokens[pos].value == "(") {
                        ++pos;
                        std::vector<std::string> params;
                        while (tokens[pos].value != ")") {
                            params.push_back(tokens[pos++].value);
                        }
                        ++pos;
                        entity.methods.push_back({ vis, memberName, params });
                    }
                }
                else {
                    ++pos;
                }
            }
            ++pos; // Skip closing brace
        }

        entities.push_back(entity);
    }

    void PlantUMLParser::parseRelation() {
        std::string from = tokens[pos++].value;
        std::string relationType = tokens[pos++].value;
        std::string to = tokens[pos++].value;
        relations.push_back({ from, to, relationType });
    }
}

namespace SmallPlantUML
{
    Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

    bool Parser::match(TokenType type, const std::string& value) {
        if (pos >= tokens.size()) return false;
        return tokens[pos].type == type && (value.empty() || tokens[pos].value == value);
    }

    Token Parser::consume() {
        return pos < tokens.size() ? tokens[pos++] : Token{ TokenType::EndOfFile, "" };
    }

    Entity Parser::parseEntity() {
        consume(); // 'entity'
        Token nameToken = consume();
        Entity entity{ nameToken.value, {} };

        consume(); // '{'
        while (!match(TokenType::Symbol, "}")) {
            consume(); // '*'
            Token fieldName = consume();
            consume(); // ':'
            Token fieldType = consume();
            entity.fields.push_back({ fieldName.value, fieldType.value });
        }
        consume(); // '}'
        return entity;
    }

    Relation Parser::parseRelation() {
        Token from = consume();
        consume(); // '-->'
        Token to = consume();
        consume(); // ':'
        Token via = consume();
        return { from.value, to.value, via.value };
    }

    Schema Parser::parse() {
        Schema schema;
        while (!match(TokenType::EndOfFile)) {
            if (match(TokenType::Keyword, "entity")) {
                schema.entities.push_back(parseEntity());
            }
            else if (match(TokenType::Identifier) && tokens[pos + 1].value == "-->") {
                schema.relations.push_back(parseRelation());
            }
            else {
                consume();
            }
        }
        return schema;
    }

}