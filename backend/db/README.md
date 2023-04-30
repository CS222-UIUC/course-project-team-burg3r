# Scrappy.py


This python scrapper helps to fetch all the courses from UIUC's course explorer.

**Requirement**

- `geckodriver`
- `bs4`
- `selenium`
- `re`
- `requests`
- `datetime`
- `json`

**Usage**

```
python3 scrapper.py
```

note: if the script failed and you want to start from specific index, just modify line 181;

```python3
for row in rows[starting_index:]:
```

to merge all json files into one single json containing all the courses in the json files: 

```
parser.sh <source_folder> <output_file.json>
```

**Known Issue**
1. Some of the courses are using one CRN for both lab and lecture section (for example: https://courses.illinois.edu/schedule/2023/fall/ABE/100). This script does not support that. Instead you will the script outputing "they did it again".
