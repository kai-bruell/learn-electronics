# P02: Breadboard-Praxis & Multimeter

---

## Teil A: Das Breadboard verstehen

- Jede waagerechte 5er-Gruppe im Hauptfeld ist intern verbunden
- Verschiedene Reihen sind getrennt
- Der Trenngraben in der Mitte trennt links und rechts — ideal für ICs
- Stromschienen (+ / –) laufen längs durch — bei manchen Breadboards mit unsichtbarer Unterbrechung in der Mitte

**Alles mit dem Multimeter im Piep-Modus nachprüfen.** Piept → verbunden. Kein Piep → getrennt.

---

## Teil B: Das Multimeter

### Die drei Grundmessungen

| Messung    | Symbol | Einheit | Schaltung   |
|------------|--------|---------|-------------|
| Spannung   | U, V   | Volt    | **parallel** zum Bauteil |
| Strom      | I, A   | Ampere  | **in Reihe** (Stromkreis aufgetrennt) |
| Widerstand | R, Ω   | Ohm     | **außerhalb** der Schaltung, stromlos |

### Spannungsmessung (parallel)

```
+9V ──┬──── Widerstand ──┬──── LED ──┬── GND
      │                  │           │
     [V]                [V]         [V]
   Gesamt           U_Widerstand   U_LED
```

Die Messspitzen des Multimeters werden **parallel** zum zu messenden Bauteil gehalten — der Strom fließt weiter durch die normale Schaltung.

**Was du siehst (Kirchhoff):**
```
U_gesamt = U_Widerstand + U_LED
9V       ≈ (Messwert)   + (Messwert)
```
Die Teilspannungen addieren sich zur Gesamtspannung → Kirchhoffsches Spannungsgesetz in der Praxis.

### Strommessung (in Reihe)

```
+9V ──── Widerstand ──── [A] ──── LED ──── GND
                       Multimeter
                       in Reihe!
```

Der Stromkreis wird aufgetrennt, das Multimeter wird **als Teil der Leitung** eingebaut. Der gesamte Strom fließt durch das Gerät.

> **WICHTIG:** Multimeter im Strommessmodus (A) niemals direkt an eine Spannungsquelle halten — das ist quasi ein Kurzschluss und zerstört die Multimeter-Sicherung sofort (oder das Gerät).

**Messwert mit berechnetem Wert vergleichen:**
```
Gegeben: 9V Batterie, 470 Ω Widerstand, rote LED (~2V)

U_Widerstand = 9V – 2V = 7V
I = U/R = 7V / 470Ω ≈ 14,9 mA

→ Gemessener Strom sollte ca. 15 mA sein
```

### Widerstandsmessung

- Bauteil **aus der Schaltung nehmen** oder zumindest ein Bein abheben
- Warum? Parallelwege in der Schaltung verfälschen das Ergebnis
- Multimeter auf Ω-Bereich, Messspitzen an beide Beine

**Vergleich Farbring → Messwert:**
```
470 Ω: Gelb – Violett – Braun – Gold (±5%)
         4       7      ×10    ±5%
→ 47 × 10 = 470 Ω
→ Zulässiger Bereich: 446,5 Ω bis 493,5 Ω

1kΩ: Braun – Schwarz – Rot – Gold (±5%)
       1        0      ×100  ±5%
→ 10 × 100 = 1.000 Ω
→ Zulässiger Bereich: 950 Ω bis 1.050 Ω
```

---

## Theoriefragen (mit Antworten)

**1. Warum darf man mit dem Multimeter im Strommessmodus (A) niemals direkt an eine Spannungsquelle gehen?**

Im Amperemodus hat das Multimeter einen sehr kleinen Innenwiderstand (fast 0 Ω) — genau so designed, damit es den Stromkreis beim Messen in Reihe kaum beeinflusst. Direkt an die Spannungsquelle bedeutet aber: kein anderer Widerstand in der Schaltung begrenzt den Strom. Das Multimeter wird zum einzigen Pfad → Kurzschluss → der Strom ist nur durch den Innenwiderstand der Quelle begrenzt → Shunt oder Sicherung im Multimeter stirbt.

Das Multimeter kann immer nur maximal den eingestellten Bereich verkraften. Auf 10A eingestellt darf man kurz an ein echtes 10A-Netzteil — aber nur wenn Gerät und Netzteil das wirklich können. Billige Geräte lügen oft bei den Specs.

**2. Warum muss das Messgerät bei der Strommessung in Reihe, bei der Spannungsmessung aber parallel geschaltet werden?**

Strom wird in Reihe gemessen weil der gesamte Strom den Shunt-Widerstand im Multimeter passieren muss. Das Multimeter misst dabei die winzige Spannung über dem bekannten Shunt und rechnet via `I = U/R` zurück — es misst also immer Spannung, auch beim Strom. Würde man parallel messen, würde der Strom den Weg des geringsten Widerstands nehmen (durch den Shunt), das Bauteil daneben überbrücken und die Schaltung komplett verändern.

> *Hinweis: "Weg des geringsten Widerstands" ist vereinfacht. Präziser: Strom fließt durch alle Pfade gleichzeitig, proportional zum Leitwert (1/R). Bei großem Widerstandsunterschied fließt praktisch alles durch den niederohmigen Pfad.*

Spannung misst den Unterschied zweier Potentiale. Ein Potentialunterschied existiert nur zwischen zwei Punkten — deshalb parallel. Das Voltmeter hat einen riesigen Innenwiderstand (~1 MΩ) damit es so gut wie keinen Strom abzweigt und die Schaltung nicht beeinflusst.

**3. Was bedeuten die farbigen Ringe auf einem Widerstand? Dekodiere: orange-orange-braun-gold.**

```
Orange – Orange – Braun – Gold
   3        3      ×10    ±5%

→ 33 × 10 = 330 Ω  (±5%)
```

**4. Warum sollte man Widerstände niemals unter Spannung messen?**

Das Multimeter im Widerstandsmodus legt selbst eine kleine Messspannung an. Liegt gleichzeitig externe Spannung am Bauteil, überlagern sich die Spannungen → falscher Messwert. Außerdem besteht die Gefahr, das Messgerät zu beschädigen.

**5. Wie unterscheiden sich die langen und kurzen Stromschienen (Power Rails) bei einem Standard-Breadboard mit Mitteltrennung?**

Viele Breadboards haben in der Mitte der langen Stromschienen eine unsichtbare Unterbrechung. Die obere Hälfte und untere Hälfte der roten (+) Schiene sind dann **nicht** verbunden — obwohl der rote Strich durchläuft. Vor der ersten Nutzung immer mit dem Durchgangsprüfer testen und ggf. mit einem Jumperkabel überbrücken.

---
