# P03: Kirchhoffsche Gesetze

## Lernziel
Du verstehst die beiden Kirchhoffschen Gesetze und kannst sie auf reale Schaltungen anwenden — als Werkzeug um Spannungen und Ströme systematisch zu berechnen, auch wenn Ohm allein nicht mehr reicht.

## Hintergrund

Du hast das Kirchhoffsche Spannungsgesetz bereits in P01 kennengelernt — ohne es so zu nennen. Dort hast du festgestellt:

```
U_Quelle = U_LED + U_Widerstand
```

Das war kein Zufall. Das ist ein Naturgesetz. Hier lernst du beide Gesetze formal kennen und übst sie gezielt.

---

## Die zwei Gesetze

### Gesetz 1: Knotenregel (Kirchhoffscher Stromgesetz, KCL)

> **Die Summe aller Ströme, die in einen Knoten fließen, ist gleich der Summe aller Ströme, die aus ihm herausfließen.**

```
Σ I_ein = Σ I_aus
```

Ein Knoten ist ein Punkt in der Schaltung, an dem sich Leitungen verzweigen.

**Analogie:** Wasserrohr-Kreuzung. Was reinkommt, muss raus — Wasser kann sich nicht anhäufen.

### Gesetz 2: Maschenregel (Kirchhoffsches Spannungsgesetz, KVL)

> **Die Summe aller Spannungen in einer geschlossenen Masche ist null.**

```
Σ U = 0
```

Oder praktischer formuliert:

> **Die Summe aller Spannungsabfälle ist gleich der Quellenspannung.**

```
U_Quelle = U_1 + U_2 + U_3 + ...
```

**Analogie:** Du startest bei einem Hügel, gehst bergab und bergauf — am Ende bist du wieder auf der gleichen Höhe. Energie kann nicht aus dem Nichts entstehen.

---

## Aufgabe

### Teil A: Maschenregel bestätigen (KVL)

Baue die Schaltung aus P01/P02 erneut auf: `9V → 470Ω → LED → GND`

1. Miss die Spannung über dem Widerstand (U_R).
2. Miss die Spannung über der LED (U_LED).
3. Miss die Gesamtspannung der Batterie (U_ges).
4. Rechne: `U_R + U_LED = ?` — Was stellst du fest?
5. Füge einen zweiten Widerstand (220Ω) in Reihe ein und wiederhole die Messungen. Gilt die Regel noch?

### Teil B: Knotenregel bestätigen (KCL)

Baue eine einfache Parallelschaltung: zwei Widerstände (470Ω und 1kΩ) parallel an 9V.

1. Miss den Strom durch den 470Ω-Zweig (I_1).
2. Miss den Strom durch den 1kΩ-Zweig (I_2).
3. Miss den Gesamtstrom aus der Quelle (I_ges).
4. Rechne: `I_1 + I_2 = ?` — Was stellst du fest?

### Teil C: Anwendung — Unbekannte berechnen

Gegeben ist folgende Schaltung (nur auf dem Papier, kein Aufbau nötig):

```
12V → R1 (330Ω) → Knoten A → R2 (470Ω) → GND
                           → R3 (1kΩ)  → GND
```

1. Berechne die Spannung am Knoten A (Tipp: Gesamtstrom zuerst — aber Vorsicht, R2 und R3 sind parallel!).
2. Berechne den Strom durch R2 und durch R3.
3. Überprüfe mit der Knotenregel: Stimmt `I_R2 + I_R3 = I_ges`?

## Theoriefragen

1. Was ist ein "Knoten" in einer Schaltung? Nenne ein Beispiel aus deinem Alltag.
2. Warum kann die Summe der Spannungen in einer Masche niemals ungleich null sein? (Energieerhaltung)
3. Du misst in einem Zweig 30 mA und in einem anderen 20 mA. Wie viel Strom fließt aus der Quelle?
4. Was haben die Kirchhoffschen Gesetze mit dem Energieerhaltungssatz zu tun?
5. Wo endet Ohms Gesetz und wo beginnt Kirchhoff? Wann brauchst du beide?

## Material

- 1x 9V-Batterie + Clip
- 1x Breadboard
- 1x LED (beliebige Farbe)
- Widerstände: 220Ω, 470Ω, 1kΩ
- Jumper-Kabel
- 1x Multimeter
