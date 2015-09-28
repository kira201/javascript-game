# Factory

* 解耦
* 可根据外部配置创建对象

## 简单工厂的实现
```js
基类 heros/HeroBase.js
Class HeroBase {
	constructor(config){
		this.config = config;
	}
}
module.exports = HeroBase;
```

子类1 heros/Hero1.js
```js
var HeroBase = require('./HeroBase.js')
Class Npc1 extends HeroBase {}
module.exports = Npc1;
```

子类2 heros/Hero2.js
```js
var HeroBase = require('./HeroBase.js');
Class Npc2 extends HeroBase {}
module.exports = Npc2;
```

简单工厂的实现 heros/index.js
```js
module.exports = {
	'Hero1': require('./Hero1.js'),
	'Hero2': require('./Hero2.js'),
};
//根据配置动态实例化相关类
module.exports = function createHero(config){
	var heros = require('./heros/index.js');
	//根据className获取类对象
	var HeroClass = heros[config.className];
	if(!HeroClass) {
		//错误的类名称
		throw new Error('class' + config.className + 'not exist');
	}
	//创建新的实例对象
	return new HeroClass(config);
};
```

使用 test.js
```js
var heroFactory = require('./heros/index.js');
var a = heroFactory.createHero({className:'Hero1'});
var b = heroFactory.createHero({className:'Hero2'});
```

## 改进的工厂
Hero3.js 需要实例化之后进行初始化的工作
```js
var HeroBase = require('./HeroBase.js');
class Hero3 extends HeroBase{
	init(){}
}
//实现自身复杂的实例化过程
Hero3.create = function(config){
	var obj = new Hero3(config);
	obj.init();
	return obj;
}
```
heros/index.js
```js
module.exports = {
	'Hero1': require('./Hero1.js'),
	'Hero2': require('./Hero2.js'),
	'Hero3': require('./Hero3.js'),
	/*支持新类只需在此添加一键值对*/
};
//根据配置动态实例化相关类
module.exports = function createHero(config){
	var heros = require('./heros/index.js');
	//根据className获取类对象
	var HeroClass = heros[config.className];
	if(!HeroClass) {
		//错误的类名称
		throw new Error('class' + config.className + 'not exist');
	}
	//创建新的实例对象
	if(typeof HeroClass.create === 'function'){
		//使用自身的create方法来生成对象
		return HeroClass.create(config);
	}else{
		return new HeroClass(config);
	}
};
