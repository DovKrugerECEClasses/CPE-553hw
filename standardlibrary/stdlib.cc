int main() {
	vector<int> list = buildVector(5, 10, 1000); // from 5 stepping by 10 to 1000
	removeMultiples(list, 3); // remove all numbers that are multiples of 3
	print(list);

	map<string,double> m;
	load(m, "stocks.dat"); // load the stock quotes into the map m
	// write code to print out the map.  Because it is a tree,
	// it will print in sorted order

	cout << m["AAPL"] << '\n'; // O(log n)
	 
	unordered_map<string,double> hash;
	load(hash, "stocks.dat"); // load the stock quotes into the unordered_map hash
	// write code to print out the hashmap.  It will be in a random order because
	// hashmaps are not sorted (but they are faster for lookup).
	cout << hash["AAPL"] << '\n';
}
