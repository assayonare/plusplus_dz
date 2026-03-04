#include <iostream>
#include <fstream>
#include <iomanip>
#include "sample.h"

using namespace std;

template<typename T>
void PrintSample(const Sample<T>& sample, const string& name) {
    cout << name << " (" << sample.GetSizeX() << "x" << sample.GetSizeY() << "):" << endl;
    for (int i = 0; i < sample.GetSizeX(); ++i) {
        cout << "  ";
        for (int j = 0; j < sample.GetSizeY(); ++j) {
            cout << setw(5) << sample(i, j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "=== ТЕСТИРОВАНИЕ КЛАССА Sample ===\n\n";

    try {
        // 1. Тест конструктора и изменения размера

        cout << "1. Тест конструктора и изменения размера:\n";
        
        Sample<double> sample1;
        cout << "  После создания (пустая): размер = " 
             << sample1.GetSizeX() << "x" << sample1.GetSizeY() << endl;
        
        sample1.Resize(3); // квадратная 3x3
        cout << "  После Resize(3): размер = " 
             << sample1.GetSizeX() << "x" << sample1.GetSizeY() << endl;
        
        sample1.Resize(2, 4); // прямоугольная 2x4
        cout << "  После Resize(2,4): размер = " 
             << sample1.GetSizeX() << "x" << sample1.GetSizeY() << endl;
        
        cout << "  IsSquare(): " << (sample1.IsSquare() ? "да" : "нет") << endl;
        cout << "  IsZeroSize(): " << (sample1.IsZeroSize() ? "да" : "нет") << endl;
        cout << endl;

        // 2. Тест SetValue и operator()

        cout << "2. Тест SetValue и operator():\n";
        
        Sample<int> sample2;
        sample2.Resize(3, 3);
        sample2.SetValue(5);
        PrintSample(sample2, "  sample2 (все = 5)");
        
        sample2(0, 0) = 10;
        sample2(1, 1) = 20;
        sample2(2, 2) = 30;
        cout << "  После изменений:\n";
        PrintSample(sample2, "  sample2");

        // 3. Тест операций с числом

        cout << "3. Тест операций с числом:\n";
        
        Sample<int> sample3 = sample2;
        
        sample3 += 1;
        PrintSample(sample3, "  sample3 = sample2 + 1");
        
        sample3 *= 2;
        PrintSample(sample3, "  sample3 *= 2");
        
        sample3 /= 2;
        PrintSample(sample3, "  sample3 /= 2");
        
        try {
            sample3 /= 0;
        } catch (const exception& e) {
            cout << "  Ошибка при делении на 0: " << e.what() << endl << endl;
        }

        // 4. Тест операций с двумя выборками

        cout << "4. Тест операций с двумя выборками:\n";
        
        Sample<int> sample4;
        sample4.Resize(3, 3);
        sample4.SetValue(1);
        
        Sample<int> sample5;
        sample5.Resize(3, 3);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                sample5(i, j) = i * 3 + j + 1;
            }
        }
        
        PrintSample(sample4, "  sample4");
        PrintSample(sample5, "  sample5");
        
        sample4 += sample5;
        PrintSample(sample4, "  sample4 += sample5");
        
        sample4 -= sample5;
        PrintSample(sample4, "  sample4 -= sample5");
        
        sample4 *= sample5;
        PrintSample(sample4, "  sample4 *= sample5");
        
        
        Sample<int> sample6;
        sample6.Resize(2, 3);
        cout << "  sample4 и sample6 одного размера? " 
             << (sample4.IsEqualSize(sample6) ? "да" : "нет") << endl << endl;

        // 5. Тест GetMax

        cout << "5. Тест GetMax:\n";
        cout << "  Максимум в sample5: " << sample5.GetMax() << endl << endl;

        // 6. Тест GetPointer
    
        cout << "6. Тест GetPointer:\n";
        int* ptr = sample5.GetPointer();
        cout << "  Первый элемент через указатель: " << *ptr << endl;
        cout << "  Второй элемент через указатель: " << *(ptr + 1) << endl << endl;

        // 7. Тест GetSize для квадратной выборки

        cout << "7. Тест GetSize (для квадратной выборки):\n";
        Sample<double> square;
        square.Resize(4, 4);
        cout << "  GetSize() для квадратной 4x4: " << square.GetSize() << endl;
        
        try {
            sample5.GetSize();

            Sample<int> rect;
            rect.Resize(2, 4);
            rect.GetSize();
        } catch (const exception& e) {
            cout << "  Ошибка при GetSize() для прямоугольной: " << e.what() << endl << endl;
        }

        // 8. Тест оператора присваивания

        cout << "8. Тест оператора присваивания:\n";
        Sample<int> sample7;
        sample7 = sample5;
        PrintSample(sample7, "  sample7 = sample5");

        // 9. Тест работы с разными типами

        cout << "9. Тест работы с разными типами:\n";
        
        Sample<double> sample_d;
        sample_d.Resize(2, 2);
        sample_d.SetValue(3.14);
        PrintSample(sample_d, "  Sample<double>");
        
        Sample<float> sample_f;
        sample_f.Resize(2, 2);
        sample_f(0, 0) = 1.1f;
        sample_f(0, 1) = 2.2f;
        sample_f(1, 0) = 3.3f;
        sample_f(1, 1) = 4.4f;
        PrintSample(sample_f, "  Sample<float>");

        // 10. Тест Save/Load
   
        cout << "10. Тест Save/Load:\n";
        
        ofstream outFile("sample_test.txt");
        if (outFile.is_open()) {
            sample5.Save(outFile);
            outFile.close();
            cout << "  sample5 сохранен в файл 'sample_test.txt'\n";
        }

        Sample<int> sample8;
        ifstream inFile("sample_test.txt");
        if (inFile.is_open()) {
            sample8.Load(inFile);
            inFile.close();
            cout << "  sample8 загружен из файла\n";
            PrintSample(sample8, "  sample8");
        }

        // 11. Тест const operator()

        cout << "11. Тест const operator():\n";
        const Sample<int>& const_ref = sample5;
        cout << "  const элемент (1,1): " << const_ref(1, 1) << endl << endl;

        // 12. Тест виртуальной функции

        cout << "12. Тест виртуальной функции operator*= (демонстрация полиморфизма):\n";
    
        Sample<double>* base_ptr = new Sample<double>();
        base_ptr->Resize(2, 2);
        base_ptr->SetValue(2.0);
        
        Sample<double> other;
        other.Resize(2, 2);
        other.SetValue(3.0);
        
        *base_ptr *= other; 
        PrintSample(*base_ptr, "  Результат *=");
        
        delete base_ptr;

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    cout << "=== ТЕСТИРОВАНИЕ ЗАВЕРШЕНО ===" << endl;
    return 0;
}