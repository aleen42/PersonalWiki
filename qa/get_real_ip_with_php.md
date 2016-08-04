## How to get real IP of clients with PHP [Back](./qa.md)

{%ace edit=false, lang='php', theme='tomorrow'%}
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
{%endace%}
