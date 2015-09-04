## Docker	[Back](./../summary.md)

<img src="./logo.png" title="Docker" alt="Docker" >

### Othere Languages

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


### 2. About images & containers
===

- As the last step in your installation, you ran the docker run `hello-world` command. With this one command, you completed the core tasks to using Docker. The command you ran had three parts.

<img src="./container_explainer.png" alt="docker_explainer">

- A **container**: A container is a stripped-to-basics version of a Linux operating system.
- An **image**: An image is software you load into a container.
- When you ran the command, the Docker software:
	- 1. checked to see if you had the `hello-word` software image
	- 2. downloaded the image from the Docker Hub (more about the hub later)
	- 3. loaded the image into the container and “ran” it
- Depending on how it was built, an image might run a simple, single command and then exit. This is what `hello-world` did.
- A Docker image, though, is capable of much more. An image can start software as complex as a database, wait for you (or someone else) to add data, store the data for later use, and then wait for the next person.
- Who built the `hello-world` software image though? In this case, Docker did but anyone can. Docker lets people (or companies) create and share software through Docker images. Using Docker, you don’t have to worry about whether your computer can run the software in a Docker image — a Docker container can always run it.

### 3. About finding the whalesay image
===

- People all over the world create Docker images. You can find these images by browsing the Docker Hub.

##### Step1: Locate the whalesay image

- i. Open your browser and browse to [**the Docker Hub**](https://hub.docker.com/?utm_source=getting_started_guide&utm_medium=embedded_Linux&utm_campaign=find_whalesay).
	- The Docker Hub contains images from individuals like you and official images
from organizations like RedHat, IBM, Google, and a whole lot more.
- ii. Click Browser & Search.
- iii. Enter the word `whalesay` in the search bar.
- iv. Click on the `docker/whalesay` image in the results.
	- Each image repository contains **information** about an image. It should include information such as **what kind of software the image contains** and **how to use it**. You may notice that the whalesay image is based on a Linux distribution called Ubuntu. In the next step, you run the whalesay image on your machine.

##### Step2: Run the Whalesay image

- i. Call the following comand in the terminal:
	- The first time you run a software image, the `docker` command looks for it on your local system. If the image isn't there, then `docker` gets it from the hub.
	```bash 
$ docker run docker/whalesay cowsay boo
```
- ii. Find what images you have by calling the following command:
	- When you run an image in a container, Docker downloads the image to your computer. This local copy of the image saves you time. Docker only downloads the image again if the image’s source changes on the hub. You can, of course, delete the image yourself. (You’ll learn more about that later)
	```bash 
$ docker images
REPOSITORY           TAG         IMAGE ID            CREATED            VIRTUAL SIZE
docker/whalesay      latest      fb434121fc77        3 hours ago        247 MB
hello-world          latest      91c95931e552        5 weeks ago        910 B
```

<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
