cmake_minimum_required(VERSION 3.14)

project(TCPEncryptedServer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TCPEncryptedServer
  main.cpp
  src/cipher.cpp
  src/base64.cpp
  include/cipher.h
  include/base64.h
)

include_directories(include)

target_link_libraries(TCPEncryptedServer /usr/lib64/libssl.so /usr/lib64/libcrypto.so)
