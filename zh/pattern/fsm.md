# 有限状态机

* 简化问题难度 * 逻辑清晰 * 消除switch语句

class StateBase {
	construct(owner){
		this.owner = owner
	}
	enter(){
		//状态进入
	}
	exit(){
		//状态更新
	}
	update(dt){
		//状态进行中
	}
}

class GameObject {
	construct(){
		this.currentState = null;
	}
	changeState(state){
		if(this.currentState){
			this.currentState.exit();
		}
		var newState = new StateClass(this);
		this.currentState = newState;
		newState.enter();
	}
	update(dt){
		if(this.currentState){
			this.currentState.update(dt);
		}
	}
}

extend({methods}, {property}, {events})