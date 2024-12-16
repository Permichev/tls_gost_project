#pragma once
#include <vector>
#include <openssl/evp.h>

class GostHash {
public:
    GostHash();
    ~GostHash();
    void update(const unsigned char* data, size_t len);
    std::vector<unsigned char> finalize();

private:
    EVP_MD_CTX* ctx; // используем EVP_MD_CTX напрямую, без forward declaration
};
