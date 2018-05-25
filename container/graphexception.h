#ifndef GRAPHEXCEPTION_H
#define GRAPHEXCEPTION_H

#include <stdexcept>
#include <QString>
#include <QDebug>

class Exception {
public:
    Exception(const QString& message) noexcept
        : _message(message)
    {
    }

    inline const QString& toString() const noexcept { return _message; }

protected:
    QString _message;
};

class SerializeException : public Exception
{
public:
    inline SerializeException(const QString& message) noexcept
        : Exception(message)
    {
    }
};

class DeserializeException : public Exception
{
public:
    inline DeserializeException(const QString& message) noexcept
        : Exception(message)
    {
    }
};

class AllocateException : public Exception
{
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

class DeallocateException : Exception
{
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
