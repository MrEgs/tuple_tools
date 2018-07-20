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
#include <memory>
#include <vector>
#include <type_traits>

#include "tt_predicative_get.h"
#include "tt_for_each.h"
#include "tt_bind.h"

using namespace tuple_tools;

struct A { int a = 1; };
struct B { int b = 2; };
struct C { int c = 3; };
struct D { int d = 4; };
struct E : D { int e = 5; };
struct F { int f = 5; };

std::ostream& operator<<(std::ostream& out, const A& a) { return out << "A{a=" << a.a << "}"; }
std::ostream& operator<<(std::ostream& out, const B& b) { return out << "B{b=" << b.b << "}"; }
std::ostream& operator<<(std::ostream& out, const C& c) { return out << "C{c=" << c.c << "}"; }
std::ostream& operator<<(std::ostream& out, const D& d) { return out << "D{d=" << d.d << "}"; }
std::ostream& operator<<(std::ostream& out, const E& e) { return out << "E{e=" << e.e << "}"; }


struct Callbacks
{
    void process(const A& a) const {
        std::cout << "Callbacks::process(A) A::a=" << a.a << "\n";
    }
    void process(const C& c) const {
        std::cout << "Callbacks::process(C) C::c=" << c.c << "\n";
    }
};

template<class, class = void>
struct have_callback : std::false_type {};

template<class T>
struct have_callback<T, decltype(Callbacks{}.process(std::declval<T>()))> : std::true_type {};

int main()
{
    std::tuple<A, B, C, E, D> tuple;

    Callbacks callbacks;

    for_each(tuple,
             [](const auto& t)
             {
                 std::cout << t << "\n";
             }
    );

    for_each<have_callback>(
        tuple,
        [&callbacks](const auto& t) {
            callbacks.process(t);
        }
    );

    return 0;
}
