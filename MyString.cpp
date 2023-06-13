#include <iostream>
#include <string>
using namespace std;

class MyString {
private:
    char* arrayStr = nullptr;
    int lengthSize = 0;
    int maxSize = 10;
    int countSymbol(const char array2[]) {
        int counter = 0;
        for (int i = 0; array2[i] != '\0'; i++) {
            counter++;
        }
        return counter;
    }

    int getMinLength(const char str1[], const char str2[]) {
        int length1 = countSymbol(str1);
        int length2 = countSymbol(str2);
        return (length1 < length2) ? length1 : length2;
    }

public:
    MyString() {
        arrayStr = new char[maxSize + 1]();
        arrayStr[maxSize] = '\0';
    }

    MyString(const char array2[]) : MyString() {
        int length = countSymbol(array2);
        if (length > maxSize) {
            delete[] arrayStr;
            arrayStr = new char[length + 1];
            maxSize = length;
        }
        lengthSize = length;
        for (int i = 0; i < length; i++) {
            arrayStr[i] = array2[i];
        }
        arrayStr[length] = '\0';
    }

    ~MyString() {
        cout << this<<endl;
        if (arrayStr != nullptr) delete[] arrayStr;
    }

    char* operator+(const char str[]) {
        int strLength = countSymbol(str);
        int newLength = lengthSize + strLength;

        char* newArrayStr = new char[newLength + 1];
        for (int i = 0; i < lengthSize; i++) {
            newArrayStr[i] = arrayStr[i];
        }
        for (int i = lengthSize, k = 0; i < newLength; i++, k++) {
            newArrayStr[i] = str[k];
        }
        newArrayStr[newLength] = '\0';



        return newArrayStr;
    }

    char* operator+(const MyString& other){
        int strLength = other.lengthSize;
        int newLength = lengthSize + strLength;

        char* newArrayStr = new char[newLength + 1];
        for (int i = 0; i < lengthSize; i++) {
            newArrayStr[i] = arrayStr[i];
        }
        for (int i = lengthSize, k = 0; i < newLength; i++, k++) {
            newArrayStr[i] = other.arrayStr[k];
        }
        newArrayStr[newLength] = '\0';


        return newArrayStr;
    }


    MyString& operator=(const MyString& other) {
        if (this != &other) {
            lengthSize = other.lengthSize;
            if (lengthSize > maxSize) {
                delete[] arrayStr;
                arrayStr = new char[lengthSize];
                maxSize = lengthSize;
            }
            for (int i = 0; i < lengthSize; i++) {
                arrayStr[i] = other.arrayStr[i];
            }
        }
        return *this;
    }


    MyString& operator=(const char str[]) {
        lengthSize = countSymbol(str);
        if (lengthSize > maxSize) {
            delete[] arrayStr;
            arrayStr = new char[lengthSize];
            maxSize = lengthSize;
        }
        for (int i = 0; i < lengthSize; i++) {
            arrayStr[i] = str[i];
        }
        arrayStr[lengthSize] = '\0';
        return *this;
    }
    void operator+=(const char array2[]) {
        int size = countSymbol(array2);
        int newLength = lengthSize + size;
        char* newArrayStr = new char[newLength+1]();
        for (int i = 0; i < lengthSize; i++) {
            newArrayStr[i] = arrayStr[i];
        }
        for (int i = lengthSize, k = 0; i < newLength; i++, k++) {
            newArrayStr[i] = array2[k];
        }
        newArrayStr[newLength] = '\0';

        delete[] arrayStr;
        arrayStr = newArrayStr;
        lengthSize = newLength;
    }



    void show() {
        for (int i = 0; i < lengthSize; i++) {
            cout << arrayStr[i];
        }
    }

    int length() {
        return lengthSize;
    }

    char& operator[](int index) {
        return arrayStr[index];
    }

    bool operator==(MyString& other) {
        if (other.length() != lengthSize) return false;
        for (int i = 0; i < lengthSize; i++) {
            if (other[i] != arrayStr[i]) return false;
        }
        return true;
    }

    bool operator==(const char other[]) {
        int sizeOther = countSymbol(other);
        if (sizeOther != lengthSize) return false;
        for (int i = 0; i < lengthSize; i++) {
            if (other[i] != arrayStr[i]) return false;
        }
        return true;
    }

