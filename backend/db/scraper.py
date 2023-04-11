import os
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.firefox.options import Options

from selenium.webdriver.common.by import By
import re
import requests

import datetime
import json


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def convert_time(time_str):
    # print(time_str)
    start, end = time_str.split(' - ')
    start_time = datetime.datetime.strptime(start, '%I:%M%p')
    end_time = datetime.datetime.strptime(end, '%I:%M%p')
    start_str = start_time.strftime('%H:%M')
    end_str = end_time.strftime('%H:%M')
    return (start_str, end_str)


def get_name(to_extract):
    parts = to_extract.split('/')
    result = "/".join(parts[-2:]).replace("/", "")
    return result


def process_row(row):
    status = "restricted"
    if (cells[2].get_text().strip().find("open") != -1):
        status = "open"
    if (cells[2].get_text().strip().find("close") != -1):
        status = "closed"
    crn = cells[3].get_text().strip()

    course_type = cells[4].get_text().strip()
    section = cells[5].get_text().strip()

    # process time field, online courses might have n.a time
    time = cells[6].get_text().strip()[4:]
    pattern = r'[^0-9APMa-z:\s-]'
    if (re.search(pattern, time)):
        start, end = "N/A", "N/A"
    else:
        start, end = convert_time(time)

    day = cells[7].get_text().strip()
    instructor = cells[8].get_text().strip()
    section = {'crn': crn,
               'status': status,
               'type': course_type,
               'section': section,
               'startTime': start,
               'endTime': end,
               'day': day,
               'instructor': instructor,
               'url': url}
    return section


def get_sections(url):
    driver = webdriver.Firefox()
    # options = Options()
    # options.add_argument('-headless')
    # driver = webdriver.Firefox(options=options)
    driver.get(url)
    html = driver.page_source

    soup = BeautifulSoup(html, "html.parser")

    # click the collapse all button, clean up table interface
    button = driver.find_element(By.ID, 'collapseAllTR')
    button.click()

    rows = soup.find_all('tr', {'class': ['even', 'odd']})

    sections = []

    for row in rows:
        cells = row.find_all('td')
        divs4 = cells[4].find_all('div')
        if len(divs4) > 1:
            print(f"{bcolors.WARNING}They did it again...{bcolors.ENDC}")
            sections.append(
                {"need attention": "yes", "crn": cells[3].get_text().strip()})
        else:
            status = "restricted"
            if (cells[2].get_text().strip().find("open") != -1):
                status = "open"
            if (cells[2].get_text().strip().find("close") != -1):
                status = "closed"
            crn = cells[3].get_text().strip()

            course_type = cells[4].get_text().strip()
            section = cells[5].get_text().strip()

            # process time field, online courses might have n.a time
            time = cells[6].get_text().strip()[4:]
            pattern = r'[^0-9APMa-z:\s-]'
            if (re.search(pattern, time)):
                start, end = "N/A", "N/A"
            else:
                start, end = convert_time(time)

            day = cells[7].get_text().strip()
            instructor = cells[8].get_text().strip()
            section = {'crn': crn,
                       'status': status,
                       'type': course_type,
                       'section': section,
                       'startTime': start,
                       'endTime': end,
                       'day': day,
                       'instructor': instructor,
                       'url': url}
            sections.append(section)

    driver.quit()
    return sections


def get_subject(url):
    driver = webdriver.Firefox()
    driver.get(url)
    html = driver.page_source
    soup = BeautifulSoup(html, "html.parser")

    table = soup.find("table", {"id": "default-dt"})
    rows = table.find_all("tr")

    courses = []

    for row in rows[1:]:
        cells = row.find_all("td")
        code = cells[0].get_text().strip()
        title = cells[1].get_text().strip()

        print("fetching: " + url + "/" + code.rsplit(' ', 1)[-1].strip())
        # os.system('clear')

        # Call the get_section() function for this course
        sections = get_sections(url+"/"+code.rsplit(' ', 1)[-1].strip())
        courses.append(
            {"courseCode": code, "title": title, "url": url, "sections": sections})
    filename = code + ".json"
    with open(filename, 'w') as f:
        json.dump(courses, f, indent=2)
    driver.quit()
    print(f"Data has been saved to {filename}.json!")
    driver.quit()
    return courses

# how it works: main page -> subject page -> courses


def main():
    # get_sections("https://courses.illinois.edu/schedule/2023/spring/ABE/341")
    driver = webdriver.Firefox()
    driver.get("https://courses.illinois.edu/schedule/DEFAULT/DEFAULT")
    html = driver.page_source

    soup = BeautifulSoup(html, "html.parser")

    rows = soup.find_all('tr', {'class': ['even', 'odd']})
    subjects = []

    for row in rows[62:]:
        cells = row.find_all("td")
        code = cells[0].get_text().strip()
        title = cells[1].get_text().strip()

        url = "https://courses.illinois.edu/schedule/2023/spring/" + code.strip()
        print("fetching: " + url)
        # os.system('clear')

        # Call the get_subject() function for this course
        course = get_subject(url)
        subjects.append(
            {"subjectCode": code, "subject": title, "url": url, "courses": course})
    data = {'subjects': subjects}

    # Save the data in JSON format
    with open('data.json', 'w') as f:
        json.dump(data, f, indent=2)
    driver.quit()
    print("Data has been saved to data.json!")


if __name__ == "__main__":
    main()
