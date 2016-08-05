## Differences between CGI, FastCGI, PHP-CGI, PHP-FPM, Spawn-FCGI [Back](./qa.md)

### CGI

- **CGI**, Common Gateway Interface, is a tool for HTTP server to contact with programs on other servers, which can be used into any languages with standard input, standard output and environmental variables, such as PHP, Perl, or Tcl.

### FastCGI

- **FastCGI** is a kind of CGI which is long-live, which will always be running. With FastCGI, it'll take less time t fork(which is a problem of fork-and-execute mode in CGI). In additional, FastCGI also supports for distributed computing.
- It is also not language related, which is an opened extension of CGI, which is used to keep CGI running in the memory. It's well-known that loading of CGI has been the main reason of low performance.

- the main process of running FastCGI:
    1. Loading the Process Manager of FastCGI when a Web server has booted(IIS ISAPI or Apache Module)
    - The Process Manager of FastCGI will initiate itself to create several CGI processes, which are used to wait for connection of Web servers.
    - When requests from clients have reached the Web server, the Process Manager of FastCGI will select a CGI set up before to connect, whose environmental variables and standard input will be sent to the sub process `php-cgi` of FastCGI.
    - This sub process will return standard output and error info to the Web server with the same connection. Requests will be finished when it closes the connection.
- Therefore, FastCGI only set once for parsing `php.ini`, loading extensions and initiating all the data structures.

#### shortcuts

- Because of multi-processes, FastCGI will cost more memory than CGI, whose each process(PHP-CGI) will cost about 7Mb to 25Mb memory.

> - Data from the article: [Nginx 0.8x + PHP 5.2.13(FastCGI) is 10 times better than Apache(Edition 6)](http://blog.s135.com/nginx_php_v6/)
- when 30k connection happens in parallel, 10 Nginx processes will only cost 150Mb Mem(15Mb * 10), and 64 PHP-CGI will only cost about 1280Mb(20Mb * 64).

### PHP-CGI

- **PHP-CGI** is one kind of the Process Manager of FastCGI, which is within php itself.
- The command to boot is as follow:

```bash
php-cgi -b 127.0.0.1:9000
```

#### shortcuts

- After changing `php.ini`, you should reboot PHP-CGI to make the new `php.ini` work.
- When a PHP-CGI process is killed, all the PHP code will cannot run.(PHP-FPM and Spawn-FCGI do not have the same problem)

### PHP-FPM

- **PHP-FPM** is another kind of the Process Manager of FastCGI, which can be downloaded [here](http://php-fpm.org/download).
- It's actually a patch for PHP, which is used to integrate the Process Manager of FastCGI into PHP, which should be make into PHP before version 5.3.2.
- **PHP-FPM** can be used to control sub processes of PHP-CGI:

```bash
/usr/local/php/sbin/php-fpm [options]

# options
# --start:      start a fastcgi process of php
# --stop:       force to kill a fastcgi process of php
# --quit:       smooth to kill a fastcgi process of php
# --restart:    restart a fastcgi process of php
# --reload:     smooth to reload php.ini
# --logrotate:  enable log files again
```

### Spawn-FCGI

- **Spawn-FCGI** is a general kind of the Process Manager of FastCGI， which is one part of lighttpd.
