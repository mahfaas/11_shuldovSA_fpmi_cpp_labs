add_executable(mersenne_boost_tests mersenne_boost_tests.cpp)

target_include_directories(mersenne_boost_tests PRIVATE
    "C:/Users/Stanislau/vcpkg/installed/x64-mingw-static/include"
)

target_link_libraries(mersenne_boost_tests PRIVATE mersenne_lib)

add_test(NAME MersenneBoostTest COMMAND mersenne_boost_tests)
