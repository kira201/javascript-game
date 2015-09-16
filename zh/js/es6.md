# ES6

精简一部分常用的ES6语法

## 块级作用域和变量声明
```js
function test(){
	"use strict"
	var x = 1,
      y = 1,
      z = 1;
	{
		var x = 2;//函数级作用域，变量声明提前
		let y = 2;//块级作用域
		const z = 2;//块级作用域
		console.log(x, y, z); //=> 2 2 2
	}
	console.log(x, y, z); //=> 2 1 1
}
test();
//经过babel把es6转码成es5的代码如下：
function test() {
  "use strict";
  var x = 1,
      y = 1,
      z = 1;
  {
    var x = 2; //函数级作用域，变量声明提前
    var _y = 2; //块级作用域
    var _z = 2; //块级作用域
    console.log(x, _y, _z); //=> 2 2 2
  }
  console.log(x, y, z); //=> 2 1 1
}
test();
```

## 常量
禁止给常量赋值，严格模式下nodejs报语法错误，babel转码失败。
```js
const x = 123;
x = 456;//语法错误
```

## 变量的解构
ES6允许按照一定模式，从数组和对象中提取值，对变量进行赋值，这被称为解构（Destructuring）。
```js
"use strict"
//从对象中解构出x,y属性到变量
var {x, y} = {a:0, x:1, y:2};
console.log(x, y); //=> 1 2

//解构出前3个元素到变量
var [a, b, c] = [1, 2, 3, 4, 5];
console.log(a, b, c);//=> 1 2 3

//从数组中忽略一个
var [x, ,y] = [1, 2, 3];
console.log(x, y); //=>1 3

//解构出x,y属性到变量，剩下的属性放到other中
var {x, y, ...other} = {x:100, y:200, a:1, b:2, c:3};
console.log(x, y, other); //=> 100 200 {a: 1, b: 2, c: 3}

//解构失败的变量为undefined
var [foo] = [];
console.log(foo); //=>undefined
var [one, two] = [1];
console.log(one, two); //=> 1 undefined

//默认值
var [one, two=2] = [1];
console.log(one, two); //=> 1 2

//交换变量
var x = 1, y = 2;
[x, y] = [y, x];
console.log(x, y); //=> 2 1

//函数参数的解构
function test1([x, y]){
	return x + y;
}
var sum = test1([1, 2]);
console.log(sum) //=> 3
function test2({x,y=2,...other}){
	console.log(x); //=>100
	console.log(y); //=>2
	console.log(other); //=> {z:300}
}
test2({x:100,z:300});

//函数返回多个值
function test(){
	return [1,2];
}
var [x, y] = test();
console.log(x, y); //=> 1, 2
```

## 字符串模板
```js
//模板字符串
var x = 1, y =2;
var str = `x:${x}, y:${y}`;//变量嵌入
console.log(str); //=> "x:1, y:2"

//多行文本
var str = `hello ${x}
world ${y}`;
console.log(str) //=>hello 1\nworld 2

//嵌入表达式
var str = `${x} + ${y} = ${x+y}`;
console.log(str) //=> "1 + 2 = 3"
```
## 对象字面量的扩展
```js
var x = 1, y = 2;
var obj = {x, y}; //对象的简介表示法等价于var obj = {x:x, y:y}
console.log(obj); //{x:1, y:2}
var obj = {
	x,
	y,
	foo(){}
};
console.log(obj); //{x:1, y:2, foo:function(){}}
//字面量对象可以用表达式作为属性名
var obj = {
	['x' + 'y']: 3
};
console.log(obj); //{xy: 3}
```
## 类(Class)
```js
//类
class Point {
	constructor(x, y){
		this.x = x;
		this.y = y;
	}
	toString(){
		return `(${this.x},${this.y})`;
	}
}
//继承
class Circle extends Point {
  constructor(x, y, r){
    super(x, y);
    this.r = r;
  }
  hitTest(p){//判断点是否在圆形内部
  	var dx = this.x - p.x;
  	var dy = this.y - p.y;
    var distance = Math.sqrt(dx*dx + dy*dy);
    return distance <= this.r;
  }
}
var p = new Point(0,0);
var c = new Circle(1,2,3);
console.log(p.toString()); //=>(0,0)
console.log(c.hitTest(p)); //=>true
```
## 函数扩展
```js
//函数参数默认值，nodejs4.0尚未支持
function test(x, y = 'world'){
	console.log(x + ' ' + y);
}
test('hello'); //=> 'hello world'
test('hello', 'es6'); //=> 'hello es6'

//多余参数，nodejs4.0尚未支持
function test(x, y, ...other){
	console.log(x); //=>1
	console.log(y); //=>2
	console.log(other); //=> [3, 4, 5]
}
test(1,2,3,4,5);

//扩展运算符，nodejs4.0尚未支持
console.log(1, ...[2, 3, 4], 5); //等价于console.log(1,2,3,4,5)
```

## 箭头函数
```js
var sqrt = x => x*x;
console.log(sqrt(3)); //=>9
var add = (x, y) => x+y;
console.log(add(1,2)); //=>3
var random = () => Math.floor(Math.random()*100 + 1);
console.log(random()); //返回1-100的随机整数
var foo = () => {
	var x = 1;
	var y = 2;
	return {x, y}
};//函数内有多行语句用大括号括起来
```

## 函数生成器Generator
```js
var g = function*(){
	yield 'hello';
}
```
