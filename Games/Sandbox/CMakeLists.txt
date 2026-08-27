# "Sandbox" 이라는 이름의 실행 파일 생성
add_executable(Sandbox main.cpp)

# "Sandbox" 실행 파일이 "Engine" 라이브러리를 사용할 수 있도록 링크
target_link_libraries(Sandbox PRIVATE Engine)
