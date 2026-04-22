#include <iostream>
#include <string>
#include <fstream>

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
    char country[50];
};

struct Mountain
{
    char name[50];
    int height;
    Location location;
    mountainType type;
};

void showInfo(const Mountain &m)
{
    string normalType[] = {"Вулканическая", "Складчатая", "Платообразная", "Другая"};
    cout << "\nНазвание: " << m.name << endl;
    cout << "Высота: " << m.height << "м" << endl;
    cout << "Страна: " << m.location.country << endl;
    cout << "Тип: " << normalType[m.type] << endl;
}

void printMountainInfo(const Mountain (&m)[20])
{
    for (int i = 0; i < 20; i++)
    {
        cout << "Вершина " << i + 1 << endl;
        showInfo(m[i]);
        cout << endl;
    }
}

double searchAverageHeight(const Mountain (&m)[20])
{
    int sum = 0;
    for (int i = 0; i < 20; i++)
        sum += m[i].height;
    return sum / 20.0;
}

void sortByHeight(Mountain (&m)[20], void (*show)(const Mountain (&)[20]))
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19 - i; j++)
        {
            if (m[j].height > m[j + 1].height)
            {
                Mountain temp = m[j];
                m[j] = m[j + 1];
                m[j + 1] = temp;
            }
        }
    }
    show(m);
}

void searchEightthousandth(const Mountain (&m)[20])
{
    cout << "\nСтраны 3-х восьмитысячников" << endl;
    int count = 0;
    for (int i = 19; i >= 0 && count < 3; i--)
    {
        if (m[i].height >= 8000)
        {
            cout << count + 1 << ". " << m[i].location.country << " (Вершина: " << m[i].name << ")" << endl;
            count++;
        }
    }
}

void changeData(Mountain (&m)[20])
{
    int lookingHeight;
    cout << "\nВведите высоту для поиска: ";
    cin >> lookingHeight;
    bool isFound = false;

    for (int i = 0; i < 20; i++)
    {
        if (m[i].height == lookingHeight)
        {
            isFound = true;
            cout << "Найдена: " << m[i].name << ". Изменить тип? (1-да, 0-нет): ";
            bool choice;
            cin >> choice;
            if (choice)
            {
                int t;
                cout << "0-Вулкан, 1-Складка, 2-Плато, 3-Другое: ";
                cin >> t;
                switch (t)
                { // Исправлено: добавлены break
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
            cout << "Текущие данные: ";
            showInfo(m[i]);
            break;
        }
    }
    if (!isFound)
        cout << "Вершина не найдена." << endl;
}

void printFiltered(const Mountain *m, int count)
{
    for (int i = 0; i < count; i++)
        showInfo(m[i]);
}

void searchByCountry(const Mountain (&m)[20])
{
    string target;
    cout << "\nВведите страну для фильтра: ";
    cin >> target;
    int count = 0;
    for (int i = 0; i < 20; i++)
        if (m[i].location.country == target)
            count++;

    if (count > 0)
    {
        Mountain *filtered = new Mountain[count];
        int ind = 0;
        for (int i = 0; i < 20; i++)
        {
            if (m[i].location.country == target)
                filtered[ind++] = m[i];
        }
        printFiltered(filtered, count);
        delete[] filtered;
    }
    else
        cout << "Ничего не найдено." << endl;
}

void writeTextFile(const Mountain (&m)[20], string filename)
{
    ofstream fout(filename);
    if (fout.is_open())
    {
        for (int i = 0; i < 20; i++)
            fout << m[i].name << " " << m[i].height << endl;
        fout.close();
    }
}

void updateFromTextFile(Mountain (&m)[20], string filename)
{
    cout << "\nЧтение данных из текстового файла..." << endl;
    ifstream fin(filename);
    if (!fin.is_open())
    {
        cout << "Ошибка чтения файла " << filename << endl;
        return;
    }

    string nameFromFile;
    int heightFromFile;
    int foundCount = 0;

    while (fin >> nameFromFile >> heightFromFile)
    {
        for (int i = 0; i < 20; i++)
        {
            if (string(m[i].name) == nameFromFile)
            {
                m[i].height = heightFromFile;
                cout << i + 1 << ". " << m[i].name << ", новая высота: " << m[i].height << "м" << endl;

                foundCount++;
            }
        }
    }

    if (foundCount == 0)
    {
        cout << "Совпадений имен для обновления не найдено" << endl;
    }

    fin.close();
}

void writeBinary(const Mountain (&m)[20], string filename)
{
    ofstream fout(filename, ios::binary);
    if (fout.is_open())
    {
        fout.write((char *)&m, sizeof(m));
        fout.close();
    }
}

void readBinary(Mountain (&m)[20], string filename)
{
    cout << "\nЧтение из бинарного файла..." << endl;
    ifstream fin(filename, ios::binary);
    if (fin.is_open())
    {
        fin.read((char *)&m, sizeof(m));
        fin.close();
        for (int i = 0; i < 20; i++)
        {
            cout << i + 1 << ". " << m[i].name << " " << m[i].height << "м" << endl;
        }
        cout << "Бинарные данные успешно загружены и выведены" << endl;
    }
    else
    {
        cout << "Ошибка чтения файла " << filename << endl;
    }
}

int main()
{
    Mountain mountain[20] = {
        {"Эверест", 8848, {"Непал"}, FOLDED},
        {"Чогори", 8611, {"Пакистан"}, FOLDED},
        {"Канченджанга", 8586, {"Индия"}, FOLDED},
        {"Лхоцзе", 8516, {"Китай"}, FOLDED},
        {"Макалу", 8485, {"Непал"}, FOLDED},
        {"Чо-Ойю", 8188, {"Китай"}, FOLDED},
        {"Дхаулагири", 8167, {"Непал"}, FOLDED},
        {"Манаслу", 8163, {"Непал"}, FOLDED},
        {"Нангапарбат", 8125, {"Пакистан"}, FOLDED},
        {"Аннапурна", 8091, {"Непал"}, FOLDED},
        {"Эльбрус", 5642, {"Россия"}, VOLCANIC},
        {"Казбек", 5033, {"Грузия"}, VOLCANIC},
        {"Килиманджаро", 5895, {"Танзания"}, VOLCANIC},
        {"Монблан", 4810, {"Франция"}, FOLDED},
        {"Белуха", 4506, {"Россия"}, FOLDED},
        {"Арарат", 5165, {"Турция"}, VOLCANIC},
        {"Фудзияма", 3776, {"Япония"}, VOLCANIC},
        {"Олимп", 2917, {"Греция"}, FOLDED},
        {"Рорайма", 2810, {"Венесуэла"}, PLATEAU},
        {"Народная", 1895, {"Россия"}, FOLDED}};

    cout << "Исходные данные" << endl;
    printMountainInfo(mountain);

    cout << "\nСредняя высота: " << searchAverageHeight(mountain) << " м" << endl;

    cout << "\nСортировка по высоте" << endl;
    sortByHeight(mountain, printMountainInfo);

    searchEightthousandth(mountain);

    changeData(mountain);
    searchByCountry(mountain);

    writeTextFile(mountain, "textmountains.txt");
    updateFromTextFile(mountain, "textmountains.txt");

    writeBinary(mountain, "binmountains.bin");
    readBinary(mountain, "binmountains.bin");

    return 0;
}