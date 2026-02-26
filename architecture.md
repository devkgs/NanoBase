# Table:
uniqueid | columns_names
row:
1 cell1 cell2 cell3...
2 cell1 cell2 cell3...

Table: sensor2
|-----------|-----------|--------|
|unique_id  | timestamp | temp   |
|-----------|-----------|--------|
| 123       | 23:12     | 23.5°C |
| 124       | 23:13     | 24.5°C |


# Architecture
```
[ Database ]
         /    \
        v      v
 [Serialization] [Types.h] <--- (La structure Row)
        |          ^
        v         /
 [ JsonEngine ]--/
```

database
types
serialization
jsonengine
storage
filestorage

## Database

jsonSerilizer(: Serializer
jsonDeserializer: Deserializer

Input: Serializer object, Storage object

### save database:
for tables
    create table
    for rows
        for row item
            write value

### load database


## JsonSerializer

## JsonDeSerializer


## Storage interface
Generic storage interface. 

### IOutputStorage: 
- write. Write

### IInputStorage:
- 

## database
output/input stream. [ois]
jsonserlizer [jsr]
database [db]

db(ois)
jsr.save(ois)


//////////////////////
```
////////////////////////////////////////////////////////////////////////////////////////
class JsonSerializer : public ISerializer {
private:
    IOutputStorage& storage;
    std::stringstream buffer; // Plus efficace qu'une string pour concaténer
    bool firstRow = true;

public:
    explicit JsonSerializer(IOutputStorage& s) : storage(s) {}

    void beginTable(const std::string& tableName) override {
        buffer.str(""); // On vide le buffer
        buffer << "{ \"" << tableName << "\": [";
        firstRow = true;
    }

    void serializeRow(const Row& row) override {
        if (!firstRow) buffer << ",";
        
        buffer << "{ \"id\": " << row.id << ", \"data\": [";
        // ... ici on boucle sur row.cells pour remplir le JSON ...
        buffer << "] }";
        
        firstRow = false;
    }

    void endTable() override {
        buffer << "]}";
        // C'est ici qu'on utilise le storage !
        storage.save(buffer.str()); 
    }
};

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
class JsonDeserializer : public IDeserializer {
private:
    IInputStorage& storage;

public:
    explicit JsonDeserializer(IInputStorage& s) : storage(s) {}

    std::optional<Row> readNextRow() override {
        // 1. On récupère le bloc de données via le storage
        auto data = storage.load();
        if (!data) return std::nullopt;

        // 2. On parse la string 'data' (qui est du JSON) 
        // 3. On retourne la prochaine Row construite
        return Row{ /* ... données parsées ... */ };
    }
};

////////////////////////////////////////////////////////////////////////////////////////
// Interface pour la lecture
class IInputStorage {
public:
    virtual ~IInputStorage() = default;
    virtual std::optional<std::string> load() = 0;
};

// Interface pour l'écriture
class IOutputStorage {
public:
    virtual ~IOutputStorage() = default;
    virtual void save(const std::string& content) = 0;
};

// LA classe qui fait les deux
class FileStorage : public IInputStorage, public IOutputStorage {
    std::string filename;
public:
    explicit FileStorage(std::string f) : filename(std::move(f)) {}
    void save(const std::string& content) override { /* ... */ }
    std::optional<std::string> load() override { /* ... */ }
};
////////////////////////////////////////////////////////////////////////////////////////
void Database::load(IDeserializer& deserializer) {
    if (deserializer.loadContent()) {
        Table newTable;
        newTable.columnNames = deserializer.getColumnNames();
        newTable.nextId = deserializer.getNextId();
        newTable.rows = deserializer.getAllRows();
        
        this->table_ = std::move(newTable);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
void Database::loadAll(IDeserializer& deserializer) {
    if (!deserializer.loadContent()) return;

    for (const auto& name : deserializer.getTableNames()) {
        Table t;
        t.columnNames = deserializer.getColumnNames(name);
        t.rows = deserializer.getRows(name);
        t.nextId = deserializer.getNextId(name);
        
        this->tables_[name] = std::move(t); // On stocke dans une map de tables
    }
}


{////////////////////////////////////////////////////////////////////////////////////////
  "tableName": "Users",
  "nextId": 3,
  "columnNames": ["id", "name", "email"],
  "rows": [
    {
      "id": 1,
      "cells": ["Alice", "alice@example.com"]
    },
    {
      "id": 2,
      "cells": ["Bob", "bob@db.com"]
    }
  ]
}
```