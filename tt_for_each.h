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

#ifndef TT_FOR_EACH_H__
#define TT_FOR_EACH_H__

#include <tuple>

namespace tuple_tools {

template<bool = false>
struct conditional
{
    template<class Func, class... Arg>
    inline static void invoke(Func&, Arg&&...) {};
};

template<>
struct conditional<true>
{
    template<class Func, class... Arg>
    inline static void invoke(Func& func, Arg&&... arg) { func(std::forward<Arg>(arg)...); };
};


template<class, template<class> class>
struct tuple_for_each
{
    template<class Tuple, class T>
    static void invoke(const Tuple&, const T&) {}
};


template<size_t I, size_t... Tail, template<class> class Cond>
struct tuple_for_each<std::index_sequence<I, Tail...>, Cond>
{
    using Next = tuple_for_each<std::index_sequence<Tail...>, Cond>;

    template<class Tuple, class Func>
    static void invoke(const Tuple& tuple, Func& func)
    {
        using Condition = Cond<typename std::tuple_element<I, Tuple>::type>;

        conditional<Condition::value>::invoke(func, std::get<I>(tuple));

        Next::invoke(tuple, func);
    }
};


template<class T>
using always = std::true_type;

template<template <class> class Cond = always, class Func, class... TupleT>
void for_each(const std::tuple<TupleT...>& tuple, Func&& func)
{
    using tuple_indexes = std::index_sequence_for<TupleT...>;
    tuple_for_each<tuple_indexes, Cond>::invoke(tuple, func);
}

} // namespace tuple_tools

#endif // TT_FOR_EACH_H__
