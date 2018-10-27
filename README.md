# IOT Sensor de Movimento

## Functions e Hosting

### Executar local

```
$ npm install -g firebase-tools
$ firebase login
$ cd firebase/functions
$ npm install
$ firebase serve
```

Fazer GET

http://localhost:5001/iot-sensor-movimento/us-central1/iot?id=abc&action=start&timestamp=134556789

Acessar Dashboard

http://localhost:5000/

Parametros:

id = valor aleatório de identificação do movimento identificado

action = start/stop

timestamp = timestamp do momento de inicio ou pausa da captura de movimento

### Deploy

```
$ cd firebase
$ npm install
$ firebase deploy
```

Fazer GET URL Pública

https://us-central1-iot-sensor-movimento.cloudfunctions.net/iot?id=abc&action=start&timestamp=134556789

## Ideia do projeto

placa ESP32 -> WI-FI -> GET functions -> salvar database

client -> ler database

```
database : {
  presence : {
    zcxnzbcnxcb: {
      dateTimeStart: '09/10/2018 18:30',
      dateTimeStop: '09/10/2018 18:31'
    },
    zcxnzbcnxcb: {
      dateTimeStart: '09/10/2018 18:30',
      dateTimeStop: '09/10/2018 18:31'
    },
    zcxnzbcnxcb: {
      dateTimeStart: '09/10/2018 18:30',
      dateTimeStop: '09/10/2018 18:31'
    }
  }
}

// get(khjkfgjhkjgf, start, timestamp)
// get(khjkfgjhkjgf, stop, timestamp)
```

