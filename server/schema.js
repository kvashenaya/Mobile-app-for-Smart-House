const {buildSchema} = require('graphql')

const schema = buildSchema(`   
    type User {
        id: ID
        Indicator: String
        Value: String
    }
    type State {
        id: Int
        Enabled: Boolean
    }
    type Query {
        getUser(id: ID): User
    }
    type Mutation {
        updateState(id: Int, Enabled: Boolean): State
    }
`)

module.exports = schema


// import {
//     GraphQLObjectType,
//     GraphQLString,
//     GraphQLInt,
//     GraphQLSchema,
//     GraphQLList,
//     GraphQLNonNull
//   } from 'graphql';
// import Db from './db';

// const Sensor = new GraphQLObjectType({
//     name: 'Sensor',
//     description: 'This represents a Sensor',
//     fields: () => {
//       return {
//         id: {
//           type: GraphQLInt,
//           resolve (Sensor) {
//             return Sensor.id;
//           }
//         },
//         Indicator: {
//           type: GraphQLString,
//           resolve (Sensor) {
//             return Sensor.Indicator;
//           }
//         },
//         Value: {
//           type: GraphQLInt,
//           resolve (Sensor) {
//             return Sensor.Value;
//           }
//         },
//       };
//     }
//   });
  
//   const Query = new GraphQLObjectType({
//     name: 'Query',
//     description: 'Root query object',
//     fields: () => {
//       return {
//         sensors: {
//           type: new GraphQLList(Sensor),
//           args: {
//             id: {
//               type: GraphQLInt
//             },
//             Value: {
//               type: GraphQLInt
//             }
//           },
//           resolve (root, args) {
//             return Db.models.Sensor.findAll({ where: args });
//           }
//         },
//       };
//     }
//   });
  
// const Schema = new GraphQLSchema({
// query: Query
// });

// export default Schema;
