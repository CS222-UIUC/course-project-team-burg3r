# Overall flowchart:

![Flowchart](https://github.com/CS222-UIUC/course-project-team-burg3r/raw/master/backend/FunctionFlowchart.png)

# Data Format

1.  a typical json for a single course:

note: some of the information here might not be very necessary, and I think is best for the generator to check the status when it generates the schedule.

```json
{
  "courseCode": "ABE 225",
  "title": "ABE Principles: Bioenvironment",
  "url": "https://courses.illinois.edu/schedule/2023/spring/ABE",
  "sections": [
    {
      "crn": "57090",
      "status": "restricted",
      "type": "Laboratory",
      "section": "AB1",
      "startTime": "08:00",
      "endTime": "09:50",
      "day": "F",
      "instructor": "242 Agricultural Engr Sciences Bld",
      "url": "https://courses.illinois.edu/schedule/2023/spring/ABE/225"
    },
    {
      "crn": "57091",
      "status": "restricted",
      "type": "Laboratory",
      "section": "AB2",
      "startTime": "10:00",
      "endTime": "11:50",
      "day": "F",
      "instructor": "242 Agricultural Engr Sciences Bld",
      "url": "https://courses.illinois.edu/schedule/2023/spring/ABE/225"
    },
    {
      "crn": "57089",
      "status": "restricted",
      "type": "Lecture-Discussion",
      "section": "AE1",
      "startTime": "08:30",
      "endTime": "09:50",
      "day": "TR",
      "instructor": "208 Agricultural Engr Sciences Bld",
      "url": "https://courses.illinois.edu/schedule/2023/spring/ABE/225"
    }
  ]
}
```

2. Example schedule output

Function was given 5 total courses, 3 of which were required, and 4 total required sections (Ex: Lecture, Lab/Discussion). Constraints on course times were also provided. Preferences were 09:00 to 16:00, with a 00:10 padding between courses. It generated 6 possible schedules and here is one example:

```json
[
  {
    "schedule": [
      {
        "course": "CSE 414",
        "crn": 58767,
        "days": [
          {
            "day": "T",
            "end_time": "15:15",
            "start_time": "14:00"
          },
          {
            "day": "R",
            "end_time": "15:15",
            "start_time": "14:00"
          }
        ],
        "location": "1404 Siebel Center for Comp Sci",
        "section": "AL2",
        "type": "Lecture"
      },
      {
        "course": "CS 222",
        "crn": 71617,
        "days": [
          {
            "day": "W",
            "end_time": "13:50",
            "start_time": "13:00"
          }
        ],
        "location": "1002 Electrical & Computer Eng Bldg",
        "section": "SDL",
        "type": "Laboratory-Discussion"
      },
      {
        "course": "CS 225",
        "crn": 31208,
        "days": [
          {
            "day": "M",
            "end_time": "11:50",
            "start_time": "11:00"
          },
          {
            "day": "W",
            "end_time": "11:50",
            "start_time": "11:00"
          },
          {
            "day": "F",
            "end_time": "11:50",
            "start_time": "11:00"
          }
        ],
        "location": "THEAT Lincoln Hall",
        "section": "AL1",
        "type": "Lecture"
      },
      {
        "course": "CS 225",
        "crn": 31227,
        "days": [
          {
            "day": "R",
            "end_time": "10:50",
            "start_time": "09:00"
          }
        ],
        "location": "4029 Campus Instructional Facility",
        "section": "AYE",
        "type": "Laboratory-Discussion"
      }
    ]
  }
]
```

# Webserver configuration

This project uses Nginx as the webserver. A working `nginx.conf` can be found in this directory; put it in `/etc/nginx/conf.d/` and reload nginx using `systemctl reload nginx`.

Make sure that the user nginx is running under (`www-data`) has read and write access to `/var/www/burg3r`

# API

There's a very simple api written in json

required packages:

- `express`
- `spawn`

a simple `pm2 start api.js` should work. For more documentations on PM2, [here](https://pm2.keymetrics.io/).

sample request:

```curl
curl -X POST -H "Content-Type: application/json" -d @in.json http://localhost:3000/process -o example/o.json
```
