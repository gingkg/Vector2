#include <iostream>
 #include<stdlib.h>
 #include <ctime>
using namespace std;
typedef int Rank;//��
#define DEFAULT_CAPACITY 3//Ĭ�ϵĳ�ʼ������ʵ�ʿ������õĸ���
#define NCOUNT 10000000//Ĭ�ϵ�ѭ�����Ҵ���
template <typename T> class Vector{//����ģ����
protected:
	Rank _size;int _capacity;T* _elem;//��ģ��������������
	void copyFrom(T const* A,Rank lo,Rank hi);//����������A[lo,hi)
	void expand();//�ռ䲻��ʱ����
	void shrink();//��װ���ӹ�Сʱѹ��
	bool bubble(Rank lo,Rank hi);//ɨ�轻��
	void bubbleSort(Rank lo,Rank hi);//���������㷨
	Rank max(Rank lo,Rank hi);//ѡȡ���Ԫ��
	void selectionSort(Rank lo,Rank hi);//ѡ�������㷨
	void merge(Rank lo,Rank mi,Rank hi);//�鲢�㷨
	void mergeSort(Rank lo,Rank hi);//�鲢�����㷨
	Rank partion(Rank lo,Rank hi);//��㹹���㷨
	void quickSort(Rank lo,Rank hi);//���������㷨
	void heapSort(Rank lo,Rank hi);//������

public:
	//���캯��
	Vector(int c=DEFAULT_CAPACITY,int s=0,T v=0)//����ΪC����ģΪS������Ԫ�س�ʼΪv
	{
		_elem=new T[_capacity=c];
		for(_size=0;_size<s;_elem[_size++]=v);
	}//s<=c

	Vector(T const* A,Rank lo,Rank hi)//�������临��
	{
		copyFrom(A,lo,hi);
	}

	Vector(T const* A,Rank n)//�������帴��
	{
		copyFrom(A,0,n);
	}

	Vector(Vector<T> const& V,Rank lo,Rank hi)//�������临��
	{
		copyFrom(V._elem,lo,hi);
	}

	Vector(Vector<T> const& V)//�������帴��
	{
		copyFrom(V._elem,0,V._size);
	}

//��������
	~Vector(){delete [] _elem;}//�ͷ��ڲ��ռ�

//ֻ�����ʽӿ�
	Rank size() const
	{
		return _size;
	}//��ģ

	bool empty() const
	{
		return !_size;
	}//�п�

	int disordered() const;//�ж������Ƿ�������

	Rank find(T const& e) const
	{
		return find(e,0,(Rank)_size);
	}//���������������

	Rank find(T const& e,Rank lo,Rank hi) const;//���������������

	Rank search(T const& e) const//���������������
	{
		return (0>=_size)?-1:search(e,(Rank)0,(Rank)_size);
	}

	Rank search(T const& e,Rank lo,Rank hi) const;//���������������

//��д���ʽӿ�
    T& operator[](Rank r) const;//�����±����������������������ʽ���ø�Ԫ��
    Vector<T> & operator=(Vector<T> const&);//���ظ�ֵ���������Ա�ֱ�ӿ�¡����

Vector<Vector<T> > & operator=(Vector<Vector<T> > const& );//




    T remove(Rank r);//ɾ����Ϊr��Ԫ��
    int remove(Rank lo,Rank hi);//ɾ����������[lo,hi)��Ԫ��
    Rank insert(Rank r,T const& e);//����Ԫ��
    Rank insert(T const& e)
    {
    	return insert(_size,e);
    }//Ĭ����ΪĩԪ�ز���

    void sort(Rank lo,Rank hi);//��[lo,hi)����
    void sort()
    {
    	sort(0,_size);
    }//��������

    void unsort(Rank lo,Rank hi);//��[lo,hi)����
    void unsort()
    {
    	unsort(0,_size);
    }//��������

    int deduplicate();//����ȥ��
    int uniquify();//����ȥ��

//����
    void traverse(void(*)(T&));//������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
    template <typename VST> void traverse(VST&);//������ʹ�ú������󣬿�ȫ�����޸ģ�

};//Vector


