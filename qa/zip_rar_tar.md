## What are the differences between .zip, .rar, .deb, and .tar files [Back](./qa.md)

Refer to https://www.quora.com/What-is-difference-between-zip-rar-deb-and-tar-files.

- **Zip** : ZIP file format was basically widely used to group files for single downloading over Internet.
    - It is fastest tool to compress and group several files together.
    - Released under public domain
- **Tar (tar.gz and tar.bzip2):** Often referred to as a *tarball* , name is derived from *(t)ape (ar)chive* , originally developed to write data to sequential I/O devices with no file system.
    - tar.gz compress more good than zip but takes longer time
    - Universal choice among linux developers and users
    - tar.bzip2 is better than tar.gz but slower.
- **Rar** : The only software that creates RAR files ( *WinRAR* ) but Windows-only.
    - You can uncompress RAR files on Mac and Linux, but not create them.
    - RAR can also split up compressed archives into multiple parts which makes it cool for sharing large files over Internet.
- **Deb** :Extension of the *Debian software package* format and most used for *binary packages* .
    - Debian packages are standard *Unix archives* that include two tar archives
    - one archive holds the control information and another contains the program data.
