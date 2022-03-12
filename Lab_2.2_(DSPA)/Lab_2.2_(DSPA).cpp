#include <set>
#include <locale>
#include <iostream>

using namespace std;
const int maxSize = 10;

struct ListItem
{
    int data;
    int next;
};

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int CheckedInput() // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

void InitList(ListItem* StatList[maxSize]) // инициализация списка
{
    for (int i = 0; i < maxSize; i++)
    {
        StatList[i] = new ListItem;
        StatList[i]->data = 0; StatList[i]->next = -1;
    }
}

bool isEmpty(ListItem* StatList[maxSize]) // проверка списка на пустоту
{
    if (StatList[0]->next == -1)
    {
        return true;
    }
    return false;
}

bool isFull(ListItem* StatList[maxSize]) // проверка списка на заполненность
{
    for (int i = 0; i < maxSize; i++)
    {
        if (StatList[i]->next == -1)
        {
            return false;
        }
    }
    return true;
}

void PrintList(ListItem* StatList[maxSize]) // вывод списка 
{
    int current = StatList[0]->next;
    while (current != 0)
    {
        cout << StatList[current]->data << " ";
        current = StatList[current]->next;
    }
}

int Search(ListItem* StatList[maxSize], int infoToSearch) // поиск элемента по инфо-части
{
    int current = StatList[0]->next;
    if (isEmpty(StatList))
    {
        return -1;
    }
    while (current != 0)
    {
        if (StatList[current]->data == infoToSearch)
        {
            return current;
        }
        current = StatList[current]->next;
    }
    return -1;
}

void Delete(ListItem* StatList[maxSize], int indexToDel) // удаление элемента
{
    int current = StatList[0]->next;
    int previous = 0;
    while (current != indexToDel && current != 0)
    {
        previous = current;
        current = StatList[current]->next;
    }
    if (current == 0)
    {
        cout << "Данная ячейка пустая.";
    }
    else
    {
        StatList[previous]->next = StatList[current]->next; // по композиции: следующий предыдущего есть следующий текущего
        StatList[current]->next = -1; StatList[current]->data = 0; // очищаем выбранный
    }

}

void Add(ListItem* StatList[maxSize], int infoToAdd) // добавление элемента 
{
    if (isEmpty(StatList))
    {
        StatList[0]->next = 1; //следующий с индексом 1, т.к. не с чем сравнивать
        StatList[1]->data = infoToAdd; // к первому добавляем данные
        StatList[1]->next = 0; // снова возврат к головному элементу массива
    }
    else
    {
        int current = StatList[0]->next; // Если массив не был пустым, то текущий(самый маленький элемент) 
        int previous = 0; // предыдущий у нас пока головной элемент
        while (current != 0) // пока не вернемся обратно к головному элементу
        {
            if (StatList[current]->data > infoToAdd) // если текущий больше, чем введенное нами число
            {
                int index = 1;
                while (StatList[index]->next != -1) // пока не дойдем до пустого
                {
                    index++; // получаем индекс последнего элемента
                }
                StatList[index]->data = infoToAdd; // добавили данные в след. пустой элемент
                StatList[index]->next = current; // следующий за ним тот, который был его больше
                StatList[previous]->next = index; // предыдущий указывает теперь на добавленный нами элемент
                break;
            }
            previous = current; // предыдуший отодвигаем
            current = StatList[current]->next; // текущий тоже
        }
        if (current == 0) // если не нашли элемент, больший введенного
        {
            int index = 1;
            while (StatList[index]->next != -1)
            {
                index++;
            }
            StatList[index]->data = infoToAdd;
            StatList[index]->next = 0; // возвращаемся к головному элемнту
            StatList[previous]->next = index;
        }
    }
}

void DeleteAll(ListItem* StatList[maxSize]) // очищение памяти
{
    for (int i = 0; i < maxSize; i++)
    {
        delete StatList[i];
    }
}

void CallMenu(ListItem* StatList[maxSize]) // меню
{
    bool work = true;
    int choice;
    while (work)
    {
        cout << "Выбор действия:\n1 - Вывод списка\n2 - Поиск элемента с заданной информационной частью\n3 - Добавление элемента\n4 - Удаление заданного элемента\n5 - Завершить работу\n";
        cout << "Действие: "; choice = CheckedInput(1, 5);
        switch (choice)
        {
        case 1:
            if (isEmpty(StatList))
            {
                cout << "Список пустой.";
            }
            else
            {
                cout << "Список: "; PrintList(StatList);
            }
            cout << "\n\n";
            break;
        case 2:
            int elemsIndex;
            cout << "Введите информационную часть, индекс которой надо найти: "; elemsIndex = Search(StatList, CheckedInput());
            if (elemsIndex == -1)
            {
                cout << "Такого элемента в списке нет.";
            }
            else
            {
                cout << "Элемент " << elemsIndex << "-ый в списке.";
            }
            cout << "\n\n";
            break;
        case 3:
            if (isFull(StatList))
            {
                cout << "Список полон. Добавить элемент нельзя.\n\n";
                break;
            }
            cout << "Введите элемент, который хотели бы добавить: "; Add(StatList, CheckedInput());
            cout << "\n\n";
            break;
        case 4:
            if (isEmpty(StatList))
            {
                cout << "Список пустой. Удалять нечего\n\n";
                break;
            }
            cout << "Введите индекс удаляемого элемента (от 1 до 20): "; Delete(StatList, CheckedInput(1, 20));
            cout << "\n\n";
            break;
        case 5:
            work = false;
            DeleteAll(StatList);
            break;
        default:
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    ListItem* StatList[maxSize];
    InitList(StatList);
    CallMenu(StatList);
}