///////////////////////////////////////////////////////////////////////////////
//
// http://protoc.sourceforge.net/
//
// Copyright (C) 2013 Bjorn Reese <breese@users.sourceforge.net>
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
// MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE AUTHORS AND
// CONTRIBUTORS ACCEPT NO RESPONSIBILITY IN ANY CONCEIVABLE MANNER.
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <protoc/transenc/codes.hpp>
#include <protoc/transenc/encoder.hpp>

namespace protoc
{
namespace transenc
{

encoder::encoder(output& buffer)
    : buffer(buffer)
{
};

std::size_t encoder::put()
{
    return put_token(code_null);
}

std::size_t encoder::put(bool value)
{
    return put_token((value) ? code_true : code_false);
}

std::size_t encoder::put(protoc::int8_t value)
{
    if (value >= -32)
    {
        const std::size_t size = sizeof(output::value_type);

        if (!buffer.grow(size))
        {
            return 0;
        }

        write(value);
        return size;
    }
    else
    {
        const output::value_type type(code_int8);
        const std::size_t size = sizeof(type) + sizeof(protoc::int8_t);

        if (!buffer.grow(size))
        {
            return 0;
        }

        buffer.write(type);
        write(value);
        return size;
    }
}

std::size_t encoder::put(protoc::int16_t value)
{
    const output::value_type type(code_int16);
    const std::size_t size = sizeof(type) + sizeof(protoc::int16_t);

    if (!buffer.grow(size))
    {
        return 0;
    }

    buffer.write(type);
    write(value);

    return size;
}

std::size_t encoder::put(protoc::int32_t value)
{
    const output::value_type type(code_int32);
    const std::size_t size = sizeof(type) + sizeof(protoc::int32_t);

    if (!buffer.grow(size))
    {
        return 0;
    }

    buffer.write(type);
    write(value);

    return size;
}

std::size_t encoder::put(protoc::int64_t value)
{
    const output::value_type type(code_int64);
    const std::size_t size = sizeof(type) + sizeof(protoc::int64_t);

    if (!buffer.grow(size))
    {
        return 0;
    }

    buffer.write(type);
    write(value);

    return size;
}

std::size_t encoder::put(protoc::float32_t value)
{
    const output::value_type type(code_float32);
    const std::size_t size = sizeof(type) + sizeof(protoc::float32_t);

    if (!buffer.grow(size))
    {
        return 0;
    }

    buffer.write(type);
    // IEEE 754 single precision
    const protoc::int32_t endian = 0x03020100;
    protoc::int8_t *value_buffer = (protoc::int8_t *)&value;
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[0]]));
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[1]]));
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[2]]));
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[3]]));

    return size;
}

std::size_t encoder::put(protoc::float64_t value)
{
    const output::value_type type(code_float64);
    const std::size_t size = sizeof(type) + sizeof(protoc::float64_t);

    if (!buffer.grow(size))
    {
        return 0;
    }

    buffer.write(type);
    // IEEE 754 double precision
    const protoc::int64_t endian = 0x0706050403020100;
    protoc::int8_t *value_buffer = (protoc::int8_t *)&value;
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[0]]));
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[1]]));
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[2]]));
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[3]]));
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[4]]));
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[5]]));
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[6]]));
    buffer.write(static_cast<output::value_type>(value_buffer[((protoc::int8_t *)&endian)[7]]));

    return size;
}

std::size_t encoder::put(const char *value)
{
    return put(std::string(value));
}

std::size_t encoder::put(const std::string& value)
{
    const std::string::size_type length = value.size();

    std::size_t size = 0;

    if (length < static_cast<std::string::size_type>(std::numeric_limits<protoc::uint8_t>::max()))
    {
        if (!buffer.grow(sizeof(output::value_type) + sizeof(protoc::uint8_t) + length))
        {
            return 0;
        }
        buffer.write(code_string_int8);
        size = write(static_cast<uint8_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<protoc::uint16_t>::max()))
    {
        if (!buffer.grow(sizeof(output::value_type) + sizeof(protoc::uint16_t) + length))
        {
            return 0;
        }
        buffer.write(code_string_int16);
        size = write(static_cast<uint16_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<protoc::uint32_t>::max()))
    {
        if (!buffer.grow(sizeof(output::value_type) + sizeof(protoc::uint32_t) + length))
        {
            return 0;
        }
        buffer.write(code_string_int32);
        size = write(static_cast<uint32_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<protoc::int64_t>::max()))
    {
        if (!buffer.grow(sizeof(output::value_type) + sizeof(protoc::int64_t) + length))
        {
            return 0;
        }
        buffer.write(code_string_int64);
        size = write(static_cast<int64_t>(length));
    }
    else
    {
        return 0;
    }

    for (std::string::const_iterator it = value.begin(); it != value.end(); ++it)
    {
        buffer.write(*it);
    }

    return sizeof(output::value_type) + size + length;
}

