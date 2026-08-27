# CMake 최소 요구 버전 설정
cmake_minimum_required(VERSION 3.20)

# 프로젝트 이름과 언어 설정
project(WorldForge LANGUAGES CXX)

# 서브디렉토리 추가 (폴더 안의 CMakeLists.txt들 가서 읽고 와)
add_subdirectory(Engine)
add_subdirectory(Games/Sandbox)
