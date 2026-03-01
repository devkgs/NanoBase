#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "JsonEngine.h"
#include "Storage.h"

//template <typename T> // public OutputStorage<T>
class MockOutputStorage : public OutputStorage<std::string> {
    //MOCK_METHOD(void, save, (const std::string& content), (override));
public:
    std::string data;

    void save(const std::string &content) override {
        data = content;
    }
};

TEST(JsonSerializerTest, FullSerializationFlow) {
    // 1. Setup
    MockOutputStorage mock_output_storage;
    JsonSerializer serializer(mock_output_storage);

    std::vector<std::string> columns = {"name", "age"};

    Row row;
    row.id = 1;
    row.cells = {"Alice", 25}; // std::variant géré par std::visit

    // 2. Action
    serializer.startTable("Users", columns, 10);
    serializer.serializeRow(row);
    serializer.endTable();

    // 3. Verification
    auto result = nlohmann::json::parse(mock_output_storage.data);

    EXPECT_EQ(result["tableName"], "Users");
    EXPECT_EQ(result["nextId"], 10);
    EXPECT_EQ(result["columnNames"].size(), 2);
    EXPECT_EQ(result["rows"].size(), 1);
    EXPECT_EQ(result["rows"][0]["id"], 1);
    EXPECT_EQ(result["rows"][0]["cells"][0], "Alice");
    EXPECT_EQ(result["rows"][0]["cells"][1], 25);
}

TEST(JsonSerializerTest, HandleSpecialCharacters) {
    MockOutputStorage mock_storage;
    JsonSerializer serializer(mock_storage);

    std::vector<std::string> columns = {"notes"};
    Row row;
    row.id = 1;
    // Test with quotes, backslashes and newlines
    row.cells = {"He said \"Hello\"\nLine 2 \\"};

    serializer.startTable("SpecialTable", columns, 1);
    serializer.serializeRow(row);
    serializer.endTable();

    auto result = nlohmann::json::parse(mock_storage.data);

    // nlohmann should have escaped these automatically
    EXPECT_EQ(result["rows"][0]["cells"][0], "He said \"Hello\"\nLine 2 \\");
}

/*
TEST(JsonSerializerTest, startTable_test) {
    MockOutputStorage mock_output_storage;
    JsonSerializer js(mock_output_storage);
    js.startTable("test_table", {"personal_id", "name", "age"}, 1);

    // TODO verify mock calls here
}

TEST(JsonSerializerTest, serializerRow_test) {
    MockOutputStorage mock_output_storage;
    JsonSerializer js(mock_output_storage);
    js.startTable("test_table", {"personal_id", "name", "age"}, 1);

    //EXPECT_CALL(mock_output_storage, save(testing::HasSubstr("\"Alice\""))).Times(1);

    js.serializeRow({1, {"Alice", 25}});

    // TODO verify mock calls here
}

TEST(JsonSerializerTest, endTable_test) {
    MockOutputStorage mock_output_storage;
    JsonSerializer js(mock_output_storage);
    js.endTable();

    // TODO verify mock calls here
}
*/