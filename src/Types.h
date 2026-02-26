
#ifndef NANOBASE_TYPES_H
#define NANOBASE_TYPES_H

#include <variant>

using CellValue = std::variant<int, double, std::string>;

struct Row {
    int id;
    std::vector<CellValue> cells;
};

#endif //NANOBASE_TYPES_H