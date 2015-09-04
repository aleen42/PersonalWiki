## Docker	[Back](./../summary.md)

<img src="./logo.png" title="Docker" alt="Docker" >

### 其他語言

- [**英文**](./en.md)

### 1. 安裝
===

- i. 在超級管理員權限下登錄Ubuntu, 或者用`sudo`執行命令
- ii. 保證你已經安裝`wget`
	- 檢測方式
	```bash
$ which wget
```
	- 如果`wget`沒有安裝, 則在更新安裝包管理器後安裝`wget`
	```bash
$ sudo apt-get update
$ sdo apt-get install wget
```

- iii. 獲取最新的docker安裝包.
	- 系統會索取你的`sudo`密碼. 然後, 它會下載並安裝Docker及其依賴包.
	```bash
$ wget -q0- https://get.docker.com/ | sh
```
	- **提醒1:** 如果公司使用了代理服務器, 那麼你可能會發現安裝過程會出現`apt-key`命令出錯. 為了解決問題, 直接通過下面的命令來添加這個鑰匙:
	```bash
$ wget -qO- https://get.docker.com/gpg | sudo apt-key add -
```
	- **提醒2:** Docker目前只支持64位系統

- iv: 確保 `docker` 安裝成功的方法:

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
	- 下面這條消息表示你已經成功安裝`Docker`.
	```bash
Hello from Docker.
```
	- `Docker`通過了下面的步驟來顯示這條信息
 		- 1. Docker客戶端連接了Docker虛擬機.
 		- 2. Docker虛擬機從Docker Hub上拉"hello-world"的鏡像到本地.
 		- 3. Docker虛擬機通過這個鏡像創建一個新的容器, 並通過這個容器運行可執行文件從而產生數據流.
 		- 4. Docker虛擬機把消息數據流發送到Docker客戶端, 然後由客戶端把消息顯示在終端上.

	- 如果想嘗試更野心的東西, 你可以通過下面的指令來運行一個Ubuntu容器
	```bash 
$ docker run -it ubuntu bash
```
	- 通過一個免費的Docker Hub帳號, 分享鏡像, 自動化工作流或其他東西: [https://hub.docker.com](https://hub.docker.com)
	- 更多例子和想法, 請瀏覽: [https://docs.docker.com/userguide/](https://docs.docker.com/userguide/)

### 2. 關於鏡像和容器

===

- 在上一部安裝中過程中, 你用Docke執行了`docker run hello-world`的指令. 其實這一過程已經完成了Docker的核心任務. 該條指令分為了三個部分:

<img src="./container_explainer_zn.png" alt="docker_explainer">

- **容器**: Linux操作系統的最核心版本. (容器是由Linux內核提供的)
- **鏡像**: 可加載到容器的軟件.
- 如果你執行該條指令, Docker會進行下面的步驟:
	- 1. 檢測你是否擁有`hello-world`的鏡像
	- 2. 如果沒有, 則從Docker Hub上下載該鏡像下來 (後面會討論到Docker Hub)
	- 3. 把鏡像加載到容器中並執行
- 實際當中, 一個Docker鏡像可能只是像`hello-word`鏡像一樣執行一條簡單的, 單一的指令, 然後退出.
- 然而, 一個Docker鏡像可以承載更多的東西. 如一個鏡像可以啟動像數據庫一樣複雜的軟件, 然後進行操作數據並等待下一個人去操作數據.
- 那麼是誰創建了`hello-word`鏡像呢? 在這個例子中, 是Docker創建的, 而且我們也可以自己創建自己的鏡像. 如果使用Docker, 你就能運行所有Docker鏡像中能運行的軟件.

### 3. 關於從Docker Hub找到鏡像
===

- 來自四面八方的人都在創建鏡像, 而你可以通過Docker Hub來找到這些鏡像.

##### 步驟1: 定位你想要找的鏡像

- i. 打開瀏覽器並瀏覽[**Docker Hub**](https://hub.docker.com/?utm_source=getting_started_guide&utm_medium=embedded_Linux&utm_campaign=find_whalesay).
	- Docker Hub 包含私人鏡像以及像RedHat, IBM, Google或其他的.
- ii. 點擊搜索框`Browser & Search`.
- iii. 在搜索框輸入單詞 `whalesay`.
- iv. 在結果列表中點擊`docker/whalesay`鏡像.
	- 每一個鏡像倉庫都包含關於這個鏡像的信息. 這些信息應該包括**镜像中包含哪種類型的軟件**和**如何去使用這個鏡像**. 你會發現`docker/whale`鏡像是基於Linux的一個發行版, Ubuntu. 下一步將會介紹如何去運行這個鏡像.

##### 步驟2: 執行`Whalesay`鏡像

- i. 在終端執行下面的命令:
	- 第一次執行這個鏡像時, 這條指令會先查詢本地系統是否擁有這個鏡像. 如果鏡像不存在, `Docker`會從Docker Hub上下載到本地
	```bash 
$ docker run docker/whalesay cowsay boo
```
- ii. 通過執行下面的命令來查詢本地含有哪些鏡像:
	- 當你第一次在容器中執行一個鏡像且本地無該镜像时, Docker會下載該鏡像到你的電腦上. 這個本地的緩存將會大大節省你的時間. Docker只會在遠程的鏡像源產生改變時, 才會重新下載. 當然你也可以刪除你的鏡像. (刪除鏡像將會在後面介紹)
	```bash 
$ docker images
REPOSITORY           TAG         IMAGE ID            CREATED            VIRTUAL SIZE
docker/whalesay      latest      fb434121fc77        3 hours ago        247 MB
hello-world          latest      91c95931e552        5 weeks ago        910 B
```

<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
