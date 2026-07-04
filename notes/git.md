# Git Lesson: Wrong Repository Structure (Common Beginner Mistake)

## Problem
I initialized Git in the wrong directory level or created nested repositories unintentionally.

This caused `git status` to show paths like:
../../.gitignore
../../notes/

instead of clean project-relative paths.

## Why this happens
- Running `git init` inside a subfolder instead of the project root
- Cloning a repo, then creating another Git repo inside it
- Mixing multiple project levels in one workspace

## Symptoms
- Files appear with ../../ paths in git status
- Confusing file tracking behavior
- Push/pull issues or missing files in remote repository

## How I diagnosed it
Commands used:
- pwd → checked current location
- git rev-parse --show-toplevel → checked Git root
- git status → revealed incorrect structure

## Correct structure should be:
cpp-qt-roadmap/
├── .git/
├── README.md
├── notes/
├── week01/
│   └── day01/

## Fix applied
- Moved to correct repository root
- Removed incorrect nested Git initialization (if needed)
- Re-added and committed files from root level

## Lesson learned
Always verify the repository root BEFORE running:
- git init
- git add .
- git commit

Rule:
"If git paths look weird, check repo root immediately."àà

