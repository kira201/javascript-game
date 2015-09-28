# 数据绑定

```javascript
class Events{
	constructor(){
		//存储订阅事件的容器
		this.events = {};
	}
	emit(eventName, ...args){
		if(!this.events[eventName]){
			return;
		}
		//从容器中取出相关事件的所有订阅，依次执行
		var events = this.events[eventName];
		for(var i=0; i<events.length; i++){
			events[i][0].apply(events[i][1], args);
		}
	}
	on(eventName, callback, context){
		if(!this.events[eventName]){
			this.events[eventName] = [];
		}
		//将订阅的回调及上下文对象存储在容器内
		if(this.events[eventName].indexOf(callback) === -1){
			this.events[eventName].push([callback, context]);
		}
	}
	off(eventName, callback){
		if(!this.events[eventName]){
			return;
		}
		if(callback){
			//从容器内移除某个事件
			var idx = this.events[eventName].indexOf(callback);
			this.events[eventName].splice(idx, 1);
		}else{
			//从容器内移除所有相关事件
			delete this.events[eventName];
		}
	}
}

```