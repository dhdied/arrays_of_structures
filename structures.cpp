#include <iostream>
using namespace std;

enum mountainType
{
    VOLCANIC,
    FOLDED,
    PLATEAU,
    OTHER
};

struct Location
{
    string country;
};

struct Mountain
{
    string name;
    int height;
    Location location;
    mountainType type;

    void showInfo() const
    {
        cout << "Название горной вершины: " << name << endl;
        cout << "Высота горной вершины (м): " << height << endl;
        cout << "Страна местонахождения горной вершины: " << location.country << endl;
        string normalType[] = {"Вулканическая", "Складчатая", "Платообразная", "Другая"};
        cout << "Тип горной вершины: " << normalType[type] << endl
             << endl;
    }
};

void printMountainInfo(const Mountain (&m)[20])
{
    for (int i = 0; i < 20; i++)
    {
        cout << "Информация о вершине №" << (i + 1) << endl;
        m[i].showInfo();
    }
}

double searchAverageHeight(const Mountain (&m)[20])
{
    int sum = 0;
    for (int i = 0; i < 20; i++)
    {
        sum += m[i].height;
    }

    double result = sum / (double)20;

    return result;
}

void sortByHeight(Mountain (&m)[20], void (*show)(const Mountain (&)[20]))
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19 - i; j++)
        {
            if (m[j].height > m[j + 1].height)
            {
                Mountain current = m[j];
                m[j] = m[j + 1];
                m[j + 1] = current;
            }
        }
    }

    show(m);
}

void searchEightthousandth(const Mountain (&m)[20])
{
    cout << "!Данные по странам о восьмитысячниках!" << endl;
    for (int i = 19; i > 16; i--)
    {
        if (m[i].height >= 8000)
        {
            cout << "Горная вершина " << m[i].name << ", которая имеет высоту " << m[i].height << " (м), расположенная в " << m[i].location.country << endl;
        }
        else
        {
            cout << "Восьмитысячники кончились :D" << endl;
            break;
        }
    }
    cout << "\n";
}

void changeData(Mountain (&m)[20])
{
    int lookingHeight;
    cout << "Введите высоту той горы, котроую хотите найти:" << endl;
    cin >> lookingHeight;

    cout << "Осуществляем поиск..." << endl;

    bool isFound = false;

    for (int i = 0; i < 20; i++)
    {
        if (m[i].height == lookingHeight)
        {
            isFound = true;
            cout << "Найдена гора " << m[i].name << endl;

            bool changeType;
            cout << "Изменить тип? (1 - да, 0 - нет):" << endl;
            cin >> changeType;
            if (changeType)
            {
                int typeChoice;
                cout << "Выберите новый тип (0-Вулкан, 1-Складчатая, 2-Плато, 3-Другое): ";
                cin >> typeChoice;

                switch (typeChoice)
                {
                case 0:
                    m[i].type = VOLCANIC;
                    break;
                case 1:
                    m[i].type = FOLDED;
                    break;
                case 2:
                    m[i].type = PLATEAU;
                    break;
                default:
                    m[i].type = OTHER;
                    break;
                }
            }
            else
            {
                cout << "Вы решили не изменять данные типа горной вершины" << endl;
            }

            bool changeCountry;
            cout << "Изменить страну? (1 - да, 0 - нет):" << endl;
            cin >> changeCountry;
            if (changeCountry)
            {
                cout << "Введите новую страну местонахождения горной вершины:" << endl;
                cin.ignore(32767, '\n');
                getline(cin, m[i].location.country);
            }
            else
            {
                cout << "Вы решили не изменять данные страны местонахождения горной вершины" << endl;
            }

            cout << "!Обновленные данные!" << endl;
            cout << "Название горной вершины: " << m[i].name << endl;
            cout << "Высота горной вершины: " << m[i].height << " (м)" << endl;

            string normalType[] = {"Вулканическая", "Складчатая", "Платообразная", "Другая"};
            cout << "Тип горной вершины: " << normalType[m[i].type] << endl;
            cout << "Страна местонахождения горной вершины: " << m[i].location.country << endl;

            break;
        }
    }

    if (!isFound)
    {
        cout << "Горная вершина с высотой " << lookingHeight << " (м) не найдена" << endl;
    }
}

void printFiltered(Mountain *m, int count)
{
    for (int i = 0; i < count; i++)
    {
        m[i].showInfo();
    }
}

void searchByCountry(const Mountain (&m)[20])
{
    string targerCountry;
    cout << "Введите страну: ";
    cin >> targerCountry;

    int count = 0;
    for (int i = 0; i < 20; i++)
    {
        if (m[i].location.country == targerCountry)
        {
            count++;
        }
    }

    if (count > 0)
    {
        Mountain *filtered = new Mountain[count];
        int ind = 0;
        for (int i = 0; i < 20; i++)
        {
            if (m[i].location.country == targerCountry)
            {
                filtered[ind++] = m[i];
            }
        }

        printFiltered(filtered, count);

        delete[] filtered;
    }
    else
    {
        cout << "В этой стране гор не найдено" << endl;
    }
}

int main()
{
    Mountain mountain[20] = {
        {"Нангапарбат", 8125, {"Пакистан"}, FOLDED},
        {"Чогори", 8611, {"Пакистан"}, FOLDED},
        {"Канченджанга", 8586, {"Индия"}, FOLDED},
        {"Казбек", 5033, {"Грузия"}, VOLCANIC},
        {"Олимп", 2917, {"Греция"}, FOLDED},
        {"Чо-Ойю", 8188, {"Китай"}, FOLDED},
        {"Эверест", 8848, {"Непал"}, FOLDED},
        {"Манаслу", 8163, {"Непал"}, FOLDED},
        {"Дхаулагири", 8167, {"Непал"}, FOLDED},
        {"Аннапурна", 8091, {"Непал"}, FOLDED},
        {"Эльбрус", 5642, {"Россия"}, VOLCANIC},
        {"Килиманджаро", 5895, {"Танзания"}, VOLCANIC},
        {"Монблан", 4810, {"Франция"}, FOLDED},
        {"Лхоцзе", 8516, {"Китай"}, FOLDED},
        {"Белуха", 4506, {"Россия"}, FOLDED},
        {"Арарат", 5165, {"Турция"}, VOLCANIC},
        {"Народная", 1895, {"Россия"}, FOLDED},
        {"Рорайма", 2810, {"Венесуэла"}, PLATEAU},
        {"Фудзияма", 3776, {"Япония"}, VOLCANIC},
        {"Макалу", 8485, {"Непал"}, FOLDED}};

    printMountainInfo(mountain);

    double averageHeight = searchAverageHeight(mountain);
    cout << "Среднее значение высот по 20 вершинам (м): " << averageHeight << endl
         << endl;

    cout << "Сортируем массив структур по возрастанию высоты..." << endl;
    sortByHeight(mountain, printMountainInfo);

    searchEightthousandth(mountain);

    changeData(mountain);

    searchByCountry(mountain);

    return 0;
}