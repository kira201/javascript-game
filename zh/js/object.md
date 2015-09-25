# 对象(Object)
* 对象是JavaScript的基本数据类型
* 对象是一组属性的无序集合，每个属性都是一个key/value对
* 对象的属性名是字符串。
* 其他叫法：散列表、字典、关联数组等。
* 对象可以从一个称为原型的对象上继承属性。这种原型式继承是JavaScript的核心特性。

## 创建对象
```javascript
var a = {x:1, y:2}; //推荐使用对象直接量创建对象
var b = new Object(); //通过new方法创建对象是不推荐的。
function Test(){
  this.a = 1;
  this.b = 2;
}//定义构造函数
var c = new Test(); //Test{a:1, b:2} 通过new+构造函数创建对象
var d = new Date();
var e = []; //数组直接量
var f = new Array();
var g = /abc/; //正则表达式直接量
var h = new Regexp("javascript"); //

## 原型链
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

## 属性访问
```javascript
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