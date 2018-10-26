#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <regex>
using namespace std;

/*
	Tags in html are enclosed in angle brackets <>
	For each tag in properly formed xhtml, there is a matching end tag
	which begins with a forward slash (/)
	<A> </A>
	For example,
  <page>
    <title>AlgeriA</title>
    <id>5</id>
    <revision>
      <id>18063769</id>
      <timestamp>2005-07-03T11:13:13Z</timestamp>
      <contributor>
        <username>Docu</username>
        <id>8029</id>
      </contributor>
      <minor />
      <comment>adding cur_id=5: {{R from CamelCase}}</comment>
      <text xml:space="preserve">#REDIRECT [[Algeria]]{{R from CamelCase}}</text>
    </revision>
  </page>

	Extract all the start tags (not the matching end tags)
	Read in the html file and output a list of the unique tags in the document.
	That is to say, there are many occurrences of each tag

 */

void readHTMLFileOutputTags(const char filename[]) {
	ifstream f(filename);
	char buf[4096]; // make sure it's big enough
	regex tag("<(\\w+)>");
	smatch m;
	unordered_map<string, uint32_t> frequency;
	uint32_t line = 0;
	while (!f.eof()) {
		f.getline(buf, 4096);
		line++;
		if (line % 1000 == 0)
			cerr << "Read " << line << '\n'; 
		string s(buf);
		while(regex_search(s, m, tag)) {
			for (auto x : m) {
				//				cout << "Found " << x << " count=" << frequency[x] << '\n';
				frequency[x]++;
			}
			s = m.suffix().str();			
		}
	}
	cout << "Done searching\n";
	for (auto x: frequency) {
		cout << x.first << "==>" << x.second << '\n';
	}
	multimap<uint32_t, string> byFreq;
	for (auto x : frequency) {
		byFreq.insert(make_pair(x.second, x.first));
	}
	for (auto x : byFreq) {
		cout << x.first << "==>" << x.second << '\n';
	}
}
int main(int argc, char* argv[]) {
	readHTMLFileOutputTags(argv[1]);
}
	
