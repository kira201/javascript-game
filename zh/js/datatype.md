# 数据类型

## 数字(Number)
```javascript
//将数字直接量赋值给一个变量
var foo = 1; //整数
foo = 3.14; //浮点数
foo = 0xff; //十六进制数
foo = .33333; //整数部分为零可省略
foo = 1.23e45; //指数计数法
foo = Infinity; //Infinity是一个表示无穷大的数字直接量
foo = -Infinity;//负无穷大
foo = NaN; //NaN表示一个无意义的数字直接量

//类型判断
typeof 123 === 'number' //true
typeof Infinity === 'number' // true
typeof NaN === 'number' //true
1/0 === Infinity //true
Infinity === Infinity+1 //true 无穷大等于无穷大
123 < Infinity //true
isFinity(123) //true 123是一个有限的数字，不是无穷大的数
NaN !== NaN //true 两个NaN是不相等的
isNaN(0/0) === true //true 判断数值是否为NaN必须用isNaN函数判断

//高级算数运算使用Math对象定义的函数和常量来实现
foo = min + Math.floor(Math.random() * (max - min + 1)); //在min和max之间去一个整数随机数

//关于数字的坑
//当+运算符两边有一个不是数字的时候，+运算符会把两边都转换为字符串然后相加。
//当做数值计算时要注意，必要时用Number(v)或者parseInt(v)强制转换成数值然后进行计算。
'1' + 1 === '11';
var foo = {};
foo + 1 === '[object Object]1' ;//等价于 foo.toString() + 1

//浮点运算带来的精度误差，需要注意的一个坑。
0.3 - 0.2 !== 0.1; //true

//关于parseInt函数的坑
parseInt('09'); //ie浏览器把字符串当成8进制数来转换 结果为0 chrome浏览器的值为9
parseInt('09', 10); //9 强制以10进制来转换字符串
```

## 字符串(String)
```javascript
var str = ''; //空串
str = 'hello "world"'; //单引号括起来的字符串里可保护双引号
str = "I'm Peter"; //双引号括起来的字符串里可包含单引号
str = 'I\'m Peter'; //转义字符
str = "Hello" + "World"; //字符串连接
typeof str === 'string'; //true
'hello' === 'hello' //true 直接进行字符串的比较
str = 'hello world'; //可以把字符串当作只读的数组来使用
str.length === 11; //true 长度属性
str[0] === 'h'; //true 用数组下标存取
str.charAt(0) === 'h'; //true 取出字符串位置0的字符
str.substring(1, 4) === 'ell'; //true 取出位置1到4之间的字符串
str.substr(1, 4) === 'ello'; //true 从位置1开始取，取出长度为4的字符串
str.substr(6) === 'world'; //true 从位置6开始取，取出剩余的字符串
str.substr(-3) === 'rld'; //true 从字符串的最后取出长度为3的字符串
str.indexOf('world') === 6; //true 查询world首次在字符串中出现的位置
str.indexOf('abc') === -1; //true 查找的字符串不存在则返回-1
str.indexOf('world', 7) === -1; //true 从字符串第七个位置之后开始查找
str.split(' '); //['hello', 'world'] 用空格分割字符串
'a  b\tc'.split(/\s+/); //['a', 'b', 'c'] 用正则表达式分割字符串 用空白符分割
s.replace('h', 'H'); //Hello world 字符串替换
s.toUpperCase(); //HELLO WORLD 转成大写
```

## 布尔值(Boolean)
```javascript
var flag = true //布尔值true
flag = false //布尔值false
Boolean(1); //true 强制转成布尔值
Boolean(undefined); //false
Boolean(null); //false
Boolean(0); //false
Boolean(-0); //false
Boolean(NaN); //false
Boolean(''); //false
typeof flag === 'boolean' //true
```

## 空值(null)和未定义值(undefined)
```javascript
var foo = null //空值null
var bar //等价于 var bar = undefined;
typeof null === 'object' //类型居然为object，真是一个坑，一个历史悠久的坑。
typeof undefined === 'undefined' //true
foo == bar //true null==undefined这是规定，不解释，因为我解释不明白。
foo === bar //false
null === null // true
0 == null //false
0 == undefined //false
foo == null //true
bar == null //true
foo === null) //true
bar !== null) //true
//注意:json中只支持null值不支持undefi值
```
