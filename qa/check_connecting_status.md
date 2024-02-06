## How to check connecting status [Back](./qa.md)

1. The summary of sockets:

    ```bash
    ss -s 
    ```

2. Statistic of connections to a specific port like `80`:

    ```bash
    netstat -nat | grep -i "80" | wc -l
    ```

3. Statistic of connections to a specific protocol like `httpd`:

    ```bash
    ps -ef | grep httpd | wc -l 
    ```

4. Statistic of established connections:

    ```bash
    netstat -na | grep ESTABLISHED | wc -l 
    ```

5. Statistic of connections sorted by IP:

    ```bash
    netstat -ntu | awk '{print $5}' | cut -d: -f1 | sort | uniq -c | sort -n 
    ```

6. Statistic of top 10 visited urls via Nginx:

    ```bash
    cat /var/log/nginx/access.log | awk '{print $7}' | sort | uniq -c | sort -nr | head -n 10 
    ```

7. Statistic of top 10 IPs to visit via Nginx:

    ```bash
    cat /var/log/nginx/access.log | awk '{print $1}' | sort | uniq -c | sort -nr | head -n 10 
    ```

8. Statistic of top 10 time periods to visit via Nginx:

    ```bash
    cat /var/log/nginx/access.log | grep -P "\[{1}(.+)]" -o | cut -c 14-15 | sort | uniq -c | sort -nr | head 
    ```

9. Statistic of TCP connections grouped by their state:

    ```bash
    netstat -tan | grep ^tcp | awk '{++a[$6]} END{for (i in a) print i, a[i]}' 
    ```

    - `TIME_WAIT`: Waiting for enough time to pass to be sure the remote TCP received the acknowledgment of its connection termination request.
    - `CLOSE_WAIT`: Waiting for a connection termination request from the local user.
    - `ESTABLISHED`: An open connection, data received can be delivered to the user. The normal state for the data transfer phase of the connection.
    - `LISTEN`: Waiting for a connection request from any remote TCP end-point.
