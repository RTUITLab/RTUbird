# RTUBird

[![Build Status](https://dev.azure.com/rtuitlab/RTU%20IT%20Lab/_apis/build/status/CyberBird?branchName=master)](https://dev.azure.com/rtuitlab/RTU%20IT%20Lab/_build/latest?definitionId=158&branchName=master)

## Overview

App contains three parts:
* Unreal Engine **Game**
* Node.JS **Server**
* HTML5 **Controller**

**Game** and **Controller** links via **Server**, using Socket.IO library.

![NetworkInteraction-Overview](docs/images/1-NetworkInteraction-Overview.png)

## Production

**WebClient**

In `./WebClient`:
1. Run `npm i` to install dependencies
2. Set up [variables](https://github.com/RTUITLab/CyberBird/tree/master/WebClient) in `.env` file
3. Run `npm run build` to build web application


**Server**

In `./Server`:
1. Run `npm i` to install dependencies
2. Set up [variables](https://github.com/RTUITLab/CyberBird/tree/master/Server) in `.env` file
3. Run `node server.js` to run application


**GameClient**

Download built application from [Releases](https://github.com/RTUITLab/CyberBird/releases).


## Development guides

+ [WebClient](https://github.com/RTUITLab/CyberBird/tree/master/WebClient)
+ [Server](https://github.com/RTUITLab/CyberBird/tree/master/Server)

