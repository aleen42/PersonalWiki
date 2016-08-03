## How to set the default window size of the Terminal in Ubuntu [Back](./qa.md)

i. the first step is to install gconf-editor with `apt-get`

```bash
apt-get install gconf-editor
```

ii. then, open a terminal, and set the size with mouse. Type `xwininfo` to mark down the last value

```
-geometry 155x28+263+138
```

iii. find the key `/desktop/gnome/applications/terminal/exec` with gconf-editor:
