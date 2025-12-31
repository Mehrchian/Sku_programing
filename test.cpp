#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class CONVOLUTION
{
private:
    int *X, *H, *convolutionArr;
    int Min_X, Max_X, Min_H, Max_H;
    int Min_Convolution, Max_Convolution;

public:
    void wPrint(const string& text)
    {
        for (char c : text)
        {
            cout << c << flush;
        }
    }

    void SignalReception()
    {
        wPrint("\nEnter Min index of X: ");
        cin >> Min_X;
        wPrint("Enter Max index of X: ");
        cin >> Max_X;

        int size_X = Max_X - Min_X + 1;
        X = new int[size_X];

        wPrint("Enter values of X:\n");
        for (int i = 0; i < size_X; i++)
            cin >> X[i];
    }

    void ConvolutionWithFilter(int *H, int Min_H, int Max_H, const string& title)
    {
        Min_Convolution = Min_X + Min_H;
        Max_Convolution = Max_X + Max_H;

        int size_conv = Max_Convolution - Min_Convolution + 1;
        convolutionArr = new int[size_conv];

        for (int i = 0; i < size_conv; i++)
            convolutionArr[i] = 0;

        for (int n = Min_Convolution; n <= Max_Convolution; n++)
        {
            for (int k = Min_H; k <= Max_H; k++)
            {
                int xIndex = n - k;
                if (xIndex >= Min_X && xIndex <= Max_X)
                {
                    convolutionArr[n - Min_Convolution] +=
                        X[xIndex - Min_X] * H[k - Min_H];
                }
            }
        }

        wPrint("\n" + title + "\n");
        for (int i = 0; i < size_conv; i++)
            cout << convolutionArr[i] << " ";
        cout << endl;

        delete[] convolutionArr;
    }

    void ApplyAverageFilter()
    {
        Min_H = -1;
        Max_H = 1;
        H = new int[3];

        H[0] = 1;
        H[1] = 1;
        H[2] = 1;

        ConvolutionWithFilter(H, Min_H, Max_H, "Average Filter Output:");
        delete[] H;
    }

    void ApplyDerivativeFilter()
    {
        Min_H = -1;
        Max_H = 1;
        H = new int[3];

        H[0] = -1;
        H[1] = 0;
        H[2] = 1;

        ConvolutionWithFilter(H, Min_H, Max_H, "Derivative Filter Output:");
        delete[] H;
    }
};

int main()
{
    CONVOLUTION system;

    system.SignalReception();

    system.ApplyAverageFilter();
    system.ApplyDerivativeFilter();

    return 0;
}
