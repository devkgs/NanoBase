#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Database.h"

class MockSerializer : public Serializer {
public:
    // MOCK_METHOD(type_retour, nom, (arguments), (override))
    MOCK_METHOD(void, startTable, (const std::string&, const std::vector<std::string>&), (override));
    MOCK_METHOD(void, endTable, (), (override));
    MOCK_METHOD(void, startRow, (int), (override));
    MOCK_METHOD(void, endRow, (), (override));
    MOCK_METHOD(void, writeValue, (const CellValue&), (override));
};

void setupPersonTable(Database &db) {
    db.createTable("person", {"personal_id", "name", "age"});
    db.insertInto("person", {1, "Alice", 25});
    db.insertInto("person", {2, "Bob", 55});
    db.insertInto("person", {2, "Charlie", 25});
}


// TODO add Test create a table if the table name already exists

TEST(DataBaseTest, createTable_test) {

}

TEST(DataBaseTest, insertInto_test) {
    Database db;
    db.createTable("person", {"personal_id", "name", "age"});

    auto ret = db.insertInto("person", {1, "Alice", 25});
    ASSERT_TRUE(std::holds_alternative<int>(ret));
    ASSERT_EQ(1, std::get<int>(ret));

    ret = db.insertInto("person", {2, "Bob", 55});
    ASSERT_TRUE(std::holds_alternative<int>(ret));
    ASSERT_EQ(2, std::get<int>(ret));
}

TEST(DataBaseTest, insertInto_fail_test) {
    Database db;
    db.createTable("person", {"personal_id", "name", "age"});

    auto ret = db.insertInto("bad_table", {1, "Alice", 25});
    ASSERT_TRUE(std::holds_alternative<Database::DbError>(ret));
    ASSERT_EQ(Database::DbError::TableNotFound, std::get<Database::DbError>(ret));
}

TEST(DataBaseTest, getUniqueId_test) {
    Database db;
    setupPersonTable(db);

    auto uid = db.getUniqueId("person", "name", "Alice");
    ASSERT_FALSE(std::holds_alternative<Database::DbError>(uid));
    ASSERT_TRUE(std::holds_alternative<int>(uid));
    ASSERT_EQ(1, std::get<int>(uid));

    uid = db.getUniqueId("person", "name", "Charlie");
    ASSERT_TRUE(std::holds_alternative<int>(uid));
    ASSERT_EQ(3, std::get<int>(uid));

    uid = db.getUniqueId("person", "age", 25);
    ASSERT_TRUE(std::holds_alternative<int>(uid));
}

TEST(DataBaseTest, getUniqueId_case_sensitive_test) {
    Database db;
    setupPersonTable(db);

    auto uid = db.getUniqueId("person", "name", "alice");
    ASSERT_TRUE(std::holds_alternative<Database::DbError>(uid));
}

TEST(DataBaseTest, getUniqueId_not_found_test) {
    Database db;
    setupPersonTable(db);

    auto uid = db.getUniqueId("person", "name", "nobody");
    ASSERT_TRUE(std::holds_alternative<Database::DbError>(uid));
}

// TODO fill the test
TEST(DataBaseTest, check_errors) {
/*    Database db;
    db.createTable("person", {"personal_id", "name", "age"});
    db.insertInto("invalid_table", {1, "Alice", 25});
*/
}

TEST(DataBaseTest, deleteRow_test) {
    Database db;
    setupPersonTable(db);

    auto uid = db.getUniqueId("person", "name", "Alice");
    ASSERT_TRUE(std::holds_alternative<int>(uid));

    db.deleteRow("person", std::get<int>(uid));

    uid = db.getUniqueId("person", "name", "Alice");
    ASSERT_TRUE(std::holds_alternative<Database::DbError>(uid));

    // Check with invalid table name
}

TEST(DataBaseTest, save_test) {
    Database db;

    db.createTable("table1", {"personal_id", "name", "age"});
    db.insertInto("table1", {1, "Alice", 25});
    db.insertInto("table1", {2, "Bob", 55});
    db.insertInto("table1", {2, "Charlie", 25});

    db.createTable("table2", {"personal_id", "name", "age"});
    db.insertInto("table2", {1, "Donald", 25});
    db.insertInto("table2", {2, "Eric", 55});
    db.insertInto("table2", {2, "Frank", 25});

    MockSerializer m;

    EXPECT_CALL(m, startTable(testing::_, testing::_)).Times(2);
    EXPECT_CALL(m, startRow(testing::_)).Times(6);
    EXPECT_CALL(m, writeValue(testing::_)).Times(18);
    db.save(m);
}