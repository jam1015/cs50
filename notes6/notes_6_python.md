---
title: "CS50 Lecture 6: Python"
author: Jordan Mandel
date: 2021_08_17
geometry: margin=2.54cm
output: pdf_document
---
# Intro
```
print("hello, world")
```


## can get strings

```
answer = get_string("What's your name? ")
print("hello, " + answer)
```

```
from cs50 import get_string

answer = get_string("What's your name? ")
print("hello, " + answer)
```

## F strings
```
print(f"hello, {anser})
```

## if/else:

```
if x < y:
	print("x is less than y")
elif x > y:
	print("x is greater than y")
else:
	print("x is equal to y")
```

## boolean expression:

```
while True:
	print("hellow, world")
```

## we can write a loop:

```
i=0
while i < 3:
	print("hello, world")
	i += 1
```

## can write for loop:

```
for i in [0, 1, 2]: // this is like a list
	print("cough")
```

`range(3)` gives `[0, 1, 2]`
`range(0, 101, 2)` goes from `0` to `100` in increments of `2`.

we can print an integet with print `i`.

# data types
- `bool`: `True`, `False`
- `float`
- `int`
- `str`

More complex types include

- `range`: sequence of numbers
- `list`: sequence of mutable values: can grow or shrink
- `tuple`: tuple: collection of ordered values
- `dict`: key value pairs
- `set`: unique values with no duplicates


# CS50 Library
- `get_float`
- `get_int`
- `get_string`

Can import individual functions

```
from cs50 import get_flost
from cs50 import get_int
from cs50 import get_string
```
or
```
from cs50 import get_float, get_int, get_string
```
or
```
import cs50
```

# some image manipulation
- It's a higher level language

```
from PIL import Image, ImageFilter
before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.BoxBlur(1))
after.save("out.bmp")
```

- Can change arguments to BoxBlur to see how many are included.
```
words = set()

def check(word):
	if word.lower() in words:
		return True
	else:
		return False

def size():
	return len(words)

def unload()
	return true

def load(dictionary):
	file = open(dictionary, "r")
	for line in file:
		words.add(line.rstrip())
file.close()
return True
```
