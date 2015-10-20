# 组件模式
组件基类 components/Component.js
```js
class Component {
	constructor(owner, confg){
		this.owner = owner;
		this.config = config;
	},
	sendMessage(){
		this.owner.sendMessage.apply(this.owner, arguments);
	},
	onAdd(){},
	onRemove(){},
	onMessage(){}
}
```

组件1 Component1.js
```js
class Component1 extends Component{}
module.exports = Component1;
```

组件2 Component2.js
```js
class Component2 extends Component{}
module.exports = Component2;
```

组件工厂 components/index.js
```js
var components = {
	Component1: require('./Component1.js'),
	Component2: require('./Component2.js'),
};
module.exports = function createComponent(owner, config){
	var ComponentClass = components[config.className];
	if(!ComponentClass){
		throw new Error('component:' + config.className + ' not exist');
	}
	if(typeof ComponentClass.create === 'function'){
		return ComponentClass.create(owner, config);
	}else{
		return new ComponentClass(owner, config);
	}
}
```

GameObject.js
```js
var componentFactory = require('./components/index.js');

class GameObject {
	constructor(){
		this.components = {};
	}
	addComponent(config){
		var name = config.name;
		if(this.components[name]){
			throw new Error('component:' + name + ' already exist');
		}
		var component = componentFactory(this, config);
		component.onAdd();
		this.components[name] = component;
	}
	removeComponent(name){
		var component = this.components[name];
		if(component){
			component.onRemove();
		}
	}
	sendMessage(){
		for(var i in this.components){
			this.components[i].onMessage.apply(this.components[i], arguments);
		}
	}
}
```