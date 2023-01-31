import React, { useState } from "react";
import { BIO } from './BIO'
import {
  SafeAreaView,
  StyleSheet,
  Text,
  View,
  Image,
  TextInput,
  Button,
  TouchableOpacity,
  Alert
} from "react-native";
import { StatusBar } from 'expo-status-bar'
import * as LocalAuthentication from 'expo-local-authentication'
import { clickProps } from "react-native-web/dist/cjs/modules/forwardedProps";

export const Start = (props) => {
    const [password, setPassword] = useState("");  
    const [click, setClick] = useState(true);
    const [clickForfot, setClickForfot] = useState(false);
    const [elementVisible, setElementVisible] = useState(false); 
    return (
      <View style={styles.container}>
        <View style={{justifyContent: 'center', alignItems: "center"}}>
          <Text style={{fontSize: 30}}>WELCOME HOME</Text>
          <Text style={{fontSize: 20}}>PLEASE, AUTORIZE</Text>
        </View> 
        <BIO/> 
        <StatusBar style="auto" />
        
        {elementVisible ? (
          <View style={styles.inlineBlock}>
            <TextInput
              //backgroundColor = 'white'
              placeholder="Password"
              placeholderTextColor="#003f5c"
              secureTextEntry={click}
              onChangeText={(password) => setPassword(password)}
            /> 
            <TouchableOpacity >
            <Button 
              onPress={() => setClick(!click)}
              style={styles.loginBtn} 
              title="eye" 
              color='#a66f6f' />
          </TouchableOpacity>
          </View>) : 
          (<React.Fragment style={styles.fragment}>
            <TouchableOpacity >
            <Button 
              onPress={() => setElementVisible(!elementVisible)} 
              style={styles.loginBtn} 
              title="Login with password" 
              color='#a66f6f'/>
            </TouchableOpacity>
            <TouchableOpacity>
            <Text style={styles.forgot_button}>Forgot Password?</Text> 
            </TouchableOpacity>  
          </React.Fragment>       
        ) }
         
        <TouchableOpacity >
          <Button 
            onPress={password == "123" ? props.onPress : 
              Alert.alert('WRONG PASSWORD', 'Try again', [
                {
                  text: 'OK',
                },
              ])
            } 
            style={styles.loginBtn} 
            title="GO TO DATA" 
            color='#a66f6f' />
        </TouchableOpacity> 
      </View> 
    );
  }
  const styles = StyleSheet.create({
    container: {
      flex: 1,
      flexDirection: 'column',
      backgroundColor: '#F5F0F0',
      alignItems: 'center',
      justifyContent: 'space-around', 
    },
    inputView: {
      backgroundColor: "#FFC0CB",
      borderRadius: 5,
      //width: "70%",
      //height: "5%",
      //marginBottom: 20,
      alignItems: "center",
    },
    TextInput: {
      //height: "20%",
      //flex: 1,
      // padding: 10,
      // marginLeft: 20,
    },
    forgot_button: {
      //height: "5%",
      //marginBottom: 30,
    },
    loginBtn: {
      //width: "10%",
      borderRadius: 5,
      alignItems: "center",
      justifyContent: "center",
      backgroundColor: "#a66f6f",
    },
    inlineBlock: {
      flexDirection: 'row',
      //height: '25%',
    },
    fragment: {
      alignItems: "center",
      justifyContent: "center",
    },
});




