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

#include "predicative_get.h"
#include "bind.h"

using namespace tuple_tools;

struct A { int a = 1; };
struct B { int b = 2; };
struct C { int c = 3; };
struct D { int d = 4; };
struct E : D { int e = 5; };
std::ostream& operator<<(std::ostream& out, const A& a) { return out << "A{a=" << a.a << "}"; }
std::ostream& operator<<(std::ostream& out, const B& b) { return out << "B{b=" << b.b << "}"; }
std::ostream& operator<<(std::ostream& out, const C& c) { return out << "C{c=" << c.c << "}"; }
std::ostream& operator<<(std::ostream& out, const D& d) { return out << "D{d=" << d.d << "}"; }
std::ostream& operator<<(std::ostream& out, const E& e) { return out << "E{e=" << e.e << "}"; }


template<class T, class V>
using is_ptr_vector_of = std::is_base_of<typename T::value_type::element_type, V>;


template<class T, class Tuple>
auto& getStorageFor(Tuple& tuple)
{
    return predicative_get<rbind<is_ptr_vector_of, T>::template type>(tuple);
}

template<class Tuple, class T>
void emplace_back(Tuple& tuple, std::unique_ptr<T>&& ptr)
{
    auto&& vector = getStorageFor<T>(tuple);
    vector.emplace_back(std::move(ptr));
}


int main()
{
    std::tuple<
        std::vector<std::unique_ptr<A>>,
        std::vector<std::unique_ptr<D>>
        > objectStorage;

    emplace_back(objectStorage, std::make_unique<A>());
    emplace_back(objectStorage, std::make_unique<A>());
    emplace_back(objectStorage, std::make_unique<E>());
    emplace_back(objectStorage, std::make_unique<E>());
    emplace_back(objectStorage, std::make_unique<E>());

    std::cout << "num A objects: "
              << std::get<std::vector<std::unique_ptr<A>>>(objectStorage).size()
              << "\n";
    std::cout << "num D objects: "
              << std::get<std::vector<std::unique_ptr<D>>>(objectStorage).size()
              << "\n";


    std::tuple<A, B, C, E, D> tuple;
    std::cout
        << predicative_get<bind<std::is_same, B>::type>(tuple)
        << "\n"
        << predicative_get<bind<std::is_same, C>::type>(tuple)
        << "\n"
        << predicative_get<bind<std::is_base_of, D>::type>(tuple)
        << "\n";

    return 0;
}
