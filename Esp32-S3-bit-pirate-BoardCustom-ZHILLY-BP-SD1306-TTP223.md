Documentation de référence (v1.0)
1. Présentation du projet

Board custom pour le firmware ESP32 Bit Pirate v1.7, fonctionnant sur un ESP32-S3 DevKitC-1 N16R8 avec :

     Écran OLED SSD1306 128×64 (I2C)
     3 capteurs tactiles TTP223 (navigation type T-Embed)
     Sélection du mode de connexion (WIFI / HOTSPOT / SERIAL) via interface physique

Contribution originale : vue SSD1306 (Ssd1306DeviceView) + input 3 boutons actifs hauts (CustomInput) intégrées au framework du board custom.
2. Matériel requis
Élément
	
Référence
	
Qté
	
Prix indicatif
MCU	ESP32-S3 DevKitC-1 N16R8 (16MB flash, 8MB PSRAM octal)	1	~10 €
Écran	SSD1306 OLED 0.96" 128×64, I2C (adresse 0x3C)	1	~4 €
Boutons	TTP223 capteurs tactiles capacitifs (momentanés, actifs HAUT par défaut)	3	~2 €
Alim	USB-C (port natif du DevKit)	—	—
 
 

⚠️ Notes matériel :

     Les TTP223 doivent avoir leurs pads A/B non soudés (mode momentané actif haut)
     L'adresse OLED : 0x3C standard (certains modules : 0x3D)

3. Schéma de câblage
Vue d'ensemble
                    ┌──────────────────────────────┐
                    │   ESP32-S3 DevKitC-1 N16R8   │
                    │                              │
   OLED SSD1306     │                              │
   ┌──────────┐     │                              │
   │ VCC ─────┼─────┤ 3.3V                         │
   │ GND ─────┼─────┤ GND           (masses        │
   │ SDA ─────┼─────┤ GPIO 8         communes)     │
   │ SCL ─────┼─────┤ GPIO 18                      │
   └──────────┘     │                              │
                    │                              │
   TTP223 ▼         │                              │
   ┌──────────┐     │                              │
   │ VCC ─────┼─────┤ 3.3V                         │
   │ GND ─────┼─────┤ GND                          │
   │ I/O ─────┼─────┤ GPIO 10                      │
   └──────────┘     │                              │
                    │                              │
   TTP223 ▲         │      (idem pour ▲ et OK)     │
   │ I/O ─────┼─────┤ GPIO 11                      │
                    │                              │
   TTP223 OK        │                              │
   │ I/O ─────┼─────┤ GPIO 12                      │
                    │                              │
                    │ USB natif → flash + serial   │
                    └──────────────────────────────┘
					
					
					
Tableau détaillé des connexions
#
	
Composant
	
Broche composant
	
GPIO ESP32-S3
	
Type de signal
	
Partagé avec
1	OLED SSD1306	VCC	3.3V	alimentation	TTP223 (VCC)
2	OLED SSD1306	GND	GND	masse commune	tous les GND
3	OLED SSD1306	SDA	GPIO 8	I2C data	bus I2C outils (pinmap T-Embed CC1101)
4	OLED SSD1306	SCL	GPIO 18	I2C clock	bus I2C outils (pinmap T-Embed CC1101)
5	TTP223 « ▼ »	VCC	3.3V	alimentation	OLED
6	TTP223 « ▼ »	GND	GND	masse	commune
7	TTP223 « ▼ »	I/O (SIG)	GPIO 10	entrée digitale, active HAUTE	—
8	TTP223 « ▲ »	VCC	3.3V	alimentation	—
9	TTP223 « ▲ »	GND	GND	masse	—
10	TTP223 « ▲ »	I/O (SIG)	GPIO 11	entrée digitale, active HAUTE	—
11	TTP223 « OK »	VCC	3.3V	alimentation	—
12	TTP223 « OK »	GND	GND	masse	—
13	TTP223 « OK »	I/O (SIG)	GPIO 12	entrée digitale, active HAUTE	—
 
 
Signification des boutons
Bouton
	
