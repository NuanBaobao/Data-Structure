#include<bits/stdc++.h>
using namespace std;
struct student //学生类
{
    string name;   // 姓名
    string phone;  //电话
    int class_num; //班级
    int dorm;      //宿舍
};

template <class T>
void changeLength(T *&arr, int oldLength, int newLength)//改变数组长度
{
    T *temp = new T[newLength];
    int number = min(oldLength, newLength);
    copy(arr, arr + number, temp); //参数分别是首指针，末指针，目标位置指针
    delete[] arr;
    arr = temp;
}


class linearlist
{
public:
    //构造函数
    linearlist(int n = 10);
    //析构函数
    ~linearlist() { delete[] stu; };
    //四种操作
    void insert(string &name, string &phone, int &class_num, int &dorm);
    void erase(string &name);
    void edit_phone(string &name, string &new_info);
    void edit_class_dorm(string &name, int decision, int &new_info);
    bool serch(string &name);
    //计算宿舍号的异或值
    int calculate_xor(int &class_num);

private:
    struct student *stu;
    int len;  //数组容量
    int size; //元素个数
};
//构造函数
linearlist::linearlist(int n)
{
    stu = new student[n];
    len = n;
    size = 0;
}

//插入函数
void linearlist::insert(string &name, string &phone, int &class_num, int &dorm)
{
    if (len == size)
    {
        changeLength(stu, len, len * 2);
        len *= 2;
    }
    stu[size].name = name;
    stu[size].phone = phone;
    stu[size].class_num = class_num;
    stu[size].dorm = dorm;
    size++;
}

//删除函数
void linearlist::erase(string &name)
{
    int index = 0; //name对应的元素的索引
    while (stu[index].name != name && index < size)
        index++;
    copy(stu + index + 1, stu + size, stu + index);
    stu[--size].~student(); //调用析构函数
}

//编辑号码
void linearlist::edit_phone(string &name, string &new_info)
{
    int index = 0;
    while (stu[index].name != name && index < size)
        index++;
    stu[index].phone = new_info;
}
//编辑宿舍班级
void linearlist::edit_class_dorm(string &name, int decision, int &new_info)
{
    int index = 0;
    while (stu[index].name != name && index < size)
        index++;
    if (decision == 2)
        stu[index].class_num = new_info;
    else
        stu[index].dorm = new_info;
}
//查找
bool linearlist::serch(string &name)
{
    int index = 0;
    while (stu[index].name != name && index < size)
        index++;
    if (index >= size)
        return 0;
    else
        return 1;
}
//宿舍异或和
int linearlist::calculate_xor(int &class_num)
{
    int result_xor = 0;
    for (int i = 0; i < size; i++)
    {
        if (stu[i].class_num == class_num)
            result_xor ^= stu[i].dorm;
    }
    return result_xor;
}
int main()
{
    int judge, n, index_result = 0, i = 0;
    string name, phone, new_phone;
    int decision, new_info, dorm, class_num;
    cin >> n;
    int *result = new int[n];//记录结果
    linearlist s;
    for (i = 0; i < n; i++)
    {
        cin >> judge;//输入选项
        switch (judge)
        {
        case 0://0 姓名 电话 班级 宿舍 插入一条记录
            cin >> name >> phone >> class_num >> dorm;
            s.insert(name, phone, class_num, dorm);
            break;
        case 1://1 姓名 根据姓名删除一条记录
            cin >> name;
            s.erase(name);
            break;
        case 2://2 姓名 编辑项目 项目新值
            cin >> name >> decision;
            if (decision == 1)
            {
                cin >> new_phone;
                s.edit_phone(name, new_phone);
            }
            else
            {
                cin >> new_info;
                s.edit_class_dorm(name, decision, new_info);
            }
            break;
        case 3://3 姓名 根据姓名查找，找到输出1，未找到输出0
            cin >> name;
            result[index_result] = s.serch(name);
            index_result++;
            break;
        case 4://4 班级 输出该班级的所有成员的宿舍号的异或值
            cin >> class_num;
            result[index_result] = s.calculate_xor(class_num);
            index_result++;
            break;
        default:
            break;
        }
    }
    for (int j = 0; j < index_result; j++)
    {
        cout << result[j] << endl;
    }
    return 0;
}