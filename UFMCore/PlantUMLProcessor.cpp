#include "pch.h"
#include "UFMCore\PlantUMLProcessor.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace PlantUML
{

    PlantUMLProcessor::PlantUMLProcessor(const std::string& filepath)
        : filepath(filepath) {
    }

    std::string PlantUMLProcessor::loadFile(const std::string& filename) {
        std::ifstream inFile(filename);
        std::stringstream buffer;
        if (!inFile) {
            throw std::runtime_error("Erreur d'ouverture du fichier : " + filename);
        }
        buffer << inFile.rdbuf();
        return buffer.str();
    }

    void PlantUMLProcessor::process() {
        std::string input = loadFile(filepath);

        PlantUMLTokenizer tokenizer;
        tokens = tokenizer.tokenize(input);

        PlantUMLParser parser(tokens);
        parser.parse();

        entities = parser.getEntities();
        relations = parser.getRelations();
    }

    const std::vector<Entity>& PlantUMLProcessor::getEntities() const {
        return entities;
    }

    const std::vector<Relation>& PlantUMLProcessor::getRelations() const {
        return relations;
    }

    void PlantUMLProcessor::dumpEntities(std::ostream& out) const {
        out << "=== Entities Dump ===\n";
        for (const auto& entity : entities) {
            out << "Entity: " << entity.name << "\n";
            for (const auto& attribute : entity.attributes) {
                out << "  - " << attribute.name << " : " << attribute.type << "\n";
            }
            out << "\n";
        }
    }

    void PlantUMLProcessor::dumpRelations(std::ostream& out) const {
        out << "=== Relations Dump ===\n";
        for (const auto& relation : relations) {
            out << relation.from << " --(" << relation.type << ")--> " << relation.to << "\n";
        }
        out << "\n";
    }

}

namespace SmallPlantUML
{
    SchemaAnalyzer::SchemaAnalyzer(const std::string& filePath) : filePath(filePath) {
        analyze();
    }

    void SchemaAnalyzer::analyze() {
        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "Unable to open file: " << filePath << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        Tokenizer tokenizer(buffer.str());
        auto tokens = tokenizer.tokenize();

        Parser parser(tokens);
        schema = parser.parse();
    }

    const Schema& SchemaAnalyzer::getSchema() const {
        return schema;
    }

    void SchemaAnalyzer::printSummary() const {
        std::cout << "Entities:\n";
        for (const auto& entity : schema.entities) {
            std::cout << "- " << entity.name << "\n";
            for (const auto& field : entity.fields) {
                std::cout << "    > " << field.name << " : " << field.type << "\n";
            }
        }

        std::cout << "\nRelations:\n";
        for (const auto& rel : schema.relations) {
            std::cout << rel.source << " --> " << rel.target << " : " << rel.fieldName << "\n";
        }
    }

}