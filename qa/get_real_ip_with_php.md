## How to get real IP of clients with PHP [Back](./qa.md)

```php
<?php
function getIP()
{
    $ip = false;
    $ips = [];

    /** Firstly, check $_SERVER['HTTP_CLIENT_IP'] */
    if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
        $ip = $_SERVER['HTTP_CLIENT_IP'];
    }

    /** Secondly, check $_SERVER['HTTP_X_FORWARDED_FOR'] */
    if (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
        $ips = explode(', ', $_SERVER['HTTP_X_FORWARDED_FOR']);
    }

    /** remove the HTTP_CLIENT_IP from HTTP_X_FORWARDED_FOR */
    if ($ip) {
        array_unshift($ips, $ip);
        $ip = false;
    }

    /** check legal IP */
    for ($i = 0; $i < count($ips); $i++) {
        if (!eregi("^(10|172\.16|192\.168)\.", $ips[$i])) {
            $ip = $ips[$i];
            break;
        }
    }

    return ($ip ? $ip : $_SERVER['REMOTE_ADDR']);
}
?>
```

### Method from Stack Overflow

The simplest way to get the visitor's/client's [IP address](http://en.wikipedia.org/wiki/IP_address) is using the `$_SERVER['REMOTE_ADDR']` or `$_SERVER['REMOTE_HOST']` variables.

However, sometimes this does not return the correct IP address of the visitor, so we can use some other server variables to get the IP address.

The below both functions are equivalent with the difference only in how and from where the values are retrieved.

`getenv()` is used to get the value of an environment variable in PHP.

```php
<?php
// Function to get the client IP address
function get_client_ip() {
    $ipaddress = '';
    if (getenv('HTTP_CLIENT_IP'))
        $ipaddress = getenv('HTTP_CLIENT_IP');
    else if(getenv('HTTP_X_FORWARDED_FOR'))
        $ipaddress = getenv('HTTP_X_FORWARDED_FOR');
    else if(getenv('HTTP_X_FORWARDED'))
        $ipaddress = getenv('HTTP_X_FORWARDED');
    else if(getenv('HTTP_FORWARDED_FOR'))
        $ipaddress = getenv('HTTP_FORWARDED_FOR');
    else if(getenv('HTTP_FORWARDED'))
       $ipaddress = getenv('HTTP_FORWARDED');
    else if(getenv('REMOTE_ADDR'))
        $ipaddress = getenv('REMOTE_ADDR');
    else
        $ipaddress = 'UNKNOWN';
    return $ipaddress;
}
?>
```

`$_SERVER` is an array that contains server variables created by the web server.

```php
<?php
// Function to get the client IP address
function get_client_ip() {
    $ipaddress = '';
    if (isset($_SERVER['HTTP_CLIENT_IP']))
        $ipaddress = $_SERVER['HTTP_CLIENT_IP'];
    else if(isset($_SERVER['HTTP_X_FORWARDED_FOR']))
        $ipaddress = $_SERVER['HTTP_X_FORWARDED_FOR'];
    else if(isset($_SERVER['HTTP_X_FORWARDED']))
        $ipaddress = $_SERVER['HTTP_X_FORWARDED'];
    else if(isset($_SERVER['HTTP_FORWARDED_FOR']))
        $ipaddress = $_SERVER['HTTP_FORWARDED_FOR'];
    else if(isset($_SERVER['HTTP_FORWARDED']))
        $ipaddress = $_SERVER['HTTP_FORWARDED'];
    else if(isset($_SERVER['REMOTE_ADDR']))
        $ipaddress = $_SERVER['REMOTE_ADDR'];
    else
        $ipaddress = 'UNKNOWN';
    return $ipaddress;
}
?>
```
