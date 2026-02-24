#ifndef NANOBASE_STORAGE_H
#define NANOBASE_STORAGE_H

#include <string>
#include <optional>

class InputStorage {
public:
    virtual ~InputStorage() = default;
    virtual std::optional<std::string> load() = 0;
};

class OutputStorage {
public:
    virtual ~OutputStorage() = default;
    virtual void save(const std::string& content) = 0;
};

class Storage : public InputStorage, public OutputStorage {};
#endif //NANOBASE_STORAGE_H