template <typename T>//Ԫ������
void Vector<T>::copyFrom(T const* A,Rank lo,Rank hi)//����������A[lo,hi)Ϊ������������
{
	_elem=new T[_capacity=2*(hi-lo)];//����ռ�
	_size=0;//��ģ����
	while(lo<hi)
	{
		_elem[_size++]=A[lo++];
	}
}

template <typename T> Vector<T>& Vector<T>::operator=(Vector<T> const& V)//���ظ�ֵ������
{
	if(_elem) delete [] _elem;//�ͷ�ԭ������
	copyFrom(V._elem,0,V.size());//���帴��
	return *this;//���ص�ǰ��������ã��Ա���ʽ��ֵ
}

template <typename T> void Vector<T>::expand()//�����ռ䲻��ʱ����
{
	if(_size<_capacity) return;//��δ��Աʱ����������
	if(_capacity<DEFAULT_CAPACITY)_capacity=DEFAULT_CAPACITY;//��������С����
	T* oldElem=_elem;
	_elem=new T[_capacity<<1];//�����ӱ�
	for(int i=0;i<_size;i++)
		_elem[i]=oldElem[i];//����ԭ�������ݣ�TΪ�������ͣ��������ظ�ֵ��������
	delete [] oldElem;//�ͷ�ԭ�ռ�
}

template <typename T> void Vector<T>::shrink()//��װ���ӹ�Сʱѹ��������ռ�ռ�
{
	if(_capacity<DEFAULT_CAPACITY<<1) return;//����������DEFAULT_CAPACITY����
	if(_size<<2>_capacity)return;//��25%Ϊ��
	T* oldElem=_elem;
	_elem=new T[_capacity>>=1];//��������
	for(int i=0;i<_size;i++)
		_elem[i]=oldElem[i];//����ԭ��������
	delete [] oldElem;//�ͷ�ԭ�ռ�
}

template <typename T> T& Vector<T>::operator[](Rank r) const//�����±������
{

	return _elem[r];//assert:0<=r<=_size
}



template <typename T> void permute(Vector<T>& V)//�������������ʹ��Ԫ�صȸ��ʳ�����ÿ��λ��
{
	for(int i=V.size();i>0;i--)//�Ժ���ǰ
		swap(V[i-1],V[rand()%i]);//V[i-1]��V[0,i)��ĳһ���Ԫ�ؽ���
}

template <typename T> void Vector<T>::unsort(Rank lo,Rank hi)//�ȸ���������������[lo,hi)
{
	T* V=_elem+lo;//��������_elem[lo,hi)������һ����V[0,hi-lo)
	for(Rank i=hi-lo;i>0;i--)//�Ժ���ǰ
		swap(V[i-1],V[rand()%i]);//V[i-1]��V[0,i)��ĳһ���Ԫ�ؽ���
}

template <typename T> static bool lt(T* a,T* b){return lt(*a,*b);}//less than
template <typename T> static bool lt(T& a,T& b){return a<b;}//less than
template <typename T> static bool eq(T* a,T* b){return eq(*a,*b);}//equal
template <typename T> static bool eq(T& a,T& b){return a==b;}//equal

template <typename T>//����������˳����ң��������һ��Ԫ��e��λ�ã�ʧ��ʱ������lo-1
Rank Vector<T>::find(T const& e,Rank lo,Rank hi)const//assert��0<=lo<hi<=_size
{
	while((lo<hi--)&&(e!=_elem[hi]));//�Ӻ���ǰ
	return hi;//��hi<lo,����ζ��ʧ�ܣ�����hi������Ԫ�ص���
}

template <typename T>//��e��Ϊ��ΪrԪ�ز���
Rank Vector<T>::insert(Rank r,T const& e)
{
	expand();//���б�Ҫ������
	for(int i=_size;i>r;i--)
	{
		_elem[i]=_elem[i-1];
	}//�Ժ���ǰ�����Ԫ��˳�κ���һ����Ԫ
	_elem[r]=e;
	_size++;//������Ԫ�ز���������
	return r;//������
}

