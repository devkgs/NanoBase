
#ifndef NANOBASE_SERIALIZER_H
#define NANOBASE_SERIALIZER_H

#include <string>
#include <variant>

using CellValue = std::variant<int, double, std::string>;

class Serializer {
public:

    virtual void startTable(const std::string &name, const std::vector<std::string> &columns_name) = 0;
    virtual void endTable() = 0;
    virtual void startRow(int uid) = 0;
    virtual void endRow() = 0;
    virtual void writeValue(const CellValue& value) = 0;
    virtual ~Serializer() = default;
};


#endif //NANOBASE_SERIALIZER_H