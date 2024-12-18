#pragma once
#include <vector>

class KeySchedule {
public:
    KeySchedule();
    void computeEarlySecret(const std::vector<unsigned char>& psk);
    void computeHandshakeSecret(const std::vector<unsigned char>& shared_secret);
    void computeMasterSecret(const std::vector<unsigned char>& context);

    std::vector<unsigned char> getEarlySecret() const { return early_secret; }
    std::vector<unsigned char> getHandshakeSecret() const { return handshake_secret; }
    std::vector<unsigned char> getMasterSecret() const { return master_secret; }

private:
    std::vector<unsigned char> early_secret;
    std::vector<unsigned char> handshake_secret;
    std::vector<unsigned char> master_secret;
};
