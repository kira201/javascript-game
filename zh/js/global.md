# 内置类型与全局函数
```javascript
var foo = function(){} //函数表达式
typeof foo === 'function' //true
foo instanceof Function //true

var reg = /^abc/ //正则表达式
typeof reg === 'object' //true
reg instanceof RegExp //true

var date = new Date() //日期时间对象
typeof date === 'object'
date instanceof Date
```
