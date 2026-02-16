#include "gtest/gtest.h"
#include "Database.h"


// TODO add Test create a table if the table name already exists

TEST(DataBaseTest, createTable_test) {

}

TEST(DataBaseTest, insertInto_test) {
    Database db;
    db.createTable("person", {"id", "name", "age"});

    auto ret = db.insertInto("person", {1, "Alice", 25});
    ASSERT_TRUE(std::holds_alternative<int>(ret));
    ASSERT_EQ(1, std::get<int>(ret));

    ret = db.insertInto("person", {2, "Bob", 55});
    ASSERT_TRUE(std::holds_alternative<int>(ret));
    ASSERT_EQ(2, std::get<int>(ret));
}

TEST(DataBaseTest, insertInto_fail_test) {
    Database db;
    db.createTable("person", {"id", "name", "age"});

    auto ret = db.insertInto("bad_table", {1, "Alice", 25});
    ASSERT_TRUE(std::holds_alternative<Database::DbError>(ret));
    ASSERT_EQ(Database::DbError::TableNotFound, std::get<Database::DbError>(ret));
}

TEST(DataBaseTest, getUniqueId_test) {
    Database db;
    db.createTable("person", {"id", "name", "age"});

    db.insertInto("person", {1, "Alice", 25});
    db.insertInto("person", {2, "Bob", 55});
    db.insertInto("person", {2, "Charlie", 25});

    auto uid = db.getUniqueId("person", "name", "Alice");
    ASSERT_FALSE(std::holds_alternative<Database::DbError>(uid));
    ASSERT_TRUE(std::holds_alternative<int>(uid));

    uid = db.getUniqueId("person", "age", 25);
    ASSERT_TRUE(std::holds_alternative<int>(uid));
}

TEST(DataBaseTest, getUniqueId_case_sensitive_test) {
    Database db;
    db.createTable("person", {"id", "name", "age"});

    db.insertInto("person", {1, "Alice", 25});
    db.insertInto("person", {2, "Bob", 55});

    auto uid = db.getUniqueId("person", "name", "alice");
    ASSERT_TRUE(std::holds_alternative<Database::DbError>(uid));
}

TEST(DataBaseTest, getUniqueId_not_found_test) {
    Database db;
    db.createTable("person", {"id", "name", "age"});

    db.insertInto("person", {1, "Alice", 25});
    db.insertInto("person", {2, "Bob", 55});

    auto uid = db.getUniqueId("person", "name", "nobody");
    ASSERT_TRUE(std::holds_alternative<Database::DbError>(uid));
}

TEST(DataBaseTest, check_errors) {
    Database db;
    db.createTable("person", {"id", "name", "age"});

    db.insertInto("unvalid_table", {1, "Alice", 25});
}

TEST(DataBaseTest, deleteRow_test) {
    Database db;
    db.createTable("person", {"id", "name", "age"});

    db.insertInto("person", {1, "Alice", 25});
    db.insertInto("person", {2, "Bob", 55});

    auto uid = db.getUniqueId("person", "name", "Alice");
    ASSERT_TRUE(std::holds_alternative<int>(uid));

    db.deleteRow("person", std::get<int>(uid));

    uid = db.getUniqueId("person", "name", "Alice");
    ASSERT_TRUE(std::holds_alternative<Database::DbError>(uid));

    // Check with unvalid table name
}