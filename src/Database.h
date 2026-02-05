#ifndef NANOBASE_DATABASE_H
#define NANOBASE_DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>


using CellValue = std::variant<int, double, std::string>;

using Row = std::vector<CellValue>;

struct Table {
    std::string name;
    std::vector<std::string> columnNames;
    std::vector<Row> rows;
};

class Database {
private:
    std::unordered_map<std::string, Table> tables;

public:
    // create dynamic table
    void createTable(const std::string& name, const std::vector<std::string>& columns) {
        tables[name] = {name, columns, {}};
        std::cout << "Table '" << name << "' with " << columns.size() << " colums.\n";
    }

    // Add line
    void insertInto(const std::string& tableName, const Row& row) {
        if (tables.find(tableName) != tables.end()) {
            tables[tableName].rows.push_back(row);
        }
    }

    // Print table
    void printTable(const std::string& tableName) {
        auto& table = tables[tableName];
        for (const auto& col : table.columnNames) std::cout << col << "\t";
        std::cout << "\n---------------------------\n";
        // Logic to get info from variant (std::visit) here...
    }
};



#endif //NANOBASE_DATABASE_H