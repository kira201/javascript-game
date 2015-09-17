# JSON（JavaScript Object Notation）
* JSON全称JavaScript对象表示法。
* 互联网上最流行的数据交换格式。
* 轻量级文本格式
* 自我描述，易读，易写

## 支持的6种数据类型
* 数字(number)
* 字符串(string)
* 布尔(boolean) true false
* 空值 null
* 对象(object)
* 数组(array)

## 与JavaScript的不同之处
语法上是JavaScript语法的子集，完全兼容于JavaScript字面量表示。会JavaScript即会JSON表示，但要注意以下几点不同之处：
* 字符串只能用双引号，JavaScript单引号和双引号都可以
* JSON中对象表示的键值必须用双引号括起来， JavaScript中可以省略或者用单引号。
* JavaScript中可以保留最后一个用于分隔键值对的逗号, JSON不可以。
* JSON中的对象和数组只能容纳上面的6种数据类型，JavaScript中可以存储任意数据类型。

## 序列化与解析API
* JSON.stringify(obj) //将变量序列化为字符串
* JSON.parse(str) //将JSON字符串还原为内存数据结构
```javascript
var str = JSON.stringify(obj);
//若被解析的字符串为非法的JSON格式，会抛出异常，所以使用JSON.parse的时候要用try catch保护起来
var obj = null;
try{
    var obj = JSON.parse(str);
}catch(e){
}
//可用stringify和parse函数来深克隆对象纯粹的对象(plainobject)
function cloneObject(obj){
    return JSON.parse(JSON.stringify(obj));
}
//运行效率要比下面的方法更好
function cloneObject(obj) {
    if (obj !== Object(obj)) return obj;
    if (Array.isArray(obj)) {
        var result = [];
        for (var i = 0, len = obj.length; i < len; i++) {
            result[i] = cloneObject(obj[i]);
        }
        return result;
    } else {
        var result = {}
        for (var i in obj) {
            result[i] = cloneObject(obj[i]);
        }
        return result;
    }
};
```

## 一些适用场景
* 数据文件，配置文件
* 玩家数据的持久化存储
* 网络传输通信

## JSONSchema
JSONSchema是描述你的JSON数据格式，可用于校验和生成某种特定格式的JSON数据。
适合用于数据编辑器的制作，