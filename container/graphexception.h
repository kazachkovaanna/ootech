#ifndef GRAPHEXCEPTION_H
#define GRAPHEXCEPTION_H

#include <stdexcept>
#include <QString>
#include <QDebug>

class RuntimeException : protected std::runtime_error
{
public:
    RuntimeException(const QString& message);

    inline QString toString() const { return what(); }
};

class SerializeException : public RuntimeException
{
public:
    SerializeException(const QString& message)
        : RuntimeException(message)
    {
    }
};

class DeserializeException : public RuntimeException
{
public:
    DeserializeException(const QString& message)
        : RuntimeException(message)
    {
    }
};

class AllocateException : public RuntimeException
{
public:
    AllocateException();
};

class DeallocateException
{
public:
    DeallocateException();
};

#endif // GRAPHEXCEPTION_H
