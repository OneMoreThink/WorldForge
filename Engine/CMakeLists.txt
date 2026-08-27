# "Engine" 이라는 이름의 라이브러리 생성
add_library(Engine STATIC
    Core/Engine.cpp
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(Engine PUBLIC cxx_std_23)
