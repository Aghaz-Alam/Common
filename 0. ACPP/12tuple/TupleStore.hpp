#pragma once
#include <tuple>
#include <stdexcept>
#include <utility>
#include <cstddef>

template<typename... Ts>
class TupleStore {
    std::tuple<Ts...> data;
    static constexpr std::size_t N = sizeof...(Ts);

public:
    // ------------------------------------------------------
    // Set element at compile-time index I
    // ------------------------------------------------------
    template<std::size_t I, typename U>
    void set(U&& value) {
        static_assert(I < N, "Tuple index out of range");
        std::get<I>(data) = std::forward<U>(value);
    }

    // ------------------------------------------------------
    // Get element at compile-time index I
    // ------------------------------------------------------
    template<std::size_t I>
    const auto& get() const {
        static_assert(I < N, "Tuple index out of range");
        return std::get<I>(data);
    }

    // ------------------------------------------------------
    // Remove element (reset to default value)
    // ------------------------------------------------------
    template<std::size_t I>
    void remove() {
        static_assert(I < N, "Tuple index out of range");
        std::get<I>(data) = typename std::tuple_element<I, std::tuple<Ts...>>::type{};
    }

    // ------------------------------------------------------
    // Check if index exists (always true if valid)
    // ------------------------------------------------------
    template<std::size_t I>
    bool exists() const {
        static_assert(I < N, "Tuple index out of range");
        return true;
    }

    // ------------------------------------------------------
    // Get total size of the tuple
    // ------------------------------------------------------
    static constexpr std::size_t size() { return N; }

    // ------------------------------------------------------
    // Clear all elements
    // ------------------------------------------------------
    void clear() {
        clear_impl(std::make_index_sequence<N>{});
    }

private:
    template<std::size_t... Is>
    void clear_impl(std::index_sequence<Is...>) {
        ((std::get<Is>(data) = typename std::tuple_element<Is, std::tuple<Ts...>>::type{}), ...);
    }
};
