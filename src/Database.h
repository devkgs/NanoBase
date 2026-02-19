#ifndef NANOBASE_DATABASE_H
#define NANOBASE_DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
#include <optional>
#include "Serializer.h"


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

    static std::string to_string(const DbError e);
    std::optional<DbError> createTable(const std::string &tableName, const std::vector<std::string> &columns);
    std::variant<int, DbError> insertInto(const std::string &tableName, const std::vector<CellValue> &cells);
    std::variant<int, DbError> getUniqueId(const std::string &tableName, const std::string &column_name,
                                           const CellValue &value);
    std::optional<DbError> deleteRow(const std::string &tableName, int uniqueId);
    void printTable(const std::string &tableName);
    void save(Serializer &s);
private:
    std::unordered_map<std::string, Table> tables;
};


#endif //NANOBASE_DATABASE_H
