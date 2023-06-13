#include<iostream>
using namespace std;


//Реализуйте спецификацию шаблона для вектора из булевских значений.Помните, что на каждое значение должен быть потрачен только 1 бит памяти.
//Предусмотрите следующие операции :
//1. Метод добавления в конец вектора
//2. Метод и оператор получения и изменения значения по индексу
//3. Метод size
//4. Метод insert и erase

template <typename T>
class vector
{
    
};

template <>
class vector<bool>
{
private:
    unsigned char* data; // указатель на массив байтов, каждый char - 1 байт. 
    int size; // размер вектора в битах(сколько битов занято) 
    int byteCount; // количество байтов, необходимых для хранения вектора
public:
    vector(int s) : size(s) 
    { 
        byteCount = (size + 7) / 8; // вычисляем кол-во байтов, которое хватит под определённое кол-во бит 
        data = new unsigned char[byteCount]; // массив  байтов 
        memset(data, 0, byteCount); // инициализируем нулями
        
    }
    ~vector() {
        delete[] data;
    }
    bool get(int index) const // геттер 
    {
        if (index >= size || index < 0)
        {
            throw std::out_of_range("Index out of range");
        }
        else 
        {
            unsigned char byte = data[index / 8]; // определяется байт с данным битом 
            unsigned char mask = 1 << (index % 8); // маска с битовым сдвигом: 0000 0001 -> 0000 0100 для 1<<2 
            return ((byte & mask) != 0); // битовая операция &: если элемент ненулевой, то в результате (byte & mask) получится выражение, отличное от нуля -> return true;
        }
         
    }
    void set(int index, bool value) //cеттер
    {
        if (index >= size || index < 0)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            unsigned char& byte = data[index / 8]; // ссылка для доступа к оригинальному байту 
            unsigned char mask = 1 << (index % 8);
            if (value)
            {
                byte |= mask; // сравниваем каждый бит; единицы сохраняться, нужный элемент станет 1. 
            }
            else
            {
                byte &= ~mask; // ~ - инвертируем: 0000 0100 -> 1111 1011; все единички сохраняться, а нужный элемент обнулится 
            }
        }
    }
    void push_back(bool value) 
    {
        if (size % 8 == 0) //если байт заполнен, то выделяем новую память. 
        {
             // новый размер 
            byteCount++;
            unsigned char* new_data = new unsigned char[byteCount]; 

            memcpy(new_data, data, byteCount-1);
            memset(new_data + byteCount-1, 0, 1);
            //for (int i = 0; i < byteCount; i++)  // копируем байты 
            //{
            //    new_data[i] = data[i];
            //}

            // добавляем новый элемент в конец
            new_data[byteCount-1] |= (value << (size % 8));


            // Обновляем данные и размер вектора
            delete[] data;
            data = new_data;
            size++;
            
        }
        else 
        {
            // добавляем новый элемент в последний байт
            if(value)
                data[byteCount-1] |= (value << (size % 8));
            size++;
        }
    }

    bool operator[](int index) 
    {
        return get(index);
    }
    bool at(int index)
    {
        return get(index);
    }
    int Size()
    {
        return size;
    }

    void insert(int index, bool value) {
        if (index >= size || index < 0)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            // добавляем новый элемент
            push_back(value);

            // сдвигаем элементы вправо начиная с конца до нужного индекса
            for (int i = size - 1; i > index; i--) {
                bool bit = get(i - 1);
                set(i, bit);
            }

            // вставляем элемент в нужное место
            set(index, value);
        }
        
    }
    void erase(int index) 
    {
        if (index >= size || index < 0) 
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            for (int i = index; i < size - 1; i++) // сдвигаем элементы влево начиная с удаленного элемента
            {
                bool bit = get(i + 1);
                set(i, bit);
            }
            size--;
        }
    }



    friend std::ostream& operator<<(std::ostream& out, const vector &bv);
};

std::ostream& operator<<(std::ostream& out,const vector<bool> &bv)
{
    for (int j = 0; j < bv.size; ++j)
    {
        if ((j!=0)&&(j%8 == 0))
            out << " ";
        out << bv.get(j);
    }
    return out;
}

int main()
{
    vector<bool> bv(10);// задаём вектор
    cout <<"Bool vector (size = 10): "<< bv << endl; // выводим 

    //Размер вектора
    cout << "Size: " << bv.Size() << endl;


    //изменение по индексу
    bv.set(5, true);
    bv.set(6, 1);

    cout <<"Changed 5 and 6 elements: " << bv << endl;

    //push_back
    bv.push_back(1);
    bv.push_back(false);

    cout << "New elements: " << bv << endl;

    //обращение по индексу / с помощью метода
    cout << "5 element: "<<bv[5] <<"\n" << "6 element: " << bv.at(6) << endl;
    

    bv.insert(5, true);
    
    cout <<"New element inserted on pos 5: " << bv << endl;
   


    bv.erase(5);
    bv.erase(6);

    cout <<"5 and 6 elements deleted: " << bv;
}