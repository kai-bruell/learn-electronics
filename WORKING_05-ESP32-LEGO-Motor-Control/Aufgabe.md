# P05: ESP32 LEGO Motor Control

Steuerung von 7 LEGO 8883 DC-Motoren über einen ESP32-Mikrocontroller mit zwei PCA9685-PWM-Treibern und vier TB6612FNG-H-Brücken-Motortreibern.

---

## Stückliste

| Anzahl | Komponente | Typ |
|:---:|---|---|
| 1 | ESP32 DevKit (Schraubklemmen) | Mikrocontroller |
| 2 | PCA9685 Breakout Board | 16-Kanal 12-Bit PWM-Treiber (I2C) |
| 4 | TB6612FNG Breakout Board | Dual H-Brücken Motortreiber |
| 1 | Buck Converter (einstellbar) | DC-DC Step-Down Spannungsregler |
| 1 | Netzteil 9V DC | Stromversorgung |
| 7 | LEGO 8883 Motor | DC-Motor (9V, max. 850 mA) |
| 7 | LEGO 8884 Verlängerungskabel | Werden aufgeschnitten und an Motortreiber angeschlossen |
| 1 | Breadboard | Aufbau und Verdrahtung |
| — | Jumper-Kabel | Verbindungen |

---

## Komponentenbeschreibung

### ESP32 — Mikrocontroller

Der ESP32 ist ein 32-Bit-Mikrocontroller mit integriertem Wi-Fi und Bluetooth. In dieser Schaltung dient er ausschließlich als **Master auf dem I2C-Bus**. Er sendet Steuerbefehle an die beiden PCA9685-Chips und hat darüber hinaus keine direkte Verbindung zu den Motoren oder Motortreibern.

Relevante Eigenschaften:
- **I2C-Bus:** Der ESP32 stellt zwei Pins bereit — GPIO 21 (SDA, Datenleitung) und GPIO 22 (SCL, Taktleitung). Über diese zwei Leitungen kommuniziert er mit beiden PCA9685 gleichzeitig. Jeder PCA9685 hat eine eigene Adresse, sodass der ESP32 gezielt ansprechen kann, mit welchem Chip er gerade spricht.
- **Betriebsspannung:** 3,3V. Der ESP32 arbeitet mit 3,3V-Logikpegeln. Eine höhere Spannung an den GPIOs zerstört den Chip.

Der ESP32 hat selbst PWM-fähige Pins, aber nicht genug für 7 Motoren mit je 3 Steuerleitungen (21 Pins). Deshalb werden die PCA9685 als PWM-Erweiterung eingesetzt.

---

### PCA9685 — 16-Kanal 12-Bit PWM-Treiber

Der PCA9685 ist ein über I2C angesteuerter PWM-Controller. Ein einzelner Chip stellt **16 unabhängige PWM-Ausgänge** bereit, jeder mit 12-Bit Auflösung (Werte 0–4095). Das bedeutet: Der ESP32 schickt per I2C einen Befehl wie "Kanal 3 auf Wert 2048", und der PCA9685 erzeugt ab diesem Moment selbstständig ein PWM-Signal mit 50% Duty-Cycle auf diesem Kanal — ohne weitere Kommunikation.

**I2C-Adressierung:** Ab Werk hat jeder PCA9685 die Adresse 0x40. Da zwei Chips am selben Bus hängen, muss einer umkonfiguriert werden. Dafür wird auf der Platine das Lötpad **A0** gebrückt (kurzgeschlossen), was die Adresse auf 0x41 verschiebt. Der ESP32 unterscheidet die beiden Chips dann ausschließlich über die Adresse.

**Funktionszuweisung in dieser Schaltung:**

| Chip | Adresse | Aufgabe | Genutzte Kanäle |
|---|---|---|---|
| PCA9685 #1 | 0x40 | **Richtungssignale** — IN1/IN2 der TB6612FNG | CH 0–13 (14 von 16) |
| PCA9685 #2 | 0x41 | **Geschwindigkeitssignale** — PWMA/PWMB der TB6612FNG | CH 0–6 (7 von 16) |

Beachte: PCA9685 #1 gibt an seinen Kanälen immer nur 0 oder 4095 aus — also rein digitales HIGH oder LOW. Die volle PWM-Fähigkeit (stufenlose Werte zwischen 0 und 4095) wird nur bei PCA9685 #2 tatsächlich genutzt. PCA9685 #1 wird somit als reiner digitaler Ausgangs-Expander verwendet — technisch funktional, aber ein Shift-Register (z.B. 74HC595) wäre für diesen Zweck ausreichend und günstiger.

**Relevante Pins:**

