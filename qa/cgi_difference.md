## Differences between CGI, FastCGI, PHP-CGI, PHP-FPM, Spawn-FCGI [Back](./qa.md)

### CGI

- **CGI**, Common Gateway Interface, is a tool for HTTP server to contact with programs on other servers, which can be used into any languages with standard input, standard output and environmental variables, such as PHP, Perl, or Tcl.

### FastCGI

- **FastCGI** is a kind of CGI which is long-live, which will always be running. With FastCGI, it'll take less time t fork(which is a problem of fork-and-execute mode in CGI). In additional, FastCGI also supports for distributed computing.
- It is also not language related, which is an opened extension of CGI, which is used to keep CGI running in the memory. It's well-known that loading of CGI has been the main reason of low performance.

- the main process of running FastCGI:
    1. Loading the Process Manager of FastCGI when a Web server has booted(IIS ISAPI or Apache Module)
    - the Process Manager of FastCGI will initiate itself to create several CGI processes, which are used to wait for connection of Web servers.

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
