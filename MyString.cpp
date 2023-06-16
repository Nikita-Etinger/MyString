#include <iostream>
#include<string>
using namespace std;

class MyString {
private:
    char* data;
    int length;

public:
    MyString(const char* str = "") {
        length = stringLength(str);
        data = new char[length + 1];
        stringCopy(data, str);
    }

    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        stringCopy(data, other.data);
    }

    ~MyString() {
        delete[] data;
    }

    char& operator[](int index) {
        return data[index];
    }

    bool operator<(MyString& other) {
        return stringCompare(data, other.data) < 0;
    }

    bool operator==(MyString& other){
        return stringCompare(data, other.data) == 0;
    }

    bool empty() const {
        return (length == 0 ? 1 : 0);
    }

    int size() const {
        return length;
    }

    void clear() {
        delete[] data;
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }

    void insert(int pos, const char* str) {
        int strLength = stringLength(str);
        char* newData = new char[length + strLength + 1];

        stringCopy(newData, data, pos);
        stringCopy(newData + pos, str);
        stringCopy(newData + pos + strLength, data + pos);

        delete[] data;
        data = newData;
        length += strLength;
    }

    void push(char ch) {
        char* newData = new char[length + 2];
        stringCopy(newData, data);
        newData[length] = ch;
        newData[length + 1] = '\0';

        delete[] data;
        data = newData;
        length++;
    }

    void pop() {
        if (length > 0) {
            data[length - 1] = '\0';
            length--;
        }
    }

    int stoi() const {
        int result = 0;
        int sign = 1;
        int i = 0;

        if (data[0] == '-') {
            sign = -1;
            i = 1;
        }

        while (data[i] != '\0') {
            if (data[i] >= '0' && data[i] <= '9') {
                result = result * 10 + (data[i] - '0');
                i++;
            }
            else {
                break;
            }
        }

        return result * sign;
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            stringCopy(data, other.data);
        }
        return *this;
    }

    friend ostream& operator<<( ostream& os, const MyString& str) {
        os << str.data;
        return os;
    }

    int stringLength(const char* str) {
        int length = 0;
        while (str[length] != '\0') {
            length++;
        }
        return length;
    }

    void stringCopy(char* dest, const char* sour, int start = 0) {
        int i = 0;
        while (sour[start + i] != '\0') {
            dest[i] = sour[start + i];
            i++;
        }
        dest[i] = '\0';
    }

    int stringCompare(const char* str1, const char* str2) {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0') {
            if (str1[i] < str2[i]) {
                return -1;
            }
            else if (str1[i] > str2[i]) {
                return 1;
            }
            i++;
        }

        if (str1[i] == '\0' && str2[i] == '\0') {
            return 0;
        }
        else if (str1[i] == '\0') {
            return -1;
        }
        else {
            return 1;
        }
    }
    bool operator<(const MyString& other){
        return stringCompare(data, other.data) < 0;
    }
};



int main() {
     locale::global( locale(""));

    MyString myStr = "Привет";
     string stdStr = "Привет";

     cout << "MyString: " << myStr <<  endl;
     cout << " string: " << stdStr <<  endl;
     cout <<  endl;

     cout << "myStr[0]: " << myStr[0] <<  endl;
     cout << "stdStr[0]: " << stdStr[0] <<  endl;
     cout <<  endl;

    if (myStr < MyString("Мир")) {
         cout << "myStr меньше, чем \"Мир\"" <<  endl;
    }
    else {
         cout << "myStr не меньше, чем \"Мир\"" <<  endl;
    }

    if (stdStr <  string("Мир")) {
         cout << "stdStr меньше, чем \"Мир\"" <<  endl;
    }
    else {
         cout << "stdStr не меньше, чем \"Мир\"" <<  endl;
    }
     cout <<  endl;

    MyString myStr2 = myStr;
     string stdStr2 = stdStr;

     cout << "myStr2 после присваивания: " << myStr2 <<  endl;
     cout << "stdStr2 после присваивания: " << stdStr2 <<  endl;
     cout <<  endl;

    myStr.clear();
    myStr.insert(0, "12345");

    stdStr.clear();
    stdStr.insert(0, "12345");

     cout << "myStr stoi: " << myStr.stoi() <<  endl;
     cout << "stdStr stoi: " <<  stoi(stdStr) <<  endl;
     cout <<  endl;

     cout << "myStr пустая: " << (myStr.empty() ? "да" : "нет") <<  endl;
     cout << "stdStr пустая: " << (stdStr.empty() ? "да" : "нет") <<  endl;

     cout << "Размер myStr: " << myStr.size() <<  endl;
     cout << "Размер stdStr: " << stdStr.size() <<  endl;
     cout <<  endl;

    myStr.clear();
    stdStr.clear();

    myStr.insert(0, "Привет");
    stdStr.insert(0, "Привет");

    myStr.push('!');
    stdStr.push_back('!');

     cout << "myStr после insert(0, \"Привет\") и функции push(!): " << myStr <<  endl;
     cout << "myStr после insert(0, \"Привет\") и функции push(!): " << stdStr <<  endl;
     cout <<  endl;

    return 0;
}