| Pin | Funktion |
|---|---|
| VCC | Logikversorgung (3,3V) |
| GND | Masse |
| SDA | I2C-Datenleitung |
| SCL | I2C-Taktleitung |
| CH 0–15 | PWM-Ausgänge |
| A0–A5 | Adresspads (Lötzinn-Brücken zur Adressänderung) |

---

### TB6612FNG — Dual H-Brücken Motortreiber

Der TB6612FNG ist das zentrale Bindeglied zwischen Logik und Motorstrom. Er enthält **zwei vollständige H-Brücken** (Kanal A und Kanal B), kann also **zwei Motoren** unabhängig voneinander ansteuern. Vier Chips steuern somit 8 Motorkanäle — 7 werden genutzt, 1 bleibt Reserve.

**Warum eine H-Brücke?**

Ein DC-Motor dreht sich in die eine Richtung, wenn Strom von links nach rechts durch ihn fließt, und in die andere Richtung, wenn der Strom umgekehrt fließt. Eine H-Brücke besteht aus vier Transistoren (als Schalter), die in H-Form um den Motor angeordnet sind:

```
     VCC                 VCC
      |                   |
    [S1]               [S3]
      |                   |
      +---[ Motor M ]----+
      |                   |
    [S2]               [S4]
      |                   |
     GND                 GND
```

- **S1 + S4 geschlossen, S2 + S3 offen:** Strom fließt links→rechts durch den Motor → Drehung vorwärts.
- **S3 + S2 geschlossen, S1 + S4 offen:** Strom fließt rechts→links durch den Motor → Drehung rückwärts.
- **S1 + S3 geschlossen:** Beide Motoranschlüsse auf VCC → Motor kurzgeschlossen → aktive Bremse.
- **Alle offen:** Kein Strom → Motor trudelt frei aus.

Im TB6612FNG sind S1–S4 als MOSFET-Transistoren realisiert. Die Logikeingänge IN1 und IN2 steuern, welche Schalter geschlossen werden:

| IN1 | IN2 | Modus |
|---|---|---|
| HIGH | LOW | Vorwärts (CW) |
| LOW | HIGH | Rückwärts (CCW) |
| HIGH | HIGH | Aktive Bremse (Short Brake) |
| LOW | LOW | Motor aus (Stop, trudelt nach) |

Der **PWM-Pin** moduliert zusätzlich die Geschwindigkeit: Er schaltet die H-Brücke mit einer definierten Frequenz (hier 1000 Hz) ein und aus. Ein PWM-Wert von 2048 (50%) bedeutet: Die H-Brücke ist 50% der Zeit geschlossen → der Motor läuft mit halber Geschwindigkeit.

**Zwei getrennte Spannungsdomänen:**

Der TB6612FNG arbeitet mit zwei vollständig getrennten Spannungen:

| Pin | Spannung | Funktion |
|---|---|---|
| **VM** | 9V (Netzteil) | Motorversorgung — der Strom, der durch die H-Brücke zum Motor fließt |
| **VCC** | 3,3V (Buck Converter) | Logikversorgung — Spannung für die internen Steuerlogik-Schaltkreise |
| **STBY** | 3,3V (Buck Converter) | Standby — muss HIGH sein, damit der Chip arbeitet. Bei LOW sind alle Ausgänge deaktiviert |

Diese Trennung ist das zentrale Sicherheitsmerkmal: Die 9V Motorspannung berührt nie die 3,3V Logik. Die H-Brücke ist der kontrollierte Übergang zwischen beiden Welten. Eine Verwechslung von VM und VCC zerstört den Chip sofort.

**Relevante Pins pro Kanal:**