template <typename T>
int Vector<T>::remove(Rank lo,Rank hi)//ɾ������[lo,hi)
{
	if(lo==hi) return 0;//
	while(hi<_size){_elem[lo++]=_elem[hi++];}//˳��ǰ��
	_size=lo;//���¹�ģ
	shrink();//
	return hi-lo;//
}

template <typename T>
T Vector<T>::remove(Rank r)//��Ԫ��ɾ��
{
	T e=_elem[r];//���ݱ�ɾ��Ԫ��
	remove(r,r+1);//
	return e;//
}

template <typename T>
int Vector<T>::deduplicate()//��������Ψһ��
{
	int oldSize=_size;//��¼ԭ��ģ
	Rank i=1;
	while(i<_size)//��ǰ���ע�⿼���Ԫ��
	{
		(find(_elem[i],0,i)<0)?//����ǰ׺��Ѱ����֮��ͬ��
		i++:remove(i);//����ͬ������������
	}
	return oldSize-_size;//������ģ�仯��
}


template <typename T>
void Vector<T>::traverse(void (*visit)(T&))//���ú���ָ����Ƶı���
{
	for(int i=0;i<_size;i++){visit(_elem[i]);}
}

template <typename T> template <typename VST>//Ԫ�����͡�������
void Vector<T>::traverse(VST& visit)//���ú���������Ƶı���
{
	for(int i=0;i<_size;i++){visit(_elem[i]);}
}

template <typename T> struct Increase//�������󣺵���һ��T�����
{
	virtual void operator()(T& e){e++;}
}; //����T����ֱ�ӵ�����������++

template <typename T> void increase(Vector<T> & V)//ͳһ���������еĸ�Ԫ��
{
	V.traverse(Increase<T>());
}//��Increase<T>()Ϊ�����������б���

template <typename T> int Vector<T>::disordered()const//������������������Ԫ�ضԵ�����
{
	int n=0;//������
	for(int i=1;i<_size;i++)
	{
		if(_elem[i-1]>_elem[i])n++;//�������
	}
	return n;
}

template <typename T> int Vector<T>::uniquify()//����Ψһ��
{
	Rank i=0,j=0;//���ӻ��조���ڡ�Ԫ�ص���
	while(++j<_size)//
		if(_elem[i]!=_elem[j])//������ͬ��
	{
		_elem[++i]!=_elem[j];//���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
	}
	_size=++i;
	shrink();//ֱ�ӽس�β������Ԫ��
	return j-i;//������ģ�仯��
}



template <typename T> static Rank binSearchA(T *A,T const& e,Rank lo,Rank hi)//���ֲ���A
{
	while(lo<hi)
	{
		Rank mi=(lo+hi)>>1;//
		if(e<A[mi])hi=mi;//
		else if(A[mi]<e)lo=mi+1;//
		else return mi;
	}
	return -1;
}

template <typename T> static Rank binSearchB(T *A,T const& e,Rank lo,Rank hi)//���ֲ���B
{
	while(1<hi-lo)
	{
		Rank mi=(lo+hi)>>1;//
		(e<A[mi])?hi=mi:lo=mi;//
	}
	return (e==A[lo])?lo:-1;
}

template <typename T> static Rank binSearchC(T *A,T const& e,Rank lo,Rank hi)//���ֲ���C
{
	while(lo<hi)
	{
		Rank mi=(lo+hi)>>1;//
		(e<A[mi])?hi=mi:lo=mi+1;//
	}
	return --lo;
}



