## Differences between CGI, FastCGI, PHP-CGI, PHP-FPM, Spawn-FCGI [Back](./qa.md)

### CGI

- **CGI**, Common Gateway Interface, is a tool for HTTP server to contact with programs on other servers, which can be used into any languages with standard input, standard output and environmental variables, such as PHP, Perl, or Tcl.

### FastCGI

- **FastCGI** is a kind of CGI which is long-live, which will always be running. With FastCGI, it'll take less time t fork(which is a problem of fork-and-execute mode in CGI). In additional, FastCGI also supports for distributed computing.

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
