## Docker	[Back](./../summary.md)

- [**Chinese**](./zn.md)

### 1. Install
===

- i. Log into your Ubuntu installation as a user with `sudo` privileges.
- ii. Verify that you have `wget` installed.
	- Check
	```bash
$ which wget
```
	- If `wget` isn’t installed, install it after updating your manager:
	```bash
$ sudo apt-get update
$ sdo apt-get install wget
```

- iii. Get the latest Docker package.
	- The system prompts you for your `sudo` password. Then, it downloads and installs Docker and its dependencies.
	```bash
$ wget -q0- https://get.docker.com/ | sh
```
	- **Note1:** If your company is behind a filtering proxy, you may find that the `apt-key` command fails for the Docker repo during installation. To work around this, add the key directly using the following:
	```bash
$ wget -qO- https://get.docker.com/gpg | sudo apt-key add -
```
	- **Note2:** Docker currently only supports 64bit platforms.

- iv: Verify `docker` is installed correctly:

	```bash

```

====

### 2. Command of generating codes
===

<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
