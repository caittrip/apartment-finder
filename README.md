Apartment Finder

COP3530 Project 2 | Group 84

For our project, we decided to create an apartment finder that sorts through a database of about 100k apartments throughout the country and 
based on user inputted data like max rent, minimum bed/bath, location, and square footage, we give a score to apartments that best fit their 
priorities using Heap Sort and Merge Sort to rank these apartments based on their score. It outputs in a readable manner that displays 10 apartments
ranked highest to lowest in score with the ability to read each listing in detail, skip to next or previous page, or exit. We implemented a way
to track the time between both sort algorithms, and a check to make sure both sorted the same way.

Team
| Name | GitHub | Role |
|---|---|---|
| Vedhika Anand | vedhika2727 | Questionnaire, results interface, input validation |
| Caitlyn Tripician | caittrip | Data cleaning and loading, filtering, merge sort |
| Derek Sung | Dsung0107 | Scoring formula, heap sort, sort timing |

Features
- Questionnaire for state, city, max rent, minimum bedrooms and bathrooms, desired square footage, and 1–5 importance ratings
- Filter for listings that don't meet the requirements
- A 0–100 match score weighted by user inputted affordability and space
- Results ranked by 0-100 score, using listing ID to break ties
- Timed heap sort vs merge sort and a check to show both match
- Interactable and easy-to-read output that shows data in pages

Data
[Apartment for Rent Classified (100K)](https://archive.ics.uci.edu/dataset/555/apartment+for+rent+classified), UCI Machine Learning Repository. Cleaned in R (`data/Data-Cleaning.Rmd`) to 99,431 listings in `data/apartment_data.csv`.

TO RUN PROGRAM:
The program requires a C++14 compiler and must be run from the project root so it can open `data/apartment_data.csv`.

Option 1: CLion
1. Open the project folder in CLion and let CMake load.
2. Go to Run -> Edit Configurations, select `apartment_finder`, and set Working directory to the project folder.
3. Click Run.

Option 2: Terminal
From the project root:

With CMake
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
Then run `.\build\apartment_finder.exe` 

With g++
```bash
g++ -std=c++14 -O2 *.cpp -o apartment_finder
```
Then run `.\apartment_finder.exe` 

How to Use:
1. Enter a state abbreviation (i.e. `FL`) and city (i.e. `Gainesville`), or press `Enter` to skip either.
2. Enter your max rent, minimum bedrooms and bathrooms, desired square footage, and importance ratings.
3. Use `n` or `p` to page through results, `d` to view a listing, `r` to search again, or `q` to quit.

Project Structure
| File | Purpose                                       |
|---|-----------------------------------------------|
| `main.cpp` | questionnaire, timing, and results menu       |
| `ApartmentLoader` | reads the csv into `Apartment` objects        |
| `Filtering` | removes listings that don't meet requirements |
| `Scoring` | algorithm to calculate match score            |
| `HeapSort` | iterative and in-place heap sort              |
| `MergeSort` | recursive merge sort                          |
| `Apartment.h` | apartment struct                              |