///////////////////////////////////////////////////////////////////////////////
//
// http://protoc.sourceforge.net/
//
// Copyright (C) 2013 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/test/unit_test.hpp>

#include <sstream>
#include <limits>
#include <protoc/exceptions.hpp>
#include <protoc/json/oarchive.hpp>

using namespace protoc;

BOOST_AUTO_TEST_SUITE(json_oarchive_suite)

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    std::ostringstream result;
    json::oarchive ar(result);
    BOOST_REQUIRE_EQUAL(result.str().data(), "");
}

BOOST_AUTO_TEST_CASE(test_false)
{
    std::ostringstream result;
    json::oarchive out(result);
    bool value = false;
    out << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "false");
}

BOOST_AUTO_TEST_CASE(test_const_false)
{
    std::ostringstream result;
    json::oarchive out(result);
    const bool value = false;
    out << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "false");
}

BOOST_AUTO_TEST_CASE(test_true)
{
    std::ostringstream result;
    json::oarchive out(result);
    bool value = true;
    out << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "true");
}

BOOST_AUTO_TEST_CASE(test_const_true)
{
    std::ostringstream result;
    json::oarchive out(result);
    const bool value = true;
    out << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "true");
}

//-----------------------------------------------------------------------------
// Integers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int_zero)
{
    std::ostringstream result;
    json::oarchive ar(result);
    int value = 0;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "0");
}

BOOST_AUTO_TEST_CASE(test_const_int_zero)
{
    std::ostringstream result;
    json::oarchive ar(result);
    const int value = 0;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "0");
}

BOOST_AUTO_TEST_CASE(test_int_one)
{
    std::ostringstream result;
    json::oarchive ar(result);
    int value = 1;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "1");
}

BOOST_AUTO_TEST_CASE(test_int_minus_one)
{
    std::ostringstream result;
    json::oarchive ar(result);
    int value = -1;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "-1");
}

//-----------------------------------------------------------------------------
// Float
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_double_one)
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = 1.0;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "1");
}

BOOST_AUTO_TEST_CASE(test_const_double_one)
{
    std::ostringstream result;
    json::oarchive ar(result);
    const double value = 1.0;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "1");
}

BOOST_AUTO_TEST_CASE(test_double_half)
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = 0.5;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "0.5");
}

BOOST_AUTO_TEST_CASE(test_double_max)
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = std::numeric_limits<double>::max();
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "1.7976931348623157e+308");
}

BOOST_AUTO_TEST_CASE(test_double_min)
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = std::numeric_limits<double>::min();
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "2.2250738585072014e-308");
}

BOOST_AUTO_TEST_CASE(test_double_infinity)
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = std::numeric_limits<double>::infinity();
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "null");
}

BOOST_AUTO_TEST_CASE(test_double_minus_infinity)
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = -std::numeric_limits<double>::infinity();
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "null");
}

BOOST_AUTO_TEST_CASE(test_double_nan)
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = std::numeric_limits<double>::quiet_NaN();
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "null");
}

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::string value("");
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\"");
}

BOOST_AUTO_TEST_CASE(test_const_string_empty)
{
    std::ostringstream result;
    json::oarchive ar(result);
    const std::string value("");
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_alpha)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::string value("alpha");
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"alpha\"");
}

//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_array_bool_empty)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::vector<bool> value;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "[]");
}

BOOST_AUTO_TEST_CASE(test_array_bool_one)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::vector<bool> value;
    value.push_back(true);
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "[true]");
}

BOOST_AUTO_TEST_CASE(test_array_bool_two)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::vector<bool> value;
    value.push_back(true);
    value.push_back(false);
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "[true,false]");
}

BOOST_AUTO_TEST_CASE(test_object_bool_empty)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<std::string, bool> value;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "{}");
}

BOOST_AUTO_TEST_CASE(test_object_bool_one)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<std::string, bool> value;
    value["A"] = true;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "{\"A\":true}");
}

BOOST_AUTO_TEST_CASE(test_object_bool_two)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<std::string, bool> value;
    value["A"] = true;
    value["B"] = false;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "{\"A\":true,\"B\":false}");
}

BOOST_AUTO_TEST_CASE(test_nonobject_bool_empty)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<int, bool> value;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "[]");
}

BOOST_AUTO_TEST_CASE(test_nonobject_bool_one)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<int, bool> value;
    value[2] = true;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "[[2,true]]");
}

BOOST_AUTO_TEST_CASE(test_nonobject_bool_two)
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<int, bool> value;
    value[2] = true;
    value[4] = false;
    ar << boost::serialization::make_nvp("value", value);
    BOOST_REQUIRE_EQUAL(result.str().data(), "[[2,true],[4,false]]");
}

BOOST_AUTO_TEST_SUITE_END()
