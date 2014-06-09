#include "fuzzyset.h"
#include <vector>
#include <iostream>
#include <QDebug>

using namespace std;


void FuzzySet::predict(int n)
{
    gamma = 0.32;
    alpha = gamma;
    beta = gamma;

    sourceKeys   = reader->getKeys();
    sourceValues = reader->getValues();

    omega.push_back(0);
    omega.push_back(sourceValues[1]);
    T.push_back(0);
    T.push_back(sourceValues[1]-sourceValues[0]);
    for(int i = 2; i < sourceValues.size(); i++)
    {
        omega.push_back((1-alpha)*(omega[i-1]+T[i-1])+(alpha)*sourceValues[i]);
        T.push_back((1-beta)*T[i-1]+(beta)*(omega[i]-omega[i-1]));
//        qDebug() << omega[i] << "---" << T[i];
    }
    max = omega[1];
    min = omega[1];
    for(int i = 1; i < omega.size(); i++)
    {
        if(omega[i]<min)
            min=omega[i];
        if(omega[i]>max)
            max=omega[i];
    }
    max++;
    interval = (max-min)/5;
//    qDebug() << "Interval - " << interval << " max - " << max << " min - " << min;
    for(int i = 1; i < omega.size(); i++)
    {
        if(omega[i]<min+interval)
            first.push_back(T[i]);
        else if(min+interval<=omega[i]&&omega[i]<min+interval*2)
            second.push_back(T[i]);
        else if(min+interval*2<=omega[i]&&omega[i]<min+interval*3)
            third.push_back(T[i]);
        else if(min+interval*3<=omega[i]&&omega[i]<min+interval*4)
            fourth.push_back(T[i]);
        else if(min+interval*4<=omega[i]&&omega[i]<min+interval*5)
            fifth.push_back(T[i]);
    }
    double temp=0;
    for(int i = 0; i<first.size(); i++)
    {
        temp+=first[i];
//        qDebug() << "First " << first[i];
    }
    temp/=first.size();
//    qDebug() << "Temp 1 - " << temp;
    for_1=temp;
    temp=0;
    for(int i = 0; i<second.size(); i++)
    {
        temp+=second[i];
//        qDebug() << "Second " << second[i];
    }
    temp/=second.size();
//    qDebug() << "Temp 2 - " << temp;
    for_2=temp;
    temp=0;
    for(int i = 0; i<third.size(); i++)
    {
        temp+=third[i];
//        qDebug() << "Third " << third[i];
    }
    temp/=third.size();
//    qDebug() << "Temp 3 - " << temp;
    for_3=temp;
    temp=0;
    for(int i = 0; i<fourth.size(); i++)
    {
        temp+=fourth[i];
//        qDebug() << "Fourth " << fourth[i];
    }
    temp/=fourth.size();
//    qDebug() << "Temp 4 - " << temp;
    for_4=temp;
    temp=0;
    for(int i = 0; i<fifth.size(); i++)
    {
        temp+=fifth[i];
//        qDebug() << "Fifth " << fifth[i];
    }
    temp/=fifth.size();
//    qDebug() << "Temp 5 - " << temp;
    for_5=temp;
    temp=0;
//    qDebug() << for_1 << " " << for_2 << " " << for_3 << " " << for_4 << " " << for_5;
    for(int i = 0; i < n; i++)
    {
        if(omega[omega.size()-1]<min+interval)
            resultValues.push_back(omega[omega.size()-1]+for_1);
        else if(omega[omega.size()-1]>=min+interval&&omega[omega.size()-1]<min+interval*2)
            resultValues.push_back(omega[omega.size()-1]+for_2);
        else if(omega[omega.size()-1]>=min+interval*2&&omega[omega.size()-1]<min+interval*3)
            resultValues.push_back(omega[omega.size()-1]+for_3);
        else if(omega[omega.size()-1]>=min+interval*3&&omega[omega.size()-1]<min+interval*4)
            resultValues.push_back(omega[omega.size()-1]+for_4);
        else if(omega[omega.size()-1]>=min+interval*4/*&&omega[omega.size()-1]<min+interval*5*/)
            resultValues.push_back(omega[omega.size()-1]+for_5);
        omega.push_back(resultValues[resultValues.size()-1]);
//        qDebug() << "omega" <<omega[omega.size()-1];
    }
}
