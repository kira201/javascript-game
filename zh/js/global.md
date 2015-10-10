# 内置类型与全局函数
核心语言内置的全局函数与对象，可放心适用于任何平台。不包含特定环境下的内容，比如浏览器对象模型(BOM)的内容。

## global 和 window

## 全局对象和内置的构造函数
* Number 把类型转换成数值类型的函数。本质上它是数值的包装对象的构造函数。
* String 把类型强转成字符串类型的函数。本质上它是字符串的包装对象的构造函数。
* Boolean 把类型强转成布尔类型的函数。本质上它是布尔值的包装对象的构造函数。
* Object 对象的构造函数
* Array 数组的构造函数
* Function 函数对象的构造函数
* RegExp 正则表达式的构造函数
* Data 日期对象的构造函数
* Error 错误对象构造函数
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

## 动态计算表达式 eval
可用于字符串模板，故事剧情模板，技能描述附加公式计算的字符串模板
```js
function test(strTemplate) {
    "use scrict"
    var x = 1;
    var y = 2;
    //先将字符串用`分割然后对具有()形式的部分进行表达式求职计算
    return strTemplate.split(/`/g).map(function(s) {
        if (s.substr(0, 1) === '(' && s.substr(-1) === ')') {
            var obj = eval(s); //计算出表达式
            return '颜色:' + obj.c + '值:' + obj.v
        } else {
            return s;
        }
    }).join('');
}

test("x+y=`({c:'red',v:x+y})`  \n x-y=`({c:'blue',v:x-y})`");
```

## console 对象
console.log
console.info
console.warn
console.error
console.group
console.groupCollapsed
console.groupEnd
console.log('%chello world','font-size:25px;color:red;');
console.table
console.assert
console.count('foo 被执行的次数：');
console.dir([1,2,3]);
console.time("性能测试");
var arr = [];
for (var i = 0; i < 10000; i++) {
    arr[i] = {};
};
console.timeEnd("性能测试");

console.trace('print my call stack');

monitor(func)
unmonitor(func)
debug(func)
undebug(func)
