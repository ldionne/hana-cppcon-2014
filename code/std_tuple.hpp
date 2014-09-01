// Copyright Louis Dionne 2014
// Distributed under the Boost Software License, Version 1.0.

#ifndef STD_TUPLE_HPP
#define STD_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <utility>


//////////////////////////////////////////////////////////////////////////////
// tuple
//////////////////////////////////////////////////////////////////////////////
using std::tuple;
using std::make_tuple;

//////////////////////////////////////////////////////////////////////////////
// get
//////////////////////////////////////////////////////////////////////////////
using std::get;

//////////////////////////////////////////////////////////////////////////////
// transform
//////////////////////////////////////////////////////////////////////////////
template <typename Tuple, typename F, std::size_t ...i>
constexpr decltype(auto) transform_impl(Tuple&& ts, F f, std::index_sequence<i...>) {
    return make_tuple(f(get<i>(std::forward<Tuple>(ts)))...);
}

template <typename Tuple, typename F>
constexpr decltype(auto) transform(Tuple&& ts, F&& f) {
    return transform_impl(
        std::forward<Tuple>(ts),
        std::forward<F>(f),
        std::make_index_sequence<
            std::tuple_size<std::decay_t<Tuple>>::value
        >{}
    );
}

//////////////////////////////////////////////////////////////////////////////
// the proposed C++17 "apply" function
//////////////////////////////////////////////////////////////////////////////
template <typename F, typename Tuple, std::size_t ...i>
constexpr decltype(auto) apply_impl(F&& f, Tuple&& ts, std::index_sequence<i...>) {
    return f(get<i>(std::forward<Tuple>(ts))...);
}

template <typename F, typename Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& ts) {
    return apply_impl(
        std::forward<F>(f),
        std::forward<Tuple>(ts),
        std::make_index_sequence<
            std::tuple_size<std::decay_t<Tuple>>::value
        >{}
    );
}

#endif