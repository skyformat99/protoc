#ifndef PROTOC_MSGPACK_DETAIL_TOKEN_HPP
#define PROTOC_MSGPACK_DETAIL_TOKEN_HPP

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

namespace protoc
{
namespace msgpack
{
namespace detail
{

enum token
{
    token_eof,
    token_error,

    token_null,
    token_true,
    token_false,

    token_int8,
    token_int16,
    token_int32,
    token_int64,

    token_uint8,
    token_uint16,
    token_uint32,
    token_uint64,

    token_float32,
    token_float64,

    token_str8,
    token_str16,
    token_str32,

    token_bin8,
    token_bin16,
    token_bin32,

    token_array8,
    token_array16,
    token_array32,

    token_map8,
    token_map16,
    token_map32
};

} // namespace detail
} // namespace msgpack
} // namespace protoc

#endif /* PROTOC_MSGPACK_DETAIL_TOKEN_HPP */
