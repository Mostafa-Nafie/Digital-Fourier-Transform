#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

const double pi = 3.1415926535897;

class complex
{
private:
	float real;
	float img;
public:
	complex(float real = 0, float img = 0)
	{
		this->real = real;
		this->img = img;
	}
	void setReal(float value)
	{
		this->real = value;
	}
	void setImg(float value)
	{
		this->img = value;
	}
	float getReal()
	{
		return this->real;
	}
	float getImg()
	{
		return this->img;
	}
	void scalar(float a)
	{
		this->real *= a;
		this->img *= a;
	}
	void print()
	{
		this->real = round(this->real * 100) / 100;
		this->img = round(this->img * 100) / 100;
		if (!this->img)
			std::cout << this->real;
		else if (!this->real)
			std::cout << ((this->img >= 0) ? "+j" : "-j") << abs(this->img);
		else
			std::cout << this->real << ((this->img >= 0) ? "+j" : "-j") << abs(this->img);
	}
};

void getInput(int &N, std::vector<float>& x)
{
	int n;
	std::cin >> n;
	N = n;
	for (int i = 0; i < N; i++)
	{
		float temp;
		std::cin >> temp;
		x.push_back(temp);
	}
}

std::vector<complex> calculateTwiddle(int N)
{
	std::vector<complex> twiddle;
	for (int i = 0; i < N; i++)
	{
		complex e;
		e.setReal(cos(2 * pi*i / N));
		e.setImg(-sin(2 * pi*i / N));
		twiddle.push_back(e);
	}
	return(twiddle);
}

std::vector<complex> calculateFreq(int N, std::vector<float>& signal, std::vector<complex>& twiddle)
{
	std::vector<complex>freqSig;
	for (int k = 0; k < N; k++)
	{
		complex X;
		for (int n = 0; n < N; n++)
		{
			complex e = twiddle[(n*k) % N];
			e.scalar(signal[n]);
			X.setReal(X.getReal() + e.getReal());
			X.setImg(X.getImg() + e.getImg());
		}
		freqSig.push_back(X);
	}
	return freqSig;
}


std::vector<float> calculateMagnitude(std::vector<complex>& X)
{
	std::vector<float> magnitude;
	for (int i = 0; i < X.size(); i++)
		magnitude.push_back(sqrt(pow(X[i].getReal(), 2.0) + pow(X[i].getImg(), 2.0)));
	return magnitude;
}

std::vector<float> calculatePhase(std::vector<complex>& X)
{
	std::vector<float> phase;
	for (int i = 0; i < X.size(); i++)
		phase.push_back(atan2(X[i].getImg() , X[i].getReal()) * 360 / (2 * pi));
	return phase;
}


void print(const std::vector<float>& v)
{
	std::cout << "{";
	for (int i = 0; i < v.size() - 1; i++)
		std::cout << v[i] << ", ";
	std::cout << v.back() << "}" << endl;
}


void printcomplex(std::vector<complex>& c)
{
	std::cout << "{";
	for (int i = 0; i < c.size() - 1; i++)
	{
		c[i].print();
		std::cout << ", ";
	}
	c.back().print();
	std::cout << "}" << endl;
}


void main()
{
	int N;
	std::vector<float> signal;
	std::vector<complex> freqSig;
	std::vector<complex> twiddle;
	std::vector<float> mag;
	std::vector<float> phase;

	getInput(N, signal);
	cout << "x(n) = ";
	print(signal);
	twiddle = calculateTwiddle(N);
	freqSig = calculateFreq(N, signal, twiddle);
	cout << "X(k) = ";
	printcomplex(freqSig);
	mag = calculateMagnitude(freqSig);
	phase = calculatePhase(freqSig);
	cout << "|X(k)| = ";
	print(mag);
	cout << "/__X(k) = ";
	print(phase);
	system("pause");
}