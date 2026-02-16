#ifndef NANOBASE_DATABASE_H
#define NANOBASE_DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
#include <optional>

using CellValue = std::variant<int, double, std::string>;
struct Row {
    int id;
    std::vector<CellValue> cells;
};

struct Table {
    std::string name;
    std::vector<std::string> columnNames;
    std::vector<Row> rows;
    int nextId = 1;
};

class Database {
public:
    enum class DbError {
        Success,
        TableNotFound,
        ColumnNotFound,
        TypeMismatch,
        TableExists,
        RowNotFound
    };

    std::string to_string(DbError e) {
        switch(e) {
            case DbError::TableNotFound:  return "Error: Table not found";
            case DbError::ColumnNotFound: return "Error: Column not found";
                // ...
        }
    }

    std::optional<DbError>  createTable(const std::string& tableName, const std::vector<std::string>& columns) {
        // Verify that the table did not already exist
        if (tables.contains(tableName)) {
            return DbError::TableExists;
        }
        tables[tableName] = {tableName, columns, {}};
        return std::nullopt;
    }

     std::optional<DbError> insertInto(const std::string& tableName, const std::vector<CellValue>& cells) {
        if (!tables.contains(tableName)) {
            return DbError::TableNotFound;
        }
        Table& table = tables[tableName];
        table.rows.push_back({table.nextId++, cells});

        return std::nullopt;
    }

    std::optional<int> getUniqueId(const std::string& tableName, const std::string & column_name, std::variant<int, double, std::string> value) {
        if (!tables.contains(tableName)) {
            return std::nullopt;
        }

        Table& table = tables[tableName];

        // Find column
        auto it = std::find(table.columnNames.begin(), table.columnNames.end(), column_name);

        if (it == table.columnNames.end()) {
            return std::nullopt;
        }

        // Find value in column
        int index = std::distance(table.columnNames.begin(), it);
        for (const auto& row : table.rows) {
            if (row.cells[index] == value) {
                std::cout << "found" << std::endl;
                return row.id;
            }
        }
        // Not found
        return std::nullopt;
    }

    std::optional<DbError> deleteRow(const std::string& tableName, int uniqueId) {
        if (!tables.contains(tableName)) {
            return DbError::TableNotFound;
        }

        auto& rows = tables[tableName].rows;

        auto it = std::remove_if(rows.begin(), rows.end(), [uniqueId](const Row& row) {
                return row.id == uniqueId;
            });

        if (it == rows.end()) {
           return DbError::RowNotFound;
        }

        rows.erase(it, rows.end());
        return std::nullopt;
    }


    void printTable(const std::string& tableName) {
        auto& table = tables[tableName];
        std::cout << "ID\t";
        for (const auto& col : table.columnNames) std::cout << col << "\t";
        std::cout << "\n---------------------------\n";
        // Logic to get info from variant (std::visit) here...
    }

    // Get cell
private:
    std::unordered_map<std::string, Table> tables;

};



#endif //NANOBASE_DATABASE_H