#ifndef GRAPHEXCEPTION_H
#define GRAPHEXCEPTION_H

#include <QDebug>
#include <QString>

// clang-format off
namespace Sence {
    class Exception;
    class SerializeException;
    class DeserializeException;
    class AllocateException;
    class DeallocateException;
}
// clang-format on

class Sence::Exception {
public:
    Exception(const QString& message) noexcept
        : _message(message)
    {
    }

    inline const QString& toString() const noexcept { return _message; }

protected:
    QString _message;
};

class Sence::SerializeException : public Exception {
public:
    inline SerializeException(const QString& message) noexcept
        : Exception(message)
    {
    }
};

class Sence::DeserializeException : public Exception {
public:
    inline DeserializeException(const QString& message) noexcept
        : Exception(message)
    {
    }
};

class Sence::AllocateException : public Exception {
public:
    inline AllocateException(size_t size, const QString& message) noexcept
        : Exception(message)
        , _size(size)
    {
    }

    inline size_t getSize() const noexcept { return _size; }

protected:
    size_t _size;
};

class Sence::DeallocateException : Exception {
public:
    inline DeallocateException(const void* ptr, const QString& message) noexcept
        : Exception(message)
        , _ptr(ptr)
    {
    }

    inline const void* getPtr() const noexcept { return _ptr; }

protected:
    const void* _ptr;
};

#endif // GRAPHEXCEPTION_H