template <typename T>
Rank Vector<T>::search(T const& e,Rank lo,Rank hi)const//�����������
{
	/*return(rand()%2)?
	      binSearch(_elem,e,lo,hi):fibSearch(_elem,e,lo,hi);//���ֲ��һ�Fibonacci����
*/
clock_t start1,end1,start2,end2,start3,end3;
//start = clock();
//end = clock();
//cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
    start1= clock();
	for(int i=0;i<NCOUNT;i++)
	{
		//cout<<binSearchA(_elem,e,lo,hi)<<"  ";
		binSearchA(_elem,e,lo,hi);
	}
	end1= clock();
	cout<<endl<<"�㷨A����ʱ�䣺"<<(double)(end1-start1)/CLOCKS_PER_SEC<<"S"<<endl;
	//cout<<endl;
	 start2= clock();
		for(int i=0;i<NCOUNT;i++)
	{
		//cout<<binSearchB(_elem,e,lo,hi)<<"  ";
		binSearchB(_elem,e,lo,hi);
	}
	end2= clock();
	cout<<endl<<"�㷨B����ʱ�䣺"<<(double)(end2-start2)/CLOCKS_PER_SEC<<"S"<< endl;
	//cout<<endl;
	start3= clock();
		for(int i=0;i<NCOUNT;i++)
	{
		//cout<<binSearchC(_elem,e,lo,hi)<<"  ";
		binSearchC(_elem,e,lo,hi);
	}
	end3= clock();
	cout<<endl<<"�㷨C����ʱ�䣺"<<(double)(end3-start3)/CLOCKS_PER_SEC<<"S"<<endl;
	//cout<<endl;
    return 0;
}

template<typename T>//��������������
void Vector<T>::bubbleSort(Rank lo,Rank hi)
{
	while(!bubble(lo,hi--));//����ɨ�轻����ֱ��ȫ��
}
template<typename T>bool Vector<T>::bubble(Rank lo,Rank hi)//һ��ɨ�轻��
{
	bool sorted=true;//���������־
	while (++lo<hi)//�������ң���һ���
	{
		if(_elem[lo-1]>_elem[lo])//������
		{
			sorted=false;
			swap(_elem[lo-1],_elem[lo]);//ͨ������ʹ�ֲ�����
		}
	}
	return sorted;//���������־
}



template <typename T>//�����鲢����
void Vector<T>::mergeSort(Rank lo,Rank hi)
{
	if(hi-lo<2) return;//��Ԫ��������Ȼ����
	int mi=(lo+hi)>>1;//���е�Ϊ��
	mergeSort(lo,mi);//ǰ�������
	mergeSort(mi,hi);//��������
	merge(lo,mi,hi);//�鲢
}

template <typename T>//���������Ĺ鲢
void Vector<T>::merge(Rank lo,Rank mi,Rank hi)//��miΪ�磬���������������[lo,mi)��[mi,hi)
{
	T* A=_elem+lo;//�ϲ��������A[0,hi-lo)=_elem[lo,hi)
	int lb=mi-lo;
	T* B=new T[lb];//ǰ������B[0,lb)=_elem[lo,mi)
	for(Rank i=0;i<lb;B[i]=A[i++]){}//����ǰ������
	int lc=hi-mi;
	T* C=_elem+mi;//��������C[0,lc)=_elem[mi,hi)
	for(Rank i=0,j=0,k=0;(j<lb)||(k<lc);)//��B[j]��C[k]�е�С������Aĩβ
	{
		if((j<lb)&&((!(k<lc)||(B[j]<=C[k]))))A[i++]=B[j++];
		if((k<lc)&&((!(j<lb)||(C[k]<B[j]))))A[i++]=C[k++];
	}
	delete [] B;//�ͷ���ʱ�ռ�B
}//

template <typename T>//
void Vector<T>::sort(Rank lo,Rank hi)
{
	switch(3)
	{
		case 1:bubbleSort(lo,hi);break;//
		case 2:selectionSort(lo,hi);break;//
		case 3:mergeSort(lo,hi);break;//
		case 4:heapSort(lo,hi);break;//
		default:quickSort(lo,hi);break;//
	}

}

