#ifndef NANOBASE_FILESTORAGE_H
#define NANOBASE_FILESTORAGE_H

#include "Storage.h"

class FileStorage: public Storage {
public:
    explicit FileStorage(std::string f): filename_(std::move(f)){}
    void save(const std::string& content) override;
    std::optional<std::string> load() override;
private:
    std::string filename_;

};

#endif //NANOBASE_FILESTORAGE_H