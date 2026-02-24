
#ifndef NANOBASE_SERIALIZER_H
#define NANOBASE_SERIALIZER_H

#include <string>
#include <variant>
#include <vector>
#include "Types.h"



class Serializer {
public:
    virtual void startTable(const std::string &name, const std::vector<std::string> &columns_name,
        int nextId) = 0;
    virtual void serializeRow(const Row& row) = 0;
    virtual void endTable() = 0;
    virtual ~Serializer() = default;
};

class Deserializer {
    virtual bool loadContent() = 0;
    virtual std::vector<std::string> getTableNames() = 0;
    virtual std::vector<std::string> getColumnNames(std::string tableName) = 0;
    virtual std::vector<Row> getRows(std::string tableName) = 0;
    virtual int getNextId(std::string tableName) = 0;
    virtual ~Deserializer() = default;
};

#endif //NANOBASE_SERIALIZER_H