template <typename T> void traverse2(Vector<Vector<T> > const& V)//���������ά����
{
    for(int i=0;i<V.size();i++)
	  {
	for(int j=0;j<V[i].size();j++)
   {
   	cout<<V[i][j]<<" ";
   }
   cout<<endl;
	  }
}

template <typename T> void operation(Vector<Vector<T> > const& V,int x,T const& e)//+-*/
{
	switch(x){
		case 1:
            for(int i=0;i<V.size();i++)
	            for(int j=0;j<V[i].size();j++)
                {
	                V[i][j]=V[i][j]+e;
                }
			break;
		case 2:
            for(int i=0;i<V.size();i++)
	            for(int j=0;j<V[i].size();j++)
               {
	                V[i][j]=V[i][j]-e;
               }
            break;
		case 3:
			for(int i=0;i<V.size();i++)
	            for(int j=0;j<V[i].size();j++)
               {
	                V[i][j]=V[i][j]*e;
               }
            break;
		case 4:
			for(int i=0;i<V.size();i++)
	            for(int j=0;j<V[i].size();j++)
              {
	                V[i][j]=V[i][j]/e;
              }
            break;
	}
}
template <typename T> void add(Vector<Vector<T> > const& V1,Vector<Vector<T> > const& V2)//+
{
            for(int i=0;i<V1.size();i++)
	            for(int j=0;j<V1[i].size();j++)
                {
	                V1[i][j]=V1[i][j]+V2[i][j];
                }
}

template <typename T> void sub(Vector<Vector<T> > const& V1,Vector<Vector<T> > const& V2)//-
{
            for(int i=0;i<V1.size();i++)
	            for(int j=0;j<V1[i].size();j++)
                {
	                V1[i][j]=V1[i][j]-V2[i][j];
                }
}

template <typename T> void mul(Vector<Vector<T> > const& V1,Vector<Vector<T> > const& V2)//*
{
	Vector<Vector<T> > V3,V4;
	V3=V1;
	V4=V2;

            for(int i=0;i<V1.size();i++)
	            for(int j=0;j<V2[0].size();j++)
                {
                	V1[i][j]=0;
	               for(int k=0;k<V2.size();k++)
				   {
				   	V1[i][j]=V1[i][j]+V3[i][k]*V4[k][j];
				   }
                }
}

template <typename T>
Vector<Vector<T> > & Vector<T>::operator=(Vector<Vector<T> > const& V)//���ظ�ֵ������
{
	for(int i=0;i<V.size();i++){
	if(_elem) delete [] _elem;//�ͷ�ԭ������
	copyFrom(V[i]._elem,0,V[i].size());//���帴��
	return *this;//���ص�ǰ��������ã��Ա���ʽ��ֵ
	}
}

