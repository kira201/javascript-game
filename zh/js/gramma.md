# 语法
表达式、运算符、条件、循环跟其他语言都差不多，没啥可说的。

## 相等运算符
严格相等运算符=== ：先比类型再比值
严格不相等运算符!== ：等价于!(a===b)
```js
null === null //true
undefined === undefined //true
NaN === NaN //false NaN跟任何值都不相等，只能用isNaN进行判断
Infinity === Infinity+1 //true
```
相等运算符== ：先进行类型转换再比较
不相等运算符!= ： 等价于!(a==b)
```js
//规则1：null == undefined
null == undefined //true
//规则2：数字与字符串比较 字符串转换成数字
'3e1' == 30 //true
'0' == 0 //true
'' == 0 //true
//规则3：与布尔比较 true=>1 false=>0
0 == false //true
1 == true //true
2 == true //false 
2 == false //false
//规则4：一个值为对象，另一个值为数字或字符串，对象通过toString或valueOf转成原始值再比较
[] == '' //true
[true] == 'true' //true
[1,2] == '1,2' //true
({x:1,y:2}) == '[object Object]' //true 
//规则5：其余的情况一律不等
```

## 变量声明提前
JavaScript的变量声明语句无论出现在何处，都会先于其他代码首先被执行。使用var关键词声明变量的作用域是当前的执行上下文，有可能是外围函数，或者，当变量声明在函数体之外时，则为全局变量。
```js
var scope = "global";
function test() {
    console.log(scope); //=>undefined 注意:这里并不输出"global"
    var scope = "local";
    console.log(scope);//=>"local"
}
//根据声明提前规则，上面的函数等价于
function test() {
    var scope;
    console.log(scope); //=>undefined
    scope = "local";
    console.log(scope);//=>"local"
}
```

## 创建全局变量
我们构建的开发环境会将每个模块自动运行在严格模式下，不会不小心的无意全局变量。若要创建全局变量，请使用显式的全局变量创建方法。
```js
window.gg = {}; //浏览器环境下创建全局变量的方法
global.gg = {}; //其他js运行环境下的全局变量创建方法
```

## 包装对象

## 进入断点语句
```javascript
function foo(){
    for(var i=0;i<10;i++){
        if(i===5) debugger //当i等于5时进入断点调试状态
    }
}
foo();
```

## 错误抛出和异常处理
```javascript
var foo = function(){
    throw new Error('my error'); //扔出一个自定义的错误
}
try {
    foo();
}catch(e){
    console.log(e); //Error Object
    console.log(e.message); //'my error'
    console.log(e.stack); //打印出调用堆栈信息
}
```
