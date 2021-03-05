## Slow Switch [Back](./../goog.md)
###Problem
```js
/* from Google Closure 
 * from dom.js, Line 797
 * 當我們查找每一HTML屬性時,存在低效執行
*/
switch (node.tagName) {
  case goog.dom.TagName.APPLET:
  case goog.dom.TagName.AREA:
  case goog.dom.TagName.BR:
  case goog.dom.TagName.COL:
  case goog.dom.TagName.FRAME:
  case goog.dom.TagName.HR:
  case goog.dom.TagName.IMG:
  case goog.dom.TagName.INPUT:
  case goog.dom.TagName.IFRAME:
  case goog.dom.TagName.ISINDEX:
  case goog.dom.TagName.LINK:
  case goog.dom.TagName.NOFRAMES:
  case goog.dom.TagName.NOSCRIPT:
  case goog.dom.TagName.META:
  case goog.dom.TagName.OBJECT:
  case goog.dom.TagName.PARAM:
  case goog.dom.TagName.SCRIPT:
  case goog.dom.TagName.STYLE:
  return false;
}
return true;
```

###Solution
```js
/*
 * Use a object to store and extract attributes
*/
var takesChildren{}
takesChildren[goog.dom.TagName.APPLET] = 1;
takesChildren[goog.dom.TagName.AREA] = 1;

/*
 * If we want to read some attribute
*/
return !takesChildren[node.tagName];
return !takesChildren.hasOwnProperty(node.tagName);
```
