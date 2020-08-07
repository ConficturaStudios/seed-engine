/**
 * CommonTraits.hpp
 * 
 * @copyright Copyright (c) 2020 Confictura Studios. All rights reserved.
 * @license This code is released under the MIT License.
 * 
 * This code is distributed as part of the Seed Engine project.
 * 
 * For a copy of the license, please go to https://github.com/conficturastudios/seed-engine/LICENSE
 */

#ifndef SEEDENGINE_INCLUDE_RUNTIME_COMMON_COMMON_TRAITS_H_
#define SEEDENGINE_INCLUDE_RUNTIME_COMMON_COMMON_TRAITS_H_

#include "CommonAPI.hpp"
#include <type_traits>

namespace seedengine {

    
    // Compile Time Traits

    template < template <typename...> class Base, typename Derived>
    struct is_base_of_t_impl
    {
        template<typename... T>
        static constexpr std::true_type  check(const Base<T...>*);
        static constexpr std::false_type check(...);
        using type = decltype(check(std::declval<Derived*>()));
    };

    template < template <typename...> class Base, typename Derived>
    using is_base_of_t = typename is_base_of_t_impl<Base, Derived>::type;


    template<typename T>
    struct is_numeric {
        public:
            static constexpr const bool value = std::is_integral<T>::value || std::is_floating_point<T>::value;
    };

    
    template<typename Base, typename... Types>
    struct is_base_of_all;

    template<typename Base, typename First, typename...Types>
    struct is_base_of_all<Base, First, Types...> {
        public:
            static constexpr const bool value = std::is_base_of<Base, First>::value && is_base_of_all<Base, Types...>::value;
    };

    template<typename Base, typename Last>
    struct is_base_of_all<Base, Last> {
        public:
            static constexpr const bool value = std::is_base_of<Base, Last>::value;
    };

}

#endif