# 模块化
* 模块化是多人协作、构建大型项目的基石。
* CommonJS Modules/1.0是JavaScript模块化的事实标准。
* ES6才有内置模块系统，Node.js4.0版本尚不支持。
* node.js内置支持模块化，其他JavaScript运行环境需要用模块打包工具(比如webpack)来支持。
* 模块是被缓存的，每次调用require加载模块返回的都是同一实例，可以把模块当成单例模式。

## 模块化的发展历史

## 模块定义
* 一个js源文件就是一个模块
* 在模块内声明的变量
* 建议使用module.exports导出变量，不推荐使用exports导出
* 建议将module.exports放到文件的最后一句。
```js
//counter.js模块
//变量n没有声明在任何函数体内，可以在模块的任意位置访问，但不能被其他模块直接访问。
var n = 0;
function add(){
	return ++n;
}
function get(){
	return n;
}
//导出两个函数
module.exports = {
    add:add,
    get:get
};
//在app.js文件中使用counter.js模块
var counter = require('./counter.js');
counter.add(); //=>1
counter.add(); //=>2
var anotherCounter = require('./counter.js');
anotherCounter.add(); //=>3
anotherCounter.add(); //=>4
counter.get(); //=>4
counter === anotherCounter //=>true
```

## 模块加载
* 使用var mod = require('模块文件或模块名')语法加载模块并接收模块的导出变量。
```js
//加载nodejs的内置模块时直接使用模块名称
var events = require('events');
//加载第三方模块直接使用模块名称
var _ = require('lodash');
//加载自己的模块使用相对于当前脚本文件的相对路径
var myModule = require('./myModule.js');
```

## 模块工作原理
通过分析webpack打包的代码可以看出模块的工作原理。下面的代码来自于webpack生成的打包代码，为了更清晰的说明问题，做了少部分改动，并去掉一些不必要的代码。

1. 提供一个js入口文件，通过静态分析，就能构建出依赖关系的模块文件树。
1. 将每个模块文件单独打包，封装成如下的函数
```js
function(module, exports, require) {
    "use strict";//封装时可使模块内容自动进入严格模式状态
    /*这里是模块文件内容*/
}
```
1. 然后将封装好的所有模块都塞进一个数组里 [module1, module2, module3, ...]
1. 每个模块现在对应一个数组索引，将模块源代码中require(模块名称)替换成require(模块索引)
1. 将这个模块数组作为参数传入一个立即执行的匿名函数里
```js
(function(modules){
    //现在参数modules就是那个模块列表数组
    var installedModules = {}; //存储已加载模块的缓存
    //实现用于模块加载的函数
    function require(moduleId){
        //如果加载的模块在缓存中存在，直接从缓存中取出返回
        if(installedModules[moduleId]){
            return installedModules[moduleId].exports;
        }
        //缓存中没有，加载模块并缓存结果
        var module = {exports:{}}; //创建module.exports用于接受模块导出的变量
        installedModules[moduleId] = module; //放入缓存
        //执行模块
        var moduleWrapper = modules[moduleId]; //被匿名函数封装后的模块
        /*
         *执行封装的模块包裹函数，并指定模块的上下文为module.exports
         *所以在模块中也可以用this来代替module.exports
         *因为模块代码被执行，所以module.exports已经变为模块的导出内容
         */
        moduleWrapper.call(module.exports, module, module.exports, require);
        return module.exports; //将导出内容返回
    }
    require(0);//开始加载入口文件
})(/*模块列表数组*/)
```

## 避免模块的循环引用
问题:
```js
//test1.js
var test2 = require('./test2.js');
module.exports = {
    moduleName: 'test1.js',
    test2: test2
}
//test2.js
var test1 = require('./test1.js');
module.exports = {
    module.name: 'test2.js',
    test1: test1
}
//run.js
console.log(require('./test1.js'));
/*运行结果
{ moduleName: 'test1.js',
  test2: { 
    moduleName: 'test2.js',
    test1: {} //test1为空对象
  }
}
```
原因：可以根据上节的require函数的实现进行分析
解决方案：对模块进行延时加载
```js
//test1.js
module.exports = function(){
	var test2 = require('./test2.js');
	return {
		moduleName: 'test1.js',
		test2: test2
	}
}
//test2.js
var test1 = require('./test1.js');
module.exports = {
    moduleName: 'test2.js',
    test1: test1
}
//run.js
console.log(require('./test1.js')());
*/
```

## exports的缺陷
根据上节代码看出模块加载器最终返回的是module.exports而不是exports，所以在模块中可以对module.exports赋值但不可以对exports直接赋值，只能对exports对象进行修改。
所以在模块中尽量避免使用exports，一律使用module.export， 以免引起不必要的麻烦。
```js
module.exports === exports //true 指向同一个对象
exports.name = "test";//可以 虽然修改了对象，仍然指向同一个对象
exports.test = function(){};//可以 虽然修改了对象，仍然指向同一个对象
exports = "my module";//不可以 exports现在是字符串 module.exports仍然指向原来的对象
module.exports = "my module"; //可以
exports = {
    name: 'test',
    test: function(){}
};//不可以 exports指向一个新对象 module.export仍然为原来的对象
module.exports = {
    name: 'test',
    test: function(){}
};//可以

```

