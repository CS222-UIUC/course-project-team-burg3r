# Course Burg3r

demo: [burg3r.wiki](https://burg3r.wiki)
Doxygen docs: [docs](https://docs.burg3r.wiki)

Class registration can be confusing and overwhelming for students. The Burg3r Schedule helper automatically generates potential schedules from the courses a student needs to take, taking out the trial and error of arranging courses without time conflicts. It further provides a day-to-day interface for ensuring students get from class to class smoothly, including weather, travel distance, and bus transportation information.

[README for backend](https://github.com/CS222-UIUC/course-project-team-burg3r/blob/master/backend/README.md)

# Technical Architecture

![Flowchart](https://github.com/CS222-UIUC/course-project-team-burg3r/raw/master/backend/flowchart.drawio.svg)

For more on how the backend works, please refer to the [backend README](https://github.com/CS222-UIUC/course-project-team-burg3r/blob/master/backend/README.md)

# Deployment

**required packages:**

- `nginx`
- `nodejs` and `npm` (for `pm2` and `express`)
- `pm2` via `npm`
- `express` via `npm`

1. download the api.js and executable from [releases](https://github.com/CS222-UIUC/course-project-team-burg3r/releases/latest):

```shell
wget -O api.js https://raw.githubusercontent.com/CS222-UIUC/course-project-team-burg3r/master/backend/api.js
vim api.js // change the file path
pm2 start api.js
```

2. Copy the sample nginx config `burg3r.wiki.conf` to `/etc/nginx/conf.d/your-doamin.tld.conf` with your own webroot and certificate.

your course burg3r is now available at `https://your-domain.tld/api/process`

to test if its working: `curl -X POST -H "Content-Type: application/json" -d @in.json https://your-domain.tld/api/process -o example/o.json`

consider use [lego](https://github.com/go-acme/lego) for getting a tls certificate ~~(it's far better than acme.sh)~~

note: the default nginx config blocks access from censys.io

# Credit

Frontend: Vivian, Craig
Backend: Caden, Peter
