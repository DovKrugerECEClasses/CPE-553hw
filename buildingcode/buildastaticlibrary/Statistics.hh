#pragma once

class Statistics; // forward reference because the class is below

extern "C" {
	void stats(double x[], int n, Statistics& s);
}

class Statistics {
private:
	double min_, max_, mean_, variance_;
	Statistics();
public:
	double min() const { return min_; }
	double max() const { return max_; }
	double mean() const { return mean_; }
	double variance() const { return variance_; }
	friend void stats(double x[], int n, Statistics& s);
};
