const functions = require('firebase-functions');
const firebase = require('firebase');

const config = {
  apiKey: "AIzaSyDHmoytKP_syiuyO23lrUU1f2Gas9QM914",
  authDomain: "iot-sensor-movimento.firebaseapp.com",
  databaseURL: "https://iot-sensor-movimento.firebaseio.com",
  projectId: "iot-sensor-movimento",
  storageBucket: "iot-sensor-movimento.appspot.com",
  messagingSenderId: "159562105766"
};
firebase.initializeApp(config);

exports.iot = functions.https.onRequest((req, res) => {
  
  let database = firebase.database();
  const timestamp = Date.now()
  let id = null;

  const received = {
    action: req.query.action,
    // timestamp: req.query.timestamp,
    timestamp: timestamp,
    idReceived: req.query.id,
    idTimestamp: timestamp
  }
  console.info('Received', req.query);
  console.info('Constructed', received);

  if (received.action == 'start') {
    const data = { dateTimeStart: received.timestamp }
    console.info('Saving new event', data);
    id = received.idTimestamp;

    database.ref('presence/' + received.idTimestamp).set(data);
  } else if (received.action == 'stop') {
    id = received.idReceived;
    database.ref('presence/' + received.idReceived).once('value')
      .then(snapshot => {
        const savedData = snapshot.val()
        savedData.dateTimeStop = received.timestamp
        console.info('Updating event', savedData);
        database.ref('presence/' + received.idReceived).set(savedData);
      })
      .catch(err => {
        console.error('ID not searched', err)
      })
  }

  res.send(id.toString());
  
});
