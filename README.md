# RTUBird

При сборке в релиз необходимо:
1. Открыть файл E_GM в редакторе UnrealEngine
2. В переменную BuldVersion внести значение текущей версии игры.
3. Открыть server.js
4. В переменную version внести текущие значение версии игры.

## Overview

App contains three parts:
* Unreal Engine **Game**
* Node.JS **Server**
* HTML5 **Controller**

**Game** and **Controller** links via **Server**, using Socket.IO library.

![NetworkInteraction-Overview](docs/images/1-NetworkInteraction-Overview.png)