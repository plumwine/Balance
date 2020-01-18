#pragma once
#include <DxLib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>

class Ranking
{
private:
	Ranking() {}
	Ranking(const Ranking&) {}
	Ranking& operator= (const Ranking&) {}

public:
	static Ranking& Instance();

	void Write();
	void AddWrite(std::string str);

	void SetRanking(std::vector<int> rank);

	void ReadRanking();

	std::vector<int> GetRanking();

	void Sort();

private:
	std::vector<int> ranking;
};

