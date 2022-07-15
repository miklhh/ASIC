/*
 * Traits for different types
 */

#ifndef _TRAIT_H
#define _TRAIT_H

#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

//
// Traits for Associative Arrays (is exactly std::map or std::unordered_map)
//
template <class... T>
struct is_associative_array_type : std::false_type {};

template <class... T>
struct is_associative_array_type<std::map<T...>> : std::true_type {};

template <class... T>
struct is_associative_array_type<std::unordered_map<T...>> : std::true_type {};

//
// Trait for Sets (is exactly std::set or std::unordered_set)
//
template <class... T>
struct is_set_type : std::false_type {};

template <class... T>
struct is_set_type<std::set<T...>> : std::true_type {};

template <class... T>
struct is_set_type<std::unordered_set<T...>> : std::true_type {};

#endif
