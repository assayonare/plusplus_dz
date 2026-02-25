/* Задание:
1. Массив (double)
разместить динамически массив из 10 элементов
заполнить массив значениями i*10 (i – номер элемента массива)
вывести все значения на экран
посчитать среднее арифметическое всех элементов и вывести результат на экран
2. Вектор (int)
создать вектор из 15 элементов
заполнить массив случайными значениями в диапазоне от 0 до 5 (см.пример 3.3, округление round) 
вывести все значения на экран
Алгоритмы для вектора (см.пример 3.9, Яндекс)
найти максимальный элемент массива и вывести результат на экран (max_element)
вычислить сумму всех элементов массива и вывести результат на экран (accumulate)
удалить из массива все значения равные 0 (remove, resize)
отсортировать массив по возрастанию (sort) 
удалить все повторяющиеся значения (unique, resize)
вывести результат на экран

3. Список (double)
создать пустой список
заполнить список с клавиатуры, после каждого введенного числа опрашивая продолжить ввод или нет
вывести все значения на экран
найти наибольший по модулю элемент (max_element) и вывести результат на экран
4. Ассоциативный массив map (<string, double>)
создать контейнер map для хранения показателей преломления оптического стекла
организовать ввод данных о стеклах из файла (предварительно создать файл с 10-15 стеклами)
вывести на экран весь список стекол
определить минимальный и максимальный показатель преломления и вывести на экран соответствующие им стекла
5. Ассоциативный массив set и очередь (int)
создать очередь deque из 15 элементов
заполнить массив случайными значениями в диапазоне от 0 до 5 (см.пример 3.3, округление round) 
вывести все значения на экран
создать контейнер set и записать в него все значения из контейнера deque
____________________

Выполнил: Кудрявцев Алексей
*/

#include <iostream>
#include <vector>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>


using namespace std;

int main(){

    // ______________________________________________________
    // 1. Массив double

    cout << "1. array double:" << endl;

    double *arr = new double[10];
    for (int i = 0;  i < 10; i++) {
        
        arr[i] = i * 10;

    }
    cout << "   ";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    double sum = 0;

    for (int i = 0; i < 10; i++) {
        sum += arr[i];
    }
    double avg = sum / 10;

    cout << "   avg: " << avg << endl;

    delete[] arr;
    cout << endl;
    // ______________________________________________________
    // 2. vector int

    cout << "2. vector int: " << endl;

    vector<int> vec(15);
    
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = rand() % 6;
    }
    cout << "   ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
    
    auto max_it = max_element(vec.begin(), vec.end());
    cout << "   max: " << *max_it << endl;
    
    int total_sum = accumulate(vec.begin(), vec.end(), 0);
    cout << "   sum: " << total_sum << endl;

    vec.erase(remove(vec.begin(), vec.end(), 0), vec.end());

    sort(vec.begin(), vec.end());
    
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    
    cout << "   Edited vector: " << endl;
    cout << "   ";
    for (int num : vec) {
        cout << num << " ";
    }
    
    cout << endl;
    // ______________________________________________________
    // 3. Список (double)

    cout << "3. list double:" << endl;

    list<double> lst;
    
    double value;
    char choice = 'y';

    while ((choice == 'y' || choice == 'Y') && (choice != 'n' || choice != 'N')) {
        cout << "   Input value: ";
        cin >> value;
        lst.push_back(value);
        
        cout << "   Continue? (y/n): ";
        cin >> choice;
    }
        
     
    

    cout << "   Input values: " << endl;
    cout << "   ";
    for (double num : lst) {
        cout << num << " ";
    }
    cout << endl;
    
    auto max_abs = max_element(lst.begin(), lst.end(), 
                               [](double a, double b) {
                                   return abs(a) < abs(b);
                               });
    cout << "   Max abs value: " << *max_abs << endl;
    cout << endl;
    // ______________________________________________________
    // 4. MAPы
    cout << "4. Map glasses:" << endl;
    
    map<string, double> glass_refraction;
    
    ifstream file("glasses.txt");
    if (!file.is_open()) {
        cout << "   Error read file. Create glasses.txt" << endl;
    } else {
        string name;
        double refraction;
        
        while (file >> name >> refraction) {
            glass_refraction[name] = refraction;
        }
        file.close();

        cout << "   Glasses:" << endl;
        for (const auto& glass : glass_refraction) {
            cout << "    " << setw(15) << left << glass.first 
                 << ": " << glass.second << endl;
        }
        
        if (!glass_refraction.empty()) {
            auto min_glass = min_element(glass_refraction.begin(), glass_refraction.end(),
                                         [](const auto& a, const auto& b) {
                                             return a.second < b.second;
                                         });
            
            auto max_glass = max_element(glass_refraction.begin(), glass_refraction.end(),
                                         [](const auto& a, const auto& b) {
                                             return a.second < b.second;
                                         });
            cout << endl;
            cout << "   Glass with min n: " << min_glass->first 
                 << " (" << min_glass->second << ")" << endl;
            cout << "   Glass with max n: " << max_glass->first 
                 << " (" << max_glass->second << ")" << endl;
        }
    }
    cout << endl;
    // ______________________________________________________
    // 5 Очередь и множество
    
    cout << "5. Deque and set:" << endl;
   
    deque<int> deq(15);
    
   
    for (int i = 0; i < deq.size(); i++) {
        deq[i] = rand() % 6;
    }
    
   
    cout << "   Deque: ";
    for (int num : deq) {
        cout << num << " ";
    }
    cout << endl;

    set<int> num_set(deq.begin(), deq.end());
    
    cout << "   Set: ";
    for (int num : num_set) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}