import React, { useEffect, useState } from 'react';
import './App.css';
import io from 'socket.io-client';

function App() {
  // const [token, setToken] = useState('');
  const [comment, setComment] = useState('Ждем подключения второго игрока…');
  const [wsClient] = useState(io.connect(process.env.REACT_APP_URL!, { path: "/server" }));
  const [clientId, setClientId] = useState(-1);
  const [playersReady, setReady] = useState(false);
  const [started, start] = useState(false);
  const [score, setScore] = useState<string[]>([]);

  useEffect(() => {
    if (wsClient) {
      if (window.location.hash === '') {
        setComment('Ссылка недействительна');
        wsClient.disconnect();
      } else {
        wsClient.send('5;' + window.location.hash);
        
        wsClient.send('0');
        setClientId(-1);

        wsClient.on('message', (msg: string) => {
          console.log(msg);
          if (msg === 'dis') {
            setComment('Ссылка недействительна');
            wsClient.disconnect();
          } else if (msg === '00') {
            setClientId(0);
          } else if (msg === '01') {
            setClientId(1);
          } else if (msg === '0') {
            setReady(true);
            setComment('Нажмите на Старт');
          } else if (msg === '3') {
            start(true);
            setComment('Прыгай, чтобы выжить!');
          } else {
            console.log(msg);
            let msgData = msg.split(';');

            if (msgData[0] === '2' && !started) {
              setReady(false);
              setComment('Ждем подключения второго игрока…');
            } else if (msgData[0] === '9') {
              setScore([msgData[1], msgData[2]]);
              wsClient.disconnect();
              setReady(false);
              start(false);
              setComment('Ждем подключения второго игрока…');
            }
          }
        });
      }
    }
  }, [wsClient]);

  const startGame = () => {
    wsClient.send(`3;${clientId}`);
    setComment('Ожидаем второго игрока…');
  }

  const jump = () => {
    wsClient.send(`1;${clientId}`);
  }

  const reload = () => {
    setScore([]);
    window.location.reload();
  }

  return (
    <div className="App">
      <div className="title">
        <div className="blur">CyberBird</div>
        <div className="text">CyberBird</div>
      </div>

      {score.length === 0 ?
      <>
        <div className="button">
          <div className="progress">
            <div className="clickable" onClick={started ? jump : (clientId !== -1 && playersReady ? startGame : () => {})}>
              {!started
                ? <>
                {clientId === -1 || !playersReady
                  ? <div className="button-name">START</div>
                  : <div className="button-name active">START</div>
                } </>
                : <div className="button-name active">JUMP</div>
              }
            </div>
          </div>
        </div>

        <div className="comment">{comment}</div>
      </> :
      <>
        <div className="plane">
          <div className="text">Упс… Неудача!</div>
          <div className="text">Не расстраивайся!</div>
          <div className="repeat" onClick={reload}>Начать заново</div>
        </div>

        <div className="results">
          <div className="text">Игра окончена</div>
          <div className="text">Счёт</div>
          <div className="row">
              <div className="text name">Вы</div>
              <div className="text score">{score[clientId]}</div>
          </div>
          <div className="row">
              <div className="text name">Игрок 2</div>
              <div className="text score">{score[1 - clientId]}</div>
          </div>
        </div>
      </>
      }

    </div>
  );
}

export default App;
