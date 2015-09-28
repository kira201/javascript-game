# 单例模式
一组数据和方法的封装（类），系统中存在唯一实例的对象

## 模块即是天然完美的单例模式
singleton.js
```js
var innerData = {}; //由于模块的封装，数据变量不能被其他模块直接访问
//通过导出的方法间接访问数据
module.exports = {
    set: function(key, value){
        innerData[key] = value;
    },
    get: function(key){
        return innerData[key];
    },
    remove: function(key){
        delete innerData[key]
    }
}
```
test.js
```js
var tmp1 = require('./singleton.js');
tmp1.set('foo', 100);
tmp1.get('foo') //100

var tmp2 = require('./singleton.js');
tmp2.get('foo'); //100

tmp1 === tmp2 //true 证明是单例的

```

## 简单容易理解

## 全局变量与调试
在前端，经过模块化打包工具打包后的模块系统的所有内容是封装到一个匿名函数内的，所以整个系统是零全局变量的，自身是一个封闭的系统。
一个零全局变量系统与其他系统是无法进行交互的，这时候就需要将需要的内容用真正的全局变量暴露出来。
```js
window.app = require('./app.js');
```

## 库的命名空间以及名字耦合的问题
传统的命名空间的问题
```js
//app.js
var app = window.app = {};//根命名空间
//module1.js
app.module1 = {
	test1: function(){
		console.log(app.module1.test2());
	},
	test2: function(){
		return 'test2';
	}
};
app.module2 = function(){
	app.module1.test1();
}
```
大量的代码书写会依赖与app这个名称，当与他人的库发成命名冲突时很难进行修改。

## 用模块解决命名空间的耦合问题
通过require函数访问单例的对象，并没有使用全局变量名称，完美的解决了全局变量的名字耦合问题。
```js
//application.js 
module.exports = {version:'0.0.1'};
//module1.js
function test1(){}
function test2(){}
module.exports = {
	test1: test1,
	test2: test2
}
//module2.js
var module1 = require('./module1.js');
module.exports = function(){
	module1();
}
//app.js 入口文件
var app = require('./application.js');
//组织命名空间
app.module1 = require('./module1.js');
app.module2 = require('./module2.js');
//若有需要，暴露出全局变量与外部系统进行访问
if(typeof window === 'undefined'){
	global.app = app;
}else{
	window.app = app;
}
//若与外部系统发生命名冲突只需修改全局变量的名字
window.app1 = app;
```

## 惰性加载
单例的初始化：只有当第一次require进行加载的时候模块体内容才会被执行。
