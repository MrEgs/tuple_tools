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

#ifndef TT_CONDITIONAL_H
#define TT_CONDITIONAL_H

namespace tuple_tools {

template<class T>
using unconditional = std::true_type;

template<bool predicate, class Func, class... Arg>
constexpr void invoke_if(Func&& func, Arg&&... element);

// ================================================================================
//  Implementation
// ================================================================================
template<bool = false>
struct conditional
{
    template<class Func, class... Arg>
    constexpr static void invoke(Func&&, Arg&&...) {}
};

template<>
struct conditional<true>
{
    template<class Func, class... Arg>
    constexpr static void invoke(Func&& func, Arg&&... arg) { func(std::forward<Arg>(arg)...); }
};

template<bool predicate, class Func, class... Arg>
constexpr void invoke_if(Func&& func, Arg&&... element)
{
    conditional<predicate>::invoke(std::forward<Func>(func), std::forward<Arg>(element)...);
}

} //namespace tuple_tools


#endif // TT_CONDITIONAL_H
