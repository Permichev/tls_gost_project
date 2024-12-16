#include "hkdf_gost.h"
#include "gost_hash.h"
#include <stdexcept>

// Простейшая имитация HMAC-GOST:
// Для учебного проекта можно упростить, но для реальной криптографии это некорректно.
// Здесь для наглядности: HMAC(key, data) ~ Hash(key || data).

std::vector<unsigned char> HKDF_Gost::hmac_gost(const std::vector<unsigned char>& key, const std::vector<unsigned char>& data) {
    std::vector<unsigned char> combined = key;
    combined.insert(combined.end(), data.begin(), data.end());

    GostHash gh;
    gh.update(combined.data(), combined.size());
    return gh.finalize();
}

HKDF_Gost::HKDF_Gost() {}

std::vector<unsigned char> HKDF_Gost::extract(const std::vector<unsigned char>& salt, const std::vector<unsigned char>& ikm) {
    return hmac_gost(salt, ikm);
}

std::vector<unsigned char> HKDF_Gost::expand(const std::vector<unsigned char>& prk, const std::vector<unsigned char>& info, size_t length) {
    std::vector<unsigned char> okm;
    std::vector<unsigned char> T;
    size_t hash_len = 32;
    size_t n = (length + hash_len - 1) / hash_len;

    for (size_t i = 1; i <= n; i++) {
        std::vector<unsigned char> data(T);
        data.insert(data.end(), info.begin(), info.end());
        data.push_back((unsigned char)i);
        T = hmac_gost(prk, data);
        okm.insert(okm.end(), T.begin(), T.end());
    }
    okm.resize(length);
    return okm;
}
