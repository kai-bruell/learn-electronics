# P03: Kirchhoffsche Gesetze

---

## Die zwei Gesetze

### KCL — Knotenregel (Kirchhoffsches Stromgesetz)

Ein **Knoten** ist ein Punkt, an dem sich mindestens drei Leitungen treffen.

```
Σ I_ein = Σ I_aus
```

Die Summe aller zufließenden Ströme ist gleich der Summe aller abfließenden Ströme. Folgt direkt aus der Ladungserhaltung — Ladung akkumuliert sich in einem Knoten nicht.

### KVL — Maschenregel (Kirchhoffsches Spannungsgesetz)

Eine **Masche** ist ein geschlossener Umlauf in einer Schaltung.

```
Σ U = 0
```

Die Summe aller Spannungen entlang einer geschlossenen Masche ist null. Folgt aus der Energieerhaltung — Spannung ist Energie pro Ladung, und nach einem vollständigen Umlauf ist die Nettoenergieänderung null.

Praktisch formuliert:

```
U_Quelle = U_1 + U_2 + U_3 + ...
```

---

## Theoriefragen

**1. Was ist ein Knoten, was ist eine Masche?**

**Knoten:** Verzweigungspunkt mit ≥ 3 Leitungen. Hier teilt sich Strom auf oder wird zusammengeführt.

**Masche:** Jeder geschlossene Umlauf in einem Netzwerk — egal ob du dabei durch Quellen, Widerstände oder beides läufst.

---

**2. Warum ist Σ U in einer Masche zwingend null?**

Spannung beschreibt die potentielle Energie pro Ladungseinheit (V = J/C). Ein vollständiger Umlauf bringt eine Ladung zum Ausgangspunkt zurück — das elektrische Potential ist ein konservatives Feld. Der Gesamtarbeit auf dem geschlossenen Weg ist null. Wäre die Maschensumme ≠ 0, ließe sich durch wiederholtes Umlaufen Energie erzeugen — das widerspricht dem ersten Hauptsatz der Thermodynamik.

---

**3. Zweig 1: 30 mA, Zweig 2: 20 mA — wie viel liefert die Quelle?**

```
I_ges = 30 mA + 20 mA = 50 mA
```

---

**4. Verhältnis KCL/KVL zu den Erhaltungssätzen**

| Gesetz | Erhaltungsgröße |
|--------|----------------|
| KCL    | Elektrische Ladung |
| KVL    | Energie (konservatives Potentialfeld) |

Kirchhoff hat 1845 keine neuen Naturgesetze aufgestellt — er hat Ladungs- und Energieerhaltung auf Netzwerke formalisiert.

---

**5. Abgrenzung Ohm vs. Kirchhoff**

Ohmsches Gesetz beschreibt das Verhalten eines einzelnen ohmschen Bauteils:
```
U = R × I
```

Kirchhoff beschreibt, wie sich Spannungen und Ströme in einem Netzwerk aus mehreren Bauteilen verteilen. Sobald mehr als ein Zweig existiert, reicht Ohm allein nicht — man braucht KCL und KVL um die Randbedingungen des Netzwerks aufzustellen, bevor Ohm auf einzelne Zweige angewendet werden kann.

**Typisches Vorgehen bei Netzwerkanalyse:**
1. KVL → Maschengleichungen aufstellen
2. KCL → Knotengleichungen aufstellen
3. Gleichungssystem lösen
4. Ohm → konkrete U/I-Werte der einzelnen Bauteile bestimmen
