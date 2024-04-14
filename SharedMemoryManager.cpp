#include "SharedMemoryManager.h"
#include <fcntl.h>    // For O_* constants
#include <sys/mman.h> // For shared memory
#include <unistd.h>   // For ftruncate and close
#include <sys/stat.h> // For mode constants
#include <cstring>    // For strerror
#include <cerrno>     // For errno
#include <iostream>

SharedMemoryManager::SharedMemoryManager(const std::string& name, size_t size)
    : shm_fd(-1), mapped_memory(nullptr), shm_name(name), shm_size(size) {
    shm_fd = shm_open(shm_name.c_str(), O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "Failed to open shared memory object: " << strerror(errno) << std::endl;
        return;
    }

    if (ftruncate(shm_fd, shm_size) == -1) {
        std::cerr << "Failed to set size of shared memory object: " << strerror(errno) << std::endl;
        close(shm_fd); // Cleanup on failure
        shm_fd = -1; // Mark as closed
        return;
    }
}

SharedMemoryManager::~SharedMemoryManager() {
    detach();
    // Reminder: remove() needs to be called explicitly to clean up the shared memory object.
}

void* SharedMemoryManager::attach() {
    if (mapped_memory == nullptr) {
        mapped_memory = mmap(nullptr, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (mapped_memory == MAP_FAILED) {
            std::cerr << "Failed to map shared memory: " << strerror(errno) << std::endl;
            mapped_memory = nullptr;
        }
    }
    return mapped_memory;
}

void SharedMemoryManager::detach() {
    if (mapped_memory != nullptr) {
        munmap(mapped_memory, shm_size);
        mapped_memory = nullptr;
    }
    if (shm_fd != -1) {
        close(shm_fd);
        shm_fd = -1;
    }
}

void SharedMemoryManager::remove() {
    if (shm_unlink(shm_name.c_str()) == -1) {
        std::cerr << "Failed to remove shared memory: " << strerror(errno) << std::endl;
    }
}
