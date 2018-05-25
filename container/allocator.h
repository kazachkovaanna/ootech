#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <QList>

#include "graphexception.h"

namespace Sence {
// clang-format off
    template<typename T> class GraphAllocator;
// clang-format on
}

template<typename T>
class Sence::GraphAllocator {
private:
    GraphAllocator() noexcept
    {
    }

    ~GraphAllocator() noexcept
    {
        for (T* block : _memory) {
            delete[] block;
        }

        _memory.clear();
        _free.clear();
    }

    GraphAllocator(const Sence::GraphAllocator<T>&) = delete;
    GraphAllocator& operator=(const Sence::GraphAllocator<T>&) = delete;

public:
    static GraphAllocator& instance() noexcept
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

        throw new DeallocateException(node, QString("Can't deallocate the node: [%1].").arg(node->getUuid()));
    }

private:
    void reserveMemory() noexcept(false)
    {
        try {
            T* block = new T[blockSize];

            _memory.append(block);

            for (int i = 0; i < blockSize; i++) {
                _free.append(block + i);
            }
        } catch (std::bad_alloc& e) {
            qDebug() << Q_FUNC_INFO << e.what();
            throw new AllocateException(sizeof(T), QString("Can't allocate"));
        }
    }

private:
    const int blockSize = 1000;

    QList<T*> _memory;
    QList<T*> _free;
};

#endif // ALLOCATOR_H
