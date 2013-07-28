#ifndef PROTOC_TRANSENC_IARCHIVE_HPP
#define PROTOC_TRANSENC_IARCHIVE_HPP

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

#include <protoc/transenc/reader.hpp>
#include <protoc/basic_iarchive.hpp>

namespace protoc
{
namespace transenc
{

class iarchive
    : public protoc::basic_iarchive
{
public:
    template <typename Iterator>
    iarchive(Iterator begin, Iterator end);

    virtual void load(bool&);
    virtual void load(int&);
    virtual void load(long long&);
    virtual void load(float&);
    virtual void load(double&);
    virtual void load(std::string&);

    virtual void load_record_begin();
    virtual void load_record_end();
    virtual void load_array_begin();
    virtual void load_array_end();
    virtual bool at_array_end();

    virtual bool load_null();

private:
    transenc::reader reader;
};

} // namespace transenc
} // namespace protoc

BOOST_SERIALIZATION_REGISTER_ARCHIVE(protoc::transenc::iarchive);

#include <sstream>
#include <protoc/exceptions.hpp>

namespace protoc
{
namespace transenc
{

template <typename Iterator>
inline iarchive::iarchive(Iterator begin, Iterator end)
    : reader(begin, end)
{
}

inline void iarchive::load(bool& value)
{
    value = reader.get<bool>();
    reader.next();
}

inline void iarchive::load(int& value)
{
    value = reader.get<int>();
    reader.next();
}

inline void iarchive::load(long long& value)
{
    value = reader.get<long long>();
    reader.next();
}

inline void iarchive::load(float& value)
{
    value = reader.get<float>();
    reader.next();
}

inline void iarchive::load(double& value)
{
    value = reader.get<double>();
    reader.next();
}

inline void iarchive::load(std::string& value)
{
    value = reader.get<std::string>();
    reader.next();
}

inline void iarchive::load_record_begin()
{
    reader.next(reader::token_record_begin);
}

inline void iarchive::load_record_end()
{
    reader.next(reader::token_record_end);
}

inline void iarchive::load_array_begin()
{
    reader.next(reader::token_array_begin);
}

inline void iarchive::load_array_end()
{
    reader.next(reader::token_array_end);
}

inline bool iarchive::at_array_end()
{
    // FIXME: Handle nested containers
    return (reader.type() == reader::token_array_end);
}

inline bool iarchive::load_null()
{
    const bool result = (reader.type() == reader::token_null);
    if (result)
    {
        reader.next();
    }
    return result;
}

} // namespace transenc
} // namespace protoc

#endif // PROTOC_TRANSENC_IARCHIVE_HPP
