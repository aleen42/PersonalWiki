## How to check whether it's PC's accessment in PHP [Back](./qa.md)

I just show the code here:

```php
<?php
public static function validatePC()
{
    /** contain HTTP_X_WAP_PROFILE should be a mobile device */
    if (isset($_SERVER['HTTP_X_WAP_PROFILE'])) {
        return false;
    }

    /** contain 'wap' in HTTP_VIA should be a mobile device */
    if (isset($_SERVER['HTTP_VIA'])) {
        return stristr($_SERVER['HTTP_VIA'], 'wap') ? false : true;
    }

    /** check useragent, but have compatibility problem */
    if (isset($_SERVER['HTTP_USER_AGENT'])) {
        $clientkeywords = [
            'nokia',
            'sony',
            'ericsson',
            'mot',
            'samsung',
            'htc',
            'sgh',
            'lg',
            'sharp',
            'sie-',
            'philips',
            'panasonic',
            'alcatel',
            'lenovo',
            'iphone',
            'ipod',
            'blackberry',
            'meizu',
            'android',
            'netfront',
            'symbian',
            'ucweb',
            'windowsce',
            'palm',
            'operamini',
            'operamobi',
            'openwave',
            'nexusone',
            'cldc',
            'midp',
            'wap',
            'mobile'
        ];

        /** preg match  */
        if (preg_match("/(" . implode('|', $clientkeywords) . ")/i", strtolower($_SERVER['HTTP_USER_AGENT']))) {
            return false;
        }
    }

    /** protocol, but not accurate */
    if (isset($_SERVER['HTTP_ACCEPT'])) {
        /** only support wml should be a mobile device */
        /** support both wml and html but wml is among html should be a mobile device */
        if ((strpos($_SERVER['HTTP_ACCEPT'], 'vnd.wap.wml') !== false) && (strpos($_SERVER['HTTP_ACCEPT'], 'text/html') === false || (strpos($_SERVER['HTTP_ACCEPT'], 'vnd.wap.wml') < strpos($_SERVER['HTTP_ACCEPT'], 'text/html')))) {
            return false;
        }
    }

    return true;
}

?>
```
