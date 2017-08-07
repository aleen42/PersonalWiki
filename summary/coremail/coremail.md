## Coremail	[Back](./../summary.md)

This note is mainly used to remember some developming details and working details in the Coremail inc..

### 1. Domains

Firstly, there is a list of sites for remember:

- OA: http://oa.mailtech.cn/ (OA system for original works)
- Lunkr: http://www.lunkr.cn/ (used for internal communications)
- GitLab: http://git.mailtech.cn/ (used for storing projects)
- Developing Center: http://rd.mailtech.cn/ (used for checking some documents and depoying status)
- Wiki: http://wiki.mailtech.cn/ (detailed information about any transactions in the company)
- Email System: http://mt.icoremail.net/ (for receiving and sending emails)
- SHR System: http://218.107.63.241:7888/shr/home.do
- SSL VPN: https://sslvpn.coremail.cn:8510/

### 2. Development

Then, how to develop?

#### Local installation

The main projects is `cmj`, and install it locally according to [the document](http://git.mailtech.cn/coremail/cmj).

As you can see, it's a Java project, and it means that you may have to use a Java IDE to develop, among which **IDEA** is the choice of this company.

To setup configurations for the Tomcat server, you can run the script:

```bash
node {project_root}/dev/setup.js
```

Then, specify where the Tomcat has been installed according some official documents.

When it comes to the structure of this project, there are three sub-projects:

- **javalib2**
- **templage.NG**
- **wmsvr**

As a front-end developer, what I should focus on is the project **template.NG**, which mainly used to develop templates of Coremail system. In the folder `web`, there are different kinds of templates developed before like `coremail.pad`, `coremail.XT` series, etc. And in the folder `web.modules`, you can see that `coremail.XT5` is under development.

When developing XT5, it's recommended to read documents firstly:

- As it uses webpack v1.x to build dependencies, ES6 is not supported at all
- When developing JavaScript or HTML, use `gulp watch:dev:js` to watch building process
- When developing Less, use `gulp watch:dev:css` to watch building process
- When modifying `moduleHierarchy.js`, use `gulp watch:xt5:hierarchy`
- When developing all, use `gulp dev`

There're some APIs to know on the wiki: http://rd.mailtech.cn/rd/coremail/wmdocs.php

If you want to test in different platforms, you can use the following lists of remote machines:

- XP: **rdtest-xp-01**
- IE6: **rdtest-ie6-01**
- IE7: **rdtest-ie7-01**
- IE8: **rdtest-ie8-01**
- IE9: **rdtest-ie9-01**

Webmail template:

- 5.0.5: 192.168.201.183@user09/123 
- 5.0.6: 192.168.200.191@test9/123

### 3. Advanced

- [**Workflow**](./workflow/workflow.md)
- [**The design of Coremail system**](./coremail_system_design/coremail_system_design.md)
- [**The structure of providers in Coremail**](./coremail_providers_structure/coremail_providers_structure.md)
- [**Deployment of Coremail system**](./deployment/deployment.md)
- [**Secondary Development**](./secondary_development/secondary_development.md)
- [**Lunkr + Coremail**](./lunkr_coremail/lunkr_coremail.md)
- [**Shell for replacing files of XT3**](./shell_xt3_replacement/shell_xt3_replacement.md)
