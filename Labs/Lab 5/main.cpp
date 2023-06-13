#include<iostream>
using namespace std;


//���������� ������������ ������� ��� ������� �� ��������� ��������.�������, ��� �� ������ �������� ������ ���� �������� ������ 1 ��� ������.
//������������� ��������� �������� :
//1. ����� ���������� � ����� �������
//2. ����� � �������� ��������� � ��������� �������� �� �������
//3. ����� size
//4. ����� insert � erase

template <typename T>
class vector
{
    
};

template <>
class vector<bool>
{
private:
    unsigned char* data; // ��������� �� ������ ������, ������ char - 1 ����. 
    int size; // ������ ������� � �����(������� ����� ������) 
    int byteCount; // ���������� ������, ����������� ��� �������� �������
public:
    vector(int s) : size(s) 
    { 
        byteCount = (size + 7) / 8; // ��������� ���-�� ������, ������� ������ ��� ����������� ���-�� ��� 
        data = new unsigned char[byteCount]; // ������  ������ 
        memset(data, 0, byteCount); // �������������� ������
        
    }
    ~vector() {
        delete[] data;
    }
    bool get(int index) const // ������ 
    {
        if (index >= size || index < 0)
        {
            throw std::out_of_range("Index out of range");
        }
        else 
        {
            unsigned char byte = data[index / 8]; // ������������ ���� � ������ ����� 
            unsigned char mask = 1 << (index % 8); // ����� � ������� �������: 0000 0001 -> 0000 0100 ��� 1<<2 
            return ((byte & mask) != 0); // ������� �������� &: ���� ������� ���������, �� � ���������� (byte & mask) ��������� ���������, �������� �� ���� -> return true;
        }
         
    }
    void set(int index, bool value) //c�����
    {
        if (index >= size || index < 0)
        {
            throw std::out_of_range("Index out of range");
        }
        else
        {
            unsigned char& byte = data[index / 8]; // ������ ��� ������� � ������������� ����� 
            unsigned char mask = 1 << (index % 8);
            if (value)
            {
                byte |= mask; // ���������� ������ ���; ������� �����������, ������ ������� ������ 1. 
            }
            else
            {
                byte &= ~mask; // ~ - �����������: 0000 0100 -> 1111 1011; ��� �������� �����������, � ������ ������� ��������� 
            }
        }
    }
    void push_back(bool value) 
    {
        if (size % 8 == 0) //���� ���� ��������, �� �������� ����� ������. 
        {
             // ����� ������ 
            byteCount++;
            unsigned char* new_data = new unsigned char[byteCount]; 

            memcpy(new_data, data, byteCount-1);
            memset(new_data + byteCount-1, 0, 1);
            //for (int i = 0; i < byteCount; i++)  // �������� ����� 
            //{
            //    new_data[i] = data[i];
            //}

            // ��������� ����� ������� � �����
            new_data[byteCount-1] |= (value << (size % 8));


            // ��������� ������ � ������ �������
            delete[] data;
            data = new_data;
            size++;
            
        }
        else 
        {
            // ��������� ����� ������� � ��������� ����
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
            // ��������� ����� �������
            push_back(value);

            // �������� �������� ������ ������� � ����� �� ������� �������
            for (int i = size - 1; i > index; i--) {
                bool bit = get(i - 1);
                set(i, bit);
            }

            // ��������� ������� � ������ �����
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
            for (int i = index; i < size - 1; i++) // �������� �������� ����� ������� � ���������� ��������
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
    vector<bool> bv(10);// ����� ������
    cout <<"Bool vector (size = 10): "<< bv << endl; // ������� 

    //������ �������
    cout << "Size: " << bv.Size() << endl;


    //��������� �� �������
    bv.set(5, true);
    bv.set(6, 1);

    cout <<"Changed 5 and 6 elements: " << bv << endl;

    //push_back
    bv.push_back(1);
    bv.push_back(false);

    cout << "New elements: " << bv << endl;

    //��������� �� ������� / � ������� ������
    cout << "5 element: "<<bv[5] <<"\n" << "6 element: " << bv.at(6) << endl;
    

    bv.insert(5, true);
    
    cout <<"New element inserted on pos 5: " << bv << endl;
   


    bv.erase(5);
    bv.erase(6);

    cout <<"5 and 6 elements deleted: " << bv;
}