| Pin | Funktion |
|---|---|
| AIN1 / AIN2 | Richtung Motor A (von PCA9685 #1) |
| BIN1 / BIN2 | Richtung Motor B (von PCA9685 #1) |
| PWMA | Geschwindigkeit Motor A (von PCA9685 #2) |
| PWMB | Geschwindigkeit Motor B (von PCA9685 #2) |
| AO1 / AO2 | Motorausgang A (zum Motor) |
| BO1 / BO2 | Motorausgang B (zum Motor) |
| VM | 9V Motorstrom |
| VCC | 3,3V Logik |
| GND | Masse |
| STBY | Standby (HIGH = aktiv) |

---

### Buck Converter — DC-DC Step-Down Spannungsregler

Der Buck Converter wandelt die 9V des Netzteils auf 3,3V herunter. Diese 3,3V versorgen die gesamte Logikebene: den ESP32, beide PCA9685 und die VCC- sowie STBY-Pins aller vier TB6612FNG.

Vor dem Einbau muss der Buck Converter mit einem Multimeter und dem Einstellpoti exakt auf 3,30V justiert werden — bei abgeklemmter Last, also ohne angeschlossene Verbraucher.

---

### LEGO 8883 Motor — DC-Motor

Ein bürstenbehafteter Gleichstrommotor. Betriebsspannung 9V, Leerlaufdrehzahl ca. 405 U/min, maximale Stromaufnahme 850 mA (Blockiermoment). Die Drehrichtung wird durch die Polarität bestimmt — Strom in eine Richtung dreht den Motor vorwärts, Umkehr der Polarität dreht ihn rückwärts. Genau das erledigt die H-Brücke.

---

### LEGO 8884 Verlängerungskabel — Motoranschluss

Das Kabel hat vier Adern, alle in derselben schwarzen Isolierung. Sie unterscheiden sich nur durch ihre **Dicke**:

| Ader | Funktion in dieser Schaltung |
|---|---|
| 2 dicke Mittelleiter (C1/C2) | Motoranschluss — an AO1/AO2 bzw. BO1/BO2 des TB6612FNG. Polarität bestimmt die Drehrichtung und kann im Code umgekehrt werden. |
| 2 dünne Außenleiter (GND und +9V) | **Nicht verwenden** — abschneiden und mit Schrumpfschlauch isolieren |

Die beiden dünnen Außenleiter führen im LEGO-System GND und +9V zur Verteilung an weitere Bausteine. Für den reinen Motorbetrieb über die H-Brücke werden sie nicht benötigt und müssen isoliert werden, um Kurzschlüsse zu vermeiden.

---

## Aufgabe 1: Schaltplan zeichnen

Zeichne den vollständigen Schaltplan dieser Motorsteuerung auf Papier. Der Schaltplan soll alle Komponenten, Verbindungen und Spannungsschienen enthalten.

### Zeichenkonventionen

**Ausrichtung:**
- **Versorgungsspannung oben, Masse unten.** Plus-Schienen (3,3V und 9V) werden als horizontale Linien am oberen Rand gezeichnet, die GND-Schiene als horizontale Linie am unteren Rand.
- **Signalfluss von links nach rechts.** Der ESP32 (Steuerquelle) steht links, die Motoren (Endverbraucher) rechts. Dazwischen liegen die PCA9685 und die TB6612FNG.

**Leitungen:**
- Nur **horizontal oder vertikal** — keine diagonalen Leitungen.
- **Kreuzung ohne Verbindung:** Leitungen kreuzen sich einfach.
- **Kreuzung mit Verbindung:** Ein **dicker Punkt** am Kreuzungspunkt zeigt an, dass die Leitungen elektrisch verbunden sind.

**Schienen:**
- Eine Schiene ist eine durchgehende Linie, an die mehrere Bauteile parallel angeschlossen werden. Jedes Bauteil bekommt einen kurzen Strich zur Schiene.
- Verwende **drei Schienen**: GND (unten), 3,3V (oben), 9V (oben, parallel zur 3,3V-Schiene). Beschrifte jede Schiene.

**Bauteile:**
- Breakout-Boards (ESP32, PCA9685, TB6612FNG, Buck Converter) werden als **Rechtecke** mit beschrifteten Pins gezeichnet. Nur die tatsächlich genutzten Pins einzeichnen.
- Motoren werden mit dem genormten **Kreis mit M** dargestellt.
- Das GND-Symbol (drei kürzer werdende horizontale Striche) kann alternativ direkt an Bauteilen verwendet werden, um Leitungen zur GND-Schiene einzusparen.

**Beschriftung:**
- Jedes Bauteil erhält eine Bezeichnung (z.B. "PCA9685 #1 (0x40)", "TB6612 #3", "Motor 5").
- Spannungswerte an den Schienen angeben (3,3V, 9V).
- I2C-Leitungen als SDA und SCL beschriften.

### Vorgehen

1. Zeichne die drei Schienen: GND unten, 3,3V und 9V oben.
2. Platziere den Buck Converter links — er verbindet die 9V-Schiene mit der 3,3V-Schiene.
3. Platziere den ESP32 links — er hängt an 3,3V und GND und hat zwei Ausgänge: SDA und SCL.
4. Platziere die beiden PCA9685 in der Mitte — sie hängen an 3,3V, GND, SDA und SCL.
5. Platziere die vier TB6612FNG rechts von den PCA9685 — sie hängen an 3,3V (VCC + STBY), 9V (VM) und GND. Ihre Logikeingänge (IN1/IN2/PWM) kommen von den PCA9685.
6. Platziere die 7 Motoren ganz rechts — sie hängen an den Ausgängen (AO1/AO2, BO1/BO2) der TB6612FNG.
7. Prüfe: Ist jedes Bauteil mit GND verbunden? Stimmen alle Spannungen (3,3V für Logik, 9V für Motoren)?
