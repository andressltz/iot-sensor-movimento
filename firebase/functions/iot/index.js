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

module.exports = functions.https.onRequest((req, res) => {
  
  let database = firebase.database();

  const received = {
    action: req.query.action,
    timestamp: req.query.timestamp,
    id: req.query.id
  }
  console.info('Received', req.query);

  if (received.action == 'start') {
    const data = { dateTimeStart: received.timestamp }
    console.info('Saving new event', data);

    database.ref('presence/' + received.id).set(data);
  } else if (received.action == 'stop') {
    database.ref('presence/' + received.id).once('value')
      .then(snapshot => {
        const savedData = snapshot.val()
        savedData.dateTimeStop = received.timestamp
        console.info('Updating event', savedData);
        database.ref('presence/' + received.id).set(savedData);
      })
  }

  res.send(received);
});
