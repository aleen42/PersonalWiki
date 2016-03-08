## Sublime Text 3 Pluggin [Back](./qa.md)

#### Installation on Ubuntu 14.04

i. add a repository

```bash
sudo add-apt-repository ppa:webupd8team/sublime-text-3
```

ii. update libraries of software

```bash
sudo apt-get update 
```

iii. install

```bash
sudo apt-get install sublime-text-installer
```

#### Registration

- here are some code for build **3103 **

```
—– BEGIN LICENSE —–
Michael Barnes
Single User License
EA7E-821385
8A353C41 872A0D5C DF9B2950 AFF6F667
C458EA6D 8EA3C286 98D1D650 131A97AB
AA919AEC EF20E143 B361B1E7 4C8B7F04
B085E65E 2F5F5360 8489D422 FB8FC1AA
93F6323C FD7F7544 3F39C318 D95E6480
FCCC7561 8A4A1741 68FA4223 ADCEDE07
200C25BE DBBC4855 C4CFB774 C5EC138C
0FEC1CEF D9DCECEC D3A5DAD1 01316C36
—— END LICENSE ——

—– BEGIN LICENSE —–
Nicolas Hennion
Single User License
EA7E-866075
8A01AA83 1D668D24 4484AEBC 3B04512C
827B0DE5 69E9B07A A39ACCC0 F95F5410
729D5639 4C37CECB B2522FB3 8D37FDC1
72899363 BBA441AC A5F47F08 6CD3B3FE
CEFB3783 B2E1BA96 71AAF7B4 AFB61B1D
0CC513E7 52FF2333 9F726D2C CDE53B4A
810C0D4F E1F419A3 CDA0832B 8440565A
35BF00F6 4CA9F869 ED10E245 469C233E
—— END LICENSE ——

—– BEGIN LICENSE —–
Anthony Sansone
Single User License
EA7E-878563
28B9A648 42B99D8A F2E3E9E0 16DE076E
E218B3DC F3606379 C33C1526 E8B58964
B2CB3F63 BDF901BE D31424D2 082891B5
F7058694 55FA46D8 EFC11878 0868F093
B17CAFE7 63A78881 86B78E38 0F146238
BAE22DBB D4EC71A1 0EC2E701 C7F9C648
5CF29CA3 1CB14285 19A46991 E9A98676
14FD4777 2D8A0AB6 A444EE0D CA009B54
—— END LICENSE ——

—– BEGIN LICENSE —–
Alexey Plutalov
Single User License
EA7E-860776
3DC19CC1 134CDF23 504DC871 2DE5CE55
585DC8A6 253BB0D9 637C87A2 D8D0BA85
AAE574AD BA7D6DA9 2B9773F2 324C5DEF
17830A4E FBCF9D1D 182406E9 F883EA87
E585BBA1 2538C270 E2E857C2 194283CA
7234FF9E D0392F93 1D16E021 F1914917
63909E12 203C0169 3F08FFC8 86D06EA8
73DDAEF0 AC559F30 A6A67947 B60104C6
—— END LICENSE ——

```

#### Plugins

###### Package Control

i. type `ctrl + ~`

ii. input the following code into the console:

```
import urllib.request,os; pf = 'Package Control.sublime-package'; ipp = sublime.installed_packages_path(); urllib.request.install_opener( urllib.request.build_opener( urllib.request.ProxyHandler()) ); open(os.path.join(ipp, pf), 'wb').write(urllib.request.urlopen( 'http://sublime.wbond.net/' + pf.replace(' ','%20')).read())
```

iii. type `ctrl + shift + p` to input `package contro install` and install plugins you want

###### Emmet

##### Phpcs

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../pic/tail.gif"></a>
