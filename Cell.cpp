#include "Cell.h"
#include "Soldier.h"
const char* Cell::getSymbol()
{
	if (_soldier != nullptr) return _soldier->getSymbol();
	else {
		switch (_type) {
		case CellType::FOREST:
			return " FR ";
		case CellType::SEA:
			return "SEA ";
		case CellType::FLAG_A:
			return "FlgA";
		case CellType::FLAG_B:
			return "FlgB";
		case CellType::EMPTY:
		default:
			return "    ";
		}
	}
}

