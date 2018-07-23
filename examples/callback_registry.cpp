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
#include <functional>
#include <vector>

#include "tuple_tools/bind.h"
#include "tuple_tools/predicative_get.h"
#include "tuple_tools/for_each.h"

using namespace tuple_tools;

struct A
{
    int value {0};
};

std::ostream& operator<<(std::ostream& out, const A& a)
{
    return out << "A{" << a.value << "}";
}


struct CallbackRegistry
{
    template<typename T>
    using Callback = std::function<void(T)>;

    template<typename T>
    void RegisterCallback(Callback<T>&& callback)
    {
        GetCallbacks<T>().emplace_back(std::move(callback));
    }

    template<typename T>
    void OnData(const T& t)
    {
        for (auto&& callback : GetCallbacks<T>())
        {
            callback(t);
        }
    }

private:
    // Predicate to identify a callback vector by argument type
    template<typename T, typename V>
    struct is_callback_vector : std::false_type {};

    template<typename T, typename V>
    struct is_callback_vector<std::vector<Callback<T>>, V> : std::is_same<T, V> {};

    // Friendly wrapper around predicative_get to get a vector of callbacks
    template<typename T>
    auto GetCallbacks() -> std::vector<Callback<T>>&
    {
        return predicative_get<
            rbind<is_callback_vector, T>::template type
            >(_callbacks);
    }

private:
    // Actual callback registry
    std::tuple<
        std::vector<Callback<int>>,
        std::vector<Callback<double>>,
        std::vector<Callback<A>>
        > _callbacks;
};

int main()
{
    CallbackRegistry callbacks;

    callbacks.RegisterCallback<A>(
        [](A a) {
            std::cout << "A callback: a=" << a << "\n";
        });
    callbacks.RegisterCallback<int>(
        [](int i) {
            std::cout << "int callback #1: i=" << i << "\n";
        });
    callbacks.RegisterCallback<int>(
        [](int i) {
            std::cout << "int callback #2: i=" << i << "\n";
        });
    callbacks.RegisterCallback<double>(
        [](double d) {
            std::cout << "double callback: d=" << d << "\n";
        });


    // combined with a tuple and for_each
    auto tuple = std::make_tuple(3, 5, 3.14, A{});

    for_each(tuple,
        [&callbacks](auto&& t)
        {
            callbacks.OnData(t);
        }
    );

    return 0;
}
