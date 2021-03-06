#ifndef PROTOC_WRITER_HPP
#define PROTOC_WRITER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// http://protoc.sourceforge.net/
//
// Copyright (C) 2014 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t
#include <string>
#include <boost/range/iterator_range.hpp>

namespace protoc
{

class writer
{
public:
    typedef unsigned char value_type;
    typedef std::size_t size_type;

    virtual ~writer() {}

    virtual size_type size() = 0;

    virtual size_type write() = 0; // Null
    virtual size_type write(bool) = 0;
    virtual size_type write(int) = 0;
    virtual size_type write(long long) = 0;
    virtual size_type write(float) = 0;
    virtual size_type write(double) = 0;
    virtual size_type write(const char *) = 0;
    virtual size_type write(const std::string&) = 0;
    virtual size_type write(const value_type *, size_type) = 0;

    virtual size_type record_begin() = 0;
    virtual size_type record_end() = 0;

    virtual size_type array_begin() = 0;
    virtual size_type array_begin(size_type count) = 0;
    virtual size_type array_end() = 0;

    virtual size_type map_begin() = 0;
    virtual size_type map_begin(size_type count) = 0;
    virtual size_type map_end() = 0;
};

} // namespace protoc

#endif // PROTOC_WRITER_HPP
