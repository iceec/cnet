#include<iostream>
#include<stdexcept>

using namespace std;

//模板必须一起写，你写在另一个cpp里面，另一个不调用的话，就不会有实例化了
//const函数只能调用本类型的const
//单独nullptr-1不行 但是int *p=nullptr p--; ok的 只要不是void 就行
//push_back和insert 基本类型可以memcopy

namespace Yu{
    namespace utility{



    template<class T>
        class Vector{

             class iterator{
                public: 
                    T *m_pointer;
                public:
                iterator():m_pointer(nullptr){}
                iterator(T * p):m_pointer(p){}
               // iterator(const iterator & p):m_pointer(p.m_pointer){}
                ~iterator()=default;
                bool operator==(const iterator &p)const{return m_pointer==p.m_pointer;}
                T & operator*(){return *m_pointer;}
                const T & operator*()const{return *m_pointer;}
                iterator & operator++(){
                    ++m_pointer;
                    return *this;
                }

                  iterator & operator--(){
                    --m_pointer;
                    return *this;
                }
                iterator operator -(int x){return iterator(m_pointer-x);}
                iterator operator +(int x){return iterator(m_pointer+x);}

                int operator -(iterator p){return m_pointer-p.m_pointer;}

                iterator operator++(int){
                   return iterator(m_pointer++);
                }
                 iterator operator--(int){
                   return iterator(m_pointer--);
                }

                bool operator !=(const iterator &p)const{return !(*this==p);}
            };

             class reverse_iterator{
                    public:
                     iterator p;
                    public: 
                        reverse_iterator():p(){}
                        reverse_iterator(T *s):p(s){}
                        ~reverse_iterator()=default;
                    bool operator==(const reverse_iterator & s)const{return p==s.p;}
                    bool operator !=(const reverse_iterator &s)const{return s.p!=p;}
                    T & operator*(){return *p;}
                    const T & operator*()const{return *p;}
                    reverse_iterator & operator++(){--p;return *this;}

                    reverse_iterator  operator++(int){reverse_iterator temp=*this; --p;
                    return temp;}
                    reverse_iterator & operator--(){++p;return *this;}

                    reverse_iterator  operator--(int){reverse_iterator temp=*this; ++p;
                    return temp;}

                };

            private:
            T * m_data;
            size_t m_len;
            size_t m_capatity;
           
            

            T & number(size_t wei);
            const T & number(size_t wei)const;
        
            public:

            Vector():m_data(nullptr),m_len(0),m_capatity(0){}
            ~Vector(){
                if(m_data==nullptr)
                    ;
                else if(m_len>1)
                    delete[]m_data;
                else
                    delete m_data;
                }

            void push_back(const T & p);

            void pop_back();

            iterator begin()const{
                    return iterator(m_data);
            }

            reverse_iterator rbegin()const{
                return reverse_iterator(m_data+m_len-1);
            }

            iterator  end()const{
                return iterator(m_data+m_len);
            }
            reverse_iterator rend()const{
                return reverse_iterator(m_data-1);
            }

            T & at(size_t p);
            const T &at(size_t p)const;
            T &front();
            const T &front()const;
            T &back(){return number(m_len-1);}
            const T &back()const{return number(m_len-1);}

            bool empty()const noexcept{return m_len==0;}
            void clear()const noexcept{m_len=0;}

            size_t size()const noexcept{return m_len;}

            size_t capacity()const noexcept{return m_capatity;}

            T &operator[](size_t p);

            const T &operator[](size_t p)const;

            Vector<T> &operator=(Vector<T> &p);

            void swap(Vector<T> & p);

            void resize(size_t n);

            void reserve(size_t n);

            iterator insert(iterator pos,size_t times, const T & val);

            iterator insert(iterator pos, const T & val);

           
           
            void show()const;
        };

        template<class T>
    void Vector<T>::push_back(const T & p){
    if(m_len==0){
        m_data=new T;
        
        m_capatity=1;
    }
    else if(m_len==m_capatity){

        if(m_capatity<<1<m_capatity)
            throw std::logic_error("too many elem");
        m_capatity=m_capatity<<1;
        T* data =new T[m_capatity];

        memcpy(data,m_data,sizeof(T)*m_len);
      //  for(size_t i=0;i<m_len;i++)
          //  data[i]=m_data[i];
        delete []m_data;
        m_data=data; 
        
    }
        m_data[m_len++]=p;    
}

template<class T>
    void Vector<T>::pop_back(){
    if(m_len==0)
        throw std::logic_error("no elem can pop");
    m_len--;
}

template<class T>
    void Vector<T>::show()const{

    std::cout<<"Size: "<<m_len<<" Capatity: "<<m_capatity<<"\n";

iterator pd=begin();

   for(;pd!=end();++pd){
    cout<<*pd<<" ";
   }
   cout<<endl;
        
    }

    template<class T>
        T & Vector<T>::number(size_t wei){
            if(wei>=m_len)
                logic_error("out of bound");
            return m_data[wei];
        }

