# John Heath
# CS2 Warmup Problem


def calculate_freq(s):
    freq_dict = {} # A dictionary that holds each letter and the number 
                   # of times it appears.
    for char in s:
        if char not in freq_dict:
            freq_dict.update({char : 1.0})
        else:
            freq_dict[char] += 1.0
    freqs = [] # Array that will hold frequencies
    length = len(s)
    for char in s:
        freqs.append(freq_dict[char]/length)
    return freqs
        






if __name__ == "__main__": # Asks user for input string if program is
                           # run alone.
    s = raw_input("Enter a string: ").lower()
    print(calculate_freq(s))
