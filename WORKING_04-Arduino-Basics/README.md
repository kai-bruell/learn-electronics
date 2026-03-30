# Arduino Basics

## Arduino IDE Setup Quickstart (Linux)

1. Download: https://www.arduino.cc/en/software/
2. Extrahiere die Zip Datei irgendwo hin.
3. Öffne im Verzeichnis die executable `./arduino-ide`

### Erster Start

Beim ersten Start erscheinen im Output-Log zahlreiche Meldungen. Die IDE initialisiert im Hintergrund folgendes:

- **Arduino CLI:** Das Kommandozeilen-Backend (`arduino-cli`) wird eingerichtet. Es ist das Herzstück, das Kompilieren und Hochladen übernimmt.
- **Board-Plattformen:** Die Standard-Plattform (z.B. `arduino:avr` für UNO, Mega, Nano) wird heruntergeladen. Das beinhaltet den Cross-Compiler (`avr-gcc`), Linker und Upload-Tools (`avrdude`).
- **Board-Index:** Eine JSON-Datei mit allen bekannten Boards und deren Konfigurationen wird heruntergeladen.
- **Library-Index:** Ein Verzeichnis aller verfügbaren Arduino-Bibliotheken wird geladen.
- **LSP (clangd):** Wird gestartet und konfiguriert, um Autocompletion, Fehlerhervorhebung und Code-Navigation bereitzustellen.

Alles landet standardmäßig unter `~/.arduino15/` (Konfiguration, Plattformen) und `~/Arduino/` (Sketches, Libraries).

### Mitgelieferte Tools

Die Arduino IDE bringt bereits alle wichtigen Tools mit, die man zum Entwickeln braucht:

- Serial Monitor
- Serial Plotter
- Firmware Updater
- Upload SSL Root Certificates
- Boards Manager
- Auto Format (Formatter)
- Archive Sketch
- Manage Libraries
- Auswahl der seriellen Schnittstelle

Die IDE ist eine Electron-App und damit eine Blackbox mit Bloat. Langfristig bevorzuge ich die CLI-Tools (`arduino-cli`, `avr-gcc`, `avrdude`) direkt zu nutzen und mir `clangd` als LSP in Neovim einrichten. Aber erstmal die Frage ein LLM: Geht das überhaupt?

Ja. Die Arduino IDE ist nur ein grafisches Frontend für `arduino-cli`. Alles was die IDE kann, kann `arduino-cli` auch: kompilieren, hochladen, Libraries verwalten, Boards installieren. Und `clangd` funktioniert in jedem Editor, der LSP unterstützt — also auch in Neovim. Man braucht lediglich eine `compile_commands.json`, die `arduino-cli` generieren kann.

## Was ist ein Sketch?

Ein Sketch ist ein Programm in der Arduino-Welt — eine Textdatei mit der Endung `.ino`. Der Name kommt daher, dass Arduino ursprünglich für Künstler und Designer gedacht war: man "skizziert" eine Idee in Code.

Jeder Sketch besteht aus zwei Hauptfunktionen:

- **`setup()`** — wird einmal beim Boot ausgeführt (Pins konfigurieren, Baudrate setzen, Peripherie initialisieren)
- **`loop()`** — läuft danach als Endlosschleife auf dem Main-Thread, solange das Board Strom hat

## Serial Monitor

Der Serial Monitor ist ein Terminal in der Arduino IDE, das über die serielle Schnittstelle mit dem Board kommuniziert. Man kann damit Daten vom Arduino lesen (`Serial.println()`) und Daten an den Arduino senden. Klassischer Anwendungsfall: Debugging — Variablenwerte, Statusmeldungen oder Fehlermeldungen im Klartext ausgeben.

## Serial Plotter

Der Serial Plotter liest die gleichen seriellen Daten wie der Serial Monitor, zeigt sie aber als **Echtzeit-Liniendiagramm** an. Typische Anwendung: Sensordaten visualisieren — z.B. Temperaturverlauf, Lichtstärke oder `analogRead()`-Werte. Man sieht sofort Trends, Spikes und Rauschen, statt Zahlenkolonnen lesen zu müssen. Mehrere Werte gleichzeitig plotten: einfach per Tab oder Komma in `Serial.print()` trennen.

## Burn Bootloader

Der Bootloader ist ein kleines Programm im reservierten Flash-Bereich des ATmega328P. Er läuft beim Boot zuerst und wartet auf der seriellen Schnittstelle auf einen neuen Sketch. Dank ihm kann man Sketches bequem per USB hochladen.

