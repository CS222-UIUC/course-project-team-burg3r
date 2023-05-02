# Overall flowchart:

![Flowchart](https://github.com/CS222-UIUC/course-project-team-burg3r/raw/master/backend/flowchart.png)

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

2. Required Courses + Section Type Input

This file consists of required courses and the type of sections you need: lecture, discussion, etc. This file contains preferences on start and end times for all courses throughout a day allowing you to choose when you want to have classes. It also contains a preferred padding allowing you to choose how much time to allow yourself to travel between classes or allow for breaks. The last piece of information it holds is a field to add blocked out times. These times will not contain any courses. This is useful to allow you to schedule time for work, clubs, and other various events.

```json
{
  "required_courses": [
    {
      "course": "CS 225",
      "types": ["Lecture", "Laboratory-Discussion"]
    },
    {
      "course": "CS 222",
      "types": ["Laboratory-Discussion"]
    },
    {
      "course": "CSE 414",
      "types": ["Lecture"]
    }
  ],
  "preferred_start_time": "05:00",
  "preferred_end_time": "20:00",
  "preferred_padding": "00:10",
  "block_out_times": [
    {
      "day": "MWF",
      "startTime": "07:00",
      "endTime": "08:00"
    }
  ]
}
```

3. Example schedule output

Function was given 5 total courses, 3 of which were required, and 4 total required sections (2 lectures, 2 lab-discussions). Constraints on course times were also provided. Preferences were from 05:00 to 20:00 with a 00:10 padding between courses. Blocked out times were MWF from 07:00 to 08:00. It generated 9 possible schedules and here is one example:

```json
[
    {
        "schedule": [
            {
                "course": "BLOCK",
                "crn": 0,
                "days": [
                    {
                        "day": "M",
                        "end_time": "08:00",
                        "start_time": "07:00"
                    },
                    {
                        "day": "W",
                        "end_time": "08:00",
                        "start_time": "07:00"
                    },
                    {
                        "day": "F",
                        "end_time": "08:00",
                        "start_time": "07:00"
                    }
                ],
                "location": "N/A",
                "section": "BLOCK",
                "type": "BLOCK"
            },
            {
                "course": "CS 225",
                "crn": 31229,
                "days": [
                    {
                        "day": "W",
                        "end_time": "17:50",
                        "start_time": "16:00"
                    }
                ],
                "location": "0035 Campus Instructional Facility",
                "section": "AYF",
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
