#include "manipulator.h"

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
