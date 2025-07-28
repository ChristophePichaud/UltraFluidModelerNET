#pragma once
#pragma once
#include <string>
#include <vector>
#include "PlantUMLTokenizer.h"
#include "PlantUMLParser.h"

namespace PlantUML
{
    class PlantUMLProcessor {
    public:
        explicit PlantUMLProcessor(const std::string& filepath);

        void process(); // Lance le traitement du fichier

        const std::vector<Entity>& getEntities() const;
        const std::vector<Relation>& getRelations() const;

        // Méthodes de dump
        void dumpEntities(std::ostream& out) const;
        void dumpRelations(std::ostream& out) const;

    private:
        std::string filepath;
        std::vector<Token> tokens;
        std::vector<Entity> entities;
        std::vector<Relation> relations;

        std::string loadFile(const std::string& filename);
    };
}

namespace SmallPlantUML
{
    class SchemaAnalyzer {
    public:
        explicit SchemaAnalyzer(const std::string& filePath);
        const Schema& getSchema() const;

        void printSummary() const;

    private:
        std::string filePath;
        Schema schema;

        void analyze();
    };

}