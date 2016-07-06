## Links [Back](./../HTML.md)

- links are the defining feature of the web because they allow you to move from one web page to another.
- ```<a>``` is used to create a link
	- ```<a href="http:a//aleen42.github.io">ALEEN</a>```
- **URL**
	- **relative URL** is used for linking withing own website. It's effective.
- **Email**
	- ```<a href="mailto:aleen42@vip.qq.com">aleen42@vip.qq.com</a>```
- When linking to a **Specific Part**, you can use **id**. After you click upon this `<a>` tag, url should be have a hash changed, and `location.hash` should be `#arc_shot`. We can  use `window.onhashchange` to listen to hash changed events.
	- ```<a href="#arc_shot">Arc Shot</a>```
	- ```<h1 id="arc_shot">Arc Shot</h1>```

### Appendix. Optional Attributes
- **target** is the attribute for setting where to open links.
	- **_blank**: new window
		- ```<a href="http://aleen42.github.io" target="_blank"><\a>```
	- **_parent**
	- **_self**
	- **_top**
- **download**(HTML5): used to point where to download
- **type**(HTML5): used to set MIME types
	- MINE types:

序号|内容类型|文件扩展名|描述
:----:|----|----|----
1|application/msword|doc|Microsoft Word
2|application/octet-stream| bin dms lha lzh exe class|可执行程序
3|application/pdf|pdf|Adobe Acrobat
4|application/postscript|ai eps ps|PostScript
5|appication/powerpoint|ppt|Microsoft Powerpoint
6|appication/rtf|rtf|rtf 格式
7|appication/x-compress|z|unix 压缩文件
8|application/x-gzip|gz|gzip
9|application/x-gtar|gtar|tar 文档 (gnu 格式 )
10|application/x-shockwave-flash|swf|MacroMedia Flash
11|application/x-tar|tar|tar(4.3BSD)
12|application/zip|zip|winzip
13|audio/basic|au snd|sun/next 声音文件
14|audio/mpeg|mpeg mp2|Mpeg 声音文件
15|audio/x-aiff|mid midi rmf|Midi 格式
16|audio/x-pn-realaudio|ram ra|Real Audio 声音
17|audio/x-pn-realaudio-plugin|rpm|Real Audio 插件
18|audio/x-wav|wav|Microsoft Windows 声音
19|image/cgm|cgm|计算机图形元文件
20|image/gif|gif|COMPUSERVE GIF 图像
21|image/jpeg|jpeg jpg jpe|JPEG 图像
22|image/png|png|PNG 图像

