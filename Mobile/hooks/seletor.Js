import React, { useState } from 'react';
import { View, Text, TouchableOpacity, StyleSheet } from 'react-native';

const NumberSelector = () => {
  const [selectedNumber, setSelectedNumber] = useState(null);

  const handleNumberPress = (number) => {
    setSelectedNumber(number);
  };

  return (
    <View style={styles.container}>
      <Text style={styles.title}>Selecione um número:</Text>
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
      {selectedNumber && (
        <Text style={styles.selectedNumber}>
          Você selecionou o número: {selectedNumber}
        </Text>
      )}
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
    paddingHorizontal: 20,
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
  selectedNumber: {
    fontSize: 16,
  },
});

export {NumberSelector};
