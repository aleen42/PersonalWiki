## How to add dns for a server [Back](./qa.md)

1. Use [**DNSPod**](www.dnspod.cn)
2. Have a **configuration** file for your serer:

    - Nginx:

```bash
# cd /etc/nginx/sites-enabled
# vim xxx.conf

server {
    listen       80;
    server_name  xxx.soundtooth.cn;

    location / {
        root   /var/www/video_store/api/soundcreate/public;
        index  index.php index.html index.htm;
        try_files $uri $uri/ /index.php?$query_string;
    }

    # proxy the PHP scripts to Apache listening on 127.0.0.1:80
    #
    #location ~ \.php$ {
    #    proxy_pass   http://127.0.0.1;
    #}

    # pass the PHP scripts to FastCGI server listening on 127.0.0.1:9000
    #
    location ~ \.php$ {
        root           /var/www/xxx;
        #fastcgi_pass   127.0.0.1:9000;
        fastcgi_pass   unix:/var/run/php5-fpm.sock;
        fastcgi_index  index.php;
        fastcgi_param  SCRIPT_FILENAME $document_root$fastcgi_script_name;
        include        fastcgi_params;
    }

    # deny access to .htaccess files, if Apache's document root
    # concurs with nginx's one
    #
    #location ~ /\.ht {
    #    deny  all;
    #}
}
```
