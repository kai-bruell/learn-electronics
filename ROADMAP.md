# Elektronik-Lernpfad: Roadmap

> Vom Ohmschen Gesetz zur eigenen Platine — ein strukturierter Weg durch die Elektronik.

---

## Phase 1: Elektrotechnik-Grundlagen
Spannung, Strom, Widerstand — die physikalischen Basics mit Hands-on-Messungen.

| # | Projekt | Ordner |
|---|---------|--------|
| P01 | Ohmsches Gesetz | `01-ohmsches-gesetz/` |
| P02 | Breadboard-Praxis & Multimeter | `02-breadboard-und-multimeter/` |
| P03 | Reihen- und Parallelschaltung | `03-reihen-und-parallelschaltung/` |

---

## Phase 2: Arduino-Grundlagen
Vom ersten Sketch bis zum Kombiprojekt. Digitale/Analoge I/O, PWM, serielle Kommunikation.

| # | Projekt | Ordner |
|---|---------|--------|
| P04 | Arduino IDE & Blink | `04-arduino-ide-und-blink/` |
| P05 | LED-Lauflicht | `05-led-lauflicht/` |
| P06 | Taster & Entprellung | `06-taster-und-entprellung/` |
| P07 | Analoger Eingang & Photoresistor | `07-analogeingang-photoresistor/` |
| P08 | PWM & RGB-LED | `08-pwm-und-rgb-led/` |
| P09 | Schieberegister 74HC595 | `09-schieberegister-74hc595/` |
| P10 | Buzzer & Melodie | `10-buzzer-melodie/` |
| P11 | Serielle Kommunikation & Debugging | `11-serielle-kommunikation/` |
| P12 | Kombiprojekt: Automatisches Nachtlicht | `12-kombiprojekt-nachtlicht/` |

---

## Phase 4: Tiefergehende Theorie
Ladung, Potentiale, AC/DC, Kirchhoff, Signalarten — das theoretische Fundament vertiefen.

| # | Projekt | Ordner |
|---|---------|--------|
| P13 | Elektrische Ladung & Stromrichtung | `13-elektrische-ladung/` |
| P14 | Potentiale & Ground | `14-potentiale-und-ground/` |
| P15 | Gleichstrom & Wechselstrom | `15-gleich-und-wechselstrom/` |
| P16 | Kirchhoffsche Gesetze | `16-kirchhoffsche-gesetze/` |
| P17 | Signalarten & PWM im Detail | `17-signalarten-und-pwm/` |

---

## Phase 5: Erweiterte Bauteile
Kondensatoren, Spulen, MOSFETs, Op-Amps, 555-Timer — neue Bauteile verstehen und einsetzen.

| # | Projekt | Ordner |
|---|---------|--------|
| P18 | Kondensatoren: Typen & Verhalten | `18-kondensatoren/` |
| P19 | Spulen & Induktivität | `19-spulen/` |
| P20 | MOSFET als Schalter | `20-mosfet-als-schalter/` |
| P21 | Operationsverstärker (LM358) | `21-operationsverstaerker/` |
| P22 | Timer IC 555 | `22-timer-ic-555/` |

---

## Phase 6: Schaltungen ohne Mikrocontroller
Funktionen realisieren, für die du vorher einen Arduino gebraucht hättest.

| # | Projekt | Ordner |
|---|---------|--------|
| P23 | Spannungsteiler | `23-spannungsteiler/` |
| P24 | Astabiler Multivibrator | `24-astabiler-multivibrator/` |
| P25 | Audio-Verstärker mit LM386 | `25-audioverstaerker-lm386/` |
| P26 | Logikgatter aus Transistoren | `26-logikgatter-transistoren/` |
| P27 | Logik-ICs der 74xx-Serie | `27-logik-ics-74xx/` |

---

## Phase 7: Modul-Dekonstruktion
Fertige Module durch eigene Schaltungen ersetzen — die Vorbereitung für PCB-Design.

| # | Projekt | Ordner |
|---|---------|--------|
| P28 | 5V-Netzteil mit L7805 | `28-netzteil-5v/` |
| P29 | H-Brücke aus Transistoren | `29-h-bruecke/` |
| P30 | Pegelwandler (Level Shifter) | `30-pegelwandler/` |
| P31 | Pull-up & Pull-down Widerstände | `31-pull-up-pull-down/` |

---

## Phase 8: PCB-Design
Vom Breadboard zum professionellen Schaltplan und zur eigenen Platine.

| # | Projekt | Ordner |
|---|---------|--------|
| P32 | KiCad: Schaltplan zeichnen | `32-kicad-schaltplan/` |
| P33 | PCB-Layout & Fertigung | `33-pcb-layout/` |

---

## Hardware-Übersicht

### Im Starter Kit enthalten
- ELEGOO R3 Board + USB-Kabel
- Breadboard
- 65 Jumper-Kabel + 5 DuPont-Kabel
- 74HC595 Schieberegister
- 20 LEDs (rot, grün, blau, gelb) + 1 RGB-LED
- 5 Taster, 1 Schalter, 1 Buzzer
- 2 Photoresistoren
- 110 Widerstände (div. Werte)

### Zusätzlich benötigt (ab Phase 4/5)
- Multimeter
- 9V-Batterie + Clip
- NPN-Transistoren (2N2222 oder BC547)
- PNP-Transistoren (2N3906)
- MOSFET IRLZ44N + BSS138
- NE555 Timer IC
- LM358 Op-Amp IC
- LM386 Audio-Verstärker IC
- L7805 Spannungsregler
- Logik-ICs: 74HC08, 74HC32, 74HC02
- Dioden: 1N4007, 1N4148
- Kondensatoren: 100nF, 1µF, 10µF, 100µF
- Spule/Induktivität (10mH)
- Potentiometer (10kΩ)
- Kleiner Lautsprecher (8Ω)
- Kleiner DC-Motor
- Externes Batteriepack (4x AA)
