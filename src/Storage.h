#ifndef NANOBASE_STORAGE_H
#define NANOBASE_STORAGE_H

#include <string>
#include <optional>

class IInputStorage {
public:
    virtual ~IInputStorage() = default;
    virtual std::optional<std::string> load() = 0;
};

class IOutputStorage {
public:
    virtual ~IOutputStorage() = default;
    virtual void save(const std::string& content) = 0;
};

class IStorage : public IInputStorage, public IOutputStorage {};
#endif //NANOBASE_STORAGE_H