
#include "JsonEngine.h"

JsonSerializer::JsonSerializer(OutputStorage& s): storage_(s), isFirstRow_(true) {

}


void JsonSerializer::startTable(const std::string& name,
        const std::vector<std::string>& columns_name,
        int nextId) {

}

void JsonSerializer::endTable() {

}

void JsonSerializer::serializeRow(const Row& row) {

}

