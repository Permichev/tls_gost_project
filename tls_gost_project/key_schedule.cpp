#include "key_schedule.h"
#include "hkdf_gost.h"

KeySchedule::KeySchedule() {}

void KeySchedule::computeEarlySecret(const std::vector<unsigned char>& psk) {
    HKDF_Gost hkdf;
    std::vector<unsigned char> salt; // Пустой salt
    early_secret = hkdf.extract(salt, psk);
}

void KeySchedule::computeHandshakeSecret(const std::vector<unsigned char>& shared_secret) {
    HKDF_Gost hkdf;
    handshake_secret = hkdf.extract(early_secret, shared_secret);
}

void KeySchedule::computeMasterSecret(const std::vector<unsigned char>& context) {
    HKDF_Gost hkdf;
    master_secret = hkdf.extract(handshake_secret, context);
}
