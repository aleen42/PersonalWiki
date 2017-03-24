## Coremail	[Back](./../summary.md)

This note is mainly used to remember some developming details and working details in the Coremail inc..

### Domains

Firstly, there is a list of sites for remember:

- OA: http://oa.mailtech.cn/ (OA system for original works)
- Lunkr: http://www.lunkr.cn/ (used for internal communications)
- GitLab: http://git.mailtech.cn/ (used for storing projects)
- Developing Center: http://rd.mailtech.cn/ (used for checking some documents and depoying status)
- Wiki: http://wiki.mailtech.cn/ (detailed information about any transactions in the company)
- Email System: http://mt.icoremail.net/ (for receiving and sending emails)

### Development

Then, how to develop?

#### Local installation

The main projects is `cmj`, and install it locally according to [the document](http://git.mailtech.cn/coremail/cmj).

As you can see, it's a Java project, and it means that you may have to use a Java IDE to develop, among which **IDEA** is the choice of this company.

To setup configurations for the Tomcat server, you can run the script:

```bash
node {project_root}/dev/setup.js
```

