//
// Created by jiangsheng on 18-5-18.
//
#include<vector>
#include<iostream>
#include<numeric>

class JSTALIB {
public:
    static double ATR(double *high_vector, double *low_vector, double *close_vector, int len, int currentBar) {
        if (currentBar - len + 1 >= 0) {
            double ATR_array[currentBar];
            int j = 0;
            //正好可以算到currentBar
            for (int i = currentBar - len + 1; i <= currentBar; i++) {
                ATR_array[j] = TR(high_vector, low_vector, close_vector, i);
                j++;
            }
            return MA(ATR_array, len, len-1);
        }
        return 0;
    }

    static double TR(double *high_vector, double *low_vector, double *close_vector, int currentBar) {
        double TrueHigh = 0, TrueLow = 0, TrueRange = 0;
        if (currentBar == 0) {
            TrueHigh = high_vector[currentBar];
            TrueLow = low_vector[currentBar];
        } else {
            TrueHigh = close_vector[currentBar - 1];
            TrueLow = close_vector[currentBar - 1];
            TrueHigh = std::max(TrueHigh, high_vector[currentBar]);
            TrueLow = std::min(TrueLow, low_vector[currentBar]);
        }
        TrueRange = TrueHigh - TrueLow;
        return TrueRange;
    };

    static double Summation(double *price, int len) {
        double SumValue = 0;
        for (int i = 0; i < len; ++i) {
            SumValue += price[i];
        }
        return SumValue;
    }

    static double MA(double *price, int len, int currentBar) {
        if (currentBar - len + 1 >= 0) {
            double avgValue = Summation(price + (currentBar - len + 1), len) / len;
            return avgValue;
        } else {
            return price[currentBar];
        }
    }

    static double EMA(double *price, int len, int currentBar) {
        double sFactor = 2 / double(len + 1);
        double XAvgValue = 0;

        if (currentBar == 0) {
            XAvgValue = price[currentBar];
        } else {
            double preXAvgValue = EMA(price, len, currentBar - 1);
            XAvgValue = preXAvgValue + sFactor * (price[currentBar] - preXAvgValue);
        }
        return XAvgValue;
    }
};

