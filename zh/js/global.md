# 内置类型与全局函数
核心语言内置的全局函数与对象，可放心适用于任何平台。不包含特定环境下的内容，比如浏览器对象模型(BOM)的内容。

## 全局对象和内置的构造函数
* Number 把类型转换成数值类型的函数。本质上它是数值的包装对象的构造函数。
* String 把类型强转成字符串类型的函数。本质上它是字符串的包装对象的构造函数。
* Boolean 把类型强转成布尔类型的函数。本质上它是布尔值的包装对象的构造函数。
* Object 对象的构造函数
* Array 数组的构造函数
* Function 函数对象的构造函数
* RegExp 正则表达式的构造函数
* Data 日期对象的构造函数
* Math 数学函数库
* Console 控制台对象
* JSON 解析函数库

```js
var obj = {};//推荐用字面量表示法创建对象
typeof obj === 'object' //true
obj instanceof Object //true
obj.constructor === Object //true
var obj1 = new Object();//不推荐用构造函数创建对象
typeof obj1 === 'object' //true
obj1 instanceof Object //true
obj1.constructor === Object //true

var arr = [];//推荐用字面量表示法创建对象
typeof arr === 'array' //true
arr instanceof Array //true
arr.constructor === Array //true
var arr1 = new Array();//不推荐用构造函数创建对象
typeof arr1 === 'array' //true
arr1 instanceof Array //true
arr1.constructor === Array //true

var foo = function(){} //函数表达式
typeof foo === 'function' //true
foo instanceof Function //true
foo.constructor === Function //true

var reg = /^abc/ //正则表达式
typeof reg === 'object' //true
reg instanceof RegExp //true
reg.constructor === RegExp // true

var date = new Date() //日期时间对象
typeof date === 'object'
date instanceof Date
date.constructor === Data //true
```

## 全局函数
* setInterval
* setInterval
* isFinite
* isNaN
* eval

## 动态计算表达式eval
```js
function test(){
    "use strict"
    var jsonstr = '{"x":1}';
    var obj = eval('(' + jsonstr + ')');//如果去掉小括号括号，会把里边的大括号内容解释为作用域而不是对象了。
    return obj;
}
test(); //=>{x:1}
```
