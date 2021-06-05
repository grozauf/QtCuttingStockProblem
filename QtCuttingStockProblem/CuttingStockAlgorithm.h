#pragma once

#include <vector>

struct Rect {
	int width;
	int height;

	int x, y;

	bool packed = false;
};

enum class SortType {
	BYSPACE,
	BYHEIGHT,
	BYWIDTH
};

enum class SortOrder {
	TOLOWER,
	TOGREATER
};

class CuttingStockAlgorithm {
public:

	CuttingStockAlgorithm() = default;

	bool Init(int stockWidth, int stockHeight, std::vector<Rect> &items, SortType sort, SortOrder order);

	std::vector<Rect> CutStock();

private:
	std::pair<int, int> findMaxY(int startX, int endX);
	bool TryToPack(int &startX, Rect &item, std::vector<Rect> &curItemVec, int &k);

private:
	int m_stockWidth;
	int m_stockHeight;
	std::vector<Rect> m_items;

	std::vector<std::vector<Rect>> m_packedItems;
};
