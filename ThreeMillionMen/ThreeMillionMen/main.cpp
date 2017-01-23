#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <list>
#include <algorithm>

void simple()
{
	std::ifstream file("100.txt");
	std::string name;
	std::unordered_map<std::string, std::string> names;
	std::list<std::string> sortedNames;
	int i = 0;
	while (std::getline(file, name, '\n'))
	{
		auto delim = name.find(',');
		std::pair<std::string, std::string> paper(
			name.substr(0, delim),
			name.substr(delim + 1)
		);
		names.insert(paper);
	}
	auto finder = names.begin();
	do
	{
		sortedNames.push_back(finder->second);
		finder = names.find(finder->second);
	} while (finder != names.end());
	finder = names.find(sortedNames.front());
	int changer = 1;
	while (changer)
	{
		changer = 0;
		for (auto i = names.begin(); i != names.end(); ++i)
		{
			if (i->second == finder->first)
			{
				finder = i;
				sortedNames.push_front(finder->first);
				++changer;
			}
		}
	}
}

bool gSort(std::pair<int, std::string> a, std::pair<int, std::string> b)
{
	return (a.second < b.second);
}

template <typename T, typename Q>
void resetIt(T& it, Q& lst)
{
	if ((it == lst.end()))
		it = lst.begin();
}

void serial()
{
	std::ifstream file("10.txt");
	std::list<std::pair<std::string, std::string> > original;
	std::list<std::pair<std::string, std::string> > f;
	std::list<std::pair<int, std::string> > g;
	std::list<std::pair<std::string, std::string> > h;
	std::string name;
	while (std::getline(file, name, '\n'))
	{
		auto delim = name.find(',');
		std::pair<std::string, std::string> paper(
			name.substr(0, delim),
			name.substr(delim + 1)
		);
		original.push_back(paper);
	}

	int i = 0;
	int t = 1;
	int n = original.size();
	for (auto it = original.begin(); it != original.end(); ++it)
	{
		++i;
		if (i <= n - t)
		{
			f.push_back(*it);
		}
		else
		{
			std::pair<int, std::string> tmp(i, it->first);
			g.push_back(tmp);
		}
	}
	h = f;
	g.sort(gSort);
	h.sort([](auto a, auto b)
	{
		return a.first < b.first;
	}); //sort h
	f.sort([](auto a, auto b)
	{
		return a.second < b.second;
	}); //sort f

	std::list<std::pair<std::string, std::string> > fDash;
	std::list<std::pair<int, std::string>> gDash;
	auto fIt = f.begin();
	auto gIt = g.begin();
	auto hIt = h.begin();
	while (t < n)
	{
		if (fIt != f.end() && hIt != h.end() && fIt->second == hIt->first)
		{
			fDash.push_back(std::make_pair(
				fIt->first,
				hIt->second
			));
			++fIt;
			++hIt;
		}
		else if (fIt != f.end() && gIt != g.end() && fIt->second == gIt->second)
		{
			gDash.push_back(std::make_pair(
				(gIt->first - t),
				fIt->first
			));
			++fIt;
			++gIt;

		}
		else if (fIt != f.end() && hIt != h.end() && fIt->second > hIt->first)
		{
			++hIt;
		}
		else if (fIt != f.end() && gIt != g.end() && fIt->second > gIt->second)
		{
			++gIt;
		}
		if(fIt == f.end() || fIt == --f.end())
		{
			gDash.sort();
			g.sort();
			gDash.merge(g);
			gDash.erase(std::unique(gDash.begin(), gDash.end()), gDash.end());
			gDash.sort(gSort);
			t *= 2;
			f = fDash;
			fDash.clear();
			g = gDash;
			gDash.clear();
			fIt = f.begin();
			gIt = g.begin();
			hIt = h.begin();
		}

		resetIt(gIt, g);
		resetIt(hIt, h);

	}
	g.sort([](auto a, auto b)
	{
		return a.first < b.first;
	});
	g;
}

int main()
{
	//simple();
	serial();
	return 0;
}