    bool operator<(MyString& other) {
        int minLength = getMinLength(arrayStr, other.arrayStr);
        for (int i = 0; i < minLength; i++) {
            if (arrayStr[i] < other.arrayStr[i]) {
                return true;
            }
            else if (arrayStr[i] > other.arrayStr[i]) {
                return false;
            }
        }
        return lengthSize < other.lengthSize;
    }

    bool operator<(const char other[]) {
        int minLength = getMinLength(arrayStr, other);
        for (int i = 0; i < minLength; i++) {
            if (arrayStr[i] < other[i]) {
                return true;
            }
            else if (arrayStr[i] > other[i]) {
                return false;
            }
        }
        return lengthSize < countSymbol(other);
    }

    bool operator<=(MyString& other) {
        return (*this == other) || (*this < other);
    }

    bool operator>=(MyString& other) {
        return (*this == other) || (*this > other);
    }

    bool operator<=(const char other[]) {
        return (*this == other) || (*this < other);
    }

    bool operator>=(const char other[]) {
        return (*this == other) || (*this > other);
    }

    bool operator>(MyString& other) {
        return !(*this <= other);
    }

    bool operator>(const char other[]) {
        return !(*this <= other);
    }
    friend  ostream& operator<<( ostream& os, const MyString& myString) {
        for (int i = 0; i < myString.lengthSize; i++) {
            os << myString.arrayStr[i];
        }
        return os;
    }
    bool empty(){
        if (lengthSize == 0)return 1;
        return 0;
    }

    int size() {
        return lengthSize;
    }

    void clear() {
        
        lengthSize = 0;
        /*arrayStr[maxSize] = '\0';*/
    }


    void insert(int index, const char str[]) {
        int strLength = countSymbol(str);
        int newLength = lengthSize + strLength;

        // Проверяем, требуется ли изменение размера
        if (newLength >= maxSize) {
            int newMaxSize = max(maxSize * 2, newLength + 1);
            char* newArrayStr = new char[newMaxSize];
            for (int i = 0; i < index; i++) {
                newArrayStr[i] = arrayStr[i];
            }
            for (int i = index; i < lengthSize +1; i++) {
                newArrayStr[i + strLength] = arrayStr[i];
            }
            
            delete[] arrayStr;
            arrayStr = newArrayStr;
            maxSize = newMaxSize;
        }
        else {
            // Сдвигаем существующие элементы вправо
            if (lengthSize != 0) {
                for (int i = lengthSize; i >= index; i--) {
                    arrayStr[i + strLength] = arrayStr[i];
                }
            }
        }

        // Вставляем новую строку
        for (int i = 0; i < strLength; i++) {
            arrayStr[index + i] = str[i];
        }

        lengthSize = newLength;
        maxSize = newLength;
        arrayStr[newLength+1] = '\0';
    }

    void push(const char ch) {
        if (lengthSize >= maxSize) {
            char* newArrayStr = new char[maxSize+1];

            for (int i = 0; i < lengthSize+1; i++) {
                newArrayStr[i] = arrayStr[i];
            }

            delete[] arrayStr;
            arrayStr = newArrayStr;
        }

        arrayStr[lengthSize] = ch;
        lengthSize++;
        arrayStr[lengthSize] = '\0';
        maxSize = lengthSize;
    }

    void pop() {
        if (lengthSize > 0) {
            lengthSize--;
        }
    }
    //специально для стринга 

