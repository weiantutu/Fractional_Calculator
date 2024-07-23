#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
class Fraction
{
    friend Fraction operator+(const Fraction& frac1, const Fraction& frac2); // 重载+运算符
    friend Fraction operator-(const Fraction& frac1, const Fraction& frac2); // 重载-运算符
    friend Fraction operator*(const Fraction& frac1, const Fraction& frac2); // 重载*运算符
    friend Fraction operator/(const Fraction& frac1, const Fraction& frac2); // 重载/运算符
    friend bool operator==(Fraction frac1, Fraction frac2);                  // 重载==运算符
    friend bool operator>(const Fraction& frac1, const Fraction& frac2);     // 重载>运算符
    friend bool operator<(const Fraction& frac1, const Fraction& frac2);     // 重载<运算符
    friend ostream& operator<<(ostream& out, const Fraction& frac);          // 重载<<运算符
    friend istream& operator>>(istream& in, Fraction& frac);                 // 重载>>运算符
    friend void sortFraction();                                              // 对分数数组排序
public:
    Fraction();                     // 无参构造函数
    Fraction(int n, int d);         // 带参构造函数
    Fraction(const Fraction& f);    // 复制构造函数
    void setFraction(int n, int d); // 设置分数的分子和分母
    int getNumer();                 // 获取分数的分子
    int getDeno();                  // 获取分数的分母
    void RdcFrc();                  // 当前分数约分
    void swap(Fraction& frac1);     // 交换两个分数
private:
    int numer; // 分子
    int deno;  // 分母
};
Fraction::Fraction() : numer(0), deno(1) {}
Fraction::Fraction(int n, int d) : numer(n), deno(d) {}
Fraction::Fraction(const Fraction& f) : numer(f.numer), deno(f.deno) {}
void Fraction::setFraction(int n, int d)
{
    numer = n;
    deno = d;
}
int Fraction::getNumer() { return numer; }
int Fraction::getDeno() { return deno; }
void Fraction::RdcFrc()
{
    int min = numer < deno ? numer : deno, gcd = 1;
    for (int i = 1; i <= min; i++)
    {
        if (numer % i == 0 && deno % i == 0)
        {
            gcd = i;
        }
    }
    numer /= gcd;
    deno /= gcd;
}

Fraction operator+(const Fraction& frac1, const Fraction& frac2)
{
    Fraction tmp;
    tmp.numer = frac1.numer * frac2.deno + frac1.deno * frac2.numer;
    tmp.deno = frac1.deno * frac2.deno;
    return tmp;
}
Fraction operator-(const Fraction& frac1, const Fraction& frac2)
{
    Fraction tmp;
    tmp.numer = frac1.numer * frac2.deno - frac1.deno * frac2.numer;
    tmp.deno = frac1.deno * frac2.deno;
    return tmp;
}
Fraction operator*(const Fraction& frac1, const Fraction& frac2)
{
    Fraction tmp;
    tmp.numer = frac1.numer * frac2.numer;
    tmp.deno = frac1.deno * frac2.deno;
    return tmp;
}
Fraction operator/(const Fraction& frac1, const Fraction& frac2)
{
    Fraction tmp;
    tmp.numer = frac1.numer * frac2.deno;
    tmp.deno = frac1.deno * frac2.numer;
    return tmp;
}
bool operator==(Fraction frac1, Fraction frac2)
{
    return (frac1.numer * frac2.deno == frac1.deno * frac2.numer);
}
bool operator>(const Fraction& frac1, const Fraction& frac2)
{
    return (frac1.numer * frac2.deno > frac1.deno * frac2.numer);
}
bool operator<(const Fraction& frac1, const Fraction& frac2)
{
    return (frac1.numer * frac2.deno < frac1.deno * frac2.numer);
}
ostream& operator<<(ostream& out, const Fraction& frac)
{
    out << frac.numer << '/' << frac.deno;
    return out;
}
istream& operator>>(istream& in, Fraction& frac)
{
    in >> frac.numer >> frac.deno;
    return in;
}
void Fraction::swap(Fraction& frac1)
{
    Fraction tmp;
    tmp = *this;
    *this = frac1;
    frac1 = tmp;
    return;
}

