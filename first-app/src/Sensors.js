import React, {useState, useEffect} from 'react'
import { StatusBar } from 'expo-status-bar';
import { StyleSheet, Text, View } from 'react-native';
import { FontAwesomeIcon } from '@fortawesome/react-native-fontawesome'
import {useMutation, useQuery} from "@apollo/client";
import {GET_DATA} from "../query/sensor";

export const Sensors = () => {
  const {data: dataA, loading: loadingA} = useQuery(GET_DATA, {
    variables: {
        id: 1
    }
  });
  const {data: dataT, loading: loadingT} = useQuery(GET_DATA, {
    variables: {
        id: 2
    }
  });
  const {data: dataH, loading: loadingH} = useQuery(GET_DATA, {
    variables: {
        id: 3
    }
  });
  const [valueA, setValueA] = useState(0);
  const [valueT, setValueT] = useState(0);
  const [valueH, setValueH] = useState(0);

  useEffect(() => {
    if (!loadingA && dataA.getUser) {      
      setValueA(dataA.getUser.Value)
      console.log(valueA);
    } 
  });

  useEffect(() => {
    if (!loadingT && dataT.getUser) {      
      setValueT(dataT.getUser.Value)
      console.log(valueT);
    } 
  });

  useEffect(() => {
    if (!loadingH && dataH.getUser) {      
      setValueH(()=>dataH.getUser.Value)
      console.log(valueH);
    } 
  });

// useEffect(() => {
//   if (!loadingT) {
//     setValueT(dataT.getUser.Value)
    
//     console.log(valueT)
//   }
//   }, [dataT]);

//   useEffect(() => {
//     if (!loadingH) {
//       setValueH(dataH.getUser.Value)
      
//       console.log(valueH)
//     }
//     }, [dataH]);
// if (loadingA || loadingT || loadingH) {
//   return <h1>Loading...</h1>
// }
//console.log(dataA);
// console.log(dataT);
// console.log(dataH);
  return (
    <View style={styles.container}>
      <View style={styles.mini}>       
      <Text style={styles.baseText}>Air pollution: </Text>
      <Text style={styles.baseText}>{(!loadingA)?valueA:0}</Text>
      <Text style={styles.baseText}> ppm</Text>
      </View>

      <View style={styles.mini}>
      <Text style={styles.baseText}>Temperature: </Text>
      <Text style={styles.baseText}>{(!loadingT)?valueT:0}</Text>
      <Text style={styles.baseText}> C</Text>
      </View>

      <View style={styles.mini}>
      <Text style={styles.baseText}>Humidity: </Text>
      <Text style={styles.baseText}>{(!loadingH )?valueH:0}</Text>
      <Text style={styles.baseText}> %</Text>
      </View>
    </View> 
  );
}

const styles = StyleSheet.create({
  container: {
    height: '37.3%',
    flexDirection: 'column',
    backgroundColor: '#F5F0F0',
    alignItems: 'center',
    justifyContent: 'space-around',
  },
  mini: {
    flexDirection: 'row',
  },
  baseText: {
    fontSize: 20,    
  },
  awesome:{
    color: '#A07A7A',   
    // height: '1em', 
    fontSize: 30, 
  }
});