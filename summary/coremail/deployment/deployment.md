## Deployment of Coremail system	[Back](./../coremail.md)

Configuration files of Coremail systems are always formatted with `.ini` extension name, in which items are always set as `[xxx]`, and commented with `#`.

- **coremail.cf**
    - host id
    - information of **adminsvr**
    - environmental parameters
- **global.cf**
    - information of license
    - switches of global functions
- **datasources.cf**
    - types of databases
    - host/port
    - user/password
    - name of databases
    - character set
    - connection counts/timeout
- **userschema.cf**
    - custom character field (separated with comma)
- **hosts.cf**
    - host id of devices
    - IP
    - program list
    - program id (UDID, MSID)
    - program weight (MSWeight)
    - configuration overidding