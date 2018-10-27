const functions = require('firebase-functions');
const firebase = require('firebase');

module.exports = functions.https.onRequest((req, res) => {

  let database = firebase.database();

  database.ref('presence').once('value')
    .then(snapshot => {
      res.send(snapshot.val());
    })

});
