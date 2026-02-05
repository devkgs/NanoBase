#include <iostream>
#include "Database.h"

int main() {
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    Database db;
    db.createTable("personnes", {"id", "nom", "age"});
    db.insertInto("personnes", {1, "Alice", 25});

    return 0;
}