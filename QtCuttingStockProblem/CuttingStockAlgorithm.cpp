#include "CuttingStockAlgorithm.h"

#include <algorithm>

bool CuttingStockAlgorithm::Init(int stockWidth, int stockHeight, std::vector<Rect> &items, SortType sort) {
	m_stockWidth = stockWidth;
	m_stockHeight = stockHeight;
	m_items = items;

	if (sort == SortType::BYHEIGHT) {
		std::sort(
			items.begin(), items.end(), 
			[](Rect& rl, Rect& rr) { 
				return rl.height < rr.height; 
			}
		);
	}
	else if (sort == SortType::BYSPACE) {
		std::sort(
			items.begin(), items.end(), 
			[](Rect& rl, Rect& rr) { 
				return rl.height*rl.width < rr.height*rr.width; 
			}
		);
	}
	return true;
}

std::vector<Rect> CuttingStockAlgorithm::CutStock() {
	while (true) {
		int startX = 0;
		std::vector<Rect> curItemVec;
		for (int i = 0; i < m_items.size(); ++i) {
			if (m_items[i].packed == false && (startX + m_items[i].width < m_stockWidth)) {
				int maxY = findMaxY(startX, startX + m_items[i].width);

				if (maxY + m_items[i].height > m_stockHeight) {
					continue;
				}

				m_items[i].packed = true;
				m_items[i].x = startX;
				m_items[i].y = maxY;
				curItemVec.push_back(m_items[i]);
				startX += m_items[i].width;
			}
		}

		if (curItemVec.size() == 0) {
			break;
		}

		Rect lastCurItem = curItemVec[curItemVec.size() - 1];
		lastCurItem.x = lastCurItem.x + lastCurItem.width;
		lastCurItem.width = m_stockWidth - lastCurItem.x;
		lastCurItem.height = 0;
		lastCurItem.y = findMaxY(lastCurItem.x, m_stockWidth);
		curItemVec.push_back(lastCurItem);

		m_packedItems.push_back(curItemVec);
	}

	return m_items;
}

int CuttingStockAlgorithm::findMaxY(int startX, int endX) {
	int maxY = 0;
	int prevItemsCount = (m_packedItems.size() > 0) ? m_packedItems[m_packedItems.size() - 1].size() : 0;
	std::vector<Rect>* prevItemVec = (m_packedItems.size() > 0) ? &m_packedItems[m_packedItems.size() - 1] : nullptr;

	for (int j = 0; j < prevItemsCount; ++j) {
		Rect& prevItem = (*prevItemVec)[j];
		if (prevItem.x < endX && prevItem.x + prevItem.width > startX) {
			if (prevItem.y + prevItem.height > maxY) {
				maxY = prevItem.y + prevItem.height;
			}
		}
	}

	return maxY;
}

