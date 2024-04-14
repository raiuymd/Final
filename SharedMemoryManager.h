#pragma once
#ifndef SHAREDMEMORYMANAGER_H
#define SHAREDMEMORYMANAGER_H

#include <string>
#include <cstddef> // for size_t

class SharedMemoryManager {
public:
    SharedMemoryManager(const std::string& name, size_t size);
    ~SharedMemoryManager();

    void* attach();
    void detach();
    void remove(); // Updated to no longer require a name parameter

private:
    int shm_fd;
    void* mapped_memory;
    std::string shm_name;
    size_t shm_size;
};


#endif // SHAREDMEMORYMANAGER_H

