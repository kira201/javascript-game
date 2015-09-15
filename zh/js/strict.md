# 严格模式(strict mode)
目的：
* 消除Javascript语法的一些不合理、不严谨之处，减少一些怪异行为;
* 消除代码运行的一些不安全之处，保证代码运行的安全；
* 提高编译器效率，增加运行速度；
* 为未来新版本的Javascript做好铺垫。

## 自动进入严格模式
在webpack或browserify之类的打包工具下会自动将每个模块内容封装在以严格模式的匿名函数里，无需人工指定。
```js
//这是你写的一个模块叫sqrt.js，文件内容如下
module.exports = function(x){
    return x*x;
};
//打包后变成这样子的
function(module, exports, require) {
    "use strict";
    module.exports = function(x){
        return x*x;
    }
}
```

## 禁止变量未声明就赋值，可以避免不小心引入全局变量的坑
```js
function test1(){
    v = 1; //正常模式下不小心遗漏var的后果就是创建或者更改了一个全局变量，太可怕了。
    return v;
}
function test2(){
    "use strict";
    v = 1; //语法错误
    return v;
}
test1(); //导致全局变量被创建
test2(); //报错，这样就安全多了
```

## 禁止使用with语句
```js
function test1(){
    var foo = 1;
    var bar = {foo:2};
    //严格模式下语法错误
    with (bar){
        return(foo);
    }
}
test1();//正常模式下函数返回2而不是1，是不是感觉很凌乱
function test2(){
    "use strict";
    var foo = 1;
    var bar = {foo:2};
    with (bar){
        return(foo);
    }
}//语法错误
```

# eval作用域，将eval中声明的变量放到eval作用域内，使得eval更安全一些。
```js
function test1(){
    var x = 1;
    eval('var x = 2;'); //糟糕，把x变量给改了
    return x;
}
function test2(){
    "use strict";
    var x = 1;
    eval('var x = 2;'); //安全，不会破坏函数内的变量x
    return x;
}
test1(); //返回2
test2(); //返回1
```

# 禁止this关键字指向全局变量
```js
function test1(){
    this.x = 1;
}
function test2(){
    "use strict";
    this.x = 1;
}
test1(); //糟糕，不小心创建了全局变量并赋值为1
test2(); //语法错误，避免了构造函数的误用。正确用法为 var obj = new test2();
```

# 禁止函数内部遍历调用栈
```js
function test(){
    "use strict";
    test.caller //报错
    test.arguments //报错
}
test();
```

# 对象不能有重名的属性
```js
function test(){
    "use strict";
    return {
        x:1,
        x:2,
        y:3
    }
}
test(); //(测试失败，并没有报错)
```

# 函数参数不能重名
```js
function test1(x,x,y){
    return x+y;
}
test1(1,2,3);//=>5，参数名都起错了你也不告诉我！
function test2(x,x,y){
    "use strict";
    return x+y;
}//语法错误
```

# 禁止八进制表示法
```js
function test1(){
    return 0100;
}
test1();//=>64
function test2(){
    "use strict";
    return 0100;
}//语法错误
```

# 不允许对arguments赋值
```js
function test1(){
    arguments = 1;
    return arguments;
}
test1();//返回1
function test2(){
    "use strict";
    arguments = 1;
    return arguments;
}//语法错误
```

# arguments不再追踪参数的变化
```js
function test1(x){
    x = 2;
    return arguments[0];
}
function test2(x){
    "use strict";
    x = 2;
    return arguments[0]
}
test1(1);//=>2
test2(1);//=>1
```

# 禁止使用arguments.callee
```js
//递归方法计算阶乘
var test1 = function(n){
    if(n == 0) return 1;
    //正常模式下在匿名函数内你可以这样进行递归调用
    return n * arguments.callee(n-1);
}
var test2 = function(n){
    "use strict";
    if(n == 0) return 1;
    //严格模式下你无法在匿名函数下调用自身了
    return n * arguments.callee(n-1);
}
test1(3) //=>6
test2(3) //报错，
```

# 函数必须声明在顶层
```js
var test1 = function(flag){
    if(flag){
        function foo(){return 1;}
    }else{
        function foo(){return 2;}
    }
    return foo();
}
var test2 = function(flag){
    "use strict";
    if(flag){
        function foo(){return 1;}
    }else{
        function foo(){return 2;}
    }
    return foo();
}
var test3 = function(flag){
    if(flag){
        var foo = function(){return 1;}
    }else{
        var foo = function(){return 2;}
    }
    return foo();
}
var test4 = function(flag){
    "use strict";
    if(flag){
        var foo = function(){return 1;}
    }else{
        var foo = function(){return 2;}
    }
    return foo();
}
test1(true);//=>2 正常模式下居然返回的是2
test2(true);//报错 foo不是一个函数
test3(true);//=>1 使用函数表达式时表现正常
test4(true);//=>1 使用函数表达式不受严格模式的约束
```
