Placed these `.conf` file in `/etc/nginx/conf.d/`

before reloadin nginx, use `nginx -t` to test the config files

To issue a certificate, we will be using lego (cuz acme.sh sucks and zerossl is even worse, plus acme.sh's dns mode has multiple bugs...)

```
lego --email somethin@thats.real --http --http.webroot /var/www/course-project-team-burg3r/frontend/website --domains="docs.burg3r.wiki" --domains="burg3r.wiki" -k ec384 run
```
