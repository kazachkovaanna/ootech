#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <QList>

template<typename T>
class GraphAllocator {
private:
    GraphAllocator()
    {
    }

    ~GraphAllocator()
    {
        for (T* block : _memory) {
            delete[] block;
        }

        _memory.clear();
        _free.clear();
    }

    GraphAllocator(const GraphAllocator&) = delete;

    GraphAllocator& operator=(const GraphAllocator&) = delete;

public:
    static GraphAllocator& instance()
    {
        static GraphAllocator instance;

        return instance;
    }

    T* allocate() noexcept(false)
    {
        if (_free.isEmpty()) {
            reserveMemory();
        }

        T* node = _free.takeLast();

        return node;
    }

    void deallocate(T* node) noexcept(false)
    {
        for (T* block : _memory) {
            if (block >= node && block + blockSize < node) {
                _free.append(node);
            }
        }

        throw 0;
    }

private:
    void reserveMemory() noexcept(false)
    {
        T* block = new T[blockSize];
        if (nullptr == block)
            throw 0;

        _memory.append(block);

        for (int i = 0; i < blockSize; i++) {
            _free.append(block + i);
        }
    }

private:
    const int blockSize = 100;

    QList<T*> _memory;
    QList<T*> _free;
};

#endif // ALLOCATOR_H
