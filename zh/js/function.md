# 函数
知识点：
* 函数是一段JavaScript代码，可被执行或者调用任意次。
* 用于初始化一个新创建对象的函数称为构造函数，函数名首字母一般为大写，表明此函数是一个类。
* 函数也是对象，可以随意操控。例如可以赋值给变量、作为参数传递给其他函数或者作为函数的返回值，可以给函数设置属性，甚至调用它们的方法。
* 函数挂在在一个对象上，作为对象的一个属性，就称它为对象的方法。通过对象来调用函数时，该对象就是此次调用的上下文(context)，用this来引用。
* 函数的调用可以切换上下文，也就是a对象借用b对象的方法调用，这时候的this指向a。
* 函数决定变量的作用域，函数可以嵌套定义，构成一个作用域链。函数内可以访问它们被定义时所处的作用域中的任何变量，这就是JavaScript的闭包(closure)
* 函数定义有两种 函数语句定义和函数表达式定义。
* 不在任何函数内用函数语句定义的函数将构成一个以函数名称命名的全局变量，应该尽量避免。
* 没有return语句的函数返回值为undefined。
* 函数参数无类型限制，也无个数限制

## 函数定义
```javascript
//函数语句定义一个名字叫做hello的函数
function hello(msg){
  return "hello " + msg;
}
function(){} //语法错误 函数定义语句不可以缺少函数名称

## 函数表达式
(function(){}) //正确 函数表达式
(function(){})() //正确 定义一个匿名函数然后立刻执行
var foo = function(){}; //正确 定义一个匿名函数赋给foo变量。
var foo = function bar(){}; //函数表达式也可以有名字
```

## 两种定义方式的区别
函数定义与函数表达式 两种方式都创建了新的函数对象，但函数声明语句的函数名是一个变量名，变量指向函数对象， 和通过var声明变量一样，函数定义语句中的函数被显示地提前到了脚本或函数的顶部，因此它们在整个脚本和函数内都是可见的，但是使用var 表达式定义函数，只有变量声明提前了，变量初始化代码仍然在原来的位置，用函数语句创建的函数，函数名称和函数体均被提前，所以我们可以在声明它之前就使用它。
```js
function test(){
    "use strict"
    return fn;
    function fn(){
        return true;
    }
}

function test(flag){
    "use strict"
    if(flag){
        function fn(){
            return true;
        }
    }else{
        function fn(){
            return false;
        }
    }
    return fn();
}

function test(flag){
    "use strict"
    if(flag){
        var fn = function fn(){
            return true;
        }
    }else{
        var fn = function fn(){
            return false;
        }
    }
    return fn();
}
```

## 函数调用
```js
var obj = {
  x:1,
  y:2,
  foo: test,
  bar:function(a, b){
    return this.x + this.y + a + b;
  }
};
obj.foo(); //=>Object{...} 对象方法的调用，这时候上下文this指的是obj对象本身。
obj["foo"](); //使用方括号进行访问和调用。
obj.foo().bar(1,2); //6 链式调用被jQuery广泛使用
```

## 函数是对象
```js
function fn(){}
typeof fn === 'function' //true
fn instanceof Object //true
//内置属性
fn.name
fn.constructor
fn.prototype
fn.call
fn.apply
fn.bind
//自定义属性
fn.x = 1
fn.foo = function(){
    return this.x;
}
fn.foo(); //1
```

## 一类对象 (First class)
一类对象的三个条件：可以赋值给变量、作为参数传递给其他函数、作为函数返回值。
* 作为变量
```js
var foo = function(){
	return 'foo';
}; //变量
var bar = function(){
	return 'bar';
}; //变量
foo(); //foo
bar(); //bar
var obj = {
	foo:foo,
	bar:bar
}; //作为对象属性
obj.foo(); //foo
obj.bar(); //bar
var arr = [foo, bar]; //作为数组元素
arr[0](); //foo
arr[1](); //bar
```
* 作为参数传递给其他函数
```js
//按血量从小到大进行排序
var arr = [
	{name:'aaa', hp:200},
	{name:'bbb', hp:100},
	{name:'ccc', hp:300}
	];
var compareRule = function(a, b){
	return a.hp - b.hp;
} //定义比较规则函数
arr.sort(compareRule); //作为排序函数的参数传递进来
```
* 作为函数返回值
```js
var skills = {
    fire: function(sender, target){
        console.log(sender.name + ' cast a fireball to ' + target);
    },
    ice: function(sender, target){
        console.log(sender.name + 'you cast a ice to' + target)
    }
}
function getSkill(name){
    var noimplement = function(){
        console.log('skill ' + name +  ' not implement')
    }
    var skill = skills[name];
    if(typeof skill === 'function'){
        return skill;
    }else{
        return noimplement;
    }
}
var player = {
    name:'player',
    attack: function(skillName, target){
        var fn = getSkill(skillName);
        fn(this, target);
    }
}
player.attack('fire', 'enemy1');
player.attack('ice', 'enemy1');
player.attack('xxx', 'enemy1');
```

