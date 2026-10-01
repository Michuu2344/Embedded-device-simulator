# Embedded-device-simulator
Symulator prostego urządzenia embedded napisany w C. Program uruchamia wątek symulujący pracę urządzenia (device_tick co sekundę), a wątek główny obsługuje menu konsolowe: status, ustawianie temperatury, przełączanie LED i wyświetlanie błędów. Dostęp do współdzielonego stanu Device jest chroniony mutexem, żeby uniknąć wyścigów między wątkami.
