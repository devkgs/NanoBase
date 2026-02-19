
std::variant
utiliser les tempalates?


table
row
cell

# Table
- table name
-
# Line

# Cell

# Use cases
- create a table (table name, cells names/type)
- add element to a table

# Data persistence
tables unsorted
struct table

Table:
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


# Serializer
interface serializer



## methods
- startTable(name, fields_name)
- endTable
- addRow(uid, )


