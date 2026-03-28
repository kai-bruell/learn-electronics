# Learn Electronics

Selbstgesteuerter Lernpfad durch die Elektronik.

Jede Phase baut auf der vorherigen auf. Die Richtung wird nach jedem Abschluss neu entschieden.

→ [ROADMAP.md](ROADMAP.md) · [PROJEKTE.md](PROJEKTE.md)

---

## Konvention

```
01-ohmsches-gesetz/       ← Ordner existiert  →  abgeschlossen
WORKING_03-kirchhoff/     ← WORKING_-Präfix   →  aktuell in Arbeit
```

Der Fortschritt wird live aus diesem Repo ausgelesen und in meinem [Portfolio](https://bruell.tech) angezeigt.

---

## Lagersystem

Alle Bauteile werden in einer SQLite-Datenbank verwaltet (`parts-inventory/lager.db`). Zugriff ueber:

- **Web-UI** — `uvicorn api:app --reload` in `parts-inventory/`, dann `http://localhost:8000`
- **MCP-Server** — fuer Claude Code und andere LLM-Clients

Details und Setup: [parts-inventory/README.md](parts-inventory/README.md)