std::size_t encoder::put(const std::vector<protoc::int8_t>& value)
{
    const std::string::size_type length = value.size();

    std::size_t size = 0;

    if (length < static_cast<std::string::size_type>(std::numeric_limits<protoc::int8_t>::max()))
    {
        if (!buffer.grow(sizeof(output::value_type) + sizeof(protoc::int8_t) + length))
        {
            return 0;
        }
        buffer.write(code_binary_int8);
        size = write(static_cast<int8_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<protoc::int16_t>::max()))
    {
        if (!buffer.grow(sizeof(output::value_type) + sizeof(protoc::int16_t) + length))
        {
            return 0;
        }
        buffer.write(code_binary_int16);
        size = write(static_cast<int16_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<protoc::int32_t>::max()))
    {
        if (!buffer.grow(sizeof(output::value_type) + sizeof(protoc::int32_t) + length))
        {
            return 0;
        }
        buffer.write(code_binary_int32);
        size = write(static_cast<int32_t>(length));
    }
    else
    {
        if (!buffer.grow(sizeof(output::value_type) + sizeof(protoc::int64_t) + length))
        {
            return 0;
        }
        buffer.write(code_binary_int64);
        size = write(static_cast<int64_t>(length));
    }

    for (std::vector<protoc::int8_t>::const_iterator it = value.begin(); it != value.end(); ++it)
    {
        buffer.write(*it);
    }

    return sizeof(output::value_type) + size + length;
}

std::size_t encoder::put_tuple_begin()
{
    return put_token(code_tuple_begin);
}

std::size_t encoder::put_tuple_end()
{
    return put_token(code_tuple_end);
}

std::size_t encoder::put_array_begin()
{
    return put_token(code_array_begin);
}

std::size_t encoder::put_array_end()
{
    return put_token(code_array_end);
}

std::size_t encoder::put_token(output::value_type value)
{
    const std::size_t size = sizeof(value);

    if (!buffer.grow(size))
    {
        return 0;
    }

    buffer.write(value);

    return size;
}

std::size_t encoder::write(protoc::int8_t value)
{
    buffer.write(static_cast<output::value_type>(value));
    return sizeof(protoc::int8_t);
}

std::size_t encoder::write(protoc::uint8_t value)
{
    buffer.write(static_cast<output::value_type>(value));
    return sizeof(protoc::uint8_t);
}

std::size_t encoder::write(protoc::int16_t value)
{
    buffer.write(static_cast<output::value_type>(value & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 8) & 0xFF));
    return sizeof(protoc::int16_t);
}

std::size_t encoder::write(protoc::uint16_t value)
{
    buffer.write(static_cast<output::value_type>(value & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 8) & 0xFF));
    return sizeof(protoc::uint16_t);
}

std::size_t encoder::write(protoc::int32_t value)
{
    buffer.write(static_cast<output::value_type>(value & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 8) & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 16) & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 24) & 0xFF));
    return sizeof(protoc::int32_t);
}

std::size_t encoder::write(protoc::uint32_t value)
{
    buffer.write(static_cast<output::value_type>(value & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 8) & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 16) & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 24) & 0xFF));
    return sizeof(protoc::uint32_t);
}

std::size_t encoder::write(protoc::int64_t value)
{
    buffer.write(static_cast<output::value_type>(value & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 8) & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 16) & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 24) & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 32) & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 40) & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 48) & 0xFF));
    buffer.write(static_cast<output::value_type>((value >> 54) & 0xFF));
    return sizeof(protoc::int64_t);
}

} // namespace transenc
} // namespace protoc
