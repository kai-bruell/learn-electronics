# Das Ohmsche Gesetz

Das Ohmsche Gesetz beschreibt den Zusammenhang zwischen drei Grundgrößen:

| Symbol | Größe      | Einheit    |
|--------|------------|------------|
| U      | Spannung   | Volt (V)   |
| I      | Strom      | Ampere (A) |
| R      | Widerstand | Ohm (Ω)    |

## Die Formel

```
U = R × I
```

Oder umgestellt:

```
I = U / R        (Strom berechnen)
R = U / I        (Widerstand berechnen)
```

## Einheiten des Widerstands

| Einheit    | Abkürzung | Wert in Ohm        |
|------------|-----------|--------------------|
| Ohm        | Ω         | 1 Ω                |
| Kiloohm    | kΩ        | 1.000 Ω            |
| Megaohm    | MΩ        | 1.000.000 Ω        |
| Gigaohm    | GΩ        | 1.000.000.000 Ω    |

> **Tipp:** In der Praxis begegnen dir fast immer Ω, kΩ und MΩ.

## Theoriefragen

1. **Warum braucht eine LED einen Vorwiderstand?**
   Eine LED hat fast keinen eigenen Widerstand. Ohne Vorwiderstand fließt zu viel Strom → LED brennt durch.

2. **Was passiert wenn du den Widerstand verdoppelst?**
   Der Strom halbiert sich. (`I = U/R` → R×2 bedeutet I/2)

3. **Unterschied Spannung vs. Strom:**
   - Spannung = "Druck" (treibt den Strom an)
   - Strom = "Fluss" (die tatsächlich fließenden Elektronen)

4. **Warum weichen Messwerte ab?**
   - Widerstände haben Toleranzen (±5% oder ±10%)
   - Die LED-Spannung ist nicht exakt 2V
   - Messfehler des Multimeters


Aufgabe LED zum Leuchten bringen mit einem 12V Netzteil.

Ich nehme 20 mA als Richtwert für die LED
20mA = 0.02A

Gegeben:
U=12 VDC
I=0.02 A
R=U/I
R=600 Ohm

Also brauche ich 600 Ohm Wiederstand — ABER: das ist falsch, weil die LED selbst 2V "frisst"!

Kirchhoffsches Spannungsgesetz

```
U_Quelle = U_LED + U_Widerstand
12V      =  2V   +    10V
```

Die Spannung "verteilt" sich auf alle Bauteile in der Reihe.
Was die LED verbraucht, steht dem Widerstand nicht mehr zur Verfügung.

Deshalb ist die richtige Rechnung:

```
U_Widerstand = 12V - 2V = 10V

R = U_Widerstand / I
R = 10V / 0,02A
R = 500 Ω
```

> **Merksatz:** In einer Reihenschaltung addieren sich alle Spannungen zur Gesamtspannung.

### Richtwerte Vorwärtsspannung verschiedener LEDs

| Farbe  | Vorwärtsspannung (Richtwert) |
|--------|------------------------------|
| Rot    | ~2,0 V                       |
| Gelb   | ~2,1 V                       |
| Grün   | ~2,2 V                       |
| Blau   | ~3,3 V                       |
| Weiß   | ~3,3 V                       |

> **Wichtig:** Das sind nur Richtwerte! Jede LED ist anders.
> Immer das **Datenblatt** des jeweiligen Bauteils lesen —
> dort stehen die genauen Werte für Vorwärtsspannung und maximalen Strom.
> Ein falsch berechneter Vorwiderstand kann die LED sofort zerstören.

## Praxis: Den richtigen Widerstand auswählen

Widerstände gibt es nicht in jedem beliebigen Wert — nur in bestimmten **Standardwerten** (sogenannte E-Reihen).

Die häufigste Reihe im Hobbybereich ist die **E12-Reihe**. Sie hat 12 Grundwerte:

```
10 – 12 – 15 – 18 – 22 – 27 – 33 – 39 – 47 – 56 – 68 – 82
```

Diese 12 Werte wiederholen sich in jeder Dekade — du multiplizierst sie einfach mit 10, 100, 1000 usw.:

| Grundwert | × 1  | × 10   | × 100    | × 1000       |
|-----------|------|--------|----------|--------------|
| 47        | 47 Ω | 470 Ω  | 4,7 kΩ   | 47 kΩ        |
| 56        | 56 Ω | 560 Ω  | 5,6 kΩ   | 56 kΩ        |

470 Ω und 560 Ω sind also **beide aus der gleichen E12-Reihe** — nur der Grundwert (47 bzw. 56) mit ×10 multipliziert.