    bool operator==(string& other) {
        if (lengthSize != other.size()) {
            return false;
        }
        for (int i = 0; i < lengthSize; i++) {
            if (arrayStr[i] != other[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=( string& other) {
        return !(*this == other);
    }

    bool operator<(string& other) {
        //c_str() получение ссылки на массив char объекта string 
        int minLength = getMinLength(arrayStr, other.c_str());
        for (int i = 0; i < minLength; i++) {
            if (arrayStr[i] < other[i]) {
                return true;
            }
            else if (arrayStr[i] > other[i]) {
                return false;
            }
        }
        return lengthSize < other.size();
    }

    bool operator<=(string& other) {
        return (*this == other) || (*this < other);
    }

    bool operator>(string& other) {
        return !(*this <= other);
    }

    bool operator>=(string& other) {
        return (*this == other) || (*this > other);
    }
    int stoi() {
        int num = 0;
        int index = 0;
        int k = 1;
        if (arrayStr[0] == '-') {
            k = -1;
            index = 1;
        }

        for (int i = index; i < lengthSize; i++) {
            num = num * 10 + arrayStr[i] - '0';
        }
        num *= k;
        return num;
    }
    void showAdress() {
        cout << this << endl;
    }
    void deletes() {
        delete[]arrayStr;
    }

};

int main() {
    setlocale(LC_ALL, "ru");

    // Конструкторы и оператор присваивания
    MyString myStr("Привет");

     string stdStr("Привет");

    // Оператор +=
    myStr += " Мир!";
    stdStr += " Мир!";
    //myStr.deleteAr();//ошибка удаления массива 

    // Оператор +
    MyString myStrConcat = (myStr + " Добро пожаловать!");
    string stdStrConcat = stdStr + " Добро пожаловать!";

    cout << "MyString: " << myStr << endl;
    cout << "string  : " << stdStr << endl;
    

    


    myStr.clear();
    myStr = "1234";
    stdStr.clear();
    stdStr = "1234";
    int myStrInt = myStr.stoi();
    int stdStrInt =  stoi(stdStr);
    bool isStoiTestEqual=(myStrInt==stdStrInt?1:0);
    // Оператор []

    
    myStr.pop();
    stdStr.pop_back();



    MyString insertMyStr = myStr;
    string insertStdStr = stdStr;
    insertMyStr.insert(2, "Boba");
    insertStdStr.insert(2, "Boba");
    char myStrChar = insertMyStr[0];
    char stdStrChar = insertStdStr[0];
    

    

    
    // Операторы сравнения

    bool isEqual = (insertMyStr == insertStdStr);
    bool isNotEqual = (insertMyStr != insertStdStr);
    bool isGreater = (insertMyStr > insertStdStr);
    bool isLess = (insertMyStr < insertStdStr);
    bool isGreaterOrEqual = (insertMyStr >= insertStdStr);
    bool isLessOrEqual = (insertMyStr <= insertStdStr);

    bool isMyStrEmpty = insertMyStr.empty();
    bool isStdStrEmpty = insertStdStr.empty();
    int myStrSize = insertMyStr.size();
    int stdStrSize = insertStdStr.size();
    
    cout << "MyStr";
    myStr.showAdress();
    cout << "insertMyStr";
    insertMyStr.showAdress();
    cout << "myStrConCat";
    myStrConcat.showAdress();
    
     cout<<"Stoi test  : "<< (isStoiTestEqual?  "Успех" : "Провал") << endl;
     cout << "MyString после конкатенации: " << myStrConcat <<  endl;
     cout << "string после конкатенации  : " << stdStrConcat <<  endl;
     cout << "Сравнение MyString и string:" <<  endl;
     cout << "   - Оператор ==: " << (isEqual ? "Успех" : "Провал") <<  endl;
     cout << "   - Оператор !=: " << (isNotEqual ? "Успех" : "Провал") <<  endl;
     cout << "   - Оператор > : " << (isGreater ? "Успех" : "Провал") <<  endl;
     cout << "   - Оператор < : " << (isLess ? "Успех" : "Провал") <<  endl;
     cout << "   - Оператор >=: " << (isGreaterOrEqual ? "Успех" : "Провал") <<  endl;
     cout << "   - Оператор <=: " << (isLessOrEqual ? "Успех" : "Провал") <<  endl;
     cout << "MyString после добавления Boba во вторую позицию: " << insertMyStr << endl;
     cout << "string осле добавления Boba во вторую позицию:  : " << insertStdStr << endl;
     cout << "Первый символ MyString: " << myStrChar << endl;
     cout << "Первый символ string  : " << stdStrChar << endl;

     insertMyStr.push('!');
     insertStdStr.push_back('!');
     cout << "MyString после добавления в конец !: " << insertMyStr << endl;
     cout << "string после добавления в конец !  : " << insertStdStr << endl;
     myStr.clear();


     stdStr.clear();
     
     cout << "MyString после очистки: " << myStr <<  endl;
     cout << "string после очистки  : " << stdStr <<  endl;
     cout << "Длина MyString: " << myStrSize <<  endl;
     cout << "Длина string  : " << stdStrSize <<  endl;
     cout << "MyString пустой? " << (isMyStrEmpty ? "Да" : "Нет") <<  endl;
     cout << "string пустой?   " << (isStdStrEmpty ? "Да" : "Нет") <<  endl;

    return 0;
}
//constructor 
//destructor 
//constructor copy 
//operator = 
//operator != 
//operator += 
//operator + 
//operator > 
//operator < 
//operator >= 
//operator <= 
//stoi ok
//operator[] 
//empty
//size
//clear
//insert
//push
//pop
//
