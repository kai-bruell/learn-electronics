# P02: Breadboard-Praxis & Multimeter

## Lernziel
Du verstehst den inneren Aufbau eines Breadboards und kannst das Multimeter sicher und korrekt für Spannungs-, Strom- und Widerstandsmessungen einsetzen.

## Aufgabe

### Teil A: Breadboard verstehen
1. Untersuche dein Breadboard und skizziere, welche Reihen/Spalten intern verbunden sind.
2. Miss mit dem Multimeter (Widerstandsmessmodus, kurz: Durchgangsprüfer/Piep-Modus) nach, welche Löcher tatsächlich verbunden sind — prüfe:
   - Zwei Löcher in derselben 5er-Reihe (Hauptfeld)
   - Zwei Löcher in verschiedenen 5er-Reihen
   - Zwei Löcher auf derselben Stromschiene (Power Rail)
   - Ein Loch im Hauptfeld und eines auf der Stromschiene
3. Baue eine einfache LED-Schaltung (9V → Widerstand 470Ω → LED → GND) korrekt auf dem Breadboard auf.

### Teil B: Multimeter-Praxis
Verwende dieselbe LED-Schaltung aus Teil A für alle Messungen.

1. **Spannungsmessung (parallel):** Miss die Spannung über der LED und über dem Widerstand. Miss auch die Gesamtspannung der Batterie. Addiere die Teilspannungen — was stellst du fest?
2. **Strommessung (in Reihe):** Baue das Multimeter als Strommessgerät in Reihe in die Schaltung ein und miss den fließenden Strom. Vergleiche mit dem berechneten Wert (U/R).
3. **Widerstandsmessung:** Miss einen 470Ω- und einen 1kΩ-Widerstand direkt (außerhalb der Schaltung). Vergleiche den Messwert mit dem Farbring-Sollwert.

## Theoriefragen
1. Warum darf man mit dem Multimeter im Strommessmodus (A) niemals direkt an eine Spannungsquelle gehen?
2. Warum muss das Messgerät bei der Strommessung in Reihe, bei der Spannungsmessung aber parallel geschaltet werden?
3. Was bedeuten die farbigen Ringe auf einem Widerstand? Dekodiere: orange-orange-braun-gold.
4. Warum sollte man Widerstände niemals unter Spannung messen?
5. Wie unterscheiden sich die langen und kurzen Stromschienen (Power Rails) bei einem Standard-Breadboard mit Mitteltrennung?

## Material
- 1x 9V-Batterie + Clip
- 1x Breadboard
- 1x LED (beliebige Farbe)
- Widerstände: 470Ω, 1kΩ
- Jumper-Kabel
- 1x Multimeter