void startprogram();
void sortFraction()
{
    cout << "请输入一组分数,用逗号隔开,如需由小到大排序用符号<结尾,由大到小排序用符号>结尾(如1/2,1/4,3/5<回车),输入#号键返回上一层目录:" << endl;
    string str;
    cin >> str;
    if (str == "#")
    {
        system("cls");
        startprogram();
        return;
    }
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ',' && str[i] != '/' && (str[i] < '0' || str[i] > '9') && str[i] != '<' && str[i] != '>')
        {
            cout << "输入错误！" << endl;
            sortFraction();
            return;
        }
        // 出现多个运算符的错误暂时未实现
    }
    char cmd;
    cmd = str[str.length() - 1];
    vector<Fraction> fracVec;
    stringstream tmps1(str);
    string tmp;
    while (getline(tmps1, tmp, ','))
    {
        Fraction frac;
        stringstream tmps2(tmp);
        getline(tmps2, tmp, '/');
        frac.numer = atoi(tmp.c_str());
        getline(tmps2, tmp, '/');
        frac.deno = atoi(tmp.c_str());
        fracVec.push_back(frac);
    }
    // 对fracVec中的元素进行排序
    if (cmd == '>')
    {
        for (int i = 0; i < fracVec.size(); i++)
        {
            Fraction max = fracVec[i];
            int maxIndex = i;
            for (int j = i + 1; j < fracVec.size(); j++)
            {
                if (fracVec[j] > max)
                {
                    max = fracVec[j];
                    maxIndex = j;
                }
            }
            if (maxIndex != i)
            {
                fracVec[i].swap(fracVec[maxIndex]);
            }
            // 交换arr[i]和arr[maxIndex]的值
        }
    }
    else if (cmd == '<')
    {
        for (int i = 0; i < fracVec.size(); i++)
        {
            Fraction min = fracVec[i];
            int minIndex = i;
            for (int j = i + 1; j < fracVec.size(); j++)
            {
                if (fracVec[j] < min)
                {
                    min = fracVec[j];
                    minIndex = j;
                }
            }
            if (minIndex != i)
            {
                fracVec[i].swap(fracVec[minIndex]);
            }
            // 交换arr[i]和arr[minIndex]的值
        }
    }
    else
    {
        cout << "输入错误!" << endl;
        sortFraction();
        return;
    }
    for (int i = 0; i < fracVec.size(); i++)
    {
        cout << fracVec[i] << " ";
    }
    cout << endl;
    sortFraction();
    return;
}

void calculate();
void startprogram()
{
    cout << "请选择功能(键入1或者2):" << endl;
    cout << "1.分数计算" << endl;
    cout << "2.分数排序" << endl;
    int n;
    cin >> n;
    system("cls");
    if (n == 1)
    {
        calculate();
        return;
    }
    else if (n == 2)
    {
        sortFraction();
        return;
    }
    else
    {
        cout << "输入错误!" << endl;
        startprogram();
        return;
    }
}

void calculate()
{
    cout << "请输入分数计算式(如1/2+1/3回车),输入#号键返回上一层目录:" << endl;
    string str;
    int indicate1 = 0, indicate2 = 0, indicate3 = 1;
    cin >> str;
    if (str == "#")
    {
        system("cls");
        startprogram();
        return;
    }
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && (str[i] < '0' || str[i] > '9'))
        {
            cout << "分数算式输入错误！" << endl;
            calculate();
            return;
        }
        // 出现多个运算符的错误暂时未实现
    }
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '/')
        {
            if (indicate3 <= indicate2)
            {
                indicate3 = i;
            }
            else if (indicate1 <= indicate2)
            {
                indicate1 = i;
            }
        }
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            indicate2 = i;
        }
    }
    Fraction frac1, frac2, frac3;
    int num1 = stoi(str.substr(0, indicate1));
    int num2 = stoi(str.substr(indicate1 + 1, indicate2 - indicate1 - 1));
    int num3 = stoi(str.substr(indicate2 + 1, indicate3 - indicate2 - 1));
    int num4 = stoi(str.substr(indicate3 + 1, str.length() - indicate3 - 1));
    frac1.setFraction(num1, num2);
    frac2.setFraction(num3, num4);
    switch (str[indicate2])
    {
    case '+':
        frac3 = frac1 + frac2;
        break;
    case '-':
        frac3 = frac1 - frac2;
        break;
    case '*':
        frac3 = frac1 * frac2;
        break;
    case '/':
        frac3 = frac1 / frac2;
        break;
    default:
        cout << "分数算式输入错误！" << endl;
        calculate();
        return;
    }
    frac3.RdcFrc();
    cout << "=" << frac3.getNumer() << "/" << frac3.getDeno() << endl;
    calculate();
    return;
}

int main()
{
    startprogram();
    return 0;
}