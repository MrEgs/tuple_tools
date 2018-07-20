# Tuple Tools
Tuple Tools is a utility library for std::tuple. Currently, it provides two functions to interact more conveniently with std::tuple:
 - tuple_tools::predicative_get() allows to get a tuple elemens according to a type predicate
 - tuple_tools::for_each() applies a function to all tuple elements. Elements can be filtered by an optional predicate
 
## Examples
Print all elements in a tuple
 
 ```c++
std::tuple<int, double, std::complex<double>> tuple = {3, 3.14, {1,2}};

// prints: 3 3.14 (1,2)
tuple_tools::for_each(tuple, [](auto&& t) {

    std::cout << t << " ";
        
});
```
 
Use a tuple to store vectors of unique_ptrs. Use tuple_tools::predicative_get() to retrive the vector capable of storing instances of derived classes.
```c++
struct A{}; struct B{}; struct C : B {}; struct D : B {};

template<class T>
using is_base_of_d = std::is_base_of<typename T::value_type::element_type, D>;

int main()
{
    std::tuple<
        std::vector<std::unique_ptr<A>>,
        std::vector<std::unique_ptr<B>>
        > objectStorage;

    auto&& vector = tuple_tools::predicative_get<is_base_of_d>(objectStorage);
    vector.emplace_back(std::make_unique<D>());

}

```

For more complex examples, see tt_for_each_test.cpp and tt_predicative_get_test.cpp.