      template<class T>
       const T & Vector<T>::number(size_t wei)const{
           if(wei>=m_len)
                logic_error("out of bound");
            return m_data[wei];
       }
    template<class T>
        T & Vector<T>::at(size_t p){
            return number(p);
        }

     template<class T>
       const T & Vector<T>::at(size_t p)const{
        return number(p);
       }

     template<class T>
        T & Vector<T>::front(){
            return number(0);
        }
     template<class T>
       const T & Vector<T>::front()const{
        return number(0);
       }

     template<class T>
        T & Vector<T>::operator[](size_t p){
            return at(p);
        }
    
     template<class T>
       const T & Vector<T>::operator[](size_t p)const{
        return at(p);
       }
        template<class T>
        Vector<T> & Vector<T>::operator=(Vector<T> &p){
            if(m_capatity>p.m_len){
                for(size_t i=0;i<p.m_len;i++){
                    m_data[i]=p.m_data[i];
                }
                m_len=p.m_len;
                return *this;
            }
            while(m_capatity<=p.m_len){
                if(m_capatity==0)
                    m_capatity=1;
                else if((m_capatity<<1)<m_capatity)
                    throw logic_error("too many elem");
                else
                    m_capatity=m_capatity<<1;
            }
            if(m_len<=1)
                delete m_data;
            else 
                delete []m_data;
            m_data= new T [m_capatity];
           
            m_len=p.m_len;
             for(size_t i=0;i<p.m_len;i++){
                    m_data[i]=p.m_data[i];
                }
                return *this;
        }
        template<class T>
        void Vector<T>::swap(Vector<T> &p){
            size_t t_len=p.m_len;
            size_t t_capatity=p.m_capatity;
            T *temp=p.m_data;
            

            p.m_data=m_data;
            p.m_len=m_len;
            p.m_capatity=m_capatity;
        

            m_data=temp;
            m_capatity=t_capatity;
            m_len=t_len;
          
        }

        template<class T>
        void Vector<T>::resize(size_t n){
            if(m_len>=n){
                m_len=n;
            }
            else if(m_capatity>n){
                for(size_t i=m_len;i<n;i++)
                    m_data[i]=T();
                m_len=n;
            }
            else{
                while(m_capatity<=n){
                if(m_capatity==0)
                    m_capatity=1;
                else if((m_capatity<<1)<m_capatity)
                    throw logic_error("too many elem");
                else
                    m_capatity=m_capatity<<1;
            }

            T *newdata= new T[m_capatity];

            for(size_t i=0;i<m_len;i++)
                newdata[i]=m_data[i];
             for(size_t i=m_len;i<n;i++)
                    newdata[i]=T();
            if(m_len<=1)
                delete m_data;
            else 
                delete []m_data;
            
            m_data=newdata;
          
            m_len=n;
            }
            return ;
        }

        template<class T>
          void  Vector<T>::reserve(size_t n){
            if(n<=m_capatity)
                return ;
            else{
                while(m_capatity<=n){
                if(m_capatity==0)
                    m_capatity=1;
                else if((m_capatity<<1)<m_capatity)
                    throw logic_error("too many elem");
                else
                    m_capatity=m_capatity<<1;
            }
             T *newdata= new T[m_capatity];

            for(size_t i=0;i<m_len;i++)
                newdata[i]=m_data[i];
                if(m_len<=1)
                delete m_data;
            else 
                delete []m_data;
            
            m_data=newdata;    
            
            }
          }
        template<class T>
        typename Vector<T>::iterator Vector<T>::insert(iterator pos,size_t times, const T & val){

            int insertpos=pos-begin();

            if(insertpos<0)
                throw logic_error(" insert wrong");
            
            if(m_len+times<m_capatity){
                for(size_t i=m_len-1,j=i+times;i>=insertpos;i--,j--)
                    m_data[j]=m_data[i];
                for(size_t i=0;i<times;i++)
                    m_data[i+insertpos]=val;
                m_len+=times;
                return pos;
            }
                size_t after=m_len+times;
                while(m_capatity<=after){
                    if(m_capatity==0)
                        m_capatity=1;
                    else if((m_capatity<<1)<m_capatity)
                    throw logic_error("too many elem");
                    else
                        m_capatity=m_capatity<<1;
                }
                T *newdata= new T[m_capatity];

            for(size_t i=0;i<insertpos;i++)
                newdata[i]=m_data[i];
                size_t j=insertpos;
            for(size_t i=0;i<times;i++,j++)
                newdata[j]=val;
            for(size_t i=insertpos;i<m_len;i++,j++)
                newdata[j]=m_data[i];

                if(m_len<=1)
                delete m_data;
            else 
                delete []m_data;
            m_data=newdata; 
            m_len=m_len+times;
            return iterator(m_data+insertpos);
            

            

         }
        template<class T>
        typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T & val){return insert(pos,1,val);}
    


}

}