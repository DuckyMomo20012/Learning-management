#include "Point.h"

Point::Point(Point& other) {
	_x = other._x;
	_y = other._y;
	_content = other._content;
}

ostream& operator<<(ostream& os, const Point& _point) {
	goTo(_point._x, _point._y);
	os << _point._content;
	return os;
}
