#include "Database.h"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>

using DbError = Database::DbError;

std::string Database::to_string(const DbError e) {
    switch (e) {
        case DbError::TableNotFound: return "Error: Table not found";
        case DbError::ColumnNotFound: return "Error: Column not found";
        default: return "Unknown error";
    }
}

std::optional<DbError> Database::createTable(const std::string &tableName, const std::vector<std::string> &columns) {
    if (tables.contains(tableName)) {
        return DbError::TableExists;
    }
    tables[tableName] = {tableName, columns, {}};
    return std::nullopt;
}

std::variant<int, DbError> Database::insertInto(const std::string &tableName, const std::vector<CellValue> &cells) {
    if (!tables.contains(tableName)) {
        return DbError::TableNotFound;
    }
    Table &table = tables[tableName];
    int assignedId = table.nextId++;
    table.rows.push_back({assignedId, cells});

    return assignedId;
}

std::variant<int, DbError> Database::getUniqueId(const std::string &tableName, const std::string &column_name,
                                       const CellValue &value) {
    const auto itTable = tables.find(tableName);

    if (itTable == tables.end()) {
        return DbError::TableNotFound;
    }
    Table &table = itTable->second;

    // Find column
    const auto it = std::find(table.columnNames.begin(), table.columnNames.end(), column_name);

    if (it == table.columnNames.end()) {
        return DbError::ColumnNotFound;
    }

    // Find value in column
    const auto index = std::distance(table.columnNames.begin(), it);
    for (const auto &[id, cells]: table.rows) {
        if (cells[index] == value) {
            std::cout << "found" << std::endl;
            return id;
        }
    }
    // Not found
    return DbError::RowNotFound;
}

std::optional<DbError> Database::deleteRow(const std::string &tableName, int uniqueId) {
    if (!tables.contains(tableName)) {
        return DbError::TableNotFound;
    }

    auto &rows = tables[tableName].rows;

    const auto it = std::remove_if(rows.begin(), rows.end(), [uniqueId](const Row &row) {
        return row.id == uniqueId;
    });

    if (it == rows.end()) {
        return DbError::RowNotFound;
    }

    rows.erase(it, rows.end());
    return std::nullopt;
}


void Database::printTable(const std::string &tableName) {
    const auto &table = tables[tableName];
    std::cout << "ID\t";
    for (const auto &col: table.columnNames) std::cout << col << "\t";
    std::cout << "\n---------------------------\n";
    // Logic to get info from variant (std::visit) here...
}

// Get cell
