#include "gtest/gtest.h"
#include "Database.h"


// TODO add Test create a table if the table name already exists


TEST(DataBaseTest, getUniqueId_test) {
    Database db;
    db.createTable("person", {"id", "name", "age"});

    db.insertInto("person", {1, "Alice", 25});
    db.insertInto("person", {2, "Bob", 55});
    db.insertInto("person", {2, "Charlie", 25});

    auto uid = db.getUniqueId("person", "name", "Alice");
    ASSERT_TRUE(uid.has_value());

    uid = db.getUniqueId("person", "age", 25);
    ASSERT_TRUE(uid.has_value());
}

TEST(DataBaseTest, getUniqueId_case_sensitive_test) {
    Database db;
    db.createTable("person", {"id", "name", "age"});

    db.insertInto("person", {1, "Alice", 25});
    db.insertInto("person", {2, "Bob", 55});

    auto uid = db.getUniqueId("person", "name", "alice");
    ASSERT_FALSE(uid.has_value());
}

TEST(DataBaseTest, getUniqueId_not_found_test) {
    Database db;
    db.createTable("person", {"id", "name", "age"});

    db.insertInto("person", {1, "Alice", 25});
    db.insertInto("person", {2, "Bob", 55});

    auto uid = db.getUniqueId("person", "name", "nobody");
    ASSERT_FALSE(uid.has_value());
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
    ASSERT_TRUE(uid.has_value());

    db.deleteRow("person", *uid);

    uid = db.getUniqueId("person", "name", "Alice");
    ASSERT_FALSE(uid.has_value());

    // Check with unvalid table name

}