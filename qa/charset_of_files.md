## Charsets of files [Back](./qa.md)

1. How to check the charset of a specified file?

    > REF: https://stackoverflow.com/questions/805418/how-can-i-find-encoding-of-a-file-via-a-script-on-linux
    >
    > REF: https://stackoverflow.com/a/34766140/5698182

    - On Linux/UNIX/OS X/cygwin:

        ```bash
        file -i xxx 
        ```

        Or using [uchardet](https://www.freedesktop.org/wiki/Software/uchardet) - An encoding detector library ported from Mozilla, which can detect some Chinese standard charsets like GB18030, etc. Various Linux distributions ([Debian](https://en.wikipedia.org/wiki/Debian), [Ubuntu](https://en.wikipedia.org/wiki/Ubuntu_%28operating_system%29), [openSUSE](https://en.wikipedia.org/wiki/OpenSUSE), [Pacman](https://en.wikipedia.org/wiki/Arch_Linux#Pacman), etc.) provide binaries.

        ```bash
        uchardet xxx 
        ```

    - On Windows:

        The (Linux) command-line tool 'file' is available on Windows via GnuWin32:

        http://gnuwin32.sourceforge.net/packages/file.htm

        If you have git installed, it's located in C:\Program Files\git\usr\bin.

2. How to convert the charset of a specified file in the Linux?

    > REF: https://stackoverflow.com/q/64860/5698182

    - On Linux/UNIX/OS X/cygwin:

        * Gnu [iconv](http://www.gnu.org/software/libiconv/documentation/libiconv/iconv.1.html) suggested by [Troels Arvin](https://stackoverflow.com/questions/64860/best-way-to-convert-text-files-between-character-sets#64889) is best used **as a filter**. It seems to be universally available. Example:

            ```bash
            $ iconv -f UTF-8 -t ISO-8859-15 in.txt > out.txt 
            ```

            As pointed out by [Ben](https://stackoverflow.com/questions/64860/best-way-to-convert-text-files-between-character-sets#64991), there is an [online converter using iconv](http://www.iconv.com/iconv.htm).

        * Gnu [recode](http://www.gnu.org/software/recode/recode.html) ([manual](http://www.informatik.uni-hamburg.de/RZ/software/gnu/utilities/recode_toc.html)) suggested by [Cheekysoft](https://stackoverflow.com/questions/64860/best-way-to-convert-text-files-between-character-sets#64888) will convert **one or several files in-place**. Example:

            ```bash
            $ recode UTF8..ISO-8859-15 in.txt 
            ```

            This one uses shorter aliases:

            ```bash
            $ recode utf8..l9 in.txt 
            ```

            Recode also supports *surfaces* which can be used to convert between different line ending types and encodings:

            Convert newlines from LF (Unix) to CR-LF (DOS):

            ```bash
            $ recode ../CR-LF in.txt 
            ```

            Base64 encode file:

            ```bash
            $ recode ../Base64 in.txt 
            ```

            You can also combine them.

            Convert a Base64 encoded UTF8 file with Unix line endings to Base64 encoded Latin 1 file with Dos line endings:

            ```bash
            $ recode utf8/Base64..l1/CR-LF/Base64 file.txt 
            ```

    - On Windows with [Powershell](http://www.microsoft.com/windowsserver2003/technologies/management/powershell/default.mspx) ([Jay Bazuzi](https://stackoverflow.com/questions/64860/best-way-to-convert-text-files-between-character-sets#64937)):

        * `PS C:\> gc -en utf8 in.txt | Out-File -en ascii out.txt`

            (No ISO-8859-15 support though; it says that supported charsets are unicode, utf7, utf8, utf32, ascii, bigendianunicode, default, and oem.)

