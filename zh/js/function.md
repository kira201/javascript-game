# 函数
知识点：
* 函数是一段JavaScript代码，可被执行或者调用任意次。
* 用于初始化一个新创建对象的函数称为构造函数，函数名首字母一般为大写，表面此函数是一个类。
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
(function(){}) //正确 函数表达式
(function(){})() //正确 定义一个匿名函数然后立刻执行
var foo = function(){}; //正确 定义一个匿名函数赋给foo变量。
```
## 参数

## 一等公民
函数是普通变量，可以赋值给变量、作为参数传递给其他函数、作为函数返回值。
函数是对象，关于函数对象的属性和方法

## 作用域

## 上下文

## 闭包

```javascript


//函数的递归调用
function factorial(n){
  if(n<=1) return 1;
  return n * factorial(n-1);
}

//函数作为参数传入其他函数
var arr = [2, 1, 11];
arr.sort(function(a, b){
  return a - b;
}); //[1, 2, 11]

//定义一个匿名函数然后立刻执行，保护函数里边的变量不被外部使用。可用于模块定义等用途。
var obj = (function(n){
  var x = n, y = 2*n;
  return {x:x, y:y};
})(10); //obj => {x:10, y:20}

//函数调用
function test(){
  return this;
}
test(); //Window{...} 在ECMAScript3和ECMAScript5非严格模式下，调用上下文this指向全局变量，否则为undefined
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

//函数对象有两个属性方法 call 和 apply 用于间接调用，切换上下文，方法借用
var obj2 = {x:100, y:200};
obj.bar.call(obj2, 1, 2); //303 第一个参数是上下文对象， 后边的参数是指定调用的实参
obj.bar.apply(obj2, [1, 2]);//303 apply与call类似，参数2个，一个是上下文对象 第二个是实参数组

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

//匿名函数的递归，arguments.callee属性指代的就是这个函数本身
var factorial = function(n){
  if(n <= 1) return 1;
  return n * arguments.callee(n-1);
}

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

//静态函数实现
function uuid(){
  if(uuid.id === undefined) uuid.id=0;
  uuid.id ++;
  return uuid.id;
}
uuid(); //1
uuid(); //2
uuid.id //2 uuid.id是暴露的
//静态函数的改善版本，闭包特性
var uuid = (function(){
  var id = 0;
  return function(){
    id++;
    return id;
  }
})();
uuid(); //1
uuid(); //2

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

//bind方法
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

//toString方法
Math.sin.toString() //function sin() { [native code] } 内置函数返回native code
bind.toString() //自定义函数返回JavaScript源码

//判断变量是否为函数
function isFunction(x){
  return Object.prototype.toString.call(x) === '[object Function]';
}

//函数式编程风格
//高阶函数
function not(f){
  return function(){
    var result = f.apply(this, arguments);
    return !result;
  }
}
var isEven = function(x){ return x % 2 === 0;}
var isOdd = not(isEven);
isEven(4); //true
isOdd(4); //false

//缓存计算结果
function memoize(func, hasher) {
  var memo = {};
  return function() {
    var key = arguments.length + Array.prototype.join.call(arguments, ',');
    return memo.hasOwnProperty(key) ? memo[key] : (memo[key] = func.apply(this, arguments));
  };
}
var fibonacci = memoize(function(n) {
  return n < 2 ? n: fibonacci(n - 1) + fibonacci(n - 2);
});
```
