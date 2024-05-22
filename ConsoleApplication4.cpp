#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// функция для вычисления четности
bool calculateParity(const vector<int>& codeword, const vector<int>& parityIndices) {
    bool parity = false;
    for (int index : parityIndices) {
        parity ^= codeword[index];
    }
    return parity;
}

vector<int> encode(const vector<int>& message) {
    vector<int> encodedWord(15, false);

    // тут биты с инфой
    encodedWord[2] = message[0];
    encodedWord[4] = message[1];
    encodedWord[5] = message[2];
    encodedWord[6] = message[3];
    encodedWord[8] = message[4];
    encodedWord[9] = message[5];
    encodedWord[10] = message[6];
    encodedWord[11] = message[7];
    encodedWord[12] = message[8];
    encodedWord[13] = message[9];
    encodedWord[14] = message[10];

    // тут биты проверки
    encodedWord[0] = calculateParity(encodedWord, { 2, 4, 6, 8, 10, 12, 14 });
    encodedWord[1] = calculateParity(encodedWord, { 2, 5, 6, 9, 10, 13, 14 });
    encodedWord[3] = calculateParity(encodedWord, { 4, 5, 6, 11, 12, 13, 14 });
    encodedWord[7] = calculateParity(encodedWord, { 8, 9, 10, 11, 12, 13, 14 });

    return encodedWord;
}

vector<int> decode(vector<int>& encodedWord) {
    vector<int> decodedMessage(11, false);
    vector<int> syndrome(4, false);

    // вычисляем синдром(не дауна :| )
    syndrome[0] = calculateParity(encodedWord, { 0, 2, 4, 6, 8, 10, 12, 14 });
    syndrome[1] = calculateParity(encodedWord, { 1, 2, 5, 6, 9, 10, 13, 14 });
    syndrome[2] = calculateParity(encodedWord, { 3, 4, 5, 6, 11, 12, 13, 14 });
    syndrome[3] = calculateParity(encodedWord, { 7, 8, 9, 10, 11, 12, 13, 14 });

    // проверка на наличие ошибки
    if (!(syndrome[0] || syndrome[1] || syndrome[2] || syndrome[3])) {
        cout << "Ошибки нет" << endl;
    }
    else {
        // определение позиции ошибки
        int errorPosition = 0;
        for (int i = 3; i >= 0; --i) {
            if (syndrome[i]) {
                errorPosition |= 1;
            }
            if (i > 0) {
                errorPosition <<= 1;
            }
        }
        // исправление ошибки (инвертирование бита)
        encodedWord[errorPosition - 1] = !encodedWord[errorPosition - 1];
    }

    // аборт битов с инфой
    decodedMessage[0] = encodedWord[2];
    decodedMessage[1] = encodedWord[4];
    decodedMessage[2] = encodedWord[5];
    decodedMessage[3] = encodedWord[6];
    decodedMessage[4] = encodedWord[8];
    decodedMessage[5] = encodedWord[9];
    decodedMessage[6] = encodedWord[10];
    decodedMessage[7] = encodedWord[11];
    decodedMessage[8] = encodedWord[12];
    decodedMessage[9] = encodedWord[13];
    decodedMessage[10] = encodedWord[14];

    return decodedMessage;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<int> message(11);
    vector<int> encodedWord;
    int errorIndex;
    vector<int> decodedMessage;
    int choice;
    do {
        cout << "Что хотите узнать?" << endl;
        cout << "1: Исходное сообщение" << endl; 
        cout << "2: Кодирование сообщения" << endl; 
        cout << "3: Добавление ошибки" << endl; 
        cout << "4: Декодирование сообщения" << endl; 
        cout << "0: Выход" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            srand(time(0));
            for (int i = 0; i < 11; ++i) {
                message[i] = rand() % 2;
            }
            cout << "Исходное сообщение: ";
            for (int bit : message) {
                cout << bit;
            }
            cout << endl;
            break;
        case 2:
            encodedWord = encode(message);
            cout << "Закодированное сообщение: ";
            for (int bit : encodedWord) {
                cout << bit;
            }
            cout << endl;
            break;
        case 3:
            errorIndex = rand() % 15;
            encodedWord[errorIndex] = !encodedWord[errorIndex];
            cout << "Закодированное сообщение с ошибкой: ";
            for (int bit : encodedWord) {
                cout << bit;
            }
            cout << endl;
            cout << "Позиция ошибки - число номер " << errorIndex + 1 << "\n";
            cout << endl;
            break;
        case 4:
            decodedMessage = decode(encodedWord);
            cout << "Декодированное сообщение: ";
            for (int bit : decodedMessage) {
                cout << bit;
            }
            cout << endl;
            break;
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Ошибочка." << endl;
        }
    } while (choice != 0);

    return 0;
}