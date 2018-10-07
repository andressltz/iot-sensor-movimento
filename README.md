# IOT Sensor de Movimento

## Functions

### Executar local

```
$ npm install -g firebase-tools
$ firebase login
$ cd firebase\functions
$ npm install
$ firebase serve
```

Fazer GET

http://localhost:5000/iot-sensor-movimento/us-central1/iot?id=abc&action=start&timestamp=134556789

Parametros:

id = valor aleatório de identificação do movimento identificado

action = start/stop

timestamp = timestamp do momento de inicio ou pausa da captura de movimento

### Deploy

```
$ cd firebase\functions
$ npm install
$ firebase deploy
```

Fazer GET URL Pública
https://us-central1-iot-sensor-movimento.cloudfunctions.net/iot?id=abc&action=start&timestamp=134556789


## Ideia do projeto

placa -> wifi -> post functions -> salvar database

client -> ler database

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

// post(khjkfgjhkjgf, start, timestamp)
// post(khjkfgjhkjgf, stop, timestamp)
