# Learn Electronics

Selbstgesteuerter Lernpfad durch die Elektronik.

Jede Phase baut auf der vorherigen auf. Die Richtung wird nach jedem Abschluss neu entschieden.

→ [PROJEKTE.md](PROJEKTE.md)

---

## Konvention

Phasen und Kapitel werden in [`.portfolio`](.portfolio) definiert (JSON). Status pro Kapitel: `done`, `wip`, oder kein Status (geplant).

Der Fortschritt wird live aus dieser Datei gelesen und in meinem [Portfolio](https://bruell.tech) angezeigt.

---

## Lagersystem

Alle Bauteile werden in einer SQLite-Datenbank verwaltet (`parts-inventory/lager.db`). Zugriff über:

- **Web-UI** — `uvicorn api:app --reload` in `parts-inventory/`, dann `http://localhost:8000`
- **MCP-Server** — für Claude Code und andere LLM-Clients

### MCP-Server

Der MCP-Server wird für Claude Code automatisch über `.mcp.json` konfiguriert. Für andere Clients und weitere Details siehe [parts-inventory/README.md](parts-inventory/README.md).
