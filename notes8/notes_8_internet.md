---
title: "CS50 Lecture 8: Internet"
author: Jordan Mandel
date: 2021/11/04
geometry: margin=2.54cm
---

# The Internet
- internet is the network of computers
- routers control where the data goes between the computers; they are computers themselves
- protocols are the basic agreed algorithms for communication between computers
- packets of data are sent around the internet
- **IP** stands for internet protocol. **IP Addresses** are unique for computers connected to the inernet.
	- Routers have a table mapping IP addresses to cables each connected respectively to their own routers. The routers communicate with each other with their own protocols to route packets.
- **DNS** is provided by **Internet Service Providers** (**ISP**) to map things like `cnn.com` to actual IP addresses.
- **TCP** provides ability for a server at the same IP address to provide multiple services by appendign a **port number** to the end of the IP address. 
	- can resend packets if it's not received. Asks for labeling/counting of packets.
	- net neutrality means that routers treat all packets equally.

# Web Development
- The web is just one application on the internet.  Zoom and email are others
- `HTTP` controls how we interact with TCP/IP packets
	- `GET` gets data, `POST` sends data.
- `https://www.example.com`
	- `https` is the secure version of `http`
	- `.com` is the top level domain. for commercial. some top level domains have restrictions.
	- `www` lets us know we're on the worldwide web. but it's optional because it's mostly implied. 
	- `/` at the end requests a default file.

- An HTTP request might start:
```
GET / HTTP/1.1
Host: www.example.com
...
```
	- `GET` means we are getting a file. `/` means a default file. Or more specific `GET /index.html`
	- Using version 1.1 of `HTTP`.
	- have to specify the website because the server might be hosting multiple.

- The response might be
```
HTTP/1.1 200 OK
Content-Type: text/html
...
```
	- `HTTP` version followed by status code.
	- Type of content included in packet
	- Then the actual packet content.

- We can type in an `http` web address and it will switch over to `https`.  This gets http status code `301 Moved Permanently`

- Others include
	- `200 OK`
	- `301 Moved Permanently`
	- `304 Not Modified` lets us use the cache.
	- `307 Temporary Redirect`
	- `401 Unauthorized`
	- `403 Forbidden`
	- `404 Not Found`
	- `418 I'm a Teapot`
	- `500 Internal Server Error` might be caused by buggy code on a server
	- `503 Service Unavailable`

# HTML
- Hypertext Markup Language
- An example 
```
<!DOCTYPE html>

<html lang="en">
	<head>
		<title>
		hello, title
		</title>
	</head>
	<body>
		hello, body
	</body>
</html>
```
	- first lie says it's html.
	- then we have a tag.  the `lang="en"` is an attribute tag; specifies that the page is in english.
	- there is a tree like heirarchical data structure.
