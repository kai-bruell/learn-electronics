# Die Serielle Schnittstelle

Die Serielle Schnittstelle ist die Datenleitung zwischen **Arduino und Computer**. Über diese Leitung lassen sich Sketches (Programme) hochladen oder über den Seriellen Monitor debuggen.

### Der ELEGOO UNO R3
Auf dem **ELEGOO UNO R3** sitzt der **ATmega16U**, ein programmierbarer Microcontroller. Standardmäßig läuft auf ihm die **Arduino USB-Serial Firmware**, die auf **LUFA** (Lightweight USB Framework for AVR) basiert. Diese Firmware fungiert als **Protokollwandler**, der USB-Daten in UART-Signale übersetzt – und umgekehrt. Am Computer meldet sich der Chip als **virtueller COM-Port**, sodass die **Arduino IDE** ihn automatisch als serielle Schnittstelle erkennt.

---

## Physikalische Datenübertragung via USB
Bevor die Daten den ATmega16U2 erreichen, kommen sie über das USB-Kabel an. Ein Standard-USB-2.0-Kabel hat vier Leitungen: **VCC (+5V)**, **GND (Masse)** sowie **D+** und **D-** für die Daten.

### Das Differenzsignal
Die Daten erreichen den **ATmega16U** über **D+** und **D-** des **USB-Kabels**. Hierbei handelt es sich um ein Differenzsignal:
* **Logisch 1:** D+ ist höher als D-.
* **Logisch 0:** D- ist höher als D+.
* Das verhindert Rauschen, da Störungen beide Leitungen treffen und die Differenz gleich bleibt.

### Takt und Kodierung
USB hat eine Taktfrequenz, welche man als Herzschlag bezeichnen kann (auch **Clock** genannt). USB ist synchron, braucht aber kein 5. Kabel, um den Herzschlag zu hören. Die Taktfrequenz ist in der Datenleitung über das USB Protokoll verbaut. Das heißt, der Stromfluss auf D+ / D− signalisiert sowohl 1/0 als auch Timing.

Daten werden in **NRZI Codierung** gesendet. Das heißt, man schaut nicht auf 'An' oder 'Aus', sondern auf den **Wechsel**:
* **0** = Polung wechseln
* **1** = Alles bleibt, wie es ist

Damit der Empfänger bei zu vielen Einsen (111111) nicht den Takt verliert (weil sich die Polung nie ändert), schiebt das Protokoll nach sechs Einsen eine Null ein. Dieser Wechsel **synchronisiert** den Takt beider USB Controller **zeitgleich**.

---

## Asynchrone Kommunikation (UART)
Bei der Asynchronen Kommunikation gibt es keinen gemeinsamen Takt und keine Takt-Rückgewinnung. UART nutzt meist drei Leitungen: **TX** (Senden), **RX** (Empfangen) und **GND** (Masse). Da kein Takt mitfließt, müssen beide Seiten blind darauf vertrauen, dass ihre 'Armbanduhren' nur mit minimalem Versatz ungefähr gleich schnell ticken. Diese Frequenz heißt **Baudrate**.

Das alleine wäre störanfällig, weil durch Interferenzen die Uhren nach einiger Zeit zu stark zeitlich voneinander abdriften würden.

**Wieso bleiben trotzdem beide Armbanduhren über die Zeit gleich schnell?**
Die Antwort lautet: Die Clocks bleiben **nicht gleich schnell**. Sie driften permanent. Daher ist das UART Protokoll folgendermaßen aufgebaut:

**UART sendet jedes Byte 'eingepackt'**:
`[Startbit][8 Datenbits][(optional) Parity-Bit][Stoppbit]`

* **Startbit:** signalisiert den Anfang eines Byte
* **Datenbits:** werden im Takt der eigenen Uhr gelesen
* **Stoppbit:** signalisiert das Ende des Bytes

