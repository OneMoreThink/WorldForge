# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Documentation Rules

- All docs under `docs/` are written in **English**, concise, and scannable — reference material for agents and future-you, not narrative essays. No motivational prose, no long background storytelling.
- Significant architecture or process decisions get their own file in `docs/<topic>.md`, structured as: **Decision**, **Why**, **Rules**, **Future Considerations**. Use `docs/branching-strategy.md` as the reference example for both content and length.
- `docs/roadmap.md` stays a compact reference (goal, tech stack, milestone table). Do not re-add long narrative sections. Per-milestone friction/learnings go to `ENGINE_NOTES.md`; deferred ideas go to `BACKLOG.md` (both at repo root, create on first use).
- Milestone completion is tracked via git tags (see `docs/branching-strategy.md`), not by editing `roadmap.md` — don't turn the roadmap into a changelog.