**Wann braucht man "Burn Bootloader"?**
- Frischer/leerer ATmega-Chip (z.B. als Ersatzteil gekauft)
- Bootloader ist korrupt
- Fuse-Bits ändern (Taktquelle, Clock-Divider etc.)

**Voraussetzung:** Ein **ISP-Programmer** (z.B. USBasp, oder ein zweiter Arduino als "Arduino as ISP"). Per USB allein geht es nicht — ohne funktionierenden Bootloader hört niemand auf der seriellen Schnittstelle zu.

Beim ELEGOO UNO R3 ist der Bootloader ab Werk gebrannt — man braucht das nur, wenn man den Chip tauscht oder etwas schiefgelaufen ist.

## Firmware Updater

Der Firmware Updater flasht **nicht** den Haupt-Mikrocontroller (ATmega328P) — dafür nutzt man "Upload". Er ist ausschließlich für **fest verbaute Kommunikations-Co-Prozessoren** auf Boards mit WiFi/Bluetooth gedacht, z.B.:

- **NINA-W102** (auf Arduino MKR WiFi 1010, Nano 33 IoT, UNO WiFi Rev2)
- **ESP32-basierte Module** (auf neueren Arduino-Boards)

Er aktualisiert die Firmware auf dem Wireless-Modul, damit neue Protokollversionen, Sicherheitspatches oder Bugfixes übernommen werden.

Für den **ELEGOO UNO R3** ist der Firmware Updater irrelevant — das Board hat kein WiFi/BT-Modul.

### Externe Module und der ATmega16U2

Man kann WiFi/BT-Module (z.B. ESP8266, ESP32) an den UNO anschließen, aber der Firmware Updater unterstützt nur fest verbaute Module auf offiziellen Arduino-Boards (NINA-W102 etc.). Externe Module flasht man über deren eigene Tools.

Auch den **ATmega16U2** (den USB-to-Serial-Chip auf dem UNO R3) kann man nicht mit dem Firmware Updater flashen. Der ATmega16U2 wird über den **DFU-Modus** (Device Firmware Update) geflasht. Dafür setzt man die RESET-Pins am ICSP2-Header kurz und nutzt dann `dfu-programmer`. So kann man den ATmega16U2 z.B. in ein **HID-Gerät** (Tastatur/Maus-Emulation) umwandeln.

## Upload SSL Root Certificates

Nur für Boards mit WiFi-Modul relevant. Wenn ein Arduino sich mit einem Webserver über HTTPS verbinden will, muss er dessen Zertifikat prüfen können. Dieses Tool lädt die dafür nötigen Root-Zertifikate auf das WiFi-Modul. Ohne sie: kein HTTPS.

Für den **ELEGOO UNO R3** irrelevant — kein WiFi, kein HTTPS.

## Libraries

Arduino Libraries sind fertige Code-Pakete, die einem die Arbeit mit Hardware-Modulen abnehmen. Statt z.B. das I2C-Protokoll selbst Bit für Bit zu implementieren, bindet man `Wire.h` ein und ruft Funktionen auf.

Beispiele:
- **`Servo.h`** — Servomotoren ansteuern
- **`Wire.h`** — I2C-Kommunikation
- **`SPI.h`** — SPI-Protokoll
- **`LiquidCrystal.h`** — LCD-Displays

Einige Libraries sind vorinstalliert (z.B. `Servo`, `Wire`), weitere kann man über den **Library Manager** in der IDE nachinstallieren oder manuell in `~/Arduino/libraries/` ablegen.

## Die Serielle Schnittstelle

Als Softwareentwickler war mir dieses Thema besonders wichtig, weil USB-Protokolle weit über Arduino hinausgehen — MIDI-Controller, HID-Geräte, Custom-USB-Devices. Die Bit-Ebene zu verstehen (Differenzsignale, NRZI-Kodierung, UART) ist die Grundlage, um später eigene USB-Geräte bauen zu können.

Die ausführliche Dokumentation liegt in [Serial-Port.md](Serial-Port.md):

- Physikalische Datenübertragung via USB (Differenzsignal, NRZI-Kodierung)
- Der ATmega16U2 als USB-to-UART Protokollwandler
- Asynchrone Kommunikation (UART, Baudrate, Full-Duplex)
- Das Parity-Bit (Even, Odd, Mark, Space, None)
- Konkrete Anwendungsfälle (Adressierung, Synchronisations-Check, 9-Bit-Protokolle)
