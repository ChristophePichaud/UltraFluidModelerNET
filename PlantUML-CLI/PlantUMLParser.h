//#pragma once
//class PlantUMLEngine
//{
//};
//

#pragma once
#include <string>
#include <vector>

namespace PlantUML
{
    enum class EntityType { Class, Interface, Enum };

    struct Attribute {
        char visibility;
        std::string name;
        std::string type;
    };

    struct Method {
        char visibility;
        std::string name;
        std::vector<std::string> parameters;
    };

    struct Entity {
        EntityType type;
        std::string name;
        std::vector<Attribute> attributes;
        std::vector<Method> methods;
        std::vector<std::string> enumValues;
    };

    struct Relation {
        std::string from;
        std::string to;
        std::string type;
    };

    class PlantUMLParser {
    public:
        PlantUMLParser(const std::vector<Token>& tokens);
        void parse();

        const std::vector<Entity>& getEntities() const;
        const std::vector<Relation>& getRelations() const;

    private:
        std::vector<Token> tokens;
        size_t pos;
        std::vector<Entity> entities;
        std::vector<Relation> relations;

        const Token& peek();
        bool matchKeyword(const std::string& word);
        bool lookAheadRelation();

        void parseEntity();
        void parseRelation();
    };
}

namespace SmallPlantUML
{

    struct Field {
        std::string name;
        std::string type;
    };

    struct Entity {
        std::string name;
        std::vector<Field> fields;
    };

    struct Relation {
        std::string source;
        std::string target;
        std::string fieldName;
    };

    struct Schema {
        std::vector<Entity> entities;
        std::vector<Relation> relations;
    };

    class Parser {
    public:
        explicit Parser(const std::vector<Token>& tokens);
        Schema parse();

    private:
        size_t pos;
        std::vector<Token> tokens;

        bool match(TokenType type, const std::string& value = "");
        Token consume();
        Entity parseEntity();
        Relation parseRelation();
    };

}