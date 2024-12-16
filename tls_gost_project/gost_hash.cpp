#include "gost_hash.h"
#include <openssl/evp.h>
#include <stdexcept>

GostHash::GostHash() {
    ctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_get_digestbyname("md_gost12_256");
    if (!md) {
        throw std::runtime_error("GOST hash (md_gost12_256) not found");
    }
    if (1 != EVP_DigestInit_ex(ctx, md, NULL)) {
        throw std::runtime_error("Failed to init GOST hash context");
    }
}

GostHash::~GostHash() {
    EVP_MD_CTX_free(ctx);
}

void GostHash::update(const unsigned char* data, size_t len) {
    EVP_DigestUpdate(ctx, data, len);
}

std::vector<unsigned char> GostHash::finalize() {
    unsigned char md[32];
    unsigned int md_len = 0;
    EVP_DigestFinal_ex(ctx, md, &md_len);
    return std::vector<unsigned char>(md, md + md_len);
}
