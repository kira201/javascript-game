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

## 对象(Object)
* 对象是JavaScript的基本数据类型
* 对象是一组属性的无序集合，每个属性都是一个key/value对
* 对象的属性名是字符串。
* 其他叫法：散列表、字典、关联数组等。
* 对象可以从一个称为原型的对象上继承属性。这种原型式继承是JavaScript的核心特性。

```javascript
//创建对象
var a = {x:1, y:2}; //推荐使用对象直接量创建对象
var b = new Object(); //通过new方法创建对象是不推荐的。
function Test(){
  this.a = 1;
  this.b = 2;
}
var c = new Test(); //Test{a:1, b:2} 通过new 构造函数创建对象
var d = new Date();
var e = []; //数组直接量
var f = new Array();
var g = /javascript/; //正则表达式直接量
var h = new Regexp("javascript"); //

/**
 * 通过原型继承创建一个新对象
 */
function createObject(p){
  if(p == null) throw TypeError();
  if(Object.create) //使用ECMAScript5自带的函数创建对象
    return Object.create(p);
  var t = typeof p;
  if(t !== 'object' && t != 'function') throw TypeError();
  function f(){}; //定义一个空函数
  f.prototype = p;
  return new f();
}
```
```javascript
//访问属性值
var p = {x:1, y:2}; //创建对象
p.x; //1 通过".属性名"访问属性值
p.x = 2; //属性赋值
p.z = 0; //创建新属性
p["x"] //2 通过['属性名']访问属性值
p["hello world"] = 12345; //不符合变量命名规则的属性名只能以["属性名"]这种形式进行访问。
var a = "hello world";
p[a] //12345 以[]进行属性访问时属性名可以是字符串表达式
for(var key in p){ //用for in 进行对象的属性遍历
  console.log(key, p[key]);
}
p.id //undefined 查询对象中不存在的属性不会出错，而是返回undefined
p.id.a //出错 试图访问undefined和null的属性时程序会出错。这个一个常见的错误。
delete p["hello world"]; //删除对象的一个属性
"x" in p //true 检查属性是否存在
"hello world" in p //false 属性已被删除
p.hasOwnProperty("toString") //false 检查属性名是否为自有属性
p.hasOwnProperty("x") //true "x"为自有属性
//ECMAScript 5中对属性getter和setter的实现
var o = {
  get prop1(){/*函数体*/}
  set prop1(newvalue){/*函数体*/}
}
```

## 数组(Array)
* 数组是有序的集合，元素可以是任意类型，用数组[索引]进行访问数组元素
* 数组是动态的，长度可根据需要增长或者缩减。
* 数组可以是稀疏的
* 数组有一个length长度属性，添加或者删除数组元素这个属性会自动更新，设置length的值会调整数组大小
* 数组是对象的特殊形式
* 数组继承Array.prototype中的属性，定义了一套数组操作方法。这些方法对真正的数组和类数组都有效
* 类数组不是数组，是具有length属性和非负整数属性的对象，可以看作是只读的数组借用数组的操作方法。例如Arguments对象

```javascript
var a = []; //数组直接量 等价于 a = new Array();
var a = new Array(10) ; //[undefined × 10] 创建一个长度为10的数组
var a = new Array(1,2,3); //等价于 a = [1,2,3]
a.length == 3; //true 读取数组长度
a.length = 0; //设置数组长度为0，清空数组元素
a.length = 5; //数组长度扩充到5，5个元素都是undefined
a = [1, 2, 3];
a[0] ==1; //true 读取第0个元素
a[0] = 123; //设置第0个元素为123
a.push(4); //向数组最后增加一个元素 数组为[1,2,3,4]
a.pop(); //4 从数组最后弹出一个元素 数组为[1,2,3]
a.unshift('first'); //数组为['first', 1, 2, 3]
a.shift(); //'first' 数组为[1,2,3]
var pos = 1;
a.splice(pos, 1); //删除索引位置在pos上的数组元素 [1,3]
a.splice(1, 0, 'b', 'c', 'd'); //数组插入元素 [1, 'b', 'c', 'd', 3]
//遍历数组
for(var i=0,max=a.length; i<max; i++){
  console.log(i, a[i]);
}
//ECMAScript5数组遍历方法
a.forEach(function(x){
  console.log(x);
});
var b = [[1,2],[3,4],[5,6]]; //创建二维数组
b[1][0] == 3; //true
var a = [1, 2, 3];
a.join(); //"1,2,3"
a.join(" "); //"1 2 3"
a.join(''); //"123"
var b = new Array(5);
b.join('-'); //"-----"

a.reverse(); //数组颠倒顺序 [3,2,1]
a.sort(); //排序 [1, 2, 3]
a.push(11); // [1, 2, 3, 11]
a.sort(); // 默认按照字符顺序排序 [1, 11, 2, 3]
a.sort(function(a, b){
  return a-b;
}); //用自定义排序函数进行排序 [1, 2, 3, 11]
a.sort(function(a, b){
  return b-a;
}); //用自定义排序函数进行反序排序 [1, 2, 3, 11]

//数组连接
var a = [1, 2, 3];
a.concat(4, 5); //返回一个新数组[1,2,3,4,5] 变量a仍然为[1,2,3]
a.concat([4,5]); //[1,2,3,4,5]
a.concat([4,5], [6,7]); //[1,2,3,4,5,6,7]
a.concat(4, [5, [6, 7]]); //[1,2,3,4,5,[6,7]]

//数组切片
var a = [1,2,3,4,5];
a.slice(1,3); //[2,3] 变量a仍然为[1,2,3,4,5]
a.slice(3); //[4, 5]
a.slice(1, -1); //[2,3,4]
a.slice(-3, -2); //[3]

a.toString();//"1,2,3,4,5"

//判读是否为数组
function isArray(o){
  if(Array.isArray)
    return Array.isArray(o);//ECMAScript5
  else
    return Object.prototype.toString.call(o) === "[object Array]";
}
```

## 其他内置类型
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
