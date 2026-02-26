#ifndef NANOBASE_SERIALIZER_H
#define NANOBASE_SERIALIZER_H

#include <string>
#include <vector>
#include "Types.h"

/**
 * @class Serializer
 * @brief Interface for serializing database tables into a specific format.
 */
class Serializer {
public:
    virtual ~Serializer() = default;

    /**
     * @brief Starts the serialization of a table.
     * @param name The table name.
     * @param columns_name List of column headers.
     * @param nextId Current auto-increment counter value.
     */
    virtual void startTable(const std::string &name,
                          const std::vector<std::string> &columns_name,
                          int nextId) = 0;

    /**
     * @brief Serializes a single row of data.
     * @param row The Row structure containing ID and cell values.
     */
    virtual void serializeRow(const Row& row) = 0;

    /**
     * @brief Finalizes the table serialization (closes files/tags).
     */
    virtual void endTable() = 0;
};

/**
 * @class Deserializer
 * @brief Interface for extracting table data from a storage source.
 */
class Deserializer {
public:
    virtual ~Deserializer() = default;

    /**
     * @brief Loads raw content from storage and prepares the parser.
     * @return true if content was successfully loaded.
     */
    virtual bool loadContent() = 0;

    /**
     * @brief Retrieves all table names present in the source.
     * @return A vector of table names.
     */
    virtual std::vector<std::string> getTableNames() = 0;

    /**
     * @brief Gets the column names for a specific table.
     * @param tableName The name of the target table.
     * @return A vector of column names.
     */
    virtual std::vector<std::string> getColumnNames(const std::string& tableName) = 0;

    /**
     * @brief Extracts all rows for a given table.
     * @param tableName The name of the target table.
     * @return A vector of Row objects.
     */
    virtual std::vector<Row> getRows(const std::string& tableName) = 0;

    /**
     * @brief Retrieves the nextId value to maintain auto-increment continuity.
     * @param tableName The name of the target table.
     * @return The integer value of the next ID.
     */
    virtual int getNextId(const std::string& tableName) = 0;
};

#endif //NANOBASE_SERIALIZER_H