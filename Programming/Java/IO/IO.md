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

>InputStream
>>FileInputStream(文件)

>>ByteArrayInputStream(內存)

>>StringBufferInputStream

>>PipedInputStream(管道)

>>ObjectInputStream(對象)

>>SequenceInputStream(序列)

>>AudioInputStream(聲音)

>OutputStream

>>FileOutputStream

>>ByteArrayOutputStream

>>PipedOutputStream

>>ObjectOutputStream



###Socket
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

###File
```java
BufferedReader read = new BufferedReader(new FileReader(String path));
PrintWriter write = new PrintWriter(new BufferedWriter(new FileWriter(String path)));
```

###Standard IO
```java
BufferedReader read = new BufferedReader(new InputStreamReader(System.in));
PrintWriter write = new PrintWriter(System.out, true);
```

