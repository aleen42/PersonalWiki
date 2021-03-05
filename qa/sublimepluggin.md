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

iii. type `ctrl + shift + p` to input `package contro install` and install plugins you want: 

###### All Autocomplete

###### DocBlockr

###### Emmet

###### GitGutter-Edge

###### HTML/CSS/JS Prettify

###### jQuery

###### Phpcs

- install `phpcs`, `phpcbf`, `phpmd` , `php-cs-fixer` with the following steps:

i. PHP Pear

`sudo apt-get install php-pear`

ii. PHP Code Sniffer (phpcs) Pear Package

```bash
sudo pear install PHP_CodeSniffer
#after installation please check it with this code
which phpcs
# mine return /usr/bin/phpcs
```

iii. PHP Depends Pear Package

```bash
sudo pear channel-discover pear.pdepend.org
sudo pear install pdepend/PHP_Depend
```

iv. PHP Mess Detector (phpmd) Pear Package

```bash
sudo pear channel-discover pear.phpmd.org
sudo pear remote-list -c phpmd
sudo pear install phpmd/PHP_PMD 1.5.0
#after installation please check it with this code
which phpmd
# mine return /usr/bin/phpmd
```

v. Install PHP CS-Fixer

```bash
sudo curl http://get.sensiolabs.org/php-cs-fixer.phar -o /usr/local/bin/php-cs-fixer
sudo chmod a+x /usr/local/bin/php-cs-fixer
```

vi. Install ocaml language interpreter

```bash
sudo apt-get install ocaml
```

vii. Install zlib.h libraries. Somehow my zlib library has broken. You can skip this step.

```bash
sudo apt-get install zlib1g-dev
```

viii. Install pfff

```bash
cd /opt/
git clone --depth=1 https://github.com/facebook/pfff.git
sudo ./configure
sudo make depend
sudo make
sudo make opt
```

vvi. setup for users to specify local path to the command above:

```js
{
    // Plugin settings

    // Turn the debug output on/off
    "show_debug": false,

    // Which file types (file extensions), do you want the plugin to
    // execute for
    "extensions_to_execute": ["php"],

    // Do we need to blacklist any sub extensions from extensions_to_execute
    // An example would be ["twig.php"]
    "extensions_to_blacklist": [],

    // Execute the sniffer on file save
    "phpcs_execute_on_save": true,

    // Show the error list after save.
    "phpcs_show_errors_on_save": false,

    // Show the errors in the gutter
    "phpcs_show_gutter_marks": true,

    // Show outline for errors
    "phpcs_outline_for_errors": true,

    // Show the errors in the status bar
    "phpcs_show_errors_in_status": true,

    // Show the errors in the quick panel so you can then goto line
    "phpcs_show_quick_panel": true,

    // The path to the php executable.
    // Needed for windows, or anyone who doesn't/can't make phars
    // executable. Avoid setting this if at all possible
    "phpcs_php_prefix_path": "",

    // Options include:
    // - Sniffer
    // - Fixer
    // - Mess Detector
    //
    // This will prepend the application with the path to php
    // Needed for windows, or anyone who doesn't/can't make phars
    // executable. Avoid setting this if at all possible
    "phpcs_commands_to_php_prefix": [],

    // What color to stylise the icon
    // https://www.sublimetext.com/docs/3/api_reference.html#sublime.View
    // add_regsions
    "phpcs_icon_scope_color": "comment",


    // PHP_CodeSniffer settings

    // Do you want to run the phpcs checker?
    "phpcs_sniffer_run": true,

    // Execute the sniffer on file save
    "phpcs_command_on_save": true,

    // It seems python/sublime cannot always find the phpcs application
    // If empty, then use PATH version of phpcs, else use the set value
    "phpcs_executable_path": "/usr/local/bin/phpcs",

    // Additional arguments you can specify into the application
    //
    // Example:
    // {
    //     "--standard": "PEAR",
    //     "-n"
    // }
    "phpcs_additional_args": {
        "--standard": "PSR2",
        "-n": ""
    },



    // PHP-CS-Fixer settings

    // Fix the issues on save
    "php_cs_fixer_on_save": false,

    // Show the quick panel
    "php_cs_fixer_show_quick_panel": false,

    // Path to where you have the php-cs-fixer installed
    "php_cs_fixer_executable_path": "/usr/local/bin/php-cs-fixer",

    // Additional arguments you can specify into the application
    "php_cs_fixer_additional_args": {

    },



    // phpcbf settings

    // Fix the issues on save
    "phpcbf_on_save": false,

    // Show the quick panel
    "phpcbf_show_quick_panel": false,

    // Path to where you have the phpcbf installed
    "phpcbf_executable_path": "/usr/local/bin/phpcbf",

    // Additional arguments you can specify into the application
    //
    // Example:
    // {
    //     "--level": "all"
    // }
    "phpcbf_additional_args": {
        "--standard": "PSR2",
        "-n": ""
    },



    // PHP Linter settings

    // Are we going to run php -l over the file?
    "phpcs_linter_run": true,

    // Execute the linter on file save
    "phpcs_linter_command_on_save": true,

    // It seems python/sublime cannot always find the php application
    // If empty, then use PATH version of php, else use the set value
    "phpcs_php_path": "/usr/bin/php",

    // What is the regex for the linter? Has to provide a named match for 'message' and 'line'
    "phpcs_linter_regex": "(?P<message>.*) on line (?P<line>\\d+)",



    // PHP Mess Detector settings

    // Execute phpmd
    "phpmd_run": false,

    // Execute the phpmd on file save
    "phpmd_command_on_save": true,

    // It seems python/sublime cannot always find the phpmd application
    // If empty, then use PATH version of phpmd, else use the set value
    "phpmd_executable_path": "/usr/local/bin/phpmd",

    // Additional arguments you can specify into the application
    //
    // Example:
    // {
    //     "codesize,unusedcode"
    // }
    "phpmd_additional_args": {
        "codesize,unusedcode,naming": ""
    },


    // PHP Scheck settings

    // Execute scheck
    "scheck_run": false,

    // Execute the scheck on file save
    "scheck_command_on_save": false,

    // It seems python/sublime cannot always find the scheck application
    // If empty, then use PATH version of scheck, else use the set value
    "scheck_executable_path": "",

    // Additional arguments you can specify into the application
    //
    //Example:
    //{
    //  "-php_stdlib" : "/path/to/pfff",
    //  "-strict" : ""
    //}
    "scheck_additional_args": {
        "-strict" : ""
    }
}
```

###### SublimeCodeIntel

###### Theme - Soda SolaraizedDark

###### Terminal

###### syncedSideBarBg
