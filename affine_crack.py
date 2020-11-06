fstd = [0.082, 0.015, 0.028, 0.043,
        0.127, 0.022, 0.020, 0.061, 0.070, 0.002,
        0.008, 0.040, 0.024, 0.067, 0.075, 0.019,
        0.001, 0.060, 0.063, 0.090, 0.028, 0.010,
        0.023, 0.001, 0.020, 0.001]
alist = [1,3,5,7,9,11,15,17,19,21,23,25]
blist = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]
letter = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
            'v', 'w', 'x', 'y', 'z']
letter_num = {}

def CalDist(cipher_freq):
    sum = 0
    for i in range(0,26):
        j = letter[i]
        sum += (cipher_freq[j] - standard_feq[j]) * (cipher_freq[j] - standard_feq[j])
    return sum

def Inverse(a):
    for i in range(0,26):
        if((i*a) % 26 == 1):
            return i

def Decryption(a,b,ciphertext):
    plaintext = []
    a_inverse = Inverse(a)
    for i in range(0,len(ciphertext)):
        temp_text = ""
        for j in range(0,len(ciphertext[i])):
            c = ciphertext[i][j]
            if(c.islower()):
                k = letter_num[c]
                m = a_inverse * (k - b + 26) % 26
                temp_text = temp_text + letter[m]
            else:
                temp_text = temp_text + c
        plaintext.append(temp_text)
    return plaintext

def CalFreq(text):
    plain_freq = {}
    cipher_lenth = 0
    for i in letter:
        plain_freq[i] = 0
    for i in range(0,len(text)):
        cipher_lenth = cipher_lenth + len(text[i])
        for j in range(0,len(text[i])):
            k = text[i][j]
            if(k.islower()):
                plain_freq[k] = plain_freq[k] + 1
    for i in letter:
        plain_freq[i] = plain_freq[i] / cipher_lenth
    return plain_freq
def Func(x):
    return x[2]

if __name__ == "__main__":
    ciphertext = []
    standard_feq = {}
    cipher_dist = {}
    cipher_lenth = 0
    a_crack = 0
    b_crack = 0
    min_dist = 10000 
    dist = []
    n = input("Please input the text number:")
    n = int(n)
    plaintext = ""
    for i in range(0,26):
        standard_feq[letter[i]] = fstd[i]
        # cipher_freq[letter[i]] = 0
        letter_num[letter[i]] = i

    for i in range(0,n):
        print("Please input the text ",i+1)
        ciphertext.append(input())
    for a in alist:
        for b in blist:
            temp_text = Decryption(a,b,ciphertext)
            temp_freq = CalFreq(temp_text)
            temp_dist = CalDist(temp_freq)
            dist.append([a,b,temp_dist])
            if(min_dist > temp_dist):
                min_dist = temp_dist
                a_crack = a
                b_crack = b
    dist.sort(key = Func,reverse = False)
    print("Now print the top 10")
    for i in range(0,10):
        print(dist[i])
    plaintext = Decryption(a_crack,b_crack,ciphertext)
    for i in plaintext:
        print("---------- plain text ----------")
        print(i)
    # print(plaintext)
    print(a_crack,b_crack)

    
