# VibeKat
**Mostly vibe coded by Claude Opus 4.5. Use at your own discretion!**

A GitHub Pages dashboard to track your [Open Kattis](https://open.kattis.com) progress. 

---

## Setup

### 1. Fork/Clone this repo

```bash
git clone https://github.com/YOUR_USERNAME/kattis-tracker.git
cd kattis-tracker
```

### Install requirements (tested for WSL2)
- Create a python environment `python3 -m venv venv`
- Activate using `source venv/bin/activate`
- Change directory into the scraper folder `cd scraper`
- Run `pip install -r requirements.txt`
- Run `playwright install chromium`

### 2. Create a `.env` file
Add `KATTIS_USERNAME` and `KATTIS_PASSWORD` to it.

### 3. Enable GitHub Pages

1. Go to Settings → Pages
2. Source: Deploy from a branch
3. Branch: `main`, folder: `/docs`
4. Save

### 4. Add your solutions

Put your solution files in the `solutions/` directory:
```
solutions/
├── hello.py
├── different.cpp
├── carrots.java
└── ...
```

File names should match the problem ID (e.g., `menuupdates.cpp` for `https://open.kattis.com/problems/menuupdates`)

### 5. (Optional) Add your TODO Excel file

If you have a `Grind.xlsx` file like the one this was built for:
- Put it in the repo root
- Green-highlighted cells (I am using `#C6E0B4` for reference) are detected as solved
- Problem URLs are extracted and organized by date (date of modification is used as a proxy)

### 6. View the dashboard locally

```bash
cd docs
python -m http.server 8000
# Open http://localhost:8000
```

## File Structure

```
kattis-tracker/
├── .github/
│   └── hooks/
│       └── pre-push            # Automatically syncs before pushing
├── docs/
│   ├── index.html              # Dashboard page
│   └── data.json               # Generated stats (auto-updated)
├── scraper/
│   ├── scraper_playwright.py   # Main scraper script
│   └── requirements.txt
├── solutions/                   # Your solution files
│   ├── problem1.py
│   ├── problem2.cpp
│   └── ...
├── Grind.xlsx                  # (Optional) Your TODO tracking sheet
├── solution_dates.xlsx         # List of problems solved and their respective dates
└── README.md
```

## Known Bugs
1. Trying to scrape the list of solved problems was difficult, current implementation performs early truncation the moment no unique problems are found within the page
1. There seems to be some issues with calculation of the scores. There is a discrepancy between the calculated score and the score displayed by Kattis.
1. For problems that offers a range of their scores, currently the highest value is taken, regardless of whether the problem is actually fully solved.
