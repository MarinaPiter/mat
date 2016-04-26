#include <iostream>
#include <stdlib.h>

using namespace std;

class matr
{
 int m;
 int n;
 float* data;
public:
 matr()
 {
     m=1;
     n=1;
     data = NULL;
 }

 matr(int m_, int n_)
 {
     m = m_;
     n = n_;
     data = new float[m*n];
     for(int i=0; i < m*n; i++)
     {
         data[i] = 0;
     }

 }
 ~matr()
 {
     delete data;
 }

 matr(const matr& A)
 {
     m = A.m;
     n = A.n;
     data = new float[n*m];
     for (int i = 0; i < n*m; i++)
         data[i] = A.data[i];
 }


 matr& operator=(matr& A)
 {
    m = A.getM();
    n = A.getN();
    delete data;
    data = new float[m*n];
    for(int i = 0; i < m*n; i++)
    {
      data[i] = A.get(0,i);
    }
    return *this;
 }

 float get(int i, int j)
 {
     return data[j*n+i];
 }

 void set(int i, int j, float d)
 {
     this->data[j*m+i] = d;
 }

 virtual int getN()
 {
     return n;
 }

 virtual int getM()
 {
         return m;
 }

matr operator+(matr& A)
 {
    if((m!=A.getM())||(n!=A.getN()))
{
        return A;
}
        matr* C=new matr(getM(),getN());// = matr(m,n);
        for(int i = 0; i < m*n; i++)
        {
          C->data[i] = data[i] + A.get(0,i);
        }
    return *C;
 }




 matr operator*(matr& A)
 {
    if(getM() !=n)
    {
        matr* C = new matr();
        return *C;
    }
    matr B(getN(), m);
    for(int i = 0; i < getN(); i++)
        for(int j = 0; j < m; j++)
            for(int l = 1; l <= n; l++)
            {
                B.data[i*n+j] += get(i,j)*A.data[l*n+j];
            }
    return B;

 }

 matr operator*(float& l)
 {
    matr* B = new matr(m,n);
    for (int i = 0; i < m*n; i++)
    {
        B->data[i] = l*data[i];
    }
    return *B;
 }

 matr operator-(matr& A)
 {
    if((m!=A.getM())||(n!=A.getN()))
{
        return A;
}
        matr* C=new matr(getM(),getN());// = matr(m,n);
        for(int i = 0; i < m*n; i++)
        {
          C->data[i] = data[i] - A.get(0,i);
        }
    return *C;
 }


matr transpose()
 {
   float* tmp = new float[n*m];
   matr mat(n,m);
   mat.n = n;
   mat.m = m;
   for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
         tmp[j*n + i] = data[i*n + j];
         mat.data = tmp;
         return matr(mat);

 }

virtual float determinant()
{
    matr tmp = *this;
    float k=0;
    int s;
    for(int l = 0; l < getM(); l++)
    {
        if(tmp.get(l,l) == 0)
        {
            s=l+1;
            while(s<getN())
            {
                if(tmp.get(l,s) != 0)
                {
                    for(int z=l;z<getM();z++)
                    {
                        k=-tmp.get(z,l);
                        tmp.set(z,l,tmp.get(z,s));
                        tmp.set(z,s,k);
                    }
                    s=getN();
                }
                s++;
            }
            if(getN()<=s)
                return 0;
        }
        for(int j =l+1; j < getM(); j++) // это строчки
            {
                k = tmp.get(j,l) / tmp.get(l,l);
                for(int i =l+1 ; i < getN(); i++) //это столбцы
                    tmp.set(j,i,tmp.get(j,i)-k*tmp.get(l,i));
            }
    }
  
    float det = get(0,0);
    for(int i = 1; i < getN(); i++)
      det *=tmp.get(i,i);
    cout << endl<< endl<<det<<endl;
    return det;
}


 virtual matr reverse()
{

    if (failed()||(getN()!=getM()))
    {
        matr A (0,0);
        return A;
    }
    int g;
    float D =this->determinant();
    if(D == 0)
        {
            matr A;
            return A;
        }
    matr A(getN(),getN());
    matr B(getN()-1,getN()-1);
    for(int k=0; k<getN(); k++)
    {
        for(int l=0; l<getN(); l++)
        {
            g=0;

            for (int i = 0; i < getN(); i++)
            {
                if (i == k) continue;
                if (getN() <= i) break;
                for (int j = 0; j < getN(); j++)
                {
                    if (j == l) continue;
                    if (getN() <= i) break;
                    B.set(g,0,this->get(j,i));
                    cout<<this->get(j,i);
                    g++;
                }
            }
                A.set(l,k,B.determinant()/D);
            }
}
return matr(A);

}
 ostream& print(ostream& o)
 {
     for(int i = 0; i < m*n; i++)
     {
         if(i%m == 0) o<<endl;
         o<<data[i]<<" ";
     }
     return o;
 }


 istream& read(istream& o)
 {
     delete data;
     o >> m >> n;
     float* d = new float[m*n];
     data = d;
     for (int i = 0; i < m*n; i++)
     {
         o >> data[i];
     }
     return o;
 }



 bool failed()
 {
     return ((data == NULL) || (n <= 0) || (m <= 0));
 }

};


matr* get_init(int n, int m)
{
    matr* q = new matr(n, m);
            return q;
}
