#pragma once

#include <vector>

struct Rect {
	int width;
	int height;

	int x, y;

	bool packed;
};

enum class SortType {
	BYSPACE,
	BYHEIGHT
};

class CuttingStockAlgorithm {
public:

	CuttingStockAlgorithm() = default;

	bool Init(int stockWidth, int stockHeight, std::vector<Rect> &items, SortType sort);

	std::vector<Rect> CutStock();

private:
	int findMaxY(int startX, int endX);

private:
	int m_stockWidth;
	int m_stockHeight;
	std::vector<Rect> m_items;

	std::vector<std::vector<Rect>> m_packedItems;
};
