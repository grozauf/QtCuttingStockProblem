#include "CuttingStockAlgorithm.h"

#include <algorithm>

bool CuttingStockAlgorithm::Init(int stockWidth, int stockHeight, std::vector<Rect> &items, SortType sort, SortOrder order) {
	m_stockWidth = stockWidth;
	m_stockHeight = stockHeight;

	if (sort == SortType::BYHEIGHT) {
		std::sort(
			items.begin(), items.end(), 
			[order](Rect& rl, Rect& rr) { 
				if (order == SortOrder::TOLOWER)
					return rl.height > rr.height; 
				return rl.height < rr.height;
			}
		);
	} 
	else if (sort == SortType::BYSPACE) {
		std::sort(
			items.begin(), items.end(), 
			[order](Rect& rl, Rect& rr) { 
				if (order == SortOrder::TOLOWER)
					return rl.height*rl.width > rr.height*rr.width; 
				return rl.height*rl.width < rr.height*rr.width;
			}
		);
	}
	else if (sort == SortType::BYWIDTH) {
		std::sort(
			items.begin(), items.end(),
			[order](Rect& rl, Rect& rr) {
				if (order == SortOrder::TOLOWER)
					return rl.width > rr.width;
				return rl.width < rr.width;
			}
		);
	}

	m_items = items;

	return true;
}

bool CuttingStockAlgorithm::TryToPack(int &startX, Rect &item, std::vector<Rect> &curItemVec, int &k) {
	if (startX + item.width < m_stockWidth) {
		std::pair<int, int> maxYPair = findMaxY(startX, startX + item.width);
		int maxY = maxYPair.first;

		if (maxY + item.height > m_stockHeight) {
			return false;
		}

		item.packed = true;
		item.x = startX;
		item.y = maxY;
		curItemVec.push_back(item);
		startX += item.width;

		k = maxYPair.second;

		return true;
	}
	return false;
}

std::vector<Rect> CuttingStockAlgorithm::CutStock() {
	Rect item;
	item.x = 0;
	item.y = 0;
	item.height = 0;
	item.width = m_stockWidth;
	m_packedItems.push_back(std::vector<Rect>{ item });

	while (true) {
		std::pair<int, int> maxYPair;

		int prevItemsCount = (m_packedItems.size() > 0) ? m_packedItems[m_packedItems.size() - 1].size() : 0;
		std::vector<Rect>* prevItemVec = (m_packedItems.size() > 0) ? &m_packedItems[m_packedItems.size() - 1] : nullptr;

		int k = 0;
		std::vector<Rect> curItemVec;
		while (k < prevItemsCount) {
			int startX = (*prevItemVec)[k].x;
			for (int i = 0; i < m_items.size(); ++i) {
				if (m_items[i].packed == false) {
					bool packed = TryToPack(startX, m_items[i], curItemVec, k);
					if (!packed) {
						std::swap(m_items[i].width, m_items[i].height);
						packed = TryToPack(startX, m_items[i], curItemVec, k);
						if (!packed) {
							std::swap(m_items[i].width, m_items[i].height);
						}
					}
				}
			}

			++k;
		}

		if (curItemVec.size() == 0) {
			break;
		}

		Rect lastCurItem = curItemVec[curItemVec.size() - 1];
		lastCurItem.x = lastCurItem.x + lastCurItem.width;
		lastCurItem.width = m_stockWidth - lastCurItem.x;
		lastCurItem.height = 0;
		maxYPair = findMaxY(lastCurItem.x, m_stockWidth);
		lastCurItem.y = maxYPair.first;
		curItemVec.push_back(lastCurItem);

		m_packedItems.push_back(std::move(curItemVec));
	}

	return m_items;
}

std::pair<int,int> CuttingStockAlgorithm::findMaxY(int startX, int endX) {
	int maxY = 0;
	int prevItemsCount = (m_packedItems.size() > 0) ? m_packedItems[m_packedItems.size() - 1].size() : 0;
	std::vector<Rect>* prevItemVec = (m_packedItems.size() > 0) ? &m_packedItems[m_packedItems.size() - 1] : nullptr;

	int maxYIndex = 0;
	for (int j = 0; j < prevItemsCount; ++j) {
		Rect& prevItem = (*prevItemVec)[j];
		if (prevItem.x < endX && prevItem.x + prevItem.width > startX) {
			if (prevItem.y + prevItem.height > maxY) {
				maxY = prevItem.y + prevItem.height;
			}
			maxYIndex = j;
		}
	}

	return { maxY, maxYIndex };
}

