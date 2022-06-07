/*
Имеется база сотрудников и номеров их телефонов. Требуется написать соответствующие структуры для хранения данных, и заполнить контейнер записями из базы. 
Затем необходимо реализовать методы обработки данных, а также вывести на экран всю необходимую информацию.

Важно! Имена переменным, классам и функциям давайте осознанные, состоящие из слов на английском языке.

1. Создайте структуру Person с 3 полями: фамилия, имя, отчество. Поле отчество должно быть опционального типа, т.к. не у всех людей есть отчество. 
Перегрузите оператор вывода данных для этой структуры. Также перегрузите операторы < и == (используйте tie).
2. Создайте структуру PhoneNumber с 4 полями:
· код страны (целое число)
· код города (целое число)
· номер (строка)
· добавочный номер (целое число, опциональный тип)
Для этой структуры перегрузите оператор вывода. 
Необходимо, чтобы номер телефона выводился в формате: +7(911)1234567 12, где 7 – это номер страны, 911 – номер города, 1234567 – номер, 
12 – добавочный номер. Если добавочного номера нет, то его выводить не надо. Также перегрузите операторы < и == (используйте tie)

3. Создайте класс PhoneBook, который будет в контейнере хранить пары: Человек – Номер телефона. 
Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла. 
В теле конструктора происходит считывание данных из файла и заполнение контейнера. 
Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.
В классе PhoneBook реализуйте метод SortByName, который должен сортировать элементы контейнера по фамилии людей в алфавитном порядке. 
Если фамилии будут одинаковыми, то сортировка должна выполняться по именам, если имена будут одинаковы, то сортировка производится по отчествам. 
Используйте алгоритмическую функцию sort.
Реализуйте метод SortByPhone, который должен сортировать элементы контейнера по номерам телефонов. Используйте алгоритмическую функцию sort.
Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает кортеж из строки и PhoneNumber. 
Строка должна быть пустой, если найден ровно один человек с заданном фамилией в списке. 
Если не найден ни один человек с заданной фамилией, то в строке должна быть запись «not found», если было найдено больше одного человека, 
то в строке должно быть «found more than 1».
Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер телефона и, если находит заданного человека в контейнере, 
то меняет его номер телефона на новый, иначе ничего не делает.
Функция main будет выглядеть так:
int main() {
этого
ifstream file("ХХХ"); // путь к файлу PhoneBook.txt PhoneBook book(file);
cout << book;
cout << "------SortByPhone-------" << endl;
book.SortByPhone();
cout << book;
cout << "------SortByName--------" << endl;
book.SortByName();
cout << book;
cout << "-----GetPhoneNumber-----" << endl;
// лямбда функция, которая принимает фамилию и выводит номер телефона
человека, либо строку с ошибкой
auto print_phone_number = [&book](const string& surname) {
cout << surname << "\t";
auto answer = book.GetPhoneNumber(surname);
if (get<0>(answer).empty())
cout << get<1>(answer);
else
cout << get<0>(answer);
cout << endl;
};
// вызовы лямбды
print_phone_number("Ivanov");
print_phone_number("Petrov");
cout << "----ChangePhoneNumber----" << endl;
book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
PhoneNumber{7, 123, "15344458", nullopt});
book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
PhoneNumber{ 16, 465, "9155448", 13 });
cout << book;
}
У вас должен получиться следующий вывод: (см. Методичка урока 1, стр. 28-29)
*/
#include <iostream>
#include <string>
#include <optional>
#include <iomanip>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>


//Task #1
struct Person
{
    Person(std::string Name, std::string Surname, std::string Patronymic) : a(Name), b(Surname), c(Patronymic) {}

    std::string a;
    std::string b;
    std::optional<std::string> c;

};
std::optional<std::string> getOptStr(std::string& s)
{
    if (s == "") {
        return std::nullopt;
    }
    return s;
}

std::ostream& operator<<(std::ostream& out, const Person& p)
{
    std::cout << std::setw(15) << p.a << std::setw(12) << p.b;

    if (p.c.has_value())
    {
        std::cout << std::setw(17) << p.c.value();
    }
    else
    {
        std::cout << std::setw(18);
    }

    return out;
}