## 参数
```js
//可选形参, 设置参数默认值
function test(target, msg){
  if(msg === undefined) msg = 'hello';
  if(target === undefined) target = 'world';
  return msg + ' ' + target;
}
test(); //"hello world"
test('pig'); //"hello pig"
test('school', 'goto'); //"goto school"

//可变长形参 利用arguments对象实现
//max:模仿Math.max函数实现
function max(/* ... */){
  var max = -Infinity;
  for(var i=0,len=arguments.length; i < len; i++){
    if(arguments[i]> max) max = arguments[i];
  }
  return max;
}
max(3,1,5,2); //5
var arr = [3,1,5,2]; //从一个数组中找到最大值
max.apply(this, arr); //5 技巧：利用apply特性把数组变成实参

//用对象属性用作实参，可忽略传入函数的参数顺序和数量，简化API调用的有效手段
function move(options){
  var defaults = {
    from:0,
    to:100,
    speed:10
  };
  _.defaults(options, defaults); //underscore.js中的一个函数，合并配置。
  //do something
}
move(); //无参数传入， 全部使用默认值
move({speed:100}); //速度100 其他用默认值
move({from:100, to:200}); //省略speed speed使用默认值
```

## 作用域
```js
//变量提升
```

## 上下文
```js
function test(){
  return this;
}
test(); //Window{...} 非严格模式下，调用上下文this指向全局变量，否则为undefined
//切换上下文
var obj2 = {x:100, y:200};
obj.bar.call(obj2, 1, 2); //303 第一个参数是上下文对象， 后边的参数是指定调用的实参
obj.bar.apply(obj2, [1, 2]);//303 apply与call类似，参数2个，一个是上下文对象 第二个是实参数组
//绑定上下文
function bind(f, o){
  if(f.bind) return f.bind(o);//函数的bind属性是ECMAScript5中新增的方法
  return function(){
    return f.apply(o, arguments);
  }
}
var tom = {name:'Tom'}, peter = {name:'Peter'};
function say(msg){return this.name + ' ' + msg};
var tomsay = bind(say, tom), petersay = bind(say, peter);
tomsay('hi'); //Tom:hi
petersay('hi'); //Peter:hi
```

## 闭包 (Closure)
```js
var myClosure = (function() {
	var counter = 0;
	var inc = function() {
		return ++counter;
	}
	var dec = function() {
		return --counter;
	}
	return {
		inc: inc,
		dec: dec
	}
})();

//错误的闭包用法
function constfuncs(){
  var funcs = [];
  for(var i=0; i<10; i++){
    funcs[i] = function(){return i;};
  }
  return funcs;
}
var funcs = constfuncs();
funcs[5]() //返回值是10！
```

## 立即调用的函数表达式 (IIFE)
Immediately-invoked Function Expression
```js
var obj = (function(n){
  var x = n, y = 2*n;
  return {x:x, y:y};
})(10); //obj => {x:10, y:20}
```

## 构造函数与原型
```js
//函数的属性和方法
function Test(a, b){this.a = a; this.b=b};
Test.length //2 函数的length属性表示函数的形参个数
Test.prototype //{} 函数的prototype属性指向一个对象
Test.prototype.className = 'Test';
Test.prototype.sum = function(){
  return this.a + this.b;
}
//当函数用作构造函数时候，新创建的对象会从原型上继承属性。
var o = new Test(1, 2); //{a: 1, b: 2, className: "Test", sum: function}
o.sum(); //3
```
