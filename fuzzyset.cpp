#include "fuzzyset.h"
#include <vector>
#include <iostream>
#include <QDebug>

using namespace std;


void FuzzySet::predict(int n)
{


    sourceKeys   = reader->getKeys();
    sourceValues = reader->getValues();

    switch ( seriesType ) {

    case ( WITHOUT_SEASONAL_VARIATON ) : {


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
        break;
    }

        case (WITH_SEASONAL_VARIATON) : {
            int seasons = sourceValues.size() / partsInSeason;
            int seasSumAmnt = seasons * partsInSeason - partsInSeason + 1;

            double seasonSum [seasSumAmnt];
            double seasonAver[seasSumAmnt];

            for (int i = 0; i < seasSumAmnt; ++i)
            {
                seasonSum[i] = 0;

                for (int j = i; j < i + seasons; ++j)
                {
                    seasonSum[i] += sourceValues[j];
                }
                std::cout << "\nseas sum " << seasonSum[i];
            }

            for (int i = 0; i < seasSumAmnt; ++i)
            {
                seasonAver[i] = seasonSum[i] / seasons;
                std::cout << "\nseas aver " << seasonAver[i];
            }

            double centeredAver[seasSumAmnt-1];

            for (int i = 0; i < seasSumAmnt-1; ++i)
            {
                 centeredAver[i] = (seasonAver[i] + seasonAver[i+1]) / 2.0;
                 std::cout << "\ncenter sum " << centeredAver[i];
            }

            double seasMark[seasSumAmnt-1];
            double temp     [seasSumAmnt-1];

            int indexes = seasons * partsInSeason - partsInSeason;

            for (int i = 0 ; i < indexes; ++i)
            {
                temp[i] = sourceValues[i+partsInSeason/2] / centeredAver[i];
            }

            for (int i = 0; i < partsInSeason/2; ++i)
            {
                seasMark[i] = temp[(seasons-1)*partsInSeason- partsInSeason/2 +i];
            }

            for (int i = partsInSeason/2; i < indexes; ++i)
            {
                seasMark[i] = temp[i - partsInSeason/2];
            }

            double partIndexes[partsInSeason];

            for (int i = 0; i < partsInSeason; ++i)
            {
                partIndexes[i] = 0;

                for (int j = 0; j < seasons-1; ++j)
                {
                    partIndexes[i] += seasMark[partsInSeason*j + i];
                }

                partIndexes[i] /= seasons-1;
                partIndexes[i] *= (0.7 + (random()%4)/10.0);

                #include <random>
                 std :: cout << partIndexes[i] << std::endl;
            }

            double Yx = 0, sumX= 0, xq= 0, Y= 0;

            std::cout << "size=" << sourceValues.size();

            for (unsigned int i = 1 ; i <= sourceValues.size(); ++i ) {
                Yx 	 += i * sourceValues[i-1];
                std :: cout << i * sourceValues[i-1] << '\n';
                sumX += i;
                xq   += i * i;
                Y += sourceValues[i-1];
            }

            std :: cout << " Yx  == " << Yx << std::endl;
            std::cout << " sum x " << sumX << std::endl;
            std::cout << "xQ =  " << xq << std::endl;
            std::cout << "Y == " << Y << std::endl;


            double a = 0, b = 0;

            a = -(Yx - (sumX*Y)/sourceValues.size())/(xq - (sumX * sumX)/sourceValues.size());

            std::cout << std::endl << a << '\n';

            b = Y/sourceValues.size() - a*sumX/sourceValues.size();

            std::cout << std::endl << b << '\n';



            for (unsigned int i = sourceValues.size(); i < sourceValues.size() + n; i++) {
                resultKeys  .push_back(sourceKeys[i%sourceValues.size()]);
                resultValues.push_back((a*i+b)*partIndexes[i%partsInSeason]);
            }

            double sum = 0;
            int counter = 0;

           for (int i = 0; i < resultKeys.size(); ++i)
            {
               std::cout << resultKeys[i] << "  " << resultValues[i] << std::endl;

                counter++;
               sum += resultValues[i];

                if (counter == partsInSeason) {
                    std::cout << "\nTotal : " << sum <<"\n\n";
                    counter = 0;
                    sum = 0;
                }

            }


            break;
        }
    }

}
