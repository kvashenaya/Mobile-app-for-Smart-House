const express = require('express')
const {graphqlHTTP} = require('express-graphql')
const cors = require('cors')
const schema = require('./schema')

let sensors;
let sensors2=[{ id: '1', Indicator: 'AirPollution', Value: '223' },
{ id: '2', Indicator: 'Temperature', Value: '20' },
{ id: '3', Indicator: 'Humidity', Value: '59' }];

let states=[{ id: '2', Enabled: false },
{ id: '3', Enabled: false }];

const app = express()
app.use(cors({
  origin: '*'
}))

// const {Client} = require('pg')
// const client = new Client({
//   host: 'localhost',
//   user: 'openpg',
//   port: 5432,
//   password: 'openpgpwd',
//   database: 'postgres'
// });

// client.connect();

// client.query('Select * from public."Sensor"', (err, res)=>{
//   if(!err){
//     sensors = res.rows;
//     //console.log(res.rows);
//   }
//   else{
//     console.log(err.message);
//   }
//   client.end;
// })

// client.query('Select * from public."Switcher"', (err, res)=>{
//   if(!err){
//     states = res.rows;
//     //console.log(res.rows);
//   }
//   else{
//     console.log(err.message);
//   }
//   client.end;
// })

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.post('/postData', (req, res) => {
  sensors2 = req.body;
  console.log("Sensors data (req.body): ", req.body);
  res.json('Data sensors received');
});

const root = {
  getUser: ({id}) => {
      const sensor = sensors2.find(sensor => sensor.id == id);
      if (!sensor) {
        throw new Error(`Couldn’t find Sensor with id ${id}`);
      }
      //console.log(sensor);
      return sensor;      
  },
  updateState: ({ id, Enabled }) => { 
      var state = states.find(st => st.id == id); 
      if (!state){
        console.log(`Couldn’t find Switch with id ${id}`);
      }
      state.Enabled = Enabled; 
      //console.log('States', states);
      return state;
     }
}
app.use('/graphql', graphqlHTTP({
  graphiql: true,
  schema,
  rootValue: root
}));
app.get('/getData', (req, res) => {
  res.send(states); console.log('State data', states);
});

app.listen(5000, () => console.log('server started on port 5000'));
