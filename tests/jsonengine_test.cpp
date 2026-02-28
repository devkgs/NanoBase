#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "JsonEngine.h"
#include "Storage.h"

/*
 *
 */
//template <typename T> // public OutputStorage<T>
class MockOutputStorage: public OutputStorage<std::string> {
        MOCK_METHOD(void, save, (const std::string& content), (override));
};

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
