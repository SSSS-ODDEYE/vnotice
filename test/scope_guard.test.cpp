#include <scope_guard.hpp>
#include <catch2/catch_test_macros.hpp>
#include <atomic>

struct X {
};

TEST_CASE("Scope Guard") {
    using ohtoai::scope_guard;
    SECTION("C pointer can be support by RAII") {
        FILE *fp = nullptr;
        std::atomic_bool guard_called{false};
        const std::string exception_str = "Test";
        const std::string file_name = "test.txt";
        try{
            fp = fopen(file_name.c_str() ,"a");
            auto guard = scope_guard([&] {
                fclose(fp);
                fp = nullptr;
                guard_called = true;
                remove(file_name.c_str());
            });
            throw std::runtime_error{exception_str};
        }
        catch(std::exception & e){
            REQUIRE(e.what() == exception_str);
        }
        REQUIRE(guard_called);
        REQUIRE(fp == nullptr);
    }
    SECTION("Support functional object call") {
        std::atomic_bool guard_called{false};
        struct release_helper {
            std::atomic_bool& guard_called;
            release_helper(std::atomic_bool& guard_called) : guard_called{guard_called} {}
            void operator()(X* x) {
                guard_called = true;
                delete x;
            }
        } t(guard_called);
        auto x = new X{};
        {
            auto guard = scope_guard(t, x);
        }
        REQUIRE(guard_called);
    }

    SECTION("Support member funciton and std::ref") {
        std::atomic_bool guard_called{false};
        struct release_helper {
            std::atomic_bool& guard_called;
            release_helper(std::atomic_bool& guard_called) : guard_called{guard_called} {}
            void f(X*& px) {
                guard_called = true;
                delete px;
                px = nullptr;
            }
        } t(guard_called);
        auto x = new X{};
        {
            auto guard = scope_guard{&release_helper::f, &t, std::ref(x)};
        }
        REQUIRE(guard_called);
        REQUIRE(x == nullptr);
    }
}