# 面向对象
* 面向对象不是银弹，简单至上
* 组合优于继承
* 鸭式辩型
* 用最新的es6语句

## es6中的类
```js
//定义
class Person {
    constructor(name) {
        this.name = name
    }
    hi(){
        console.log('hi, my name is ' + this.name);
    }
}
//继承
class Man extends Person {
    hi(){
    }
}
//使用
var a = new Man('peter');
a.hi();
```
## ES5类的定义
```js
//es5
function Person(name){
    this.name = name;
}
Person.prototype.hi = function(){
    console.log('hi, my name is ' + this.name);
}

var peter = new Person('Peter'); //创建实例对象
peter.name //Peter
peter.hi(); //调用方法 'hi, my name is Peter'

```

## ES5的继承
```js
//node.js里的继承实现方法
//原型继承
if (typeof Object.create === 'function') {
  // implementation from standard node.js 'util' module
  module.exports = function inherits(ctor, superCtor) {
    ctor.super_ = superCtor
    ctor.prototype = Object.create(superCtor.prototype, {
      constructor: {
        value: ctor,
        enumerable: false,
        writable: true,
        configurable: true
      }
    });
  };
} else {
  // old school shim for old browsers
  module.exports = function inherits(ctor, superCtor) {
    ctor.super_ = superCtor
    var TempCtor = function () {}
    TempCtor.prototype = superCtor.prototype
    ctor.prototype = new TempCtor()
    ctor.prototype.constructor = ctor
  }
}

//继承的使用方法，原生态
function Person(name){
  this.name = name;
}
Person.prototype.hi = function(){
  console.log('hi my name is ' + this.name);
}
function Man(){
  Person.apply(this, arguments);
}
inherits(Man, Person); //Man继承于Person
Man.prototype.hi = function(){
  console.log('A man say:');
  this.constructor.super_.prototype.hi.apply(this, arguments);
}
var a = new Man('peter');
a.hi();

```

## 另一种风格的继承
```js
//原型继承
function inherits(ctor, superCtor) {
  ctor.super_ = superCtor
  ctor.prototype = Object.create(superCtor.prototype, {
    constructor: {
      value: ctor,
      enumerable: false,
      writable: true,
      configurable: true
    }
  });
};

function BaseClass(){}//定义一个基类
BaseClass.prototype.superProto = function(){
  return this.constructor.super_.prototype;
}
/**
 * 给基类顶一个静态方法extend，用于创建子类
 * @param {Object} props 新属性新方法
 * @return {constructor} 子类构造函数
 */
BaseClass.extend = function(props){
  //创建子类构造函数
  function F(){
    //用init函数代替构造函数
    if(this.init) this.init.apply(this, arguments);
  }
  //将静态方法传递给子类
  for(var i in this){
    F[i] = this[i];
  }
  //原型继承
  inherits(F, this);
  //添加新属性新方法
  for(var i in props){
    F.prototype[i] = props[i];
  }
  return F;
}
//从BaseClass继承出一个Person的新类，添加2个新方法
var Person = BaseClass.extend({
  //init用于代替构造函数
  init: function(name){
    this.name = name;
  },
  //新方法
  hi: function(){
    console.log('hi my name is ' + this.name);  
  },
  //新方法
  work: function(){
    console.log(this.name + ' is working');
  }
});
//从Person类继承出一个Man的新类
var Man = Person.extend({
  //重写初始化方法
  init: function(name, nickname){
    this.name = name;
    this.nickname = nickname;
  },
  //重写hi方法
  hi: function(){
    //用this上下文调用父类的hi方法
    Person.prototype.hi.apply(this, arguments);
    //新加
    console.log('my nickname is ' + this.nickname);
  },
  //新方法
  sleep: function(){
    console.log(this.name + ' is sleeping');
  }
});

var a = new Man('peter', 'dog');
a.hi(); //调用重写的方法
a.work();//调用父类继承过来的方法
a.sleep();//调用
```

## 经典的继承实现
* 参考使用babel转码器将es6语法降级到es5后的代码 
* jQuery作者的继承实现方法 http://ejohn.org/blog/simple-javascript-inheritance/

## 静态方法
因为类就是函数，函数也是对象，给构造函数添加一个属性即可添加一个静态方法
```js
//定义静态方法
MyClass.myStaticMethod = function(){
}
//在类方法中调用
this.construct.myStaticMethod();
```