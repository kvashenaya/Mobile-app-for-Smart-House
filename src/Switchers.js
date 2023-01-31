import React, {useState} from 'react'
import { StatusBar } from 'expo-status-bar';
import { StyleSheet, Text, View, Switch, Alert } from 'react-native';
import { FontAwesomeIcon } from '@fortawesome/react-native-fontawesome'

export const Switchers = () => {
  const [isEnabled1, setIsEnabled1] = useState(false);
  const [isEnabled2, setIsEnabled2] = useState(false);
  const [isEnabled3, setIsEnabled3] = useState(false);

  const toggleSwitch1 = () => setIsEnabled1(previousState1 => {
    if(!isEnabled1){
      Alert.alert('CONFIRMATION', 'Activate the fire fighting system?', [
        {
          text: 'NO',
          onPress: () => previousState1,
          style: 'cancel',
        },
        {text: 'YES', onPress: () => !previousState1},
      ]);
    }
  });
  const toggleSwitch2 = () => setIsEnabled2(previousState2 => !previousState2);
  const toggleSwitch3 = () => setIsEnabled3(previousState3 => !previousState3);
  return (
    <View style={styles.container}>

      <View style={styles.mini}>
      <Text style={styles.baseText}>  Lighting  </Text>
      <Switch
        style={styles.switch}
        trackColor={{false: '#BDBDBD', true: '#A07A7A'}}
        thumbColor={isEnabled2 ? '#f5dd4b' : 'white'}
        ios_backgroundColor="#3e3e3e"
        onValueChange={toggleSwitch2}
        value={isEnabled2}
      />
      </View>

      <View style={styles.mini}>
      
      <Text style={styles.baseText}>  Door  </Text>
      <Switch 
        style={styles.switch}
        trackColor={{false: '#BDBDBD', true: '#A07A7A'}}
        thumbColor={isEnabled3 ? '#f5dd4b' : 'white'}
        ios_backgroundColor="#3e3e3e"
        onValueChange={toggleSwitch3}
        value={isEnabled3}
      />
      </View>

      <View style={styles.mini}>
      <Text style={[styles.baseText, {color: '#CD1F1F'}]}>  Fire in the house!  </Text>
      <Switch
        style={styles.switch}
        trackColor={{false: '#BDBDBD', true: '#CD1F1F'}}
        thumbColor={isEnabled1 ? '#949494' : '#CD1F1F'}
        ios_backgroundColor="#3e3e3e"
        onValueChange={toggleSwitch1}
        value={isEnabled1}
      />
      </View>

    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flexDirection: 'column',
    height: '37.3%',
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
  },
  switch: {
    //height: '1 em', 
    fontSize: 25, 
  }
});