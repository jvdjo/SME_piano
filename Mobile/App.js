import React, { useState } from 'react';
import { View, Text, TouchableOpacity, StyleSheet, Alert } from 'react-native';

const MyComponent = () => {
  const [selectedNumber, setSelectedNumber] = useState(null);

  const handleNumberPress = (number) => {
    setSelectedNumber(number);
  };

  const handleSendRequest = async () => {
    if (selectedNumber) {
      try {
        const response = await fetch('https://sme-integracao.azurewebsites.net/frequencia', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
            'Access-Control-Allow-Origin': '*'
          },
          body: JSON.stringify({ frequenciaNota: selectedNumber }),
        });

        // Verifica o status da resposta
        if (response.ok) {
          Alert.alert('Sucesso', 'Solicitação enviada com sucesso!');
        } else {
          Alert.alert('Erro', 'Falha ao enviar a solicitação.');
        }
      } catch (error) {
        Alert.alert('Erro', 'Ocorreu um erro na solicitação.');
      }
    } else {
      Alert.alert('Erro', 'Selecione um número antes de enviar a solicitação.');
    }
  };

  return (
    <View style={styles.container}>
      <Text style={styles.title}>Selecione uma faixa de frequência:</Text>
      <View style={styles.numberContainer}>
        {[1, 2, 3, 4, 5, 6, 7].map((number) => (
          <TouchableOpacity
            key={number}
            style={[
              styles.numberButton,
              selectedNumber === number && styles.selectedNumberButton,
            ]}
            onPress={() => handleNumberPress(number)}
          >
            <Text
              style={[
                styles.numberButtonText,
                selectedNumber === number && styles.selectedNumberText,
              ]}
            >
              {number}
            </Text>
          </TouchableOpacity>
        ))}
      </View>
      <TouchableOpacity style={styles.sendButton} onPress={handleSendRequest}>
        <Text style={styles.sendButtonText}>Enviar</Text>
      </TouchableOpacity>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  title: {
    fontSize: 20,
    fontWeight: 'bold',
    marginBottom: 20,
  },
  numberContainer: {
    flexDirection: 'row',
    justifyContent: 'center',
    marginBottom: 20,
  },
  numberButton: {
    paddingHorizontal: 10,
    paddingVertical: 10,
    marginHorizontal: 5,
    borderRadius: 5,
    borderWidth: 1,
    borderColor: '#000',
    backgroundColor: '#fff',
  },
  selectedNumberButton: {
    backgroundColor: '#000',
  },
  numberButtonText: {
    fontSize: 18,
  },
  selectedNumberText: {
    color: '#fff',
  },
  sendButton: {
    backgroundColor: '#000',
    paddingHorizontal: 20,
    paddingVertical: 10,
    borderRadius: 5,
  },
  sendButtonText: {
    color: '#fff',
    fontSize: 18,
    fontWeight: 'bold',
  },
});

export default MyComponent; 