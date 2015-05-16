## IO [Back](./../Java.md)
###Stream(一般指數據傳輸的通道)
- 文件操作
- 網絡傳輸
- 網頁加載
- 標準IO
- 內存讀寫

基於|類
---|--------
字節(Byte)|InputStream, OutputStream
字符(Character)|Reader, Writer

###Code(decorate the core)
```Java
/* Initialization */
//InputStreamReader(Change Byte-oriented to Character-oriented)
BufferedReader read = new BufferedReader(new InputStreamReader(socket.getInputStream))
PrintWriter write = new PrintWriter(socket.getOutputStream)

/* Operation */
read.readLine();
write.println("something");
write.flush();
```

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
