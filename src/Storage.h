#ifndef NANOBASE_STORAGE_H
#define NANOBASE_STORAGE_H

#include <string>
#include <optional>

template <typename InType>
class InputStorage {
public:
    virtual ~InputStorage() = default;
    virtual std::optional<InType> load() = 0;
};

template <typename OutType>
class OutputStorage {
public:
    virtual ~OutputStorage() = default;
    virtual void save(const OutType& content) = 0;
};

template <typename InType, typename OutType>
class Storage : public InputStorage<InType>, public OutputStorage<OutType> {};
#endif //NANOBASE_STORAGE_H