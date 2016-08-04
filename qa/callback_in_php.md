## How to pass a callback function as a parameter in PHP [Back](./qa.md)

In PHP, if you want to pass a callback function into another one, you are supposed to use `call_user_func`.

{%ace edit=false, lang='php', theme='tomorrow'%}
<?php
/** Definition */
function f($opt, $callback) {
    /** Operation */
    /** ... */
    call_user_func($callback);
}

/** Calling */
f($opt, function () use ($innerOpt) {
    echo 'callBack';
});
?>
{%endace%}