### Beispiel: Wir brauchen 500 Ω

500 Ω gibt es nicht als Standardwert. Die nächsten E12-Werte sind:
- 470 Ω → zu wenig Widerstand → etwas mehr Strom → LED leuchtet heller, aber Grenzwert näher
- 560 Ω → etwas mehr Widerstand → etwas weniger Strom → LED leuchtet minimal dunkler, aber sicherer

**Faustregel:** Im Zweifel den **nächst größeren** Wert nehmen — die LED lebt länger.

### Besondere Schreibweise auf Widerständen

Widerstände sind oft direkt beschriftet. Dabei ersetzt der Buchstabe (K oder M) das Komma —
ein alter Industrie-Standard damit Kommas auf Platinen nicht verloren gehen
oder mit Punkten verwechselt werden.

| Aufdruck | Bedeutung       |
|----------|-----------------|
| 10       | 10 Ω            |
| 100      | 100 Ω           |
| 220      | 220 Ω           |
| 330      | 330 Ω           |
| 1K       | 1.000 Ω = 1 kΩ  |
| 2K       | 2.000 Ω = 2 kΩ  |
| 5K1      | 5.100 Ω = 5,1 kΩ|
| 10K      | 10.000 Ω = 10 kΩ|
| 100K     | 100.000 Ω = 100 kΩ|
| 1M       | 1.000.000 Ω = 1 MΩ|

## Farbcode (Color Code)

Widerstände haben bunte Ringe — das ist der Farbcode.
Jede Farbe steht für eine Zahl:

| Farbe   | Ziffer | Als Multiplikator |
|---------|--------|-------------------|
| Schwarz | 0      | × 1               |
| Braun   | 1      | × 10              |
| Rot     | 2      | × 100             |
| Orange  | 3      | × 1.000           |
| Gelb    | 4      | × 10.000          |
| Grün    | 5      | × 100.000         |
| Blau    | 6      | × 1.000.000       |
| Violett | 7      | –                 |
| Grau    | 8      | –                 |
| Weiß    | 9      | –                 |

Der häufigste Fall: **4 Ringe**

```
Ring 1 = erste Ziffer
Ring 2 = zweite Ziffer
Ring 3 = Multiplikator
Ring 4 = Toleranz (Gold = ±5%, Silber = ±10%)
```

### Beispiel: 220 Ω

```
Rot – Rot – Braun – Gold
 2      2    ×10    ±5%

→ 22 × 10 = 220 Ω
```

### Beispiel: 1K (1.000 Ω)

```
Braun – Schwarz – Rot – Gold
  1        0      ×100  ±5%

→ 10 × 100 = 1.000 Ω
```

> **Merksatz:** Die ersten zwei Ringe sind die Zahl, der dritte Ring sagt wie viele Nullen dranhängen.

```
Berechnet:  500 Ω
Gewählt:    560 Ω  ← sicherere Wahl
```

## Versuchsaufbau auf dem Breadboard

### Breadboard verstehen
Tipp: Multimeter auf Durchgangsprüfung (Piepser) stellen und zwei Jumperkabel einstecken —
so siehst du schnell welche Löcher intern verbunden sind.

### LED einsetzen: Anode und Kathode
- Langes Beinchen = **Anode (+)**
- Kurzes Beinchen = **Kathode (–)**

Widerstände haben keine Durchflussrichtung — die kannst du beliebig herum einstecken.

### Wo kommt der Widerstand hin?

Elektrisch ist es egal ob der Widerstand vor oder hinter der LED sitzt —
er begrenzt den Stromfluss im gesamten Stromkreis.

**Best Practice: Widerstand auf die Seite der Anode (+)**

Warum?
- Der Widerstand ist direkt "am Eingang" und begrenzt sofort den Strom
- Wenn du aus Versehen irgendwo abrutschst oder falsch misst, passiert weniger
- In Lehrbüchern und Schaltplänen wird es so gezeichnet → erleichtert Zusammenarbeit und Fehlersuche

### Aufbau

```
12V (+) → 330 Ω → 220 Ω → Anode (LED) → Kathode (LED) → GND (–)
```

330 Ω + 220 Ω in Reihe = 550 Ω → rote LED leuchtet ✓

### Reihenfolge beim Anschließen: erst Minus, dann Plus

Wenn Plus schon verbunden ist und du mit einem Kabel abrutschst → Kurzschluss möglich.
Wenn zuerst Minus dran ist, passiert beim Hantieren mit Plus weniger schnell etwas Gefährliches.

> **Merksatz:** Erst Minus, dann Plus. Beim Trennen: erst Plus, dann Minus.

---

