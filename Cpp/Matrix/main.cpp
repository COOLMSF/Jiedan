#include "matrix.h"

using namespace std;

 
 struct Matrix1:vector<vector<int> >//使用标准容器vector做基类，需#include语句

{
    
    Matrix1(int x=0,int y=0,int z=0)//初始化，默认为0行0列空矩阵
    
    {
        
        assign(x,vector<int>(y,z));
   
    }
    
int h_size()const//常量说明不可省，否则编译无法通过
    
{
        
return size();
    
}
    
int l_size()const
    
{
        
return empty()?0:front().size();//列数要考虑空矩阵的情况
    
}
    
Matrix1 pow(int k);//矩阵的k次幂，用快速幂实现，k为0时返回此矩阵的单位矩阵
};

Matrix1 operator*(const Matrix1 &m,const Matrix1 &n)//常量引用避免拷贝

{
    if(m.l_size()!=n.h_size())return Matrix1();//非法运算返回空矩阵
    
Matrix1 ans(m.h_size(),n.l_size());
    
for(int i=0; i!=ans.h_size(); ++i)
        
for(int j=0; j!=ans.l_size(); ++j)
            
for(int k=0; k!=m.l_size(); ++k)
                
ans[i][j]+=m[i][k]*n[k][j];
   
return ans;

}

Matrix1 Matrix1::pow(int k)

{
    
if(k==0)
    
{
        
Matrix1 ans(h_size(),h_size());
        
for(int i=0; i!=ans.h_size(); ++i)
            
ans[i][i]=1;
        return ans;
    
}
    
if(k==2)return (*this)*(*this);
    
if(k%2)return pow(k-1)*(*this);
    
return pow(k/2).pow(2);
}


int main() 
{
    cout << "欢迎使用矩阵系统\n";
    cout << "1) 创建2个任意矩阵\n";
    cout << "2) 从文件读取数据相乘\n";

    int input;
    
    while (1) {
        cin >> input;
        int j, k, j1, k1;
        cout << "欢迎使用矩阵系统\n";
        cout << "1) 创建2个任意矩阵\n";
        cout << "2) 从文件读取数据相乘\n";

        if (input == 1) {
            int cnt = 0;
            cout << "输入矩阵1的大小j, k:";
            cin >> j;
            cin >> k;
            cout << "输入矩阵2的大小j1, k1:";
            cin >> j1;
            cin >> k1;

            Matrix<double> a(j, k);
            Matrix<double> b(j1, k1);

            // fill matrix
            cout << "[+] fill data for matrix A\n";
            for (int i = 0; i < j; i++) {
                for (int j = 0; j < k; j++) {
                    a.put(i, j, cnt);
                    cnt++;
                }
            }
            cout << "[+] fill data for matrix A done\n";

            cout << "[+] fill data for matrix B\n";
            for (int i = 0; i < j1; i++) {
                for (int j = 0; j < k1; j++) {
                    b.put(i, j, 2);
                }
            }
            cout << "[+] fill data for matrix B done\n";

            cout << "[+] multiply A and B\n";
            Matrix<double> c = a * b;

            for (int i = 0; i < c.getHeight(); i++) {
                for (int j = 0; j < c.getWidth(); j++) {
                    cout << c.get(i, j) << " ";
                }
                cout << "\n";
            }
        } else if (input == 2) {
            Matrix<double> a(3, 4);
            Matrix<double> b(3, 4);
            Matrix<double> c(3, 4);

            cout << "[+] read from file\n";
            a.putFromFile(3, 4, "double1.txt");
            cout << "[+] read from file done\n";
            cout << "[+] read from file\n";
            b.putFromFile(3, 4, "double2.txt");
            cout << "[+] read from file done\n";

            cout << "[+] multiply done\n";
            c = a * b;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 4; j++) {
                    cout << c.get(i, j) << " ";
                }
                cout << "\n";
            }
        } else {
            cout << "输入错误";
            exit(EXIT_FAILURE);
        }
    }


}
