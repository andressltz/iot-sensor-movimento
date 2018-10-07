const functions = require('firebase-functions');
const firebase = require('firebase');

// // Create and Deploy Your First Cloud Functions
// // https://firebase.google.com/docs/functions/write-firebase-functions
//
exports.iot = functions.https.onRequest((req, res) => {

  const config = {
    apiKey: "AIzaSyDHmoytKP_syiuyO23lrUU1f2Gas9QM914",
    authDomain: "iot-sensor-movimento.firebaseapp.com",
    databaseURL: "https://iot-sensor-movimento.firebaseio.com",
    projectId: "iot-sensor-movimento",
    storageBucket: "iot-sensor-movimento.appspot.com",
    messagingSenderId: "159562105766"
  };
  firebase.initializeApp(config);
  let database = firebase.database();

  let data = {
    action: req.query.action,
    timestamp: req.query.timestamp,
    id: req.query.id
  }
  console.log(req.query);

  if (data.action == 'start') {
    database.ref('presence/' + data.id).set({
      dateTimeStart: data.timestamp
    });
  } else if (data.action == 'stop') {
    database.ref('presence/' + data.id).set({
      dateTimeStop: data.timestamp
    });
  }

  res.send(data);
});
