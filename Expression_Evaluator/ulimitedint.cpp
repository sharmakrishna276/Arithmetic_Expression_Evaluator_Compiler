/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include <iostream>
using namespace std;

UnlimitedInt::UnlimitedInt(){
    this->size = 1;
    this->capacity = 1;
    this->sign=0;
    this->unlimited_int = new int[1];
    this->unlimited_int[0]=0;
}

UnlimitedInt::UnlimitedInt(string s){

    //assinging size
    this->size=s.length();
    
    //assigning sign
    if (s[0]=='-'){
        this->sign=-1;
        s=s.substr(1,--size);
    }
    else{
        this->sign=1;
    }

    // assigning capacity 
    this->capacity = s.length();
    this->unlimited_int = new int[capacity];

    // assigning values of unlimited_int array

    for (int i=size-1;i>=0;i--){
        char c = s.back();
        s.pop_back();
        this->unlimited_int[i]=(int)(c-'0');
    }

    if ((this->size==1) and (this->unlimited_int[0]==0)){
        this->sign=0;
    }

}

UnlimitedInt::UnlimitedInt(int i){

    string s = std::to_string(i);

    //assinging size
    this->size=s.length();
    
    //assigning sign
    if (s[0]=='-'){
        this->sign=-1;
        s=s.substr(1,--size);
    }
    else{
        this->sign=1;
    }

    // assigning capacity 
    this->capacity = s.length();
    this->unlimited_int = new int[capacity];

    // assigning values of unlimited_int array

    for (int i=size-1;i>=0;i--){
        char c = s.back();
        s.pop_back();
        this->unlimited_int[i]=(int)(c-'0');
    }

    if ((this->size==1) and (this->unlimited_int[0]==0)){
        this->sign=0;
    }

}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    this->sign=sgn;
    this->size=sz;
    this->capacity=cap;
    this->unlimited_int=ulimited_int;
}

