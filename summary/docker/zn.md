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


====

### 2. 關於鏡像和容器

===

- 在上一部安裝中過程中, 你通過用Docke執行的hello-word指令, 其實已經完成了Docker的核心任務. 該條指令分為了三個部分:

<img src="./container_explainer_zn.png" alt="docker_explainer">

- **容器**: Linux操作系統的最核心版本. (容器是由Linux內核提供的)
- **鏡像**: 可加載到容器的軟件.
- 如果你執行該條指令, Docker會進行下面的步驟:
	- 檢測你是否擁有`hello-world`的鏡像
	- 如果沒有, 則從Docker Hub上下載該鏡像下來 (後面會討論到Docker Hub)
	- 把鏡像加載到容器中並執行
- 實際當中, 一個鏡像可能只是想`hello-word`鏡像一樣執行一個簡單的, 單一的指令, 然後退出.
- 然而, 一個Docker鏡像可以承載更多的東西. 如一個鏡像可以啟動像數據庫一樣複雜的軟件, 然後進行操作數據並等待下一個人去操作數據.
- 那麼是誰創建了`hello-word`鏡像呢? 在這個例子中, 是Docker創建的, 而且我們也可以自己創建自己的鏡像. 如果使用Docker, 你就能運行所有Docker鏡像中能運行的軟件.


<a href="#" style="left:200px;"><img src="./../../pic/gotop.png"></a>
=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
