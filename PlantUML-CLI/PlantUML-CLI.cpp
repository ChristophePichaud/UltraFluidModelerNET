// PlantUML-CLI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "PlantUMLProcessor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "PlantUMLTokenizer.h"
#include "PlantUMLParser.h"
#include "GraphLayoutEngine.h"

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

int main1() 
{
	using namespace PlantUML;

    std::string input = R"(
        enum Status {
          OK
          ERROR
          UNKNOWN
        }

        interface ILogger {
          +log(message : string)
        }

        class User {
          +id : int
          +name : string
          -password : string
          +login()
          +logout()
        }

        class Admin extends User {
          +level : int
          +banUser(userId : int)
        }

        User --> ILogger
        Admin --> Status
    )";

    PlantUMLTokenizer tokenizer;
    auto tokens = tokenizer.tokenize(input);

    PlantUMLParser parser(tokens);
    parser.parse();

    for (const auto& entity : parser.getEntities()) {
        std::cout << "Entity: " << entity.name << "\n";
        if (entity.type == EntityType::Enum) {
            for (const auto& val : entity.enumValues) {
                std::cout << "  EnumValue: " << val << "\n";
            }
        }
        else {
            for (const auto& attr : entity.attributes) {
                std::cout << "  Attribute: " << attr.visibility << attr.name << " : " << attr.type << "\n";
            }
            for (const auto& method : entity.methods) {
                std::cout << "  Method: " << method.visibility << method.name << "()\n";
            }
        }
        std::cout << "\n";
    }

    for (const auto& rel : parser.getRelations()) {
        std::cout << "Relation: " << rel.from << " " << rel.type << " " << rel.to << "\n";
    }

    return 0;
}

int main() //PlantUML() 
{
    using namespace PlantUML;

    try {
        PlantUMLProcessor processor("PlantUML1.puml");
        processor.process();
        // Dump vers la console
        processor.dumpEntities(std::cout);
        processor.dumpRelations(std::cout);


        //for (const auto& entity : processor.getEntities()) {
        //    std::cout << "Entity: " << entity.name << "\n";
        //    if (entity.type == EntityType::Enum) {
        //        for (const auto& val : entity.enumValues)
        //            std::cout << "  EnumValue: " << val << "\n";
        //    }
        //    else {
        //        for (const auto& attr : entity.attributes)
        //            std::cout << "  Attribute: " << attr.visibility << attr.name << " : " << attr.type << "\n";
        //        for (const auto& method : entity.methods)
        //            std::cout << "  Method: " << method.visibility << method.name << "()\n";
        //    }
        //    std::cout << "\n";
        //}

        //for (const auto& rel : processor.getRelations()) {
        //    std::cout << "Relation: " << rel.from << " " << rel.type << " " << rel.to << "\n";
        //}

        GraphLayoutEngine engine;
        for (auto& e : mesElements)
            engine.AddElement(e);

        for (auto& e : mesElements) {
            if (e->m_pConnector)
                engine.AddConnector(e->m_pConnector->m_pElement1, e->m_pConnector->m_pElement2);
        }

        engine.RunLayout();


    }
    catch (const std::exception& ex) {
        std::cerr << "Erreur : " << ex.what() << std::endl;
    }

    return 0;
}

int mainSmallPlantUML() 
{
	using namespace SmallPlantUML;

    std::ifstream file("ecarb-schema.puml");
    std::stringstream buffer;
    buffer << file.rdbuf();

    Tokenizer tokenizer(buffer.str());
    auto tokens = tokenizer.tokenize();

    Parser parser(tokens);
    Schema schema = parser.parse();

    std::cout << "Entities:\n";
    for (const auto& entity : schema.entities) {
        std::cout << "- " << entity.name << "\n";
        for (const auto& field : entity.fields) {
            std::cout << "    > " << field.name << " : " << field.type << "\n";
        }
    }

    std::cout << "\n Relations:\n";
    for (const auto& rel : schema.relations) {
        std::cout << rel.source << " --> " << rel.target << " : " << rel.fieldName << "\n";
    }

    return 0;
}

int mainOld() 
{
    using namespace SmallPlantUML;

    SchemaAnalyzer analyzer("ecarb-schema.puml");
    analyzer.printSummary();

    // You can also access `analyzer.getSchema()` directly and process it
    return 0;
}