Die Clocks bleiben nicht gleich schnell, starten aber nach jedem Byte von vorne, wodurch die Zeitdifferenzen **minimal** bleiben. UART ist **Full-Duplex**. Da TX und RX getrennte Leitungen sind, können beide Teilnehmer gleichzeitig und unabhängig voneinander senden.

---

## Das Parity-Bit
Das lateinische Wort *paritas* bedeutet Gleichheit. Parität wird als Stimmengleichheit verschiedener Gruppen in einem Gremium verstanden. In der Elektronik ist es die Einigung beider Parteien auf einen **Modus**.

**Die 5 gängigen Parity-Modi:**
1.  **None (Keine):** Es wird schlichtweg kein Parity-Bit gesendet. Das Datenpaket ist nach den 8 Datenbits zu Ende.
2.  **Even (Gerade):** Das Bit wird so gesetzt (0 oder 1), dass die Gesamtzahl der Einsen im Paket **gerade** ist.
3.  **Odd (Ungerade):** Das Bit wird so gesetzt, dass die Gesamtzahl der Einsen **ungerade** ist.
4.  **Mark (1):** Das Parity-Bit ist **immer 1**, unabhängig vom Inhalt der Datenbits (wird selten zur Fehlerprüfung, eher zur Adressierung genutzt).
5.  **Space (0):** Das Parity-Bit ist **immer 0**.

> **Beispiel:** Datenbyte `10110001` (enthält vier `1`-en)
> * Bei **Even Parity**: Das Bit wird **0**, da 4 bereits gerade ist.
> * Bei **Odd Parity**: Das Bit wird **1**, um aus 4 (gerade) eine 5 (ungerade) zu machen.

### Was passiert bei einem Fehler?
Wenn du **Even Parity** eingestellt hast, aber der Empfänger ein Byte mit einer **ungeraden** Anzahl an Einsen erhält, setzt die Hardware ein sogenanntes **Parity Error Flag**. Das Bit kann den Fehler nur bemerken, aber nicht reparieren. Es ist ein reiner Indikator für "Datenkorruption".

---

## Konkrete Anwendungsfälle

### 1. Adressierung (Multi-Processor Communication)
Dies ist der wichtigste Anwendungsfall. In einem Netzwerk mit einem Master und mehreren Slaves (z. B. RS-485) müssen alle Slaves die Leitung abhören.
* **Mark Parity:** Der Master sendet ein Byte mit Mark-Parity (Bit = 1). Das signalisiert den Slaves: "Dieses Byte ist eine **Adresse**."
* **Space Parity:** Der Master sendet Datenbytes mit Space-Parity (Bit = 0). Das signalisiert: "Dieses Byte gehört zu den **Daten** für die zuvor genannte Adresse."
* **Vorteil:** Slaves können Datenbytes ignorieren, die nicht für sie bestimmt sind, und müssen nur bei einem "Mark-Byte" (Adresse) aufwachen und prüfen, ob sie gemeint sind.

### 2. Synchronisations-Check
Manchmal wird ein fester Parity-Zustand genutzt, um die Verbindung zu testen. Wenn der Empfänger **immer** ein Space-Bit (0) erwartet und stattdessen eine 1 empfängt, weiß er sofort, dass die Konfiguration der Baudrate oder die elektrische Verbindung grundlegend falsch ist.

### 3. Kompatibilität mit 9-Bit-Protokollen
Einige ältere Systeme nutzen 9 Datenbits statt 8. Wenn moderne Hardware nur 8-Bit-UART unterstützt, kann man das **Paritätsbit als 9. Datenbit missbrauchen**, indem man es manuell auf Mark (1) oder Space (0) setzt, um das fremde Protokoll zu emulieren.

In der modernen Programmierung (z. B. USB-zu-UART am PC) wird fast ausschließlich **None** (keine Parität) verwendet, da die Fehlerprüfung heute meist in höheren Software-Schichten (Protokollen) stattfindet.
