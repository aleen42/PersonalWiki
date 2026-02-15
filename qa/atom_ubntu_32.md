## How to install atom in Ubuntu 32 bits [Back](./qa.md)

#### Build up with script

**i.** Install all the dependencies

```bash
sudo apt-get install build-essential git libgnome-keyring-dev fakeroot
```

**ii.** Set up Node.js if you do not have the tool

```bash
curl --silent --location https://deb.nodesource.com/setup_0.12 | sudo bash -
sudo apt-get install nodejs
```

**iii.** Clone atom repository

```bash
git clone https://github.com/atom/atom
```

*Notice that: if you want the latest version of atom, you can run the command as follow:*

```bash
git fetch -p
git checkout $(git describe --tags `git rev-list --tags --max-count=1`)
```

**iv.** Build up atom

```bash
cd atom
script/build
script/grunt mkdeb
```

*Notice that: if you have a wrong run with the process of building, you can run `sudo update-alternatives --install /usr/bin/node node /usr/bin/nodejs 10` to have a try again*

#### Install via a PPA

```bash
sudo add-apt-repository ppa:webupd8team/atom
sudo apt-get update
sudo apt-get install atom
```

#### Recommended Packages

###### emmet

###### activate-power-mode

###### jquery-snippets

###### docblockr

#### Key Bindings

```cson
'.platform-win32, .platform-linux':
  'ctrl-alt-r': 'soft-wrap:toggle'
'atom-workspace, atom-workspace atom-text-editor':
  'alt-m': 'markdown-preview:toggle'
```