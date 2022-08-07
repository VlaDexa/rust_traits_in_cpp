#pragma once
#include <concepts>
#include <type_traits>

#define MakeOperatorConcept(NAME, OPERATOR)                  \
template<typename Self, typename Output, typename Rhs = Self>\
concept NAME = requires(Self lhs, Rhs rhs) {                 \
    {lhs OPERATOR rhs} -> std::same_as<Output>;              \
};                                                           \
                                                             \
template<typename Self, typename Rhs = Self>                 \
concept NAME##Assign = requires(Self &lhs, Rhs rhs) {        \
{lhs OPERATOR##= rhs};                                       \
};

MakeOperatorConcept(Add, +)
MakeOperatorConcept(BitAnd, &)
MakeOperatorConcept(BitOr, |)
MakeOperatorConcept(BitXor, ^)
MakeOperatorConcept(Div, /)
MakeOperatorConcept(Mul, *)
MakeOperatorConcept(Rem, %)
MakeOperatorConcept(Shl, <<)
MakeOperatorConcept(Shr, >>)
MakeOperatorConcept(Sub, -)

template<typename Self, typename Target>
concept Defer = requires(const Self &lhs) {
    {*lhs} -> std::same_as<std::add_lvalue_reference_t<std::add_const_t<Target>>>;
};

template<typename Self, typename Target>
concept DeferMut = requires(Self &lhs) {
    {*lhs} -> std::same_as<std::add_lvalue_reference_t<Target>>;
};

template<typename Self, typename Idx, typename Output>
concept Index = requires(const Self &lhs, Idx idx) {
    {lhs[idx]} -> std::same_as<std::add_lvalue_reference_t<std::add_const_t<Output>>>;
};

template<typename Self, typename Idx, typename Output>
concept IndexMut = requires(Self &lhs, Idx idx) {
    {lhs[idx]} -> std::same_as<std::add_lvalue_reference_t<Output>>;
};

template<typename Self, typename Output>
concept Neg = requires(Self lhs) {
    {-lhs} -> std::same_as<Output>;
};

template<typename Self, typename Output>
concept Not = requires(Self lhs) {
    {!lhs} -> std::same_as<Output>;
};

#undef MakeOperatorConcept
