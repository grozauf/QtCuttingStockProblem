#include "CuttingStockAlgorithm.h"

#include <algorithm>

bool CuttingStockAlgorithm::init(int stockWidth, int stockHeight, std::vector<Rect> &items, SortType sort, SortOrder order) {
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

// проверяем поместится ли деталь в выбранную позицию
bool CuttingStockAlgorithm::tryToPack(int &startX, Rect &item, std::vector<Rect> &curItemVec, int &prevItemIndex) {
	if (startX + item.width <= m_stockWidth) {
		// ищем максимальную высоту, на которую можно пристроить элемент
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

		prevItemIndex = maxYPair.second;

		return true;
	}
	return false;
}

std::vector<Rect> CuttingStockAlgorithm::cutStock() {
	// фиктивный элемент с нулевой высотой на нулевом слое
	Rect item;
	item.x = 0;
	item.y = 0;
	item.height = 0;
	item.width = m_stockWidth;
	m_packedItems.push_back(std::vector<Rect>{ item });

	while (true) {
		std::pair<int, int> maxYPair;

		// получаем количество элементов на предыдущем уровне
		int prevItemsCount = (m_packedItems.size() > 0) ? m_packedItems[m_packedItems.size() - 1].size() : 0;
		// получаем указатель на вектов элементов предыдущего уровня
		std::vector<Rect>* prevItemVec = (m_packedItems.size() > 0) ? &m_packedItems[m_packedItems.size() - 1] : nullptr;

		int prevItemIndex = 0;
		std::vector<Rect> curItemVec;
		while (prevItemIndex < prevItemsCount) {
			int startX = (*prevItemVec)[prevItemIndex].x;
			for (int i = 0; i < m_items.size(); ++i) {
				if (m_items[i].packed == false) {
					// пытаемся упаковать деталь как есть
					bool packed = tryToPack(startX, m_items[i], curItemVec, prevItemIndex);
					if (!packed) {
						// если упаковать не получилось, то поварачиваем деталь на 90 градусов и пытаемся снова
						std::swap(m_items[i].width, m_items[i].height);
						packed = tryToPack(startX, m_items[i], curItemVec, prevItemIndex);
						if (!packed) {
							// если опять не получилось упаковать, то возвращаем деталь в исходное положение
							std::swap(m_items[i].width, m_items[i].height);
						}
					}
				}
			}

			++prevItemIndex;
		}

		if (curItemVec.size() == 0) {
			break;
		}

		// добавляем в текущий слой фиктивный элемент с нулевой высотой, 
		// начинающийся после последнего элемента в уровне и заканцивающийся границей общей области
		Rect lastCurItem = curItemVec[curItemVec.size() - 1];
		lastCurItem.x = lastCurItem.x + lastCurItem.width;
		lastCurItem.width = m_stockWidth - lastCurItem.x;
		lastCurItem.height = 0;
		maxYPair = findMaxY(lastCurItem.x, m_stockWidth);
		lastCurItem.y = maxYPair.first;
		curItemVec.push_back(lastCurItem);

		// добавляем новый слой упакованных элементов
		m_packedItems.push_back(std::move(curItemVec));
	}

	return m_items;
}

// находим координату y для упаковки и индекс последнего изделия из предыдущего уровня, который пересекается с
// с рассматриваемым блоком
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