bool operator<(const Person& p1, const Person& p2)
{

    return tie(p1.a, p1.b, p1.c) < tie(p2.a, p2.b, p2.c);
}

bool operator==(const Person& p1, const Person& p2)
{
    return tie(p1.a, p1.b, p1.c) == tie(p2.a, p2.b, p2.c);
}

//Task #2
struct PhoneNumber
{
    PhoneNumber (int CountryCode, int CityCode, std::string Number, int AddNumber) : cc(CountryCode), ccd(CityCode), n(Number), an(AddNumber) {}
    int cc;
    int ccd;
    std::string n;
    std::optional<int> an;
};
std::optional<int> getOptInt(std::string& i)
{
    if (i == "")
        return std::nullopt;

    return stoi(i);
}
bool operator<(const PhoneNumber& p1, const PhoneNumber& p2)
{
    return tie(p1.cc, p1.ccd, p1.n, p1.an) < tie(p2.cc, p2.ccd, p2.n, p2.an);
}

//Task #3  - не доделано :(
class PhoneBook
{
public:
    PhoneBook(std::ifstream& file) {

 
        if (file.is_open())
        {
            //std::cout << "file!" << std::endl;
            std::vector<std::string> rowData;
            

            for (std::string line; getline(file, line);)
            {
                std::stringstream str(line);
                std::vector<std::string> rowData;

                for (std::string s; getline(str, s, ';');)
                {
                    rowData.push_back(s);
                }

                std::pair<Person, PhoneNumber> entry ();

            }

            file.close();
        }
        else
        {
            std::cout << "Error. Can't open file!" << std::endl;
        }
        std::cin.get();

    }

    

    void SortByName()
    {
        std::sort(myData.begin(), myData.end(), [](const std::pair<Person, PhoneNumber>& person1, const std::pair<Person, PhoneNumber>& person2)
            {
                return person1.first < person2.first;
            });
    }
    void SortByPhone()
    {
        std::sort(myData.begin(), myData.end(), [](const std::pair<Person, PhoneNumber>& phone1, const std::pair<Person, PhoneNumber>& phone2)
            {
                return phone1.second < phone2.second;
            });
    }

    std::pair<std::string, std::vector<PhoneNumber>> GetPhoneNumber(const std::string& Name)
    {
        std::vector<PhoneNumber> phoneNumbers;
        int count = 0;

        std::for_each(myData.begin(), myData.end(), [&](const auto& entry)
            {
                if (entry.first.a == Name)
                {
                    phoneNumbers.push_back(entry.second);
                    ++count;
                }
            });

        switch (count)
        {
        case 0:
            return { "not found", phoneNumbers };
        case 1:
            return { "", phoneNumbers };
        default:
            return { "found more than 1", phoneNumbers };
        }
    }

    void ChangePhoneNumber(const Person& p, const PhoneNumber& pn)
    {
        auto entry = std::find_if(myData.begin(), myData.end(), [&](const auto& entry)
            {
                return entry.first == p;
            });

        if (entry != myData.end())
        {
            entry->second = pn;
        }
    }

protected:

    std::vector<std::pair<Person, PhoneNumber>> myData;
    
};




int main()
{
    std::ifstream file("D:\\GeekBrains\\Semester1\\Diff\\homework\\HomeworkDifficultMoments1\\PhoneBook.txt");
    PhoneBook book (file);
    //std::cout <<book<< std::endl;
    std::cout << "------SortByPhone-------" << std::endl;
    book.SortByPhone();
    //std::cout << book;
    std::cout << "------SortByName--------" << std::endl;
    book.SortByName();
    //std::cout << book;
    std::cout << "-----GetPhoneNumber-----" << std::endl;
    /*   auto print_phone_number = [&book](const std::string& surname) {
            std::cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            std::cout << get<1>(answer);
        else
            std::cout << get<0>(answer);
        std::cout << std::endl;
    }; 
    //вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");*/
    std::cout << "----ChangePhoneNumber----" << std::endl;
   /* book.ChangePhoneNumber(Person{"Kotov", "Vasilii", "Eliseevich"},
        PhoneNumber{ 7, 123, "15344458", std::nullopt });*/
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
        PhoneNumber{ 16, 465, "9155448", 13 });
    //std::cout << book;
}

