/* Do NOT add/remove any includes statements from this header file */
/* unlt EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
#include<iostream>
using namespace std;

bool lt(UnlimitedInt* i1, UnlimitedInt* i2){
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
}

UnlimitedInt* get_gcd(UnlimitedInt* a, UnlimitedInt* b){
    UnlimitedInt* zero = new UnlimitedInt();
    int sgn1 = a->get_sign();
    int sgn2 = b->get_sign();
    int sz1 = a->get_size();
    int sz2 = b->get_size();
    int* arr1 = new int[sz1];
    int* arr2 = new int[sz2];
    for (int i=0;i<sz1;i++){
        arr1[i]=i[a->get_array()];
    }
    for (int i=0;i<sz2;i++){
        arr2[i]=i[b->get_array()];
    }
    UnlimitedInt* num1 = new UnlimitedInt(arr1,a->get_capacity(),abs(sgn1),sz1);
    UnlimitedInt* num2 = new UnlimitedInt(arr2,b->get_capacity(),abs(sgn2),sz2);

    bool a1 = lt(zero,num1);
    bool b1 = lt(zero,num2);

    if ((!a1)||(!b1)){
        delete num1;
        delete num2;
        return zero;
    }  

    while (a1 && b1) {
        if (lt(num2,num1)) {
            UnlimitedInt* x = UnlimitedInt::mod(num1,num2);
            delete num1;
            num1 = x;
            a1 = lt(zero,num1);
        }
        else {
            UnlimitedInt* x = UnlimitedInt::mod(num2,num1);
            delete num2;
            num2 = x;
            b1 = lt(zero,num2);
        }
    }

    if (!lt(zero,num1)){
        delete zero;
        delete num1;
        return num2;
    }
    else{
        delete zero;
        delete num2;
        return num1;
    }
}

UnlimitedRational::UnlimitedRational(){
    this->p = new UnlimitedInt();
    this->q = new UnlimitedInt();
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    int sz1 = num->get_size();
    int sz2 = den->get_size();
    int* arr1 = new int[sz1];
    int* arr2 = new int[sz2];
    for (int i=0;i<sz1;i++){
        arr1[i]=i[num->get_array()];
    }
    for (int i=0;i<sz2;i++){
        arr2[i]=i[den->get_array()];
    }

    this->p= new UnlimitedInt(arr1, num->get_capacity(), num->get_sign(), sz1);
    this->q= new UnlimitedInt(arr2, den->get_capacity(), den->get_sign(), sz2);

    UnlimitedInt* one = new UnlimitedInt(1);
    UnlimitedInt* gcd = get_gcd(this->p,this->q);
    if (lt(one,gcd)){
        UnlimitedInt* temp = UnlimitedInt::div(this->p,gcd);
        delete this->p;
        this->p = temp;

        UnlimitedInt* temq = UnlimitedInt::div(this->q,gcd);
        delete this->q;
        this->q = temq;
    }
    delete one;
    delete gcd;
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
}

string UnlimitedRational::get_q_str(){
    return q->to_string();
}

string UnlimitedRational::get_frac_str(){
    string num_str = this->get_p_str();
    string den_str = this->get_q_str();
    string ans = num_str + "/" + den_str;
    return ans;
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1 = i1->get_p();
    UnlimitedInt* num2 = i2->get_p();

    UnlimitedInt* den1 = i1->get_q();
    UnlimitedInt* den2 = i2->get_q();

    UnlimitedInt* zero1 = new UnlimitedInt();
    UnlimitedInt* zero2 = new UnlimitedInt();
    if ((!lt(zero1,num1))&&(!lt(zero1,den1))){
        UnlimitedRational* ans = new UnlimitedRational(zero1,zero2);
        return ans;
    }
    if ((!lt(zero2,den1))&&(!lt(zero2,den2))){
        UnlimitedRational* ans = new UnlimitedRational(zero1,zero2);
        return ans;
    }

    delete zero1; delete zero2;

    // (num1*den2 + num2*den1)/(den1*den2) = (a+b)/c = d/c

    UnlimitedInt* a = UnlimitedInt::mul(num1,den2);
    UnlimitedInt* b = UnlimitedInt::mul(num2,den1);
    UnlimitedInt* c = UnlimitedInt::mul(den1,den2);
    UnlimitedInt* d = UnlimitedInt::add(a,b);
    
    int sz1 = d->get_size();
    int sz2 = c->get_size();
    int* arr1 = new int[sz1];
    int* arr2 = new int[sz2];
    for (int i=0;i<sz1;i++){
        arr1[i]=i[d->get_array()];
    }
    for (int i=0;i<sz2;i++){
        arr2[i]=i[c->get_array()];
    }

    UnlimitedInt* num = new UnlimitedInt(arr1, d->get_capacity(), d->get_sign(), sz1);
    UnlimitedInt* den = new UnlimitedInt(arr2, c->get_capacity(), c->get_sign(), sz2);

    delete a; delete b; delete c; delete d;

    UnlimitedRational* ans = new UnlimitedRational(num,den);
    return ans;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1 = i1->get_p();
    UnlimitedInt* num2 = i2->get_p();

    UnlimitedInt* den1 = i1->get_q();
    UnlimitedInt* den2 = i2->get_q();

    UnlimitedInt* zero1 = new UnlimitedInt();
    UnlimitedInt* zero2 = new UnlimitedInt();
    if (!lt(zero1,num1)&&(!lt(zero1,den1))){
        UnlimitedRational* ans = new UnlimitedRational(zero1,zero2);
        return ans;
    }
    if (!lt(zero2,den1)&&(!lt(zero2,den2))){
        UnlimitedRational* ans = new UnlimitedRational(zero1,zero2);
        return ans;
    }

    delete zero1; delete zero2;

    // (num1*den2 - num2*den1)/(den1*den2) = (a-b)/c = d/c

    UnlimitedInt* a = UnlimitedInt::mul(num1,den2);
    UnlimitedInt* b = UnlimitedInt::mul(num2,den1);
    UnlimitedInt* c = UnlimitedInt::mul(den1,den2);
    UnlimitedInt* d = UnlimitedInt::sub(a,b);
    
    int sz1 = d->get_size();
    int sz2 = c->get_size();
    int* arr1 = new int[sz1];
    int* arr2 = new int[sz2];
    for (int i=0;i<sz1;i++){
        arr1[i]=i[d->get_array()];
    }
    for (int i=0;i<sz2;i++){
        arr2[i]=i[c->get_array()];
    }

    UnlimitedInt* num = new UnlimitedInt(arr1, d->get_capacity(), d->get_sign(), sz1);
    UnlimitedInt* den = new UnlimitedInt(arr2, c->get_capacity(), c->get_sign(), sz2);

    delete a; delete b; delete c; delete d;

    UnlimitedRational* ans = new UnlimitedRational(num,den);
    return ans;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1 = i1->get_p();
    UnlimitedInt* num2 = i2->get_p();

    UnlimitedInt* den1 = i1->get_q();
    UnlimitedInt* den2 = i2->get_q();

    UnlimitedInt* zero1 = new UnlimitedInt();
    UnlimitedInt* zero2 = new UnlimitedInt();
    if (!lt(zero1,num1)&&(!lt(zero1,den1))){
        UnlimitedRational* ans = new UnlimitedRational(zero1,zero2);
        return ans;
    }
    if (!lt(zero2,den1)&&(!lt(zero2,den2))){
        UnlimitedRational* ans = new UnlimitedRational(zero1,zero2);
        return ans;
    }

    delete zero1; delete zero2;

    // (num1*num2)/(den1*den2) = d/c

    UnlimitedInt* d = UnlimitedInt::mul(num1,num2);
    UnlimitedInt* c = UnlimitedInt::mul(den1,den2);
    
    int sz1 = d->get_size();
    int sz2 = c->get_size();
    int* arr1 = new int[sz1];
    int* arr2 = new int[sz2];
    for (int i=0;i<sz1;i++){
        arr1[i]=i[d->get_array()];
    }
    for (int i=0;i<sz2;i++){
        arr2[i]=i[c->get_array()];
    }

    UnlimitedInt* num = new UnlimitedInt(arr1, d->get_capacity(), d->get_sign(), sz1);
    UnlimitedInt* den = new UnlimitedInt(arr2, c->get_capacity(), c->get_sign(), sz2);

    delete c; delete d;

    UnlimitedRational* ans = new UnlimitedRational(num,den);
    return ans;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* num1 = i1->get_p();
    UnlimitedInt* num2 = i2->get_p();

    UnlimitedInt* den1 = i1->get_q();
    UnlimitedInt* den2 = i2->get_q();

    UnlimitedInt* zero1 = new UnlimitedInt();
    UnlimitedInt* zero2 = new UnlimitedInt();
    if (!lt(zero1,num1)&&(!lt(zero1,den1))){
        UnlimitedRational* ans = new UnlimitedRational(zero1,zero2);
        return ans;
    }
    if (!lt(zero2,den1)&&(!lt(zero2,den2))){
        UnlimitedRational* ans = new UnlimitedRational(zero1,zero2);
        return ans;
    }

    // (num1*den2)/(den1*num2) = d/c

    UnlimitedInt* d = UnlimitedInt::mul(num1,den2);
    UnlimitedInt* c = UnlimitedInt::mul(den1,num2);

    if (!lt(zero1,c)){
        UnlimitedRational* ans = new UnlimitedRational(zero1,zero2);
        return ans;
    }

    delete zero1; delete zero2;
    
    int sz1 = d->get_size();
    int sz2 = c->get_size();
    int* arr1 = new int[sz1];
    int* arr2 = new int[sz2];
    for (int i=0;i<sz1;i++){
        arr1[i]=i[d->get_array()];
    }
    for (int i=0;i<sz2;i++){
        arr2[i]=i[c->get_array()];
    }

    UnlimitedInt* num = new UnlimitedInt(arr1, d->get_capacity(), d->get_sign(), sz1);
    UnlimitedInt* den = new UnlimitedInt(arr2, c->get_capacity(), c->get_sign(), sz2);

    delete c; delete d;

    UnlimitedRational* ans = new UnlimitedRational(num,den);
    return ans;
}

// int main(){
//     UnlimitedInt* num1 = new UnlimitedInt(0);
//     UnlimitedInt* num2 = new UnlimitedInt(5);
//     UnlimitedRational* r = new UnlimitedRational(num1,num2);

//     UnlimitedInt* num3 = new UnlimitedInt(4);
//     UnlimitedInt* num4 = new UnlimitedInt(6);
//     UnlimitedRational* s = new UnlimitedRational(num3,num4);

//     UnlimitedRational* t = UnlimitedRational::add(r,s);
//     UnlimitedRational* u = UnlimitedRational::sub(r,s);
//     UnlimitedRational* v = UnlimitedRational::mul(r,s);
//     UnlimitedRational* w = UnlimitedRational::div(s,r);
//     UnlimitedRational* q = UnlimitedRational::add(v,w);
//     cout<<t->get_frac_str()<<endl;
//     cout<<u->get_frac_str()<<endl;
//     cout<<v->get_frac_str()<<endl;
//     cout<<w->get_frac_str()<<endl;
//     cout<<q->get_frac_str()<<endl;

//     delete num1; delete num2; delete num3; delete num4;
//     delete r; delete s; delete t; delete u; delete v; delete w;
// }