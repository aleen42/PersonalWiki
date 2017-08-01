## Lunkr + Coremail	[Back](./../coremail.md)

This article is mainly used for deploying a **Lunkr Server** (192.168.201.210) with a **Coremail Server** (192.168.200.130).

### 1. Deploy a Lunkr server

The installation package is on the filer:

`\\192.168.209.6\qc\cim\release\01.Lunkr\10.other\03.论客程序包`

Firstly, access the server and download the latest Lunkr package for installation, like `lunkr.bak.20170222.tgz`:

Then, upload the package to the server which you want to install into.

Before installing the package, you may also need to backup your local Coremail as the package will install another one to override it:

1. Stop all the served applications firstly, including MySQL:
    ```bash
    /home/coremail/sbin/cmctrl.sh stop all
    ```
2. Back up the original Coremail package:
    ```bash
    tar zcvf /home/coremail.bak.tgz /home/coremail
    ```

After that, just remove the original Coremail package:

```bash
sudo rm -rf /home/coremail
```

Then release the Lunkr package you have uploaded before:

```bash
tar zxvf /home/lunkr.bak.tgz -C /home
```

After that, just start all served applications:

```bash
/home/coremail/sbin/cmctrl.sh start all
```

### 2. Sync organizations of Coremail

Since then, you have installed a server for Lunkr in the previous section, and now you may need to synchronize data of certain organizations in Coremail with `udsyncutil`. In the following tutorial, I will take the organization, which organization id is `a`, as an example.

#### 2.1 Install a package

Before the process of synchronizing, download the related package from the following path:

`\\192.168.209.6\qc\cim\release\04.customer\CIM-9140\cmXT5.0.x_lunkr_cm_proxy_RHEL6_x86_64.tar.gz`

Then upload it to the Coremail Server, and place it at the path `/home/coremail` and release it.

After that, you can start to install the package you downloaded:

```bash
$ cd /home/coremail/install/options/lunkr_cm_proxy
$ ./install.sh

Runing in Linux system ......
Input the home directory for coremail system [/home/coremail]:
Input the home directory of java runtime library [/home/coremail/java/jdk1.8.0_45]:
Input the home directory of Tomcat [/home/coremail/java/tomcat]:
Updating Database setting ...
read configure [default/hostid] from coremail.cf...
read configure [udsvr/user] from programs.cf...
merge configure /home/coremail/install/options/lunkr_cm_proxy/conf/iplimit.cf to iplimit.cf...
T:1927100192(16:59:56)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure iplimit.cf ok!
merge configure /home/coremail/install/options/lunkr_cm_proxy/conf/programs.cf to programs.cf...
T:3727279904(16:59:56)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure programs.cf ok!
merge configure /home/coremail/install/options/lunkr_cm_proxy/conf/region.cf to region.cf...
T:2052896544(16:59:56)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure region.cf ok!
merge configure /home/coremail/install/options/lunkr_cm_proxy/conf/services.cf to services.cf...
T:3806852896(16:59:56)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure services.cf ok!
update configure [Centos6x64/BackupMirrorDir=$(COREMAIL_HOME)/var/backupmirror] to hosts.cf...
T:786081568(16:59:56)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure hosts.cf ok!
update configure [udsyncsvr/user=coremail] to programs.cf...
T:204060448(16:59:56)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure programs.cf ok!
add configure [Centos6x64/ProgramsList=udsyncsvr] to hosts.cf...
T:174827296(16:59:56)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure hosts.cf ok!
add configure [Centos6x64/ProgramsList=udsyncutil] to hosts.cf...
T:44566304(16:59:56)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure hosts.cf ok!
Removing the template comment ...
Replacing the template ...
Replacing the template var ...
call /home/coremail/install/options/lunkr_cm_proxy/ext-bin/init-setting.sh to init region
read configure [global/RegionType] from global.cf...
read configure [global/RegionId] from global.cf...
```

Set the node name for the Coremail Server:

```bash
local subnode name: sub_rtan   # important configuration, which can't be modified in the future
read configure [Default/Hostid] from coremail.cf...
read configure [global/MSPathOffset] from global.cf...
Input the DataSource information for MD ...
read configure [cm_md_db/Driver] from datasources.cf...
read configure [cm_md_db/User] from datasources.cf...
read configure [cm_md_db/Server] from datasources.cf...
read configure [cm_md_db/Port] from datasources.cf...
read configure [cm_md_db/Database] from datasources.cf...
read configure [cm_md_db/Password] from datasources.cf...
  The last MD database setting is : [mysql] cmxt (User:coremail Host:127.0.0.1 Port:3308)
Is it the MD setting the same as MD? [y/n] : [y]: y
update configure [global/MSPathOffset=28950] to global.cf...
T:3450717984(17:00:06)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure global.cf ok!
update configure [global/RegionId=sub_rtan] to global.cf...
T:2395944736(17:00:06)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure global.cf ok!
update configure [global/RegionType=subnode] to global.cf...
T:1385965344(17:00:07)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure global.cf ok!
update configure [udsyncutil/SyncOrgs=@md] to programs.cf...
T:271763232(17:00:07)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure programs.cf ok!
update configure [udsvr/UDBinLogSetting=$(COREMAIL_HOME)/var/udbinlog,10] to programs.cf...
T:87340832(17:00:07)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure programs.cf ok!
update configure [RmiServer/BinLogPushOrg=@all] to programs.cf...
T:3122591520(17:00:08)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure programs.cf ok!
update configure [udsyncsvr/SkipSyncUserAttrList=popweb] to programs.cf...
T:3835692832(17:00:08)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure programs.cf ok!
update configure [udsyncsvr/CheckRegionIPInterval=1800] to programs.cf...
T:3848976160(17:00:08)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure programs.cf ok!
Restarting server ...
try to reload all udsyncsvr...
/home/coremail/bin/sysutil --svr-cmd @all udsyncsvr reload  OK
try to call coremail to restart udsvr mdsvr mssvr rmiserver udsyncutil
```

