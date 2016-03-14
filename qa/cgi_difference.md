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

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
