## JDBC(Java Database Connectivity) [Back](./../Java.md)

###Operation
Step|Description|Code
:--:|-----------|----
1|確定Url|```String url = "jdbc:microsoft:sqlserver://localhost:1433;DatabaseName=Database"```
2|加載驅動|```Class.forName("com.microsoft.jdbc.sqlserver.SQLServerDriver").newInstance();```
3|獲取鏈接|```Connection con = DriverManager.getConnection(url, username, password);```
4|創建語句|```Statement stat = con.createStatement();```
5|執行sql|```void stat.execute(String sql);```
<empty>|<empty>|```int stat.executeUpdate(String sql);```
<empty>|<empty>|```ResultSet stat.executeQuery(String sql);```
6|獲取結果|```while(rs.next()){String result = rs.getString("Column_name")}```
7|釋放資源|<empty>

###Transaction
```Java
boolean reserve = con.getAutoCommit();
con.setAutoCommit(false);

/* Transaction */
//do something
con.commit();
con.rollback();	//roll back to the checkpoint

con.setAutoCommit(reserve);
```

=====
<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../../pic/tail.gif"></a>
