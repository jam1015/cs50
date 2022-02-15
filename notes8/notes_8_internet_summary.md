---
title: "CS50 Lecture 8: Internet"
author: Jordan Mandel
date: 2021/11/04
geometry: margin=2.54cm
---

# CSS Selectors

```
a:hover
{
	 text-decoration: underline;
}

a
{
	color: #ff0000; 
	text-decoration: none;
}

header
{
    font-size: large;
    text-align: center;
}

.centered
{
    text-align: center;
}


#harvard
{
color: #ff0000
}
```
- `<link href="styles.css" rel="styesheet">`

# Events


- List of other events besides `submit` include `blur`, `change`, `click`, `drag`, `focus`, `keyup`, `load`, `mousedown`, `mouseover`, `mouseup`, `submit`, `touchmove`, `unload`, among many others: used in jeavascript `eventplanners`


# Event Handlers
```
<html>
	<head>
		<title>Event Handlers</title>
	</head>
	<body>
		<button onclick="alertName(event)">Button 1</button>
		<button onclick="alertName(event)">Button 2</button>
	</body>
</html>
```

Then we can have:

```
function alertName(event)
{
	var trigger = event.srcElement;//what element was used to activate this
	alert('You clicked on ' + trigger.innerHTML); // the inner contents of of this
}
```
