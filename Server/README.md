## CyberBird Server

**Development**

*   Run `npm install` to install all dependencies
*   Set up env variables in `.env` file
*   Launch server with `node ./server.js

**Environment variables**
```js
    NODE_ENV=development|production // Shows additional logs while 'development'
    WS_PORT=1080 // Port where application will be started (default: 1080)
    STATIC_LOCATION=./static // Path to your static files (default: ./static)
```

**Main server messages**
```bash
X;<game_version> - check game version
0 - web client connction
3 - game started
2;0-1 - web client disconnected
1;0-1 - player jumped
4;9999 - provide token
5;9999 - check token
9;1;100 - game over, send results
```
