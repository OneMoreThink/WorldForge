# Git Branching Strategy

**Decision:** Trunk-based development.

**Why:** Solo project, single project state (no parallel versions to maintain), milestones progress sequentially rather than as independent releases — the branching overhead of git-flow (`develop`/`release`/`hotfix`) buys nothing here.

## Branches

| Branch | Purpose | Naming | Example |
|---|---|---|---|
| `main` | Always-buildable trunk; only reflects completed milestone state | - | - |
| Milestone branch | Work for one milestone (see `roadmap.md`) | `m<number>-<slug>` | `m2-renderer`, `m11-mymath` |
| Lab branch (optional) | Only for `Labs/` experiments spanning many commits | `lab/<topic>` | `lab/quaternion-slerp` |

- `Labs/` experiments: commit directly to `main` by default (the directory already isolates them). Use a `lab/*` branch only if an experiment runs multiple days or leaves the tree unstable.
- Trivial single-commit changes (typos, doc/README edits) go straight to `main`, no branch.
- Target branch lifetime: days, up to ~1-2 weeks. If a milestone runs long, sync with `main` frequently rather than letting it diverge.

## Merging

- Merge a milestone branch into `main` only after its Definition of Done is fully met.
- Use `git merge --no-ff` so the milestone shows as a single merge node in history.

```
main     ──●──────────────●───────────►
            \              /
m2-renderer  ●──●──●──●──●   (--no-ff merge)
```

## Tags

- Tag `main` right after each milestone merge: `v0.<milestone-number>-<slug>` (e.g. `v0.0-bootstrap`, `v0.2-renderer`).
- Final Capstone completion: `v1.0`.
- Use tags to diff/compare states later, e.g. `git diff v0.5-game1 v0.6-architecture`.

## Future Considerations

- If collaborators join or the repo goes public: add PR review + CI gating.
- Large milestones (M6 Architecture Refactoring, M20 Editor) may need to be split into sub-branches — revisit then.
- If multiple deployed builds must be maintained in parallel: reintroduce `release/*` branches then.
