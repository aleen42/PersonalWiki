## Docker	[Back](./../summary.md)

### Othere Languages  <img src="./logo.png" title="Docker" alt="Docker" >

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
$ docker run hello-world
```
	```
	Unable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
535020c3e8ad: Pull complete
af340544ed62: Pull complete
Digest: sha256:a68868bfe696c00866942e8f5ca39e3e31b79c1e50feaee4ce5e28df2f051d5c
Status: Downloaded newer image for hello-world:latest
```
	- The following message shows that your installation appears to be working correctly.
	```bash
Hello from Docker.
```
	- To generate this message, Docker took the following steps:
 		- 1. The Docker client contacted the Docker daemon.
 		- 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
 		- 3. The Docker daemon created a new container from that image which runs the executable that produces the output you are currently reading.
 		- 4. The Docker daemon streamed that output to the Docker client, which sent it to your terminal.

	- To try something more ambitious, you can run an Ubuntu container with:
	```bash 
$ docker run -it ubuntu bash
```
	- Share images, automate workflows, and more with a free Docker Hub account: [https://hub.docker.com](https://hub.docker.com)
	- For more examples and ideas, visit: [https://docs.docker.com/userguide/](https://docs.docker.com/userguide/)

====

### 2. About images & containers
===

<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
