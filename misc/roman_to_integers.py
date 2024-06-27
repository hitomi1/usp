def roman_to_integer(roman):
    roman_values = {
        'I': 1,
        'V': 5,
        'X': 10,
        'L': 50,
        'C': 100,
        'D': 500,
        'M': 1000
    }

    total = 0

    for i in range(len(roman)):
        if i + 1 < len(roman) and roman_values[roman[i]] < roman_values[roman[i + 1]]:
            total -= roman_values[roman[i]]
        else:
            total += roman_values[roman[i]]

    return total

print(roman_to_integer(input('Digite um número romano: ')))     
