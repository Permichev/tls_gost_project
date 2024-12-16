cmake_minimum_required(VERSION 3.20)
project(tls_gost_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к установленному OpenSSL (под macOS с Homebrew)
set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl@3")
include_directories("${OPENSSL_ROOT_DIR}/include")

add_executable(tls_gost_project
        main.cpp
        gost_hash.cpp
        gost_hash.h
        hkdf_gost.cpp
        hkdf_gost.h
        key_schedule.cpp
        key_schedule.h
)

target_link_libraries(tls_gost_project
        "${OPENSSL_ROOT_DIR}/lib/libcrypto.dylib"
        "${OPENSSL_ROOT_DIR}/lib/libssl.dylib"
)