UnlimitedInt::~UnlimitedInt(){
    delete [] unlimited_int;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_size(){
    return size;
}

//compares absolute values of the integers
bool lessthan(UnlimitedInt* i1, UnlimitedInt* i2){
    int c1= i1->get_size();
    int c2= i2->get_size();

    if (c1<c2){
        return true; 
    }
    else if (c1>c2){
        return false;
    }
    else{
        for (int i=0;i<c1;i++){
            if (i[i1->get_array()]==i[i2->get_array()]){
                continue;
            }
            else if (i[i1->get_array()]<i[i2->get_array()]){
                return true;
                }
            else{
                return false;
            }
        }
        return false;
    }
    return false;
}

//checks whether two unlimited integers are same or not
bool equal(UnlimitedInt* i1, UnlimitedInt* i2){
    int sgn1 = i1->get_sign();
    int sgn2 = i2->get_sign();
    int sz1= i1->get_size();

    if (sgn1!=sgn2) return false;
    else{
        for (int i=0;i<sz1;i++){
            if (i[i1->get_array()]!=i[i2->get_array()]){
                return false;
            }
        }
        return true;
    }
    return true;
}

// // compares two unlimited integers with sign
// bool smaller(UnlimitedInt* i1, UnlimitedInt* i2){
//     int sgn1 = i1->get_sign();
//     int sgn2 = i2->get_sign();
//     int sz1= i1->get_size();
//     int sz2= i2->get_size();

//     if (sgn1<sgn2){
//         return true;
//     }
//     else if (sgn1>sgn2){
//         return false;
//     }
//     else{
//         if (sgn1==0){
//             false;
//         }
//         else if (sgn1==1){
//             if (sz1<sz2){
//                 return true; 
//             }
//             else if (sz1>sz2){
//                 return false;
//             }
//             else{
//                 for (int i=0;i<sz1;i++){
//                     if (i[i1->get_array()]==i[i2->get_array()]){
//                         continue;
//                     }
//                     else if (i[i1->get_array()]<i[i2->get_array()]){
//                         return true;
//                         }
//                     else{
//                         return false;
//                     }
//                 }
//                 return false;
//             }
//         }
//         else{
//             if (sz1<sz2){
//                 return false; 
//             }
//             else if (sz1>sz2){
//                 return true;
//             }
//             else{
//                 for (int i=0;i<sz1;i++){
//                     if (i[i1->get_array()]==i[i2->get_array()]){
//                         continue;
//                     }
//                     else if (i[i1->get_array()]<i[i2->get_array()]){
//                         return false;
//                         }
//                     else{
//                         return true;
//                     }
//                 }
//                 return true;
//             }
//         }
//     }
//     return true;
// }


UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    
    //assigning capacity
    int cap1 = i1->get_capacity();
    int cap2 = i2->get_capacity();
    int cap = std::max(cap1,cap2)+1;

    //initializing final capacity
    int new_cap;

    //fetching sign of both numbers
    int sgn1 = i1->get_sign();
    int sgn2 = i2->get_sign(); 

    //initializing sign of output integer
    int sgn;

    //initializing array of output
    int ulimited_int[cap]={0};
    
    //initializing final array of output
    int* arr;

    //initializing new array of i1
    int op1[cap]={0};
    int j=cap;
    for (int i= cap1-1;i>=0;i--){
        op1[--j]=i[i1->get_array()];
    }

    //initializing new array of i2
    int op2[cap]={0};
    j=cap;
    for (int i=cap2-1;i>=0;i--){
        op2[--j]=i[i2->get_array()];
    }

    // both are +ve or both are -ve
    if (sgn1==sgn2){
        //assigning sign
        sgn = sgn1;

        //initializing carry
        int carry=0;

        //adding the numbers
        for (int i=cap-1;i>=0;i--){
            ulimited_int[i] = (op1[i] + op2[i] + carry)%10;
            carry = (op1[i] + op2[i] + carry)/10; 
        }

        //reducing capacity 
        int j=0;
        new_cap = cap;
        while (j<cap and ulimited_int[j++]==0){
            new_cap--;
        }

        if (new_cap==0)  return new UnlimitedInt();

        //creating final array
        arr = new int[new_cap];
        for (int i=new_cap-1;i>=0;i--){
            arr[i]=ulimited_int[i+cap-new_cap];
        }
    }
    else{
        //assigning sign
        bool cmp = lessthan(i1,i2);
        if (cmp)  sgn=sgn2;   else sgn=sgn1;

        //subtracting the numbers
        if (cmp){
            for (int i=cap-1;i>=0;i--){
                ulimited_int[i] = op2[i] - op1[i];
                if (ulimited_int[i]<0){
                    ulimited_int[i]+=10;
                    op2[i-1]-=1;
                }
            }
        }
        else{
            for (int i=cap-1;i>=0;i--){
                ulimited_int[i] = op1[i] - op2[i];
                if (ulimited_int[i]<0){
                    ulimited_int[i]+=10;
                    op1[i-1]-=1;
                }
            }           
        }

        //reducing the capacity
        int j=0;
        new_cap = cap;
        while (j<cap and ulimited_int[j++]==0){
            new_cap--;
        }

        if (new_cap==0)  return new UnlimitedInt();

        //creating final array
        arr = new int[new_cap];
        for (int i=new_cap-1;i>=0;i--){
            arr[i]=ulimited_int[i+cap-new_cap];
        }   
    }

    int sz = new_cap;
    return new UnlimitedInt(arr,new_cap,sgn,sz); 
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    int size=i2->get_size();
    int* arr = new int[size];
    for (int i=0;i<size;i++){
        arr[i]=i[i2->get_array()];
    }
    UnlimitedInt* i3 = new UnlimitedInt(arr,i2->get_capacity(),(i2->get_sign())*(-1),size);
    UnlimitedInt* res = UnlimitedInt::add(i1,i3);
    delete i3;
    return res;
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    //assigning capacity
    int cap1 = i1->get_capacity();
    int cap2 = i2->get_capacity();
    int cap = cap1+cap2;

    //initializing final capacity
    int new_cap;

    //fetching sign of both numbers
    int sgn1 = i1->get_sign();
    int sgn2 = i2->get_sign();

    //initializing sign of output integer
    int sgn = sgn1*sgn2;

    if (sgn==0)  return new UnlimitedInt();

    //initializing array of output
    int ulimited_int[cap]={0};
    
    //initializing final array of output
    int* arr;

    //initializing new array of i1
    int op1[cap1]={0};
    for (int i= cap1-1;i>=0;i--){
        op1[i]=i[i1->get_array()];
    }

    //initializing new array of i2
    int op2[cap2]={0};
    for (int i=cap2-1;i>=0;i--){
        op2[i]=i[i2->get_array()];
    }

    //multiplication
    int carry=0;

    for (int i=cap1-1;i>=0;i--){
        for (int j=cap2-1;j>=0;j--){
            ulimited_int[cap-((cap1-1-i)+(cap2-1-j))-1] += (op1[i]*op2[j] + carry);
            carry = (ulimited_int[cap-((cap1-1-i)+(cap2-1-j))-1])/10; 
            ulimited_int[cap-((cap1-1-i)+(cap2-1-j))-1] = ulimited_int[cap-((cap1-1-i)+(cap2-1-j))-1]%10;
        }
        ulimited_int[cap-((cap1-i-1)+(cap2))-1]+=carry;
        carry=0;
    }

    //reducing the capacity
    int j=0;
    new_cap = cap;
    while ((j<cap) && (ulimited_int[j++]==0)){
        new_cap--;
    }
    
    if (new_cap==0)  return new UnlimitedInt();

    //creating final array
    arr = new int[new_cap];
    for (int i=new_cap-1;i>=0;i--){
        arr[i]=ulimited_int[i+cap-new_cap];
    }   

    int sz = new_cap;

    UnlimitedInt* a = new UnlimitedInt(arr,new_cap,sgn,sz); 
    return a;
}

// UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
//     UnlimitedInt* zero = new UnlimitedInt();
//     UnlimitedInt* one = new UnlimitedInt(1);
//     UnlimitedInt* count = new UnlimitedInt();
//     int sgn1 = i1->get_sign();

//     if (sgn1==0){
//         delete one;
//         delete count;
//         return zero;
//     }

//     int sgn2 = i2->get_sign();

//     if (sgn2==0){
//         throw runtime_error("Skill Issue");
//     }

//     int sz1 = i1->get_size();
//     int sz2 = i2->get_size();
//     int* arr1 = new int[sz1];
//     int* arr2 = new int[sz2];
//     for (int i=0;i<sz1;i++){
//         arr1[i]=i[i1->get_array()];
//     }
//     for (int i=0;i<sz2;i++){
//         arr2[i]=i[i2->get_array()];
//     }
//     UnlimitedInt* num1 = new UnlimitedInt(arr1,i1->get_capacity(),abs(i1->get_sign()),sz1);
//     UnlimitedInt* num2 = new UnlimitedInt(arr2,i2->get_capacity(),abs(i2->get_sign()),sz2);

//     int cmp=lessthan(num1,num2);
//     if (cmp){
//         delete num1;
//         delete num2;
//         delete one;
//         delete count;
//         return zero;
//     }
//     else{
//         while (!cmp){
//             //repeated subtraction
//             UnlimitedInt* a = UnlimitedInt::sub(num1,num2);
//             delete num1;
//             num1 = a;

//             //increasing count by 1
//             UnlimitedInt* nCount = UnlimitedInt::add(count,one);
//             delete count;
//             count = nCount;

//             cmp=lessthan(num1,num2);
//         }

