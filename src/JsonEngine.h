#ifndef NANOBASE_JSONSERIALIZER_H
#define NANOBASE_JSONSERIALIZER_H

#include <string>
#include <vector>
#include "Serialization.h"
#include "Storage.h"

class JsonSerializer: public Serializer{
public:
    explicit JsonSerializer(OutputStorage<std::string>& s);
    ~JsonSerializer() override = default;

    void startTable(const std::string& name,
        const std::vector<std::string>& columns_name,
        int nextId) override;
    void serializeRow(const Row& row) override;
    void endTable() override;
private:
    OutputStorage<std::string>& storage_;
    bool isFirstRow_; // Track if we need to add a comma between JSON objects
};

class JsonDeserializer: public Deserializer {
public:
    explicit JsonDeserializer(InputStorage<std::string>& s): storage_(s){}
    ~JsonDeserializer() override = default;

    bool loadContent() override;
    std::vector<std::string> getTableNames() override;
    std::vector<std::string> getColumnNames(const std::string& tableName) override;
    std::vector<Row> getRows(const std::string& tableName) override;
    int getNextId(const std::string& tableName) override;
private:
    InputStorage<std::string>& storage_;
};

#endif //NANOBASE_JSONSERIALIZER_H