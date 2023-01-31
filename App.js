import React, {useState} from 'react'
import {NavigationContainer} from '@react-navigation/native';
import { Button, StyleSheet, Text, View } from 'react-native'
import { Sensors } from './src/Sensors'
import { Switchers } from './src/Switchers'
import { Start } from './src/Start'
import { library } from '@fortawesome/fontawesome-svg-core'
import { fab } from '@fortawesome/free-brands-svg-icons'
import {
  faCloud, faWater, faThermometerHalf, faFire, faLightbulb, faDoorOpen
} from "@fortawesome/free-solid-svg-icons";
import * as LocalAuthentication from 'expo-local-authentication'
import {createNativeStackNavigator} from '@react-navigation/native-stack';
import { StatusBar } from 'expo-status-bar';

library.add(fab, faCloud, faWater, faThermometerHalf, faFire, faLightbulb, faDoorOpen)

const Stack = createNativeStackNavigator();

export default function App() {
  // const [isLogin, setLogin] = useState(false);
  // const checkLogin = () => {
  //   setLogin(true)
  // }
    return(
      <NavigationContainer>
      <Stack.Navigator>
        <Stack.Screen 
          name="Home" 
          component={HomeScreen}
          options={{title: 'Control app'}}
        />
        <Stack.Screen 
          name="Profile" 
          component={ProfileScreen} 
          options={{title: 'Control app'}}
        />
      </Stack.Navigator>
    </NavigationContainer>    
    ); 
}

const HomeScreen = ({navigation}) => {
  const goToData = () =>
    navigation.navigate('Profile');

  return (
    <View style={styles.container}>   
    <Start onPress={goToData}/> 
    <StatusBar style="auto"/>  
    </View>
  );
};

const ProfileScreen = ({navigation}) => {
  return (
    <View style={styles.container}> 
      <View style={{height: '15%', justifyContent: 'center',}}><Text style={styles.baseText}>ESP32 HOUSE CONTROL</Text></View> 
      <View style={styles.bottom} />
      <Sensors/>
      <View style={styles.bottom} />
      <Switchers/>    
      <Button
        color='#a66f6f'
        title="Go to Home"
        onPress={() => navigation.navigate('Home')}
      />   
      {/* <Button title="Go back" onPress={() => navigation.goBack()} /> */}
      {/* <Text>This is page with {route.params.data}</Text>   */}   
    </View>);
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    flexDirection: 'column',
    backgroundColor: '#F5F0F0',
    alignItems: 'center',
    justifyContent: 'space-around', 
     
  },
  baseText: {
    fontSize: 25,
    fontWeight: 'bold',
  },
  bottom: {
    borderStartWidth: 300,
  },
  button: {
    //width: "10%",
    borderRadius: 5,
    alignItems: "center",
    justifyContent: "center",
    backgroundColor: "#a66f6f",
  },
});
