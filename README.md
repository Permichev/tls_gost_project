# Реализация фрагмента Key Schedule TLS 1.3 с использованием ГОСТ-алгоритмов

Данный проект демонстрирует интеграцию отечественных криптографических алгоритмов (ГОСТ) в фрагмент ключевого расписания (Key Schedule) протокола TLS 1.3. Основная цель — показать возможность замены стандартных хэш-функций (например, SHA-256) на хэш-функцию ГОСТ Р 34.11-2012 при формировании Early Secret, Handshake Secret и Master Secret.

## Основные возможности

- **Интеграция ГОСТ-движка в OpenSSL**:  
  Использование `gost-engine` для получения поддержки ГОСТ Р 34.11-2012.
  
- **Работа с ГОСТ-хэшом (md_gost12_256)**:  
  Пример кода, показывающий вызов ГОСТ-хэширования через EVP API OpenSSL.

- **Упрощённый Key Schedule TLS 1.3**:  
  Реализован учебный пример, в котором фиксированные PSK, shared_secret и context используются для демонстрации вычисления Early, Handshake и Master Secret на базе HKDF, адаптированного к ГОСТ-хэшированию.

## Требования

- **Операционная система**: macOS (ARM, Apple Silicon) или аналогичная.  
- **OpenSSL 3.0**: Установлен через Homebrew или другой пакетный менеджер.  
- **gost-engine**: Собран и установлен.  
- **CMake (3.20+)** и компилятор с поддержкой C++17**:  
  Для сборки проекта.

## Установка и настройка

1. **Установка OpenSSL 3.0**:  
   ```bash
   brew install openssl@3
   ```
   
2. **Сборка и установка gost-engine**:  
   ```bash
   git clone https://github.com/gost-engine/engine.git
   cd engine
   mkdir build && cd build
   cmake .. -DOPENSSL_ENGINES_DIR=/opt/homebrew/lib/engines-3
   cmake --build .
   sudo cmake --install .
   ```

3. **Конфигурационный файл для загрузки ГОСТ-движка (`openssl.cnf`)**:
   ```  
   openssl_conf = openssl_init

   [openssl_init]
   engines = engine_section

   [engine_section]
   gost = gost_section

   [gost_section]
   engine_id = gost
   dynamic_path = /opt/homebrew/lib/engines-3/gost.dylib
   default_algorithms = ALL
   ```
   Укажите корректный путь к `gost.dylib`, если требуется.

4. **Установка переменной окружения**:  
   ```bash
   export OPENSSL_CONF=/path/to/openssl.cnf
   ```

## Сборка проекта

1. Клонировать данный репозиторий:  
   ```bash
   git clone https://github.com/username/tls_gost_project.git
   cd tls_gost_project
   ```

2. Создать и перейти в папку сборки:
   ```bash
   mkdir build
   cd build
   ```

3. Запустить CMake и собрать:
   ```bash
   cmake ..
   cmake --build .
   ```

## Запуск

Из папки `build`:
```bash
./tls_gost_project
```

При успешной загрузке ГОСТ-движка и наличии нужного конфигурационного файла вы увидите вывод, подобный:
```
GOST hash found, proceeding with Key Schedule...
Early Secret: 2c8331f909a5f88e5813da44635b95dbe59cc51079b58945ff5c85b02d9716db
Handshake Secret: 5500ec3ce8c675706975e585dfcd94be862ae41723b538ca822138deffff6875
Master Secret: 3270ac91afe02408099019cc21372f2e497fef9257f1bd9363a0c485f175fd27
```

## Замечания

- Проект носит учебный характер. Реализация HKDF упрощена (отсутствует полноценная HMAC-логика), а данные для Key Schedule фиксированы.
- Для реальной интеграции необходимо следовать RFC 8446 и документу Р 1323565.1.030-2020, реализовать HMAC-GOST полноценно, использовать реальные параметры Handshake (ECDH), метки (labels) и контексты.
- Данный пример служит доказательством концепции (Proof of Concept) и основой для дальнейшего расширения.