Set the center region of the Lunkr Server:

```bash
try to add lunkrcenter region
remote region host ip [223.252.214.39]: 192.168.201.210   # the IP of the Lunkr Server
read configure [global/RegionMaster] from global.cf...
remote region sync port [6630]:
add configure [mtasvr/FreeIPList=192.168.200.166] to programs.cf...
T:2255746848(17:02:45)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure programs.cf ok!
add configure [mtasvr/SpamInfoTrustedIPList=192.168.200.166] to programs.cf...
T:481294112(17:02:45)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure programs.cf ok!
update configure [lunkrcenter/UdSyncSetting=192.168.200.166:6630] to region.cf...
T:2374903584(17:02:45)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure region.cf ok!
update configure [lunkrcenter/SyncUserObjType=@all] to region.cf...
T:3572606752(17:02:45)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure region.cf ok!
update configure [lunkrcenter/SkipUDCmdList=!1004] to region.cf...
T:3530835744(17:02:45)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure region.cf ok!
update configure [lunkrcenter/EnableAutoForceSyncFlags=1] to region.cf...
T:2125133600(17:02:45)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure region.cf ok!
update configure [lunkrcenter/EnableRealTimeSyncFlags=1] to region.cf...
T:3650447136(17:02:45)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure region.cf ok!
update configure [lunkrcenter/CheckRegionIPStat=0] to region.cf...
T:264840992(17:02:45)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure region.cf ok!
update configure [lunkrcenter/UpdateDomainConf=0] to region.cf...
T:1526380320(17:02:45)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure region.cf ok!
update configure [lunkrcenter/IsLunkrRegion=1] to region.cf...
T:3923334944(17:02:45)[System.Socket:Debug] SocketID:3 reconnect to 127.0.0.1:6130 send presend code[305], timeout:410 OK
upload configure region.cf ok!
Reloading server ...
```

Finally, check whether it's successful:

```bash
telnet 0 6630
```

#### 2.2 Configure

After installing the package above, it's time to configure in both of the Lunkr Server and the Coremail Server.

For the Lunkr Server:

1. Configure `region.cf`:
    ```bash
    [sub_rtan]
    NodeType="mirror"
    EnableRealTimeSyncFlags="1"
    EnableAutoForceSyncFlags="1"
    UpdateDomainConf="0"
    CheckRegionIPStat="0"
    SyncAdminType="OA,OUA"
    SyncPrivacyLevel="1"
    SyncLocalOrgCosId="1:1000"
    SkipUDCmdList="!1004"
    UdSyncDefCOS="1"
    Person.Contact.DeleteStrategy="1"
    Person.MailList.DeleteStrategy="1"
    Person.User.DeleteStrategy="1"
    SyncUserKeys="alias,privacy_level"
    SyncPersonTypes="U"
    SyncLocalOrg="sub_rtan-*"
    SyncRemoteOrg="**"
    APIHost="udsync:/sub_rtan"
    SyncType="coremail-api"
    UdSyncSetting="192.168.200.130:6630"
    ```
2. Configure `iplimit.cf`:
    ```bash
    [udsynclimit]
    iprange1="0.0.0.0-255.255.255.255:r:0:10000"
    iprange2="127.0.0.1:a:0:10000"
    iprange3="192.168.200.130:a:0:10000"
    ```
3. Restart:
    ```bash
    /home/coremail/bin/coremail restart all
    ```

For the Coremail Server:

1. Configure `region.cf`:
    ```bash
    [cen05]   # the node name of the Lunkr Server, which can be found in the `global.cf`
    IsLunkrRegion="1"
    UpdateDomainConf="0"
    CheckRegionIPStat="0"
    EnableRealTimeSyncFlags="1"
    EnableAutoForceSyncFlags="1"
    SkipUDCmdList="!1004"
    SyncUserObjType="@all"
    UdSyncSetting="192.168.202.210:6630"
    ```
2. Configure `iplimit.cf`:
    ```bash
    [udsynclimit]
    iprange="192.168.201.210:a:1:12345"
    iprange1="0.0.0.0-255.255.255.255:r:0:10000"
    iprange2="127.0.0.1:a:0:10000"
    ```
3. Restart:
    ```bash
    /home/coremail/bin/sysutil --svr-cmd @all udsyncsvr reload
    /home/coremail/bin/coremail restart udsyncutil udsvr udsyncsvr
    ```
4. Register the Lunkr Server:
    ```bash
    /home/coremail/bin/sautil callapi "{cmd:23,org_id:org_id,attrs:{org_region_id:cen05}}"
    ```

#### 2.3 Start to synchronize

In the Coremail Server:

```bash
cd /home/coremail/bin
./cim-sync-setting.sh
```

Then choose **2**, and type **#a** after that.

In the Lunkr Server:

```bash
/home/coremail/bin/sautil sync-region-oab sub_rtan --syncOrgs=a
/home/coremail/bin/udsyncutil --syncorg @sub_rtan orglist=a
```