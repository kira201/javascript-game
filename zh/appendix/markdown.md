# Markdown以及gitbook语法

# 标题1
## 标题2
### 标题3
#### 标题4
##### 标题5
###### 标题6

## 段落
paragraph1  *强调* ![图片](http://www.google.com) [链接](地址) <自动链接>

这个term1和term2有描述说明的。请参考脚注说明.[^1]。两个回车为一个段落。

这是一个`内嵌`的代码段。一个回车不是新的一行。
这是`另一个`。这个{{book.myVariable}}是一个内嵌的变量。文档修改日期:{{file.mtime}}

## 引入其他文件内容
{% include "../../LICENSE.md" %}

## 代码
```js
var a = 123;
console.log(a);
alert(12345)
```

## 代码区块
    code1
    code2

## 表格
|左对齐|中对齐|右对齐|
|---|:---:|---:|
|ab|a|1|
|1234|abc|10|

## 引用
>quote paragraph1

>quote paragraph2
>> This is nested blockquote.

## 无序列表
* list1
* list2
+ list3
- list4

## 有序列表
1. list1
1. list2
1. list3

## 分割线
ab
***
cd
