# 数组(Array)
* 数组是有序的集合，元素可以是任意类型，用数组[索引]进行访问数组元素
* 数组是动态的，长度可根据需要增长或者缩减。
* 数组可以是稀疏的
* 数组有一个length长度属性，添加或者删除数组元素这个属性会自动更新，设置length的值会调整数组大小
* 数组是对象的特殊形式
* 数组继承Array.prototype中的属性，定义了一套数组操作方法。这些方法对真正的数组和类数组都有效
* 类数组不是数组，是具有length属性和非负整数属性的对象，可以看作是只读的数组借用数组的操作方法。例如Arguments对象

```javascript
var a = []; //数组直接量 等价于 a = new Array();
var a = new Array(10) ; //[undefined × 10] 创建一个长度为10的数组
var a = new Array(1,2,3); //等价于 a = [1,2,3]
a.length == 3; //true 读取数组长度
a.length = 0; //设置数组长度为0，清空数组元素
a.length = 5; //数组长度扩充到5，5个元素都是undefined
a = [1, 2, 3];
a[0] ==1; //true 读取第0个元素
a[0] = 123; //设置第0个元素为123
a.push(4); //向数组最后增加一个元素 数组为[1,2,3,4]
a.pop(); //4 从数组最后弹出一个元素 数组为[1,2,3]
a.unshift('first'); //数组为['first', 1, 2, 3]
a.shift(); //'first' 数组为[1,2,3]
var pos = 1;
a.splice(pos, 1); //删除索引位置在pos上的数组元素 [1,3]
a.splice(1, 0, 'b', 'c', 'd'); //数组插入元素 [1, 'b', 'c', 'd', 3]
//遍历数组
for(var i=0,max=a.length; i<max; i++){
  console.log(i, a[i]);
}
//ECMAScript5数组遍历方法
a.forEach(function(x){
  console.log(x);
});
var b = [[1,2],[3,4],[5,6]]; //创建二维数组
b[1][0] == 3; //true
var a = [1, 2, 3];
a.join(); //"1,2,3"
a.join(" "); //"1 2 3"
a.join(''); //"123"
var b = new Array(5);
b.join('-'); //"-----"

a.reverse(); //数组颠倒顺序 [3,2,1]
a.sort(); //排序 [1, 2, 3]
a.push(11); // [1, 2, 3, 11]
a.sort(); // 默认按照字符顺序排序 [1, 11, 2, 3]
a.sort(function(a, b){
  return a-b;
}); //用自定义排序函数进行排序 [1, 2, 3, 11]
a.sort(function(a, b){
  return b-a;
}); //用自定义排序函数进行反序排序 [1, 2, 3, 11]

//数组连接
var a = [1, 2, 3];
a.concat(4, 5); //返回一个新数组[1,2,3,4,5] 变量a仍然为[1,2,3]
a.concat([4,5]); //[1,2,3,4,5]
a.concat([4,5], [6,7]); //[1,2,3,4,5,6,7]
a.concat(4, [5, [6, 7]]); //[1,2,3,4,5,[6,7]]

//数组切片
var a = [1,2,3,4,5];
a.slice(1,3); //[2,3] 变量a仍然为[1,2,3,4,5]
a.slice(3); //[4, 5]
a.slice(1, -1); //[2,3,4]
a.slice(-3, -2); //[3]

a.toString();//"1,2,3,4,5"

//判读是否为数组
function isArray(o){
  if(Array.isArray)
    return Array.isArray(o);//ECMAScript5
  else
    return Object.prototype.toString.call(o) === "[object Array]";
}
```