GPIO
	
Action dans le firmware
	
Code touche
▲	11	option précédente (wrap-around)	KEY_ARROW_LEFT (,)
▼	10	option suivante (wrap-around)	KEY_ARROW_RIGHT (/)
OK	12	valider la sélection	KEY_OK (\n)
 
 
Règles de câblage critiques

    Masses communes : tous les GND (OLED + 3× TTP223 + DevKit) reliés ensemble
    3.3V uniquement : jamais de 5V sur l'OLED ou les TTP223
    Port USB natif : le flash et le moniteur série passent par le port USB natif du S3 (pas le port UART) — USB CDC On Boot activé

4. Mapping GPIO complet (réservations)
GPIO
	
Fonction
	
Réservé par
8	I2C SDA (OLED + bus outils)	écran + protocole I2C
10	bouton ▼ TTP223	interface
11	bouton ▲ TTP223	interface
12	bouton OK TTP223	interface
18	I2C SCL (OLED + bus outils)	écran + protocole I2C
1	IR TX (option)	protocole infrarouge
2	IR RX (option)	protocole infrarouge
3	LoRa RST (option)	module radio
4-7	bus SPI outils (CS/CLK/MISO/MOSI)	CC1101/MCP2515/LoRa/nRF24
13	SD CS (option)	carte SD
14	SD CLK / SUBGHZ GDO (option)	protocoles
15	UART RX (option)	protocole série
16	UART TX (option)	protocole série
17	OneWire (option)	protocole 1-wire
21	LED clock (option)	bandeaux LED
39/40	SD MISO/MOSI (option)	carte SD
41/42	I2S (option)	audio
48	LED RGB du DevKit	statut
❌ 19-20	USB natif	interdit d'usage
❌ 26-37	PSRAM octal	interdit — risque de brick
❌ 43-44	UART0 debug	interdit d'usage
❌ 45-46	strapping	à éviter
 
 
5. Build et flash
Prérequis

     PlatformIO avec Python 3.10-3.13 (⚠️ PAS 3.14 — incompatibilité connue)
     VS Code + extension PlatformIO, ou CLI

Build

PowerShell:
# via le Python 3.12 (si plusieurs Pythons installés) :
& "C:\...\Python312\python.exe" -m platformio run -e zhilly-bp

# ou via l'alias profil PowerShell :
pio run -e zhilly-bp

Flash + moniteur
pio run -e zhilly-bp -t upload --upload-port COM16
pio device monitor --port COM16

⚠️ Pièges connus (documentés pour les contributeurs) :
ImportError littlefs → penv corrompu : Remove-Item -Recurse -Force "$env:USERPROFILE\.platformio\penv"  puis relancer
pio non reconnu → installer PlatformIO dans le bon Python
Carte qui reste en waiting for download → bouton BOOT maintenu pendant le lancement du flash

6. Structure des fichiers ajoutés/modifiés
| Fichier | Nature | Rôle |
|---|---|---|
| `src/Boards/Common/Views/Ssd1306DeviceView.h/.cpp` | **NOUVEAU** | vue OLED complète (toutes les méthodes IDeviceView) |
| `src/Boards/Custom/CustomInput.h/.cpp` | **MODIFIÉ** | 3 boutons TTP223 actifs hauts (▼▲OK) avec anti-rebond 120 ms |
| `src/Boards/Custom/CustomBoard.h/.cpp` | **MODIFIÉ** | support du driver SSD1306 (`#elif CUSTOM_DISPLAY_DRIVER_SSD1306`) |
| `src/Boards/Custom/CustomBoardConfig.h` | **MODIFIÉ** | macros pins I2C OLED + 3 boutons indépendants |
| `src/Configurators/TerminalTypeConfigurator.cpp` | **MODIFIÉ** | ⚠️ retrait de `DEVICE_CUSTOM` de la liste headless — **indispensable** pour le sélecteur interactif |
| `platformio.ini` | **MODIFIÉ** | env `[env:zhilly-bp]` complet |

