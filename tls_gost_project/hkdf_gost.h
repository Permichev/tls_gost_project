#pragma once
#include <vector>

class HKDF_Gost {
public:
    HKDF_Gost();
    std::vector<unsigned char> extract(const std::vector<unsigned char>& salt, const std::vector<unsigned char>& ikm);
    std::vector<unsigned char> expand(const std::vector<unsigned char>& prk, const std::vector<unsigned char>& info, size_t length);

private:
    std::vector<unsigned char> hmac_gost(const std::vector<unsigned char>& key, const std::vector<unsigned char>& data);
};