int main()
{
	cout << "Hello world!" << endl;
    int const A[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    int const B[]={1,2,5,4,7,6,9,410,3,8,9};
    Vector<int> V1(A,0,end(A)-begin(A));
    Vector<int> V2(B,0,end(B)-begin(B));
  //  Vector<int> V7(B,0,end(B)-begin(B));
    cout<<"*************"<<endl;
     //increase(V2);
      for(int i=0;i<V2.size();i++)
  {
  	cout<<V2[i]<<" ";
  }
    cout<<endl<<"***********"<<endl;

   // V1=V2;
//cout<<(V1+V2)[3];

    V1.sort(0,V1.size());//�鲢����
    V1.search(20,0,V1.size());//A,B,C����

	cout<<V1.size()<<endl;
	cout<<V1[3]<<endl;
	cout<<V2.find(4,0,end(B)-begin(B))<<endl;
	//cout<<V2.remove(4,5)<<endl;
   // cout<<V2.remove(4)<<endl;
   //V1.traverse();
   //increase(V2);
  for(int i=0;i<V1.size();i++)
  {
  	cout<<V1[i]<<" ";
  }
 // cout<<endl<<V2.disordered()<<endl;
  //cout<<V2.deduplicate()<<endl;
  cout<<endl;

  for(int i=0;i<V2.size();i++)
  {
  	cout<<V2[i]<<" ";
  }
  cout<<endl;
  V2.sort(0,V2.size());
  for(int i=0;i<V2.size();i++)
  {
  	cout<<V2[i]<<" ";
  }
  cout<<endl;

//*****************************************************
  cout<<"**********************************"<<endl;
//��ά����
//������ά����
  Vector<Vector<int> > V3(6,3,Vector<int>(6,3,1));//3*3�ľ���
   Vector<Vector<int> > V4(6,3,Vector<int>(6,3,1));//3*3�ľ���
    Vector<Vector<int> > V5(6,3,Vector<int>(6,3,1));//3*3�ľ���
     Vector<Vector<int> > V6(6,3,Vector<int>(6,3,1));//3*3�ľ���
//��ά��������Ԫ�ص����롢���
  cout<<"V3[2][2]="<<V3[2][2]<<endl;
  V3[2][2]=4;
  cout<<"V3[2][2]="<<V3[2][2]<<endl;
//ʵ�ֶ�ά�����ı������������
  for(int i=0;i<V3.size();i++)
	  for(int j=0;j<V3[i].size();j++)
		{
   	      V3[i][j]=(i+1)*(j+2);
		}
  for(int i=0;i<V4.size();i++)
	  for(int j=0;j<V4[i].size();j++)
		{
   	      V4[i][j]=(i+1)*(j+2);
		}
  for(int i=0;i<V5.size();i++)
	  for(int j=0;j<V5[i].size();j++)
		{
   	      V5[i][j]=(i+2)*(j+3);
		}

cout<<"V3:"<<endl;
  for(int i=0;i<V3.size();i++)
	  {
	    for(int j=0;j<V3[i].size();j++)
           {
   	        cout<<V3[i][j]<<" ";
           }
        cout<<endl;
	  }
cout<<"V4:"<<endl;
traverse2(V4);
cout<<"V5:"<<endl;
traverse2(V5);
V4=V5;//��ά������ֵ
cout<<"V4:::"<<endl;
traverse2(V4);

//ʵ����ά�����в�����
	cout<<"���ڲ�����...."<<endl<<V3.insert(2,Vector<int>(6,3,6))<<endl<<"����ɹ�"<<endl;
	traverse2(V3);
//ʵ���ڶ�ά�����в�����
    cout<<"���ڲ�����...."<<endl;
	for(int i=0;i<V3.size();i++)
	  {
       cout<<V3[i].insert(2,888);
       cout<<endl;
	  }
	cout<<"����ɹ�"<<endl;
	traverse2(V3);
//ʵ���������в��뵥��Ԫ��
	cout<<"���ڲ��뵥��Ԫ��...."<<endl<<V3[2].insert(2,999)<<endl<<"����ɹ�"<<endl;
	traverse2(V3);
//ʵ�ֶ�ά��������и�ֵ
    cout<<"���ڸ�ֵ..."<<endl;
	V3[3]=V2;
	cout<<"��ֵ�ɹ�..."<<endl;
	traverse2(V3);
//ʵ�ֶ�ά��������в���
	for(int i=0;i<V3.size();i++)
	  {
	    cout<<"��"<<i+1<<"�еĲ��ҽ���ǣ�"<<V3[i].find(6)<<endl;
	  }
//ʵ�ֶ�ά��������ļӼ��˳�
	traverse2(V3);
	operation(V3,1,2);//+2
	traverse2(V3);
	operation(V3,2,2);//-2
	traverse2(V3);
	operation(V3,3,2);//*2
	traverse2(V3);
	operation(V3,4,2);///2
	traverse2(V3);
//ʵ��������ά����֮��ļӼ���
cout<<"V6:"<<endl;
traverse2(V6);
cout<<"V6=V6+V5:"<<endl;
add(V6,V5);
traverse2(V6);
cout<<"V6=V6*V5:"<<endl;
mul(V6,V5);
traverse2(V6);
	return 0;
}
