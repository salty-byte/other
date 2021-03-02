# Python tips

## 変数の中身を確認する

- print
- pprint
- vars
- dir

確認対象

```
class MyObject:
  def __init__(self, id, name):
    self.id = id
    self.name = name

obj = MyObject(1, 'Taro')
```

**print**

```
print(obj)
```

出力例:

```
<__main__.MyObject object at 0x7fc5373a8490>
```

**pprint**

print をより見やすくした形式で出力する。  
オブジェクトは(そのままでは)中身まで出力されないので、vars 等と併せて利用すると良い。
https://docs.python.org/ja/3/library/pprint.html

```
from pprint import pprint
pprint(obj)
```

出力例:

```
<__main__.MyObject object at 0x7fc5373a8490>
```

**vars**

```
print(vars(obj))
```

出力例:

```
{'id': 1, 'name': 'Taro'}
```

**dir**

オブジェクト内の属性名リストを返す。

```
print(dir(obj))
```

出力例:

```
['__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'id', 'name']
```
