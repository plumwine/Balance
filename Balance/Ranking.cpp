#include "Ranking.h"
#include <algorithm>
#include <functional>


//インスタンス生成メソッド
Ranking & Ranking::Instance()
{
	static std::unique_ptr<Ranking> instance(new Ranking());

	return *instance;
}

void Ranking::Write()
{
	const char* fileName = "../ランキング.txt";

	std::ofstream ofs;
	ofs.open(fileName, std::ios::out);

	if (!ofs)
	{
#ifdef _DEBUG
		printfDx("%sファイルが開けませんでした",fileName);
#endif // _DEBUG
		return;
	}

	for (auto i = 0; i < ranking.size(); i++)
	{
		ofs << ranking[i] << std::endl;
	}
#ifdef _DEBUG
	printfDx("%s書き込み終わりました", fileName);
#endif // _DEBUG
}

void Ranking::AddWrite(std::string str)
{
	const char* fileName = "../ランキング.txt";

	std::ofstream ofs;
	ofs.open(fileName, std::ios::app);

	if (!ofs)
	{
#ifdef _DEBUG
		printfDx("ファイルが開けませんでした");
#endif // _DEBUG
		return;
	}

	ofs << str << std::endl;

#ifdef _DEBUG
	printfDx("%s書き込み終わりました", fileName);
#endif // _DEBUG
}

void Ranking::AddRanking(int add)
{
	ranking.push_back(add);
	Sort();

	if (ranking.size() > 3)
	{
		ranking.erase(ranking.begin() + 3, ranking.end());
	}
}

void Ranking::SetRanking(std::vector<int> rank)
{
	ranking = rank;
}

void Ranking::ReadRanking()
{
	const char *fileName = "../ランキング.txt";
	std::ifstream ifs(fileName);

	if (!ifs)
	{
#ifdef _DEBUG
		printfDx("%sファイルが見つかりません", fileName);
#endif // _DEBUG
		return;
	}

	std::string buf;
	while (!ifs.eof())
	{
		std::getline(ifs, buf);
		ranking.push_back(std::atoi(buf.c_str()));
	}

	ranking.pop_back();

#ifdef _DEBUG
	printfDx("%s読み込みが終わりました", fileName);
#endif // _DEBUG
}

std::vector<int> Ranking::GetRanking()
{
	return ranking;
}

void Ranking::Sort()
{
	std::sort(ranking.begin(), ranking.end(), std::greater<int>());
}