//         if (sgn1*sgn2<0){
//             bool com = lessthan(zero,num1);
//             if (com){
//                 UnlimitedInt* nCount = UnlimitedInt::add(count,one);
//                 delete count;
//                 count = nCount;
//             }
//             count->sign=-1;
//         }
//     }
//     delete zero;
//     delete one;
//     delete num1;
//     delete num2;
//     int size=count->get_size();
//     int* arr = new int[size];
//     for (int i=0;i<size;i++){
//         arr[i]=i[count->get_array()];
//     }
//     UnlimitedInt* a = new UnlimitedInt(arr,count->get_capacity(),count->get_sign(),size);
//     delete count;
//     return a;
// }


UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* zero = new UnlimitedInt();
    UnlimitedInt* one = new UnlimitedInt(1);
    UnlimitedInt* five = new UnlimitedInt(5);
    int sgn1 = i1->get_sign();

    if (sgn1==0){
        delete one;
        delete five;
        return zero;
    }

    int sgn2 = i2->get_sign();

    // if (sgn2==0){
    //     throw runtime_error(":(");
    // }

    bool cmp = lessthan(one,i2);

    if (!cmp){
        int sgn = sgn1*sgn2;
        int sz = i1->get_size();
        int* arr = new int[sz];
        for (int i=0;i<sz;i++){
            arr[i]=i[i1->get_array()];
        }
        UnlimitedInt* ans = new UnlimitedInt(arr,i1->get_capacity(),sgn,sz);
        delete zero; delete one; delete five;
        return ans;
    }

    int sz1 = i1->get_size();
    int sz2 = i2->get_size();
    int* arr1 = new int[sz1];
    int* arr2 = new int[sz2];
    for (int i=0;i<sz1;i++){
        arr1[i]=i[i1->get_array()];
    }
    for (int i=0;i<sz2;i++){
        arr2[i]=i[i2->get_array()];
    }
    UnlimitedInt* num1 = new UnlimitedInt(arr1,i1->get_capacity(),abs(sgn1),sz1);
    UnlimitedInt* num2 = new UnlimitedInt(arr2,i2->get_capacity(),abs(sgn2),sz2);

    int* arr3 = new int[sz1];
    for (int i=0;i<sz1;i++){
        arr3[i]=i[arr1];
    }

    int* arr4 = new int[1];
    arr4[0]=0;
    
    UnlimitedInt* ub = new UnlimitedInt(arr3,num1->get_capacity(),abs(sgn1),sz1);
    UnlimitedInt* lb = new UnlimitedInt(arr4,1,0,1);

    UnlimitedInt* diff = UnlimitedInt::sub(ub,lb);
    bool cmp2 = lessthan(one,diff);  // second condition: this should be true

    UnlimitedInt* sum = UnlimitedInt::add(lb,ub);
    UnlimitedInt* pdt = UnlimitedInt::mul(sum,five);
    
    int mid_sz = (pdt->get_size())-1;
    int* mid_arr = new int[mid_sz];
    for (int i=0;i<mid_sz;i++){
        mid_arr[i] = i[pdt->get_array()];
    }

    UnlimitedInt* mid = new UnlimitedInt(mid_arr,mid_sz,pdt->get_sign(),mid_sz);
    UnlimitedInt* lhs = UnlimitedInt::mul(mid,num2);

    bool cmp1 = equal(lhs,num1);  // second condition: this should be false: num2*mid!=num1

    while ((!cmp1)and(cmp2)){
        if (lessthan(num1,lhs)){
            int sz = mid->get_size();
            int* arr = new int[sz];
            for (int i=0;i<sz;i++)  arr[i]=i[mid->get_array()];

            UnlimitedInt* temp = new UnlimitedInt(arr,mid->get_capacity(),mid->get_sign(),sz);
            delete ub;
            ub = temp;
        }
        else{
            int sz = mid->get_size();
            int* arr = new int[sz];
            for (int i=0;i<sz;i++)  arr[i]=i[mid->get_array()];

            UnlimitedInt* temp = new UnlimitedInt(arr,mid->get_capacity(),mid->get_sign(),sz);
            delete lb;
            lb = temp;           
        }

        delete diff;
        diff = UnlimitedInt::sub(ub,lb);
        cmp2 = lessthan(one,diff);  // second condition: this should be true

        delete sum; delete pdt;
        sum = UnlimitedInt::add(lb,ub);
        pdt = UnlimitedInt::mul(sum,five);
        
        int mid_sz = pdt->get_size()-1;
        int* mid_arr = new int[mid_sz];
        for (int i=0;i<mid_sz;i++){
            mid_arr[i] = i[pdt->get_array()];
        }

        delete mid;
        UnlimitedInt* temp_ans = new UnlimitedInt(mid_arr,mid_sz,pdt->get_sign(),mid_sz);
        mid = temp_ans;
        delete lhs;
        lhs = UnlimitedInt::mul(mid,num2);

        cmp1 = equal(lhs,num1);  // second condition: this should be false: num2*mid!=num1
    }

    int ans_sgn= mid->get_sign();

    if (sgn1*sgn2==-1){
        if (cmp1){
            ans_sgn=-1;
        }
        else{
            UnlimitedInt* temp = UnlimitedInt::add(mid,one);
            delete mid;
            mid = temp;
            ans_sgn = -1;
        }
    }

    delete num1; delete num2; delete ub; delete lb; delete five; delete one; delete zero; delete lhs; delete sum; delete pdt; delete diff;
    int ans_sz = mid->get_size();
    int* ans_arr = new int[ans_sz];
    for (int i=0;i<ans_sz;i++){
        ans_arr[i] = i[mid->get_array()];
    }
    UnlimitedInt* ans = new UnlimitedInt(ans_arr,ans_sz,ans_sgn,ans_sz);
    delete mid;
    return ans;
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    int sz1 = i1->get_size();
    int sz2 = i2->get_size();
    int* arr1 = new int[sz1];
    int* arr2 = new int[sz2];
    for (int i=0;i<sz1;i++){
        arr1[i]=i[i1->get_array()];
    }
    for (int i=0;i<sz2;i++){
        arr2[i]=i[i2->get_array()];
    }
    UnlimitedInt* a = new UnlimitedInt(arr1,i1->get_capacity(),i1->get_sign(),i1->get_size());
    UnlimitedInt* b = new UnlimitedInt(arr2,i2->get_capacity(),i2->get_sign(),i2->get_size());
    UnlimitedInt* c = UnlimitedInt::div(a,b);
    UnlimitedInt* d = UnlimitedInt::mul(b,c);
    UnlimitedInt* e = UnlimitedInt::sub(a,d);
    delete a; delete b; delete c; delete d;
    int size=e->get_size();
    int* arr = new int[size];
    for (int i=0;i<size;i++){
        arr[i]=i[e->get_array()];
    }
    UnlimitedInt* ans = new UnlimitedInt(arr,e->get_capacity(),e->get_sign(),size);
    delete e;
    return ans;
}

string UnlimitedInt::to_string(){
    string ans;
    if (this->sign==-1){
        ans.append("-");
    }
    for (int i=0;i<this->capacity;i++){
        ans.append(std::to_string(this->unlimited_int[i]));
    }
    return ans;
}

// int main(){
//     UnlimitedInt* a = new UnlimitedInt("222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222");
//     UnlimitedInt* b = new UnlimitedInt("33333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333");
//     UnlimitedInt* e = UnlimitedInt::div(a,b);
//     UnlimitedInt* f = UnlimitedInt::mod(a,b);
//     UnlimitedInt* g = UnlimitedInt::add(e,f);
//     cout<<e->to_string()<<endl;
//     cout<<f->to_string()<<endl;
//     cout<<g->to_string()<<endl;
// }


