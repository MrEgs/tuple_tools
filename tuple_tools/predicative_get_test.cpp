/*******************************************************************************
  MIT License

  Copyright (c) 2018 Marcus Eggenberger

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*******************************************************************************/

#include "predicative_get.h"

#include <iostream>
#include <memory>
#include <vector>

#include "gtest/gtest.h"

#include "bind.h"


namespace {

using namespace tuple_tools;


template<class T, class V>
struct is_base_ptr_of
     : std::false_type {};

template<class T, class V>
struct is_base_ptr_of<std::unique_ptr<T>, V>
     : std::is_base_of<T, V> {};


TEST(predicative_get, get_by_base_ptr)
{
    struct A {};
    struct B {};
    struct C {};
    struct D :  B {};

    std::tuple<
        std::unique_ptr<A>,
        std::unique_ptr<B>
        > tuple;

    auto&& a_ptr = predicative_get<rbind<is_base_ptr_of, A>::type>(tuple);
    EXPECT_EQ(a_ptr, std::get<std::unique_ptr<A>>(tuple));

    auto&& d_ptr = predicative_get<rbind<is_base_ptr_of, D>::type>(tuple);
    EXPECT_EQ(d_ptr, std::get<std::unique_ptr<B>>(tuple));
}


} // anonymous namespace
