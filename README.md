# 🛰️ GPS Tracker on ESP8266 / GPS-трекер на базі ESP8266

![status](https://img.shields.io/badge/status-work--in--progress-yellow)
![license](https://img.shields.io/badge/license-MIT-green)
![platform](https://img.shields.io/badge/platform-ESP8266-blue)
![language](https://img.shields.io/badge/language-C-blue)

> 🇺🇦 **Українська версія нижче**  
> 🇬🇧 **English version below**

---

## 🇬🇧 English Version

> ⚠️ **This project is under development (Work in Progress)**  
> The functionality and structure may change during the development process.

---

### 📖 Overview
This project is an **experimental GPS tracker** built on the **ESP8266** microcontroller.  
It receives NMEA data from a GPS module (such as u-blox NEO-6M), parses coordinates, and can log routes in **GPX format** for later analysis.

---

### ⚙️ Features
✅ Reads GPS data via UART  
✅ Parses NMEA sentences (coordinates, speed, time)  
✅ Logs routes to GPX files  
🟡 Planned: Save logs to SD card  
🟡 Planned: Wi-Fi data transfer  
🟡 Planned: Mode switch button (private/work trip)

---

### 🚧 Development Progress
- [x] GPS data reception and parsing  
- [x] GPX logging  
- [ ] SD card saving  
- [ ] Wi-Fi connection and data upload  
- [ ] Web interface for track visualization  
- [ ] Power optimization and sleep modes  

---

### 🔌 Hardware

| Component | Description |
|------------|-------------|
| **Microcontroller** | ESP8266 (NodeMCU, Wemos D1 Mini) |
| **GPS Module** | u-blox NEO-6M (UART) |
| **Power Supply** | 5V (USB or external) |
| **Logic Level** | 3.3V UART |

---

### 🧰 Project Structure
```text
main/
├── main.c # Main logic
├── gps_parser.c/.h # GPS parsing
├── gpx_logger.c/.h # GPX logging
├── hardware_init.c/.h # Hardware setup
├── hw_config.c # Configuration
├── gps_types.h # Data types
└── CMakeLists.txt # Build configuration
```

### 🧱 Build Instructions (ESP-IDF)
idf.py set-target esp8266
idf.py build
idf.py flash
idf.py monitor

🪪 License

Released under the MIT License.
Free to use, modify, and distribute with attribution.

👨‍💻 Author

Ihor Stadnychuk
GitHub: ihorstadnychukwork-source


🇺🇦 Українська версія

⚠️ Цей проєкт перебуває у розробці (Work in Progress)
Функціональність і структура можуть змінюватися в процесі розробки.

📖 Опис

Цей проєкт — експериментальний GPS-трекер на базі мікроконтролера ESP8266.
Пристрій отримує дані з GPS-модуля (наприклад, u-blox NEO-6M), обробляє координати та може записувати маршрут у форматі GPX для подальшого аналізу.

⚙️ Можливості

✅ Отримання даних із GPS-модуля через UART
✅ Розбір координат, швидкості та часу
✅ Запис маршрутів у GPX формат
🟡 Планується: збереження даних на SD-карту
🟡 Планується: передача координат через Wi-Fi
🟡 Планується: кнопка режиму “приватна/робоча поїздка”

🚧 Хід розробки

- [x] Отримання та розбір GPS-даних
- [x] Запис у GPX формат
- [ ] Збереження на SD-карту
- [ ] Підключення Wi-Fi та передача даних  
- [ ] Вебінтерфейс для перегляду треків  
- [ ] Оптимізація енергоспоживання  

| Компонент | Опис|
|------------|-------------|
| **Мікроконтролер** | ESP8266 (NodeMCU, Wemos D1 Mini) |
| **GPS-модуль** | u-blox NEO-6M (UART) |
| **Живлення** | 5V (USB or external) |
| **Рівень логіки UART** | 3.3V UART |



🧰 Структура проєкту
```text
main/
 ├── main.c               # Основна логіка програми
 ├── gps_parser.c/.h      # Обробка GPS-даних
 ├── gpx_logger.c/.h      # Запис у GPX формат
 ├── hardware_init.c/.h   # Ініціалізація обладнання
 ├── hw_config.c          # Конфігурація модулів
 ├── gps_types.h          # Структури даних
 └── CMakeLists.txt       # Конфігурація збірки
```

🧱 Збірка проєкту (ESP-IDF)
idf.py set-target esp8266
idf.py build
idf.py flash
idf.py monitor


🪪 Ліцензія

Проєкт поширюється під ліцензією MIT — можна вільно використовувати, змінювати й розповсюджувати із зазначенням автора.

👨‍💻 Автор

Ігор Стадничук
GitHub: ihorstadnychukwork-source

⭐ Якщо проєкт цікавий — натисни Star у верхній частині сторінки,
це допомагає просувати його далі 🚀