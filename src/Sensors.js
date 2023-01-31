import React, {useState} from 'react'
import { StatusBar } from 'expo-status-bar';
import { StyleSheet, Text, View } from 'react-native';
import { FontAwesomeIcon } from '@fortawesome/react-native-fontawesome'

export const Sensors = () => {
  return (
    <View style={styles.container}>
      <View style={styles.mini}>       
      <Text style={styles.baseText}>  Air pollution: </Text>
      <Text style={styles.baseText}>0</Text>
      <Text style={styles.baseText}> ppm</Text>
      </View>

      <View style={styles.mini}>
      <Text style={styles.baseText}>  Temperature: </Text>
      <Text style={styles.baseText}>0</Text>
      <Text style={styles.baseText}> C</Text>
      </View>

      <View style={styles.mini}>
      <Text style={styles.baseText}>  Humidity: </Text>
      <Text style={styles.baseText}>0</Text>
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