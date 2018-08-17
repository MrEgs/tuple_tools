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

#include "for_each.h"

#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>

#include "gtest/gtest.h"

#include "bind.h"

namespace {

using namespace tuple_tools;


TEST(for_each, for_each_iota)
{
    std::tuple<int, double, int, double> tuple{0, 0, 0, 0};

    int iota = 0;
    for_each(tuple,
             [&iota](auto& t)
             {
                 t = iota++;
             }
    );

    EXPECT_EQ(std::get<0>(tuple), 0);
    EXPECT_EQ(std::get<1>(tuple), 1);
    EXPECT_EQ(std::get<2>(tuple), 2);
    EXPECT_EQ(std::get<3>(tuple), 3);
}


TEST(for_each, for_each_conditional)
{
    std::tuple<int, double, int, double> tuple{0, 0, 0, 0};

    int iota = 1;
    for_each<bind<std::is_same, int>::type>(tuple,
             [&iota](auto& t)
             {
                 t = iota++;
             }
    );

    EXPECT_EQ(std::get<0>(tuple), 1);
    EXPECT_EQ(std::get<1>(tuple), 0);
    EXPECT_EQ(std::get<2>(tuple), 2);
    EXPECT_EQ(std::get<3>(tuple), 0);
}

} // anonymous namespace
