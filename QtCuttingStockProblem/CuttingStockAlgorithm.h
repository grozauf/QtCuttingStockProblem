#pragma once

#include <vector>
#include <string>

struct Rect {
	int width = 0;
	int height = 0;

	int x = 0, y = 0;

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

	bool init(int stockWidth, int stockHeight, std::vector<Rect> &items, SortType sort, SortOrder order);

	std::vector<Rect> cutStock();

private:
	std::pair<int, int> findMaxY(int startX, int endX);
	bool tryToPack(int &startX, Rect &item, std::vector<Rect> &curItemVec, int &k);

private:
	int m_stockWidth = 0;
	int m_stockHeight = 0;
	std::vector<Rect> m_items;

	std::vector<std::vector<Rect>> m_packedItems;
};

inline std::string SortTypeToString(SortType sort) {
	switch (sort) {
	case SortType::BYSPACE:
		return "byspace";
	case SortType::BYHEIGHT:
		return "byheight";
	case SortType::BYWIDTH:
		return "bywidth";
	}

	return "byunknown";
}

inline std::string SortOrderToString(SortOrder order) {
	switch (order) {
	case SortOrder::TOGREATER:
		return "increasing";
	case SortOrder::TOLOWER:
		return "decreasing";
	}
	return "unknown";
}