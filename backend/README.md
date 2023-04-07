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

# Webserver configuration

This project uses Nginx as the webserver. A working `nginx.conf` can be found in this directory; put it in `/etc/nginx/conf.d/` and reload nginx using `systemctl reload nginx`.

Make sure that the user nginx is running under (`www-data`) has read and write access to `/var/www/burg3r`
