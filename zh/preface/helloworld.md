# 准备

## 过程式编程
```js
var listener = function(eventName, data) {}

function emit(eventName, data) {
  listener(eventName, data);
}

function attack(a, b) {
  var hurt = a.atk - b.def;
  if (hurt <= 0) {
    hurt = 1;
  }
  return hurt;
}

function fight(hero, enemy) {
  var maxRound = 30;
  var round = 0
  var hurt;
  var eventData;
  emit('start');
  while (round < maxRound) {
    round = round + 1;
    emit('round', round);

    hurt = attack(hero, enemy);
    enemy.hp -= hurt;
    eventData = {
      sender: hero.name,
      target: enemy.name,
      hurt: hurt
    };
    emit('attack', eventData);
    if(enemy.hp <= 0){
      emit('end', hero.name, enemy.name, '负');
      return;
    }

    hurt = attack(enemy, hero);
    hero.hp -= hurt;
    eventData = {
      sender: enemy.name,
      target: hero.name,
      hurt: hurt
    };
    emit('attack', eventData);
    if(hero.hp <= 0){
      emit('end', hero.name, enemy.name, '胜');
      return;
    }
  }
  emit('end', hero, enemy, '平');
}
```

## 数据
```js
var hero = {
  name: 'aaa',
  hp: 100,
  atk: 20,
  def: 5
};
var enemy = {
  name: 'bbb',
  hp: 100,
  atk: 10,
  def: 5
};
```

## 运行
```js
var listener = function(eventName, data){
  console.log(eventName, data);
};
fight(hero, enemy);
```

## 驱动图形
```js
var events = [];
var times = {
	start: 1000,
	round: 1000,
	attack: 500,
	end: 1000
};
var listener = function(eventName, data) {
	events.push({
		eventName: eventName,
		data: data,
		duration: times[eventName]
	});
	if(eventName === 'end'){
		playNext();
	}
}
function render(eventName, data){
	console.log(eventName, data);
	playNext();
}
function playNext(){
	var e = events.shift();
	if(e){
		setTimeout(render, e.duration, e.eventName, e.data);
	}
}
fight(hero, enemy);
```
