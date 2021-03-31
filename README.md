# RTUBird

[![Build Status](https://dev.azure.com/rtuitlab/RTU%20IT%20Lab/_apis/build/status/CyberBird?branchName=master)](https://dev.azure.com/rtuitlab/RTU%20IT%20Lab/_build/latest?definitionId=158&branchName=master)

При сборке в релиз необходимо:
1. Открыть файл E_GM в редакторе UnrealEngine
2. В переменную BuldVersion внести значение текущей версии игры.
3. Открыть server.js
4. В переменную version внести текущие значение версии игры.

## Development run

* Clone repository
* Run `npm i` in `ServerJS` and `ClientJs` directories
* Run server with `npm start` in `ServerJS`
* Run `CyberBird.exe`
* Run client with `node .\index.ts`
> `messages.txt` contains decryption of web sockets messages.

**Test application**
In server logs find message `получен токен XXXX`. XXXX is a token of your game client. Open in browser `http://localhost:1081/#XXXX` **twice** and click _start_ on each page to start the game.

## Overview

App contains three parts:
* Unreal Engine **Game**
* Node.JS **Server**
* HTML5 **Controller**

**Game** and **Controller** links via **Server**, using Socket.IO library.

![NetworkInteraction-Overview](docs/images/1-NetworkInteraction-Overview.png)