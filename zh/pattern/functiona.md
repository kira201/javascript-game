# 函数式编程

## 优势

## 纯函数

## 高阶函数
```js
//函数式编程风格
//高阶函数
function not(f){
  return function(){
    var result = f.apply(this, arguments);
    return !result;
  }
}
var isEven = function(x){ return x % 2 === 0;}
var isOdd = not(isEven);
isEven(4); //true
isOdd(4); //false

//缓存计算结果
function memoize(func, hasher) {
  var memo = {};
  return function() {
    var key = arguments.length + Array.prototype.join.call(arguments, ',');
    return memo.hasOwnProperty(key) ? memo[key] : (memo[key] = func.apply(this, arguments));
  };
}
var fibonacci = memoize(function(n) {
  return n < 2 ? n: fibonacci(n - 1) + fibonacci(n - 2);
});
```
## 科里化curry

## 代码组合

## 例子