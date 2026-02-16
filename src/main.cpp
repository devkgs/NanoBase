#include <iostream>
#include "Database.h"

int main() {
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    Database db;
    db.createTable("personnes", {"id", "nom", "age"});
    db.insertInto("personnes", {1, "Alice", 25});
    db.insertInto("personnes", {2, "Rob", 55});

    auto uid = db.getUniqueId("personnes", "nom", "Alice");
   /* if (uid.has_value()) {
        std::cout << "main found : " << *uid << std::endl;
    }

    uid = db.getUniqueId("personnes", "nom", "prout");
    if (uid.has_value()) {
        std::cout << "main found : " << *uid << std::endl;
    }else {
        std::cout << " not found ! "<< std::endl;
    }*/
    return 0;
}