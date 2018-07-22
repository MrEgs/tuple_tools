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

#include "conditional.h"

namespace tuple_tools {

/*! Apply a generic function to all members of a tuple
 *
 * If template parameter /Predicate/ is not unconditional, /func/ will only
 * be applied to tuple elements that have a type T fulfilling
 * Predicate<T>::value == true.
 *
 * Example:
 *  - Print all elements to std::cout assuming streaming overloads exist:
 *     for_each(tuple, [](auto&& elem) { std::cout << elem; });
 */
template<template <class...> class Predicate = unconditional, class Tuple, class Func>
void for_each(Tuple& tuple, Func&& func);

template<template <class...> class Predicate = unconditional, class Tuple, class Func>
void for_each(const Tuple& tuple, Func&& func);

// ================================================================================
//  Implementation
// ================================================================================
template<class IdxSeq, template<class...> class Predicate>
struct tuple_for_each
{
    template<class T, class Tuple>
    static void apply_element(const T&, const Tuple&) {}
};


template<size_t I, size_t... Tail, template<class...> class Predicate>
struct tuple_for_each<std::index_sequence<I, Tail...>, Predicate>
{
    using Next = tuple_for_each<std::index_sequence<Tail...>, Predicate>;

    template<class Func, class Tuple>
    static void apply_element(Func& func, Tuple&& tuple)
    {
        using ElementT = std::tuple_element_t<I, std::decay_t<Tuple>>;
        using Condition = Predicate<ElementT>;

        invoke_if<Condition::value>(func, std::get<I>(std::forward<Tuple>(tuple)));

        Next::apply_element(func, tuple);
    }
};


template<template <class...> class Predicate, class Tuple, class Func>
void for_each(Tuple& tuple, Func&& func)
{
    using tuple_indexes = std::make_index_sequence<std::tuple_size<Tuple>::value>;
    tuple_for_each<tuple_indexes, Predicate>::apply_element(func, tuple);
}

template<template <class...> class Predicate, class Tuple, class Func>
void for_each(const Tuple& tuple, Func&& func)
{
    using tuple_indexes = std::make_index_sequence<std::tuple_size<Tuple>::value>;
    tuple_for_each<tuple_indexes, Predicate>::apply_element(func, tuple);
}

} // namespace tuple_tools

#endif // TT_FOR_EACH_H__
