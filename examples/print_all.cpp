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

#include <iostream>

#include "tuple_tools/for_each.h"

using namespace tuple_tools;

struct A { int value = 1; };
struct B { int value = 2; };
struct C { int value = 3; };


std::ostream& operator<<(std::ostream& out, const A& a) { return out << "A{value=" << a.value << "}"; }
std::ostream& operator<<(std::ostream& out, const B& b) { return out << "B{value=" << b.value << "}"; }
std::ostream& operator<<(std::ostream& out, const C& c) { return out << "C{value=" << c.value << "}"; }

int main()
{
    std::tuple<A, B, C, A, B, C> tuple;

    int iota = 1;
    for_each(tuple,
             [&iota](auto& t)
             {
                 t.value = iota++;
             }
    );



    for_each(tuple,
             [](const auto& t)
             {
                 std::cout << t << "\n";
             }
    );


    return 0;
}
