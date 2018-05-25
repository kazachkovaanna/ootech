#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <QTextStreamManipulator>
#include <QDataStream>

template<typename T>
class DataStreamManipulator
{
    typedef QDataStream& (*SMF)(QDataStream&, T);

public:
    DataStreamManipulator(SMF func, T arg) noexcept
        : _funcPtr(func)
        , _arg(arg)
    {
    }

    void exec(QDataStream &stream) noexcept
    {
        if (_funcPtr) {
            _funcPtr(stream, _arg);
        }
    }

private:
    SMF _funcPtr;
    T _arg;
};

template<typename T>
inline QDataStream& operator<<(QDataStream& stream, DataStreamManipulator<T> manipulator) noexcept { manipulator.exec(stream); return stream; }

QDataStream& _setVersion(QDataStream& stream, QDataStream::Version version) noexcept
{
    stream.setVersion(version);
    return stream;
}

QDataStream& _setByteOrder(QDataStream& stream, QDataStream::ByteOrder byteOrder) noexcept
{
    stream.setByteOrder(byteOrder);
    return stream;
}

DataStreamManipulator<QDataStream::Version> setVersion(QDataStream::Version version) noexcept
{
    return DataStreamManipulator<QDataStream::Version>(&_setVersion, version);
}

DataStreamManipulator<QDataStream::ByteOrder> setByteOrder(QDataStream::ByteOrder byteOrder) noexcept
{
    return DataStreamManipulator<QDataStream::ByteOrder>(&_setByteOrder, byteOrder);
}

#endif // MANIPULATOR_H
