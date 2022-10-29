#include <iostream> 
#include <stdexcept> 
#include <vector> 
#include <algorithm> 
#include <ctime> 
using namespace std;
//template <typename T> 
class Stack
{
public: int size; // размер стека 
      Stack(int size) {
          this->size = size;
      }

public:
    Stack() : root(nullptr) {} //По умолчанию стек пуст 
    void push(const int& x) //добавление в стек 
    {
        Node* newnode = new Node;
        newnode->data = x;
        newnode->next = root;
        root = newnode;
    }
    bool empty() const //проверка на пустоту 
    {
        return root == nullptr;
    }
    const int& top()const //вершина стека 
    {
        if (empty())
        {
            throw length_error("stack is empty");
        }
        return root->data;
    }
    int pop() //void pop() ??? удаление из стека 
    {
        if (empty())
        {
            throw length_error("stack is empty");
        }
        Node* delnode = root;
        int x = delnode->data;
        root = delnode->next;
        delete delnode;
        return x;
    }
    unsigned int getSize() {
        return size;
    }
    ~Stack() //деструктор 
    {
        while (!empty())
        {
            pop(); //некоторая проблема - из-за неоптимальной реализации pop прозводится лишнее копирование 
        }
    }
private:
    struct Node //вспомогательная структура - узел стека 
    {
        int data; //Поле с данными 
        Node* next; //Указатель на следующий 
    };
    Node* root; //вершина стека 
};
int main()
{
    Stack st;
    Stack temp_st;
    Stack temp_st2;
    Stack count_st;
    Stack temp_count_st;
    for (int p = 1; p < 21; p++)
    {
        int N_op = 0;
        st.size = temp_st.size = 300 * p;
        srand(time(0));
        for (int i = st.size; i > 0; i--)
        {
            st.push(1 + rand() % 10);
        }
        // начальный стек (вывод) 
       /* cout << "\n" << "No sort: " << endl;
        while (!st.empty())
        {
            int temp = st.pop();
            cout << temp << " ";
            temp_st.push(temp);
        }
        while (!temp_st.empty())
        {
            int temp = temp_st.pop();
            st.push(temp);
        }*/
        cout << " " << endl;
        // нахождение min and max 
        unsigned int start_time = clock();
        N_op++;
        int max_count_st = 0; // 1 
        N_op++;
        int min_count_st = 0; // 1 
        for (int i = st.size; i > 0; i--) // n*(2+3+2+2+1) = 12n + 3 
        {
            N_op += 2;
            int temp = st.pop(); // 2 
            N_op += 2;
            if (i == st.size) {
                N_op++;
                min_count_st = temp;
            } // 3 
            N_op++;
            if (max_count_st < temp) { // 2 
                N_op++;
                max_count_st = temp; // 1 
            }
            N_op++;
            if (min_count_st > temp) { // 2 
                N_op++;
                min_count_st = temp;
            }
            N_op++;
            temp_st.push(temp); // 1 
        }
        //заполнение стека нулями для подсчета 
        N_op += 4;
        count_st.size = max_count_st - min_count_st + 1; // 4 
        N_op += 3;
        for (int i = count_st.size; i > 0; i--) // 3 + n*(1+2) 
        {
            N_op++;
            count_st.push(0); // 1 
        }
        // подсчитывает числа 
        N_op += 3;
        for (int i = temp_st.size; i > 0; i--) // 3 + n 
        {
            N_op += 2;
            int temp = temp_st.pop(); // 2 
            N_op++;
            st.push(temp); // 1 
            N_op += 2;
            int count_temp = temp - min_count_st; // 2 
            N_op += 3;
            for (int j = count_st.size; j > count_temp + 1; j--) // 3 + (n-1)/2 * 2 = n - 1   
            {
                N_op += 2;
                temp_count_st.push(count_st.pop()); // 2 
            }
            N_op += 2;
            int n = count_st.pop(); // 2 
            N_op += 2;
            count_st.push(n + 1); // 2 
            N_op += 5;
            for (int j = count_st.size - count_temp; j > 1; j--) // 5 + (n-1)*2 
            {
                N_op += 2;
                count_st.push(temp_count_st.pop()); //2 
            }
        }
        // меняем подсчет по формуле динна - количесво чисел 
        N_op += 2;
        int size = st.getSize(); // 2 
        N_op += 1;
        while (!count_st.empty()) // n * 5 
        {
            N_op += 2;
            int n = count_st.pop(); // 2 
            N_op += 2;
            size -= n; // 2 
            N_op += 1;
            temp_count_st.push(size); // 1 
        }
        N_op += 1;
        while (!temp_count_st.empty()) // n * 2 
        {
            N_op += 2;
            count_st.push(temp_count_st.pop()); // 2 
        }
        // переносим числа во временный стек  
        N_op += 4;
        for (int i = temp_st.size; i > 0; i--) // 4 + n*(1+2) 
        {
            N_op += 1;
            temp_st.push(0); // 1 
        }
        //числа по возрастанию по индексам 
        N_op += 1;
        while (!st.empty()) { // n 
            N_op += 2;
            int temp = st.pop(); // 2 
            N_op += 2;
            int tem = max_count_st - temp; // 2 
            N_op += 3;
            for (int i = tem; i > -1; i--) // 3 + n(2+2) 
            {
                N_op += 4;
                temp_count_st.push(count_st.pop()); // 2 
            }
            N_op += 6;
            for (int i = temp_st.size; i > temp_count_st.top() + 1; i--) // 6 + n*(3+2) 
            {
                N_op += 6;
                temp_st2.push(temp_st.pop()); // 2 
            }
            N_op += 1;
            temp_st.pop(); // 1 
            N_op += 1;
            temp_st.push(temp); // 1 
            N_op += 1;
            while (!temp_st2.empty()) { // n * 2 
                N_op += 2;
                temp_st.push(temp_st2.pop());  // 2 
            }
            N_op += 3;
            temp_count_st.push(temp_count_st.pop() + 1); // 3 
            N_op += 1;
            while (!temp_count_st.empty()) { // n*2 
                N_op += 2;
                count_st.push(temp_count_st.pop()); // 2 
            }
        }
        unsigned int end_time = clock();
        /*cout << "\n" << (float)(end_time - start_time)/1000;*/
        cout << "\n" << N_op;
        // отсортированный стек (вывод) 
        /*cout << "\n Sort: " << endl;
        while (!temp_st.empty())
        {
            cout << temp_st.pop() << " ";
        }*/
        cout << "\n" << st.size << endl;
        cout << "F(n): " << 16 * st.size * st.size + 57 * st.size + 21 << endl;
        cout << "O(n): " << st.size * st.size << endl;
        cout << "T(n)(c): " << (float)(end_time - start_time) << endl;
    }
    return 0;
}