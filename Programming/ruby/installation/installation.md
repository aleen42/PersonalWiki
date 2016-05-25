## Installation [Back](./../ruby.md)

#### Ubuntu Installation

i. To see whether you have installed before:

```sh
ruby
```

ii. Install by apt-get when it notify to install:

```sh
sudo apt-get install ruby
```

- *Notice: you should upgrade when its version is older than the latest stable version.*

iii. Downloads latest stable version:

- **Ruby** [downloads](https://www.ruby-lang.org/en/downloads/)
- Use `tar -zxvf` to uncompress the package.
- Configure your installation by typing  `./configure --prefix=$HOME`). Next type `make`, which will build your Ruby interpreter. This might take a few minutes. After that is done, type  `make install` to install it.
- *Notice: it takes some time to complete make process.*

<img src="./cost.png">

iv. Add your path to `$HOME/bin`

```sh
sudo vim ~/.bashrc
```

```sh
# add in the last line
export PATH=${HOME}/bin:$PATH
```

- *Notice: log out and login again to check*

v. Check the version of Ruby

```sh
ruby -v
```

<img src="./version.png">

#### Windows Installation

- To download [**Ruby**](https://www.ruby-lang.org/en/downloads/). 
