#pragma once
#ifndef OHTOAI_SCOPE_GUARD
#define OHTOAI_SCOPE_GUARD

#include <functional>

namespace ohtoai
{
    namespace detail {
        #if __cplusplus >= 202002L
            struct scope_guard {
                std::function<void()>f;
                template<typename Func, typename...Args> requires std::invocable<Func, std::unwrap_reference_t<Args>...>
                scope_guard(Func&& func, Args&&...args) :f{ [func = std::forward<Func>(func), ...args = std::forward<Args>(args)]() mutable {
                        std::invoke(std::forward<std::decay_t<Func>>(func), std::unwrap_reference_t<Args>(std::forward<Args>(args))...);
                    } }{}
                ~scope_guard() { f(); }
                scope_guard(const scope_guard&) = delete;
                scope_guard& operator=(const scope_guard&) = delete;
            };
        #elif __cplusplus >= 201703L
            template<typename F, typename...Args>
            struct scope_guard {
                F f;
                std::tuple<Args...>values;

                template<typename Fn, typename...Ts>
                scope_guard(Fn&& func, Ts&&...args) :f{ std::forward<Fn>(func) }, values{ std::forward<Ts>(args)... } {}
                ~scope_guard() {
                    std::apply(f, values);
                }
                scope_guard(const scope_guard&) = delete;
            };

            template<typename F, typename...Args>//推导指引非常重要
            scope_guard(F&&, Args&&...) -> scope_guard<std::decay_t<F>, std::decay_t<Args>...>;
        #else
            using scope_guard = void;
        #endif // !__cplusplus >= 202002L
    }

    using detail::scope_guard;
} // namespace ohtoai

#endif // !OHTOAI_SCOPE_GUARD
