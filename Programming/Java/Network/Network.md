## Network Programming [Back](./../Java.md)
- Network實現的重要機制:Socket

Step|Server|Client
:----:|------|------
1|```ServerSocket s = new ServerSocket(port);```|
1|```Socket client = s.accept();```|
2||```Socket client = new Socket(host, port);```
3|```readfromclient = new BufferedReader(new InputStreamReader(client.getInputStream()));```|```readfromserver = new BufferedReader(new InputStreamReader(socket.getInputStream()));```
3|```writetoclient = new PrintWriter(client.getOutputStream());```|```writetoserver = new PrintWriter(client.getOutputStream());```
4|```readfromclient.close();```|```readfromserver.close();```
4|```writetoclient.close();```|```writetoserver.close();```
4|```client.close();```|```client.close();```

- Stream, Socket等聲明需放在try外. 因為若放try內, 作用於只在try範圍內

