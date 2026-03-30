# Learn Electronics

Selbstgesteuerter Lernpfad durch die Elektronik.

Jede Phase baut auf der vorherigen auf. Die Richtung wird nach jedem Abschluss neu entschieden.

---

## Konvention

Phasen und Kapitel werden in [`.portfolio`](.portfolio) definiert (JSON). Status pro Kapitel: 

- `done`: Abgeschlossen
- `wip`: In Arbeit
- kein Status: In Planung.

Der Fortschritt wird live aus dieser Datei gelesen und in meinem [Portfolio](https://kai.bruell.tech) angezeigt.

---

## Lagersystem

Alle Bauteile werden in einer SQLite-Datenbank verwaltet (`parts-inventory/lager.db`). Zugriff über:

- **Web-UI** — `uvicorn api:app --reload` in `parts-inventory/`, dann `http://localhost:8000`
- **MCP-Server** — für Claude Code und andere LLM-Clients

### Was kann das Lagersystem?

- **Bauteile verwalten** — Anlegen, bearbeiten, löschen und per Volltextsuche finden. Jedes Teil hat eine automatisch vergebene Warennummer (z.B. `R-001`), Kategorie, Name, Wert und Bestand.
- **Kategorien** — 12 Standardkategorien (Resistors, ICs, LEDs, Capacitors, …) plus beliebig erweiterbar. Umbenennen passt alle Warennummern automatisch an.
- **Projekte & Stücklisten (BOM)** — Projekte anlegen und Bauteile mit Stückzahl zuordnen. Beim **Checkout** werden die BOM-Mengen vom Lagerbestand abgezogen, beim **Checkin** zurückgebucht — die Differenz wird als Verbrauch protokolliert.
- **Verbrauchsprotokoll** — Dokumentiert, welche Teile in welchem Projekt verbraucht wurden. Fehlbuchungen lassen sich nachträglich korrigieren.
- **CSV-Import** — Bestehende Teilelisten per CSV importieren; bei bekannten Warennummern wird der Bestand aufaddiert.
- **Snapshots** — Datenbank-Backups erstellen und bei Bedarf wiederherstellen.

### MCP-Server

Der MCP-Server wird für Claude Code automatisch über `.mcp.json` konfiguriert. Für andere Clients und weitere Details siehe [parts-inventory/README.md](parts-inventory/README.md).
