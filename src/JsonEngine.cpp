#include "JsonEngine.h"
#include <nlohmann/json.hpp>

JsonSerializer::JsonSerializer(OutputStorage<std::string>& s): storage_(s), isFirstRow_(true) {}

void JsonSerializer::startTable(const std::string& name,
        const std::vector<std::string>& columns_name,
        int nextId) {
        isFirstRow_ = true;
        j_ = nlohmann::json::object();
        j_["tableName"] = name;
        j_["nextId"] = nextId;
        j_["columnNames"] = columns_name;
        j_["rows"] = nlohmann::json::array();
}

void JsonSerializer::endTable() {
        std::string jsonText = j_.dump(4);
        storage_.save(jsonText);
}

void JsonSerializer::serializeRow(const Row& row) {
        nlohmann::json rowJson;
        rowJson["id"] = row.id;
        nlohmann::json cellsArray = nlohmann::json::array();

        for (const auto& cell : row.cells) {
                std::visit([&cellsArray](auto&& arg) {
                    cellsArray.push_back(arg);
                }, cell);
        }
        rowJson["cells"] = cellsArray;
        j_["rows"].push_back(rowJson);
}

