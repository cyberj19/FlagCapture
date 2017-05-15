#include "Cell.h"
#include "Soldier.h"
using namespace std;

string Cell::getSymbol()
{
	if (_soldier != nullptr) return _soldier->getSymbol();
	else {
		switch (_type) {
		case CellType::EMPTY:
			return "    ";
		case CellType::FOREST:
			return " FR ";
		case CellType::SEA:
			return "SEA ";
		case CellType::FLAG_A:
			return "FlgA";
		case CellType::FLAG_B:
			return "FlgB";
		default:
			return "    ";
		}
	}
}