⚠️ Le fix indispensable (le piège du framework)
Dans TerminalTypeConfigurator.cpp, le firmware officiel route DEVICE_CUSTOM vers selectHeadless()(sélection automatique après 3 s, seul OK écouté).
 Retirer DEVICE_CUSTOM du #if pour obtenir le sélecteur interactif complet ▼▲OK :
 
cpp
 // AVANT :
#if defined(DEVICE_M5STAMPS3) || defined(DEVICE_S3DEVKIT) || defined(DEVICE_CUSTOM)
    selected = selector.selectHeadless();

// APRÈS (le fix) :
#if defined(DEVICE_M5STAMPS3) || defined(DEVICE_S3DEVKIT)
    selected = selector.selectHeadless();
  
7. Configuration de l'env (platformio.ini — extrait)

ini
[env:zhilly-bp]
board = esp32-s3-devkitc1-n16r8
board_build.partitions = partitions/app4M_spiffs_12M_16MB.csv
lib_deps =
  thingpulse/ESP8266 and ESP32 OLED driver for SSD1306 displays@^4.6.1
  LovyanGFX=https://github.com/lovyan03/LovyanGFX
  crankyoldgit/IRremoteESP8266 @ ^2.9.0
  ${env.lib_deps}
build_flags =
  -D BOARD_HAS_PSRAM=1
  ${env.build_flags}
  -DDEVICE_CUSTOM
  -DPROTECTED_PINS="\"8, 10, 11, 12, 18, 19, 20, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 43, 44, 45, 46\""
  -DCUSTOM_INPUT_DOWN_PIN=10
  -DCUSTOM_INPUT_UP_PIN=11
  -DCUSTOM_INPUT_OK_PIN=12
  -DCUSTOM_INPUT_BUTTON_ACTIVE_LOW=0    ; TTP223 = actifs HAUTS
  -DCUSTOM_INPUT_BUTTON_PULLUP=0        ; TTP223 = pas de pullup
  -DCUSTOM_DISPLAY_DRIVER_SSD1306
  -DCUSTOM_DISPLAY_I2C_SDA=8
  -DCUSTOM_DISPLAY_I2C_SCL=18
  -DCUSTOM_DISPLAY_I2C_ADDRESS=0x3C
  ; ... (voir platformio.ini pour les pins protocoles complets)
  
  8. Utilisation

    Boot → logo « BIT PIRATE » (~1 s)
    Sélecteur : ▲ ▼ font défiler WIFI / HOTSPOT / SERIAL — OK valide (pas de timeout)
    Première configuration WiFi : choisir HOTSPOT → rejoindre l'AP depuis un téléphone → http://192.168.4.1 → configurer les credentials → reboot → mode WIFI → IP affichée → interface web sur téléphone
    Mode Serial : terminal PC (115200), taper une touche puis help pour la liste des commandes

9. Dépannage (les pièges vécus)
Symptôme
	
Cause
	
Solution
Écran noir	SDA/SCL inversés ou adresse	vérifier 8=SDA/18=SCL, essayer 0x3D
Boutons inertes	TTP223 mal câblé (I/O ≠ VCC) ou pads A/B soudés	vérifier broche SIG + pads vierges
Sélection automatique après 3 s	DEVICE_CUSTOM dans le #if headless	appliquer le fix §6
« Seul OK marche »	idem — headless n'écoute que OK	idem
Choix WIFI → retombe en Serial	credentials absents	config via HOTSPOT (§8.3)
Rien sur le moniteur	mauvais port USB (UART au lieu de natif)	brancher le port USB natif du S3
littlefs ImportError	penv Python corrompu	purger ~/.platformio/penv
Python 3.14 refusé	incompatibilité PlatformIO	installer 3.12 à côté
 
 
10. Crédits et licence

     Firmware : ESP32 Bit Pirate v1.7 (projet open-source — voir LICENSE du repo)
     Board custom : zhilly-bp — vue SSD1306 + input TTP223
     Contribution libre pour la communauté maker 🛠️

