#include <iostream>
#include <cstring>
#include <openssl/evp.h>
#include <openssl/engine.h>
#include <openssl/conf.h>
#include <openssl/crypto.h>

#include "key_schedule.h"

static void printHex(const std::vector<unsigned char>& data) {
    for (auto b : data) {
        printf("%02x", b);
    }
    printf("\n");
}

int main() {
    // Инициализируем конфигурацию (загрузит OPENSSL_CONF)
    OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CONFIG, NULL);

    // Явно подгружаем движок GOST
    ENGINE_load_dynamic();
    ENGINE *e = ENGINE_by_id("gost");
    if (!e) {
        std::cerr << "GOST engine not found!\n";
        return 1;
    }
    if (!ENGINE_init(e)) {
        std::cerr << "Failed to initialize GOST engine!\n";
        return 1;
    }
    ENGINE_set_default(e, ENGINE_METHOD_ALL);

    // Проверим доступность GOST-хэша
    const EVP_MD* gost_md = EVP_get_digestbyname("md_gost12_256");
    if (!gost_md) {
        std::cerr << "GOST hash not found!\n";
        return 1;
    }

    std::cout << "GOST hash found, proceeding with Key Schedule...\n";

    // Демонстрация ключевого расписания с использованием ГОСТ-хэширования
    KeySchedule ks;
    std::vector<unsigned char> psk = {0x01, 0x02, 0x03, 0x04};
    ks.computeEarlySecret(psk);
    std::cout << "Early Secret: ";
    printHex(ks.getEarlySecret());

    std::vector<unsigned char> shared_secret = {0x10, 0x11, 0x12, 0x13};
    ks.computeHandshakeSecret(shared_secret);
    std::cout << "Handshake Secret: ";
    printHex(ks.getHandshakeSecret());

    std::vector<unsigned char> context = {0x20, 0x21};
    ks.computeMasterSecret(context);
    std::cout << "Master Secret: ";
    printHex(ks.getMasterSecret());

    ENGINE_finish(e);
    ENGINE_free(e);

    return